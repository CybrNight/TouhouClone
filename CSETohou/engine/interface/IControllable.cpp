#include "IControllable.h"

IControllable::IControllable()
{


}

void IControllable::Input(SDL_KeyboardEvent& event){
    if (event.repeat && event.type == SDL_KEYDOWN){
        KeyHeld(event.keysym.sym);
    }else if (event.type == SDL_KEYDOWN) {
        KeyPress(event.keysym.sym);
    }
    else {
        KeyRelease(event.keysym.sym);
    }
}
