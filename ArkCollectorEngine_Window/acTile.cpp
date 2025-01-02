#include "acTile.h"
#include "acGameObject.h"
#include "acTransformComponent.h"
#include "acTilemapRendererComponent.h"

namespace ac
{
	Tile::Tile()
	{
	}
	Tile::~Tile()
	{
	}
	void Tile::Initialize()
	{
		GameObject::Initialize();
	}
	void Tile::Update()
	{
		GameObject::Update();
	}
	void Tile::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void Tile::Render(HDC InHdc)
	{
		GameObject::Render(InHdc);
	}
	void Tile::SetIndexPosition(int idxX, int idxY)
	{
		TransformComponent* tr = GetComponent<TransformComponent>();
		tr->SetPosition(math::Vector2(idxX * TilemapRendererComponent::TileSize.x, idxY * TilemapRendererComponent::TileSize.y));
	}
}