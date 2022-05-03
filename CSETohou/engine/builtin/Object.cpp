#include "Object.h"
#include "ObjectHandler.h"
#include <iostream>

Object::Object(Tag tag) {
	this->tag = tag;
}

Object::~Object() {

}

void Object::Init() {

}

Object* Object::Instantiate(Object* obj)
{
	CybrEngine::ObjectHandler::GetInstance()->Instantiate(obj);
	return obj;
}
