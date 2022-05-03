#pragma once
#include "UIObject.h"

#include <SDL.h>

#include <cmath>
#include <iterator>
#include <vector>
#include <memory>
#include "GameObject.h"

namespace CybrEngine {
    /**
     * @brief Handler class that handles input, adding/removing objects, rendering,
     * and updating all GameObjects.
     * @include handler.h
     */
    class ObjectHandler {
        static ObjectHandler* instance;
        std::shared_ptr<SDL_Renderer> renderer;

        // Separate GameObjects from their components for faster rendering and
        // collision check times (Colliders only need to check against other Colliders
        // for example)
        std::vector<std::shared_ptr<Object>> objectCreationQueue;
        std::vector<std::shared_ptr<Object>> objectProcessQueue;
        std::vector<UI::UIObject*> uiObjectList;
        std::vector<GameObject*> gameObjectList;

        bool destroyAll;

        // Private original definition of remove_object that takes in iterator from
        // public facing versions
        void RemoveObject(std::vector<std::shared_ptr<Object>>::iterator location);
        void CreateAllQueuedObjects();

        ObjectHandler();
        ~ObjectHandler();

        void Init(std::shared_ptr<SDL_Renderer> renderer);
    public:
        void DestroyAll();
        static ObjectHandler* GetInstance(std::shared_ptr<SDL_Renderer> renderer = nullptr);
        inline SDL_Renderer* GetRenderer() const { return renderer.get(); };

        /** Called every frame from GameWindow timer (~60 times per second)
         * @brief tick
         */
        void Tick();

        /** Called every second from GameWindow timer
         * @brief tick_second
         */
        void TickSecond();

        /** Called from GameWindow paintEvent when window is re-drawn
         * @brief render
         * @param painter
         */
        void Render();
        void RenderUI();

        /** Handles adding objects GameObject list
         * @brief add_object
         * @param obj
         */
        std::shared_ptr<Object> Instantiate(Object* obj);

        /** Handles removing objects from GameObject list
         * @brief remove_object
         * @param obj
         */
        void RemoveObject(std::shared_ptr<Object> obj);

        /** Handles removing objects from GameObject list
         * @brief remove_object
         * @param index
         */
        void RemoveObject(int index);


        void RemoveWithTag(Tag tag);

        /** Grabs GameObject from index
         * @brief get_object
         * @param index
         * @return GameObject*
         */
        std::shared_ptr<Object> GetObject(int index);

        std::shared_ptr<Object> GetObject(Tag tag);
    };
}
