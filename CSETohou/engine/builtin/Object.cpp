#include "Object.h"
#include "ObjectHandler.h"

Object::Object(Tag tag) {
	this->tag = tag;
}

Object::~Object() {

}

void Object::Init() {
	Start();
}

Object* Object::Instantiate(Object* obj)
{
	EngineCore::ObjectHandler::GetInstance()->Instantiate(obj);
	return obj;
}
