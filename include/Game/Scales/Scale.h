#pragma once
#include <Core/Behavior.h>


class Scale : public Core::Behavior
{
public:
	Scale(Core::GameObject* gameObject, unsigned int r, unsigned int c)
		: Behavior(gameObject), Row(r), Col(c) {}
	
	const unsigned int Row, Col;
};