#include "acScriptComponent.h"

namespace ac
{
	ScriptComponent::ScriptComponent()
		: Component(enums::EComponentType::Script)
	{
	}
	ScriptComponent::~ScriptComponent()
	{
	}
	void ScriptComponent::Initialize()
	{
	}
	void ScriptComponent::Update()
	{
	}
	void ScriptComponent::LateUpdate()
	{
	}
	void ScriptComponent::Render(HDC InHdc)
	{
	}
	void ScriptComponent::OnCollisionEnter(ColliderComponent* other)
	{
	}
	void ScriptComponent::OnCollisionStay(ColliderComponent* other)
	{
	}
	void ScriptComponent::OnCollisionExit(ColliderComponent* other)
	{
	}
}