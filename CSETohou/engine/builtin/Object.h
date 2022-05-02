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

	/// <summary>
	/// Initialize values for all Object types. Called when Object is first created and queued for creation
	/// </summary>
	virtual void Init();

	/// <summary>
	/// Called when the Object is added to game by Handler
	/// </summary>
	virtual void Start() = 0;

	/// <summary>
	/// Called every frame from Handler
	/// </summary>
	virtual void Tick() = 0;
	//virtual void TickSecond() = 0; //REMOVE ME SOON

	/// <summary>
	/// Marks current Object for destruction next cycle
	/// </summary>
	inline void Destroy() { destroyed = true; }
	Object* Instantiate(Object* obj);
	inline const Tag GetTag() const { return tag; }
	inline unsigned long long GetUUID() const { return uuid; }
	inline bool IsDestroyed() const { return destroyed; }
    inline void SetUUID(unsigned long long uuid) { this->uuid = uuid; }

};