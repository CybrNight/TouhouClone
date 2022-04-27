#ifndef CONTROLLABLE_H
#define CONTROLLABLE_H
#include <SDL.h>
/**
 * @brief Interface for all objects that can receive input from keyboard
 * @include controllable.h
 */
class IControllable
{

public:
    IControllable();
    ~IControllable(){};

    //Called every frame by Handler. Passes input to KeyPress() and KeyHeld()
    void Input(SDL_KeyboardEvent& event);

    //Called the frame a key is pressed
    virtual void KeyPress(SDL_Keycode key) = 0;

    //Called during repeat key events
    virtual void KeyHeld(SDL_Keycode key) = 0;

    //Called the frame a key is released
    virtual void KeyRelease(SDL_Keycode key) = 0;
};

#endif // CONTROLLABLE_H
