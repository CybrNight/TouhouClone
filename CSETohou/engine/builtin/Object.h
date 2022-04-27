#pragma once
#include "Tag.h"

class Object
{
	Tag tag = Tag::ObjectGeneric;
	unsigned long long uuid = -1;
	bool destroyed = false;


public:
	Object(Tag tag=Tag::ObjectGeneric);
	virtual ~Object() = 0;

	virtual void Init();
	virtual void Start() = 0;
	virtual void Tick() = 0;
	virtual void TickSecond() = 0; //Might deprecate IDK

	inline void Destroy() { destroyed = true; }
	inline const Tag GetTag() const { return tag; }
	inline unsigned long long GetUUID() const { return uuid; }
	inline bool IsDestroyed() const { return destroyed; }
    inline void SetUUID(unsigned long long uuid) { this->uuid = uuid; }

};

