#include "acComponent.h"


namespace ac
{
	ac::Component::Component(enums::EComponentType InType)
		: mType(InType)
	{
	}
	Component::~Component()
	{
	}
	void Component::Initialize()
	{
	}
	void Component::Update()
	{
	}
	void Component::LateUpdate()
	{
	}
	void Component::Render(HDC InHdc)
	{
	}
}