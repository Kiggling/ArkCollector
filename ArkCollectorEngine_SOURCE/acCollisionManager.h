#pragma once
#include "CommonInclude.h"
#include "acColliderComponent.h"
#include "acScene.h"
#include "acLayer.h"

namespace ac
{
	union CollisionID
	{
		struct
		{
			UINT32 left;
			UINT32 right;
		};
		UINT64 id;
	};
	class CollisionManager
	{
	public:
		static void Initialize();
		static void Update();
		static void LateUpdate();
		static void Render(HDC InHdc);

		static void CollisionLayerMatrixCheck(enums::ELayerType left, enums::ELayerType right, bool enable);
		static void LayerCollision(Scene* scene, enums::ELayerType left, enums::ELayerType right);
		static void ColliderCollision(ColliderComponent* left, ColliderComponent* right);
		static bool Intersect(ColliderComponent* left, ColliderComponent* right);
		static bool CollisionBetweenRect2DAndRect2D(math::Vector2 leftCenterPos, math::Vector2 rightCenterPos, math::Vector2 leftSize, math::Vector2 rightSize);
		static bool CollisionBetweenCircle2DAndCircle2D(math::Vector2 leftCenterPos, math::Vector2 rightCenterPos, math::Vector2 leftSize, math::Vector2 rightSize);
	private:
		static std::bitset<(UINT)enums::ELayerType::Max> mCollisionLayerMatrix[(UINT)enums::ELayerType::Max];
		static std::unordered_map<UINT64, bool> mCollisionMap;
	};
}