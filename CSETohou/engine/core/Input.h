#pragma once

#include <unordered_map>
#include <SDL.h>
#include <SDL_mouse.h>

namespace EngineCore {
    class Input
    {

    private:
        Input() {}
        ~Input() {}
        void Init();

        void MouseMotion(SDL_MouseMotionEvent& event);
        
        void KeyPress(SDL_KeyboardEvent& event);
        void KeyRelease(SDL_KeyboardEvent& event);

        void MouseButton(SDL_MouseButtonEvent& event);
        void MouseButtonUp(SDL_MouseButtonEvent& event);

    public:
        static Input* instance;
        static Input* GetInstance();

        std::unordered_map<SDL_Scancode, int> keyMap;
        int* mouseButtons;

        void InputEvent(SDL_Event& event);
        bool GetKey(SDL_Scancode key);
        bool GetKeyDown(SDL_Scancode key);
        bool GetKeyUp(SDL_Scancode key);

        bool GetMouseButtonDown(int mouseButton);
        bool GetMouseButton(int mouseButton);
        bool GetMouseButtonUp(int mouseButton);
    };
}