#pragma once

#include <vector>
#include "GameObject.h"
#include "Object.h";
#include <SDL.h>
#include <iterator>
#include "IControllable.h"
#include <cmath>

/**
 * @brief Handler class that handles input, adding/removing objects, rendering, and updating all GameObjects.
 * @include handler.h
 */
class GameObject;
class Handler
{

    std::shared_ptr<SDL_Renderer> renderer;

    //Separate GameObjects from their components for faster rendering and collision check times (Colliders only need to check against other Colliders for example)
    std::vector<Object*> objectCreationQueue;
    std::vector<Object*> objectProcessQueue;
    std::vector<GameObject*> gameObjectList;
    std::vector<IControllable*> inputProcessQueue;

    //Private original definition of remove_object that takes in iterator from public facing versions
    void remove_object(std::vector<Object*>::iterator location);
    void createAllQueuedObjects();


public:
    

    Handler(std::shared_ptr<SDL_Renderer>  renderer);
    ~Handler();
    static Handler* instance;

    /** Called every frame from GameWindow timer (~60 times per second)
     * @brief tick
     */
    void tick();

    /** Called every second from GameWindow timer
     * @brief tick_second
     */
    void tick_second();

    /** Called from GameWindow paintEvent when window is re-drawn
     * @brief render
     * @param painter
     */
    void render();


    void input(SDL_KeyboardEvent& keyEvent);

    /** Handles adding objects GameObject list
     * @brief add_object
     * @param obj
     */
    void instantiate(Object* obj);

    /** Handles removing objects from GameObject list
     * @brief remove_object
     * @param obj
     */
    void remove_object(Object* obj);

    /** Handles removing objects from GameObject list
     * @brief remove_object
     * @param index
     */
    void remove_object(int index);

    /** Grabs GameObject from index
     * @brief get_object
     * @param index
     * @return GameObject*
     */
    Object* get_object(int index);

    Object* get_object(Tag tag);
};

/** Global facing destroy method that calls destruct method on passed GameObject
 * @brief destroy
 * @param gameObject
 */
void destroy(Object* obj);
Object* instantiate(Object* obj);


/** Global facing instantiate method that calls Hanlder add_object method and returns pointer to passed GameObject
 * @brief instantiate
 * @param gameObject
 * @return GameObject*
 */