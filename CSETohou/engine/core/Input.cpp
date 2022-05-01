#include "Input.h"
#include <iostream>

namespace EngineCore {
    Input* Input::instance;

    void Input::Init()
    {
        keyMap = { {SDL_SCANCODE_LEFT, 0},
                  {SDL_SCANCODE_RIGHT, 0},
                  {SDL_SCANCODE_UP, 0},
                  {SDL_SCANCODE_DOWN, 0},
                  {SDL_SCANCODE_X, 0},
                  {SDL_SCANCODE_Z, 0},
                  {SDL_SCANCODE_LSHIFT, 0} };
        mouseButtons = new int[3];
    }

    void Input::InputEvent(SDL_Event& event)
    {
        switch (event.type) {
            case SDL_MOUSEMOTION:
                MouseMotion(event.motion);
                break;
            case SDL_MOUSEBUTTONDOWN:
                MouseButton(event.button);
                break;
            case SDL_MOUSEBUTTONUP:
                MouseButtonUp(event.button);
                break;
            case SDL_KEYDOWN:
                KeyPress(event.key);
                break;
            case SDL_KEYUP:
                KeyRelease(event.key);
                break;
        }
    }

    bool Input::GetMouseButton(int index) {
        if (mouseButtons[index] > 0) {
            return true;
        }
        return false;
    }

    bool Input::GetMouseButtonUp(int index) {
        if (mouseButtons[index] < 0) {
            mouseButtons[index] = 0;
            return true;
        }
        return false;
    }

    //TODO Implement
    bool Input::GetMouseButtonDown(int index) {
        if (mouseButtons[index] <= 2 && mouseButtons[index] >= 0) {
            return true;
        }
        return false;
    }

    //TODO Implement
    void Input::MouseMotion(SDL_MouseMotionEvent& event) {

    }

    void Input::KeyPress(SDL_KeyboardEvent& event)
    {
        auto key = keyMap.find(event.keysym.scancode);
        if (key != keyMap.end()) {
            std::cout << (int)event.keysym.scancode << '\n';
            (*key).second++;
        }
    }

    void Input::KeyRelease(SDL_KeyboardEvent& event) {
        auto key = keyMap.find(event.keysym.scancode);
        if (key != keyMap.end()) {
            (*key).second = -5;
        }
    }

    void Input::MouseButton(SDL_MouseButtonEvent& event)
    {
        std::cout << event.button << '\n';
        mouseButtons[event.button]++;
    }

    void Input::MouseButtonUp(SDL_MouseButtonEvent& event) {
        //Set to dirty value we can check against
        mouseButtons[event.button] = -2;
    }

    Input* Input::GetInstance()
    {
        if (instance == nullptr) {
            instance = new Input();
            instance->Init();
        }
        return instance;
    }

    bool Input::GetKey(SDL_Scancode key)
    {
        auto temp = keyMap.find(key);
        if (temp != keyMap.end()) {
            if ((*temp).second > 0) {
                return true;
            }
        }

        return false;
    }

    bool Input::GetKeyUp(SDL_Scancode key) {
        auto temp = keyMap.find(key);
        if (temp != keyMap.end()) {
            if ((*temp).second < 0) {
                (*temp).second = 0;
                return true;
            }
        }

        return false;
    }

    bool Input::GetKeyDown(SDL_Scancode key) {
        auto temp = keyMap.find(key);
        if (temp != keyMap.end()) {
            if ((*temp).second <= 1 && (*temp).second >= 0) {
                return true;
            }
        }

        return false;
    }
}