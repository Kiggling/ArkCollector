#include "acGameObject.h"
#include "acTransformComponent.h"

namespace ac
{
	GameObject::GameObject()
	{
		for (size_t i = 0; i < (UINT)enums::EComponentType::End; i++)
		{
			mComponents.push_back(nullptr);
		}
		initializeTransform();
	}
	GameObject::~GameObject()
	{
		for (Component* comp : mComponents)
		{
			if (comp == nullptr)
				continue;
			delete comp;
			comp = nullptr;
		}
	}
	void GameObject::Initialize()
	{
		for (Component* comp : mComponents)
		{
			if (comp == nullptr)
				continue;
			comp->Initialize();
		}
	}
	void GameObject::Update()
	{
		for (Component* comp : mComponents)
		{
			if (comp == nullptr)
				continue;
			comp->Update();
		}
	}
	void GameObject::LateUpdate()
	{
		for (Component* comp : mComponents)
		{
			if (comp == nullptr)
				continue;
			comp->LateUpdate();
		}
	}
	void GameObject::Render(HDC InHdc)
	{
		for (Component* comp : mComponents)
		{
			if (comp == nullptr)
				continue;
			comp->Render(InHdc);
		}
	}
	void GameObject::initializeTransform()
	{
		AddComponent<TransformComponent>();
	}
}