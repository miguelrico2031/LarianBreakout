#pragma once
#include <Core/Behavior.h>


class Scale : public Core::Behavior
{
public:
	Scale(Core::GameObject* gameObject) : Behavior(gameObject) {}
	
	unsigned int Row, Col;
};