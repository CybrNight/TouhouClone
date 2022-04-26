#include "IControllable.h"

IControllable::IControllable()
{


}

void IControllable::input(SDL_KeyboardEvent& event){
    if (event.repeat && event.type == SDL_KEYDOWN){
        key_held(event.keysym.sym);
    }else if (event.type == SDL_KEYDOWN) {
        key_press(event.keysym.sym);
    }
    else {
        key_release(event.keysym.sym);
    }
}
