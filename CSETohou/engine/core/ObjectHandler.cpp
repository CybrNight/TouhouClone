#include "ObjectHandler.h"
#include "AssetManager.h"

#include <climits>
#include <ctime>
#include <iostream>
#include <random>

Handler* Handler::instance;

Handler::Handler(std::shared_ptr<SDL_Renderer> renderer)
{
    if (instance == NULL) {
        instance = this;
    }

    this->renderer = renderer;

    srand(time(NULL));
}

// Clean up handler
Handler::~Handler()
{
    objectProcessQueue.clear();
    std::cout << "Handler: Handler destroyed\n";
}

// THIS IS WHAT MANUALLY SYNCHRONIZING AN UPDATE LOOP LOOKS LIKE
void
Handler::tick()
{
    createAllQueuedObjects();

    // Check for objects that have been marked for deletion from last cycle
    // Must happen here before temp's state is modified or used by other objects
    for (size_t i = 0; i < objectProcessQueue.size(); i++) {
        Object* temp = objectProcessQueue.at(i);
        if (temp->is_destroyed()) {
            remove_object(temp);
            objectProcessQueue.shrink_to_fit();
            continue;
        }

        // Update object if not deleted
        temp->tick();
    }

    // Create new list from gameObjectList
    std::vector<GameObject*> collisionQueue(gameObjectList);
    for (size_t i = 0; i < collisionQueue.size(); i++) {
        GameObject* first = collisionQueue.at(i);
        if (first == NULL || first->get_speed() <= 0)
            continue;

        for (size_t j = 0; j < collisionQueue.size(); j++) {
            GameObject* other = collisionQueue.at(j);

            if (other == NULL)
                continue;

            // Check if self
            if (first == other)
                continue;

            // qDebug() << myCollider->get_bounds();
            SDL_FRect temp1 = first->get_bounds();
            SDL_FRect temp2 = other->get_bounds();

            SDL_FPoint c1{ temp1.x + temp1.w / 2, temp1.y + temp1.h / 2 };
            SDL_FPoint c2{ temp2.x + temp2.w / 2, temp2.y + temp2.h / 2 };
            long distance = std::sqrt(std::pow((c2.x - c1.x), 2) + std::pow((c2.y - c1.y), 2));
            long radii = (first->get_bounds().w + other->get_bounds().w) / 2;
            if (distance <= radii) {
                if (other->get_speed() == 0) { // Call collision function on both
                                               // objects if other is stopped
                    first->collision(other);
                    other->collision(first);

                }
                else { // If other is moving then it will it have it's turn later
                    first->collision(other);
                }
            }
        }
    }
}

void Handler::tick_second()
{
    // for (size_t i = 0; i < gameObjects.size(); i++){
    // GameObject* temp = gameObjects.at(i);
    // temp->tick_second();
    //}
}

void Handler::render()
{
    for (size_t i = 0; i < gameObjectList.size(); i++) {
        GameObject* temp = gameObjectList.at(i);
        if (temp != NULL) {
            temp->render(renderer.get());
            temp->draw_bounds(renderer.get());
        }
    }
}

void
Handler::input(SDL_KeyboardEvent& keyEvent)
{
    for (size_t i = 0; i < inputProcessQueue.size(); i++) {
        IControllable* temp = inputProcessQueue.at(i);
        if (temp != NULL) {
            temp->input(keyEvent);
        }
    }
}

void
Handler::instantiate(Object* obj)
{
    bool uniqueID = true;
    unsigned long long result;

    // Generate UUID for GameObject
    do {
        std::random_device
            rd; // Get a random seed from the OS entropy device, or whatever
        std::mt19937_64 eng(rd()); // Use the 64-bit Mersenne Twister 19937
                                   // generator and seed it with entropy.

        std::uniform_int_distribution<unsigned long long> distr;
        result = distr(eng);
        for (size_t i = 0; i < objectProcessQueue.size(); i++) {
            if (objectProcessQueue.at(i)->get_uuid() == result) {
                uniqueID = false;
                break;
            }
            else {
                uniqueID = true;
            }
        }
    } while (!uniqueID);

    // Assign object with UUID for checking
    obj->set_uuid(result);
    objectCreationQueue.push_back(obj);
}

void
Handler::remove_object(std::vector<Object*>::iterator location)
{
    // Check if GameObject has components
    // Remove GameObject from objects list

    if (auto control = dynamic_cast<IControllable*>(*location)) {
        auto temp = std::find(inputProcessQueue.begin(), inputProcessQueue.end(), control);
        inputProcessQueue.erase(temp);
    }

    if (auto gameObject = dynamic_cast<GameObject*>(*location)) {
        auto temp = std::find(gameObjectList.begin(), gameObjectList.end(), gameObject);
        gameObjectList.erase(temp);
    }

    objectProcessQueue.erase(location);
}

void
Handler::createAllQueuedObjects()
{ // Setup all objects queued for
  // creation last cycle
    while (objectCreationQueue.size() > 0) {
        Object* obj = objectCreationQueue.back();

        if (obj == NULL)
            return;

        obj->init();
        obj->start();

        // After initialzing object add it to process queue and remove it from
        // creation queue
        objectProcessQueue.push_back(obj);


        if (auto gameObject = dynamic_cast<GameObject*>(obj)) {
            if (gameObject->get_sprite_path() != "none"){
                gameObject->load_sprite(AssetManager::getAssetManager()->getSprite(gameObject->get_sprite_path()));
            }
            gameObjectList.push_back(gameObject);
        }

        if (auto control = dynamic_cast<IControllable*>(obj)) {
            inputProcessQueue.push_back(control);
        }

        objectCreationQueue.pop_back();
    }
}

void
Handler::remove_object(Object* obj)
{
    remove_object(find(objectProcessQueue.begin(), objectProcessQueue.end(), obj));
}

void
Handler::remove_object(int index)
{
    remove_object(get_object(index));
}

Object*
Handler::get_object(int index)
{
    return objectProcessQueue.at(index);
}

Object*
Handler::get_object(Tag tag)
{
    for (size_t i = 0; i < objectProcessQueue.size(); i++) {
        Object* temp = objectProcessQueue.at(i);
        if (temp->get_tag() == tag) {
            return temp;
        }
    }

    return NULL;
}

Object*
get_object(Tag tag)
{
    return Handler::instance->get_object(tag);
}

void destroy(Object* obj)
{
    obj->destroy();
}

Object* instantiate(Object* obj)
{
    Handler::instance->instantiate(obj);
    return obj;
}