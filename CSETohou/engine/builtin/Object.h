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

	virtual void init();
	virtual void start() = 0;
	virtual void tick() = 0;
	virtual void tick_second() = 0; //Might deprecate IDK

	inline void destroy() { destroyed = true; }
	inline const Tag get_tag() const { return tag; }
	inline unsigned long long get_uuid() const { return uuid; }
	inline bool is_destroyed() const { return destroyed; }
    inline void set_uuid(unsigned long long uuid) { this->uuid = uuid; }

};

