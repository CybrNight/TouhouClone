#include "ObjectHandler.h"
#include "AssetManager.h"

#include <climits>
#include <ctime>
#include <iostream>
#include <random>
#include <stdexcept>
#include <algorithm>

using UI::UIObject;

namespace EngineCore {
    ObjectHandler* ObjectHandler::instance;

    ObjectHandler::ObjectHandler() {
        if (instance == NULL) {
            instance = this;
        }

        this->renderer = renderer;

        srand(time(NULL));
    }

    // Clean up handler
    ObjectHandler::~ObjectHandler() {
        objectProcessQueue.clear();
        std::cout << "Handler: Handler destroyed\n";
    }

    void ObjectHandler::Init(std::shared_ptr<SDL_Renderer> renderer)
    {
        this->renderer = renderer;
    }

    ObjectHandler* ObjectHandler::GetInstance(std::shared_ptr<SDL_Renderer> renderer)
    {
        if (instance == NULL) {
            instance = new ObjectHandler();
            instance->Init(renderer);
        }
        return instance;
    }

    // THIS IS WHAT MANUALLY SYNCHRONIZING AN UPDATE LOOP LOOKS LIKE
    void ObjectHandler::Tick() {
        if (destroyAll) {
            objectProcessQueue.clear();
            gameObjectList.clear();
            uiObjectList.clear();
            destroyAll = false;
        }
        else {
            CreateAllQueuedObjects();
        }
        // Check for objects that have been marked for deletion from last cycle
        // Must happen here before temp's state is modified or used by other objects
        for (size_t i = 0; i < objectProcessQueue.size(); i++) {
            Object* temp = objectProcessQueue.at(i);
            if (temp->IsDestroyed()) {
                RemoveObject(temp);
                delete temp;
                objectProcessQueue.shrink_to_fit();
                continue;
            }

            // Update object if not deleted
            temp->Tick();
        }

        // Create new list from gameObjectList
        std::vector<GameObject*> collisionQueue(gameObjectList);
        for (size_t i = 0; i < collisionQueue.size(); i++) {
            GameObject* first = collisionQueue.at(i);

            // Check that GameObject exists or that it's actually moving
            if (first == NULL || first->GetSpeed() <= 0)
                continue;

            // If found valid first, then iterate again
            for (size_t j = 0; j < collisionQueue.size(); j++) {
                GameObject* other = collisionQueue.at(j);

                // Check that other 
                if (other == NULL)
                    continue;

                // If we are comparing to self then skip
                if (first == other)
                    continue;

                //Get bounds from both GameObjects
                SDL_FRect temp1 = first->GetBounds();
                SDL_FRect temp2 = other->GetBounds();

                // Calculate circle boundaries from GetBounds()
                SDL_FPoint c1{ temp1.x + temp1.w / 2, temp1.y + temp1.h / 2 };
                SDL_FPoint c2{ temp2.x + temp2.w / 2, temp2.y + temp2.h / 2 };
                long distance = std::sqrt(std::pow((c2.x - c1.x), 2) + std::pow((c2.y - c1.y), 2));
                long radii = (first->GetBounds().w + other->GetBounds().w) / 2;
                if (distance <= radii) {
                    if (other->GetSpeed() == 0) { // Call collision function on both
                                                   // objects if other is stopped
                        first->Collision(other);
                        other->Collision(first);

                    }
                    else { // If other is moving then it will it have it's turn later
                        first->Collision(other);
                    }
                }
            }
        }
    }

    void ObjectHandler::TickSecond()
    {
        // for (size_t i = 0; i < gameObjects.size(); i++){
        // GameObject* temp = gameObjects.at(i);
        // temp->tick_second();
        //}
    }

    void ObjectHandler::Render()
    {
        //Render GameObjects
        for (size_t i = 0; i < gameObjectList.size(); i++) {
            if (i < gameObjectList.size()) {
                GameObject* temp = gameObjectList.at(i);
                if (temp != NULL) {
                    temp->Render(renderer.get());
                    temp->DrawBounds(renderer.get());
                }
                else {
                    throw 20;
                }
            }
        }
    }

    void ObjectHandler::RenderUI() {
        for (size_t i = 0; i < uiObjectList.size(); i++) {
            if (i < uiObjectList.size()) {
                UIObject* temp = uiObjectList.at(i);
                if (temp != NULL) {
                    temp->Render(renderer.get());
                }
            }
        }
    }

    Object* ObjectHandler::Instantiate(Object* obj) {
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
                if (objectProcessQueue.at(i)->GetUUID() == result) {
                    uniqueID = false;
                    break;
                }
                else {
                    uniqueID = true;
                }
            }
        } while (!uniqueID);

        // Assign object with UUID for checking
        obj->SetUUID(result);
        objectCreationQueue.push_back(obj);

        return obj;
    }

    void ObjectHandler::RemoveObject(std::vector<Object*>::iterator location){
        // Remove GameObject from objects list
        if (auto gameObject = dynamic_cast<GameObject*>(*location)) {
            auto temp = std::find(gameObjectList.begin(), gameObjectList.end(), gameObject);
            gameObjectList.erase(temp);
        }

        objectProcessQueue.erase(location);
    }

    void ObjectHandler::DestroyAll()
    {
        destroyAll = true;
    }

    void ObjectHandler::CreateAllQueuedObjects()
    { // Setup all objects queued for
      // creation last cycle
        while (objectCreationQueue.size() > 0) {
            Object* obj = objectCreationQueue.back();

            if (obj == NULL)
                return;

            obj->Init();
            obj->Start();

            // After initialzing object add it to process queue and remove it from
            // creation queue
            objectProcessQueue.push_back(obj);


            if (auto gameObject = dynamic_cast<GameObject*>(obj)) {
                std::string name = gameObject->GetSpriteName();
                if (name != "none") {
                    gameObject->LoadSprite(AssetManager::GetInstance()->GetCachedSprite(name));
                }
                gameObjectList.push_back(gameObject);
            }

            if (auto uiObject = dynamic_cast<UIObject*>(obj)) {
                uiObjectList.push_back(uiObject);
            }

            objectCreationQueue.pop_back();
        }
    }

    void ObjectHandler::RemoveWithTag(Tag tag)
    {
        for (size_t i = 0; i < gameObjectList.size(); i++) {
            GameObject* temp = gameObjectList.at(i);
            if (temp->GetTag() == tag) {
                temp->Destroy();
            }
        }
    }


    void ObjectHandler::RemoveObject(Object* obj) {
        RemoveObject(find(objectProcessQueue.begin(), objectProcessQueue.end(), obj));
    }

    void ObjectHandler::RemoveObject(int index) {
        RemoveObject(GetObject(index));
    }

    Object* ObjectHandler::GetObject(int index) {
        return objectProcessQueue.at(index);
    }

    Object* ObjectHandler::GetObject(Tag tag) {
        for (size_t i = 0; i < objectProcessQueue.size(); i++) {
            Object* temp = objectProcessQueue.at(i);
            if (temp->GetTag() == tag) {
                return temp;
            }
        }

        return NULL;
    }
}