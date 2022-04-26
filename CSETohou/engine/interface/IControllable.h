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

    //Called every frame by Handler. Passes input to key_press() and key_held()
    void input(SDL_KeyboardEvent& event);

    //Called the frame a key is pressed
    virtual void key_press(SDL_Keycode key) = 0;

    //Called during repeat key events
    virtual void key_held(SDL_Keycode key) = 0;

    //Called the frame a key is released
    virtual void key_release(SDL_Keycode key) = 0;
};

#endif // CONTROLLABLE_H
