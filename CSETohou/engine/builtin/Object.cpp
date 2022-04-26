#include "Object.h"

Object::Object(Tag tag) {
	this->tag = tag;
}

Object::~Object() {

}

void Object::init() {
	start();
}