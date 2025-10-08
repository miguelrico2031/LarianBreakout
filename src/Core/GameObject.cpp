#include <Core/GameObject.h>
#include <Core/Scene.h>

bool Core::GameObject::isSceneStarted() const
{
	return m_scene->isStarted();
}