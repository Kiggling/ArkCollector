#include "acCollisionManager.h"
#include "acColliderComponent.h"
#include "acSceneManager.h"

namespace ac
{
	std::bitset<(UINT)enums::ELayerType::Max> CollisionManager::mCollisionLayerMatrix[(UINT)enums::ELayerType::Max] = {};
	std::unordered_map<UINT64, bool> CollisionManager::mCollisionMap = {};

	void CollisionManager::Initialize()
	{
	}
	void CollisionManager::Update()
	{
		Scene* activeScene = SceneManager::GetActiveScene();

		// Check all layers Collision interaction Setting
		for (UINT row = 0; row < (UINT)enums::ELayerType::Max; row++)
		{
			for (UINT col = 0; col < (UINT)enums::ELayerType::Max; col++)
			if (mCollisionLayerMatrix[row][col] == true)
			{
				LayerCollision(activeScene, (enums::ELayerType)row, (enums::ELayerType)col);
			}
		}
	}
	void CollisionManager::LateUpdate()
	{

	}
	void CollisionManager::Render()
	{
	}
	void CollisionManager::CollisionLayerMatrixCheck(enums::ELayerType left, enums::ELayerType right, bool enable)
	{
		int row = 0;
		int col = 0;

		if (left <= right)
		{
			row = (UINT)left;
			col = (UINT)right;
		}
		else
		{
			row = (UINT)right;
			col = (UINT)left;
		}

		mCollisionLayerMatrix[row][col] = enable;
	}

	// Check all GameObjects in two layers 
	void CollisionManager::LayerCollision(Scene* scene, enums::ELayerType left, enums::ELayerType right)
	{
		for (GameObject* left : scene->GetLayer((enums::ELayerType)left)->GetGameObjects())
		{
			ColliderComponent* leftCol = left->GetCompenet<ColliderComponent>();

			if (leftCol == nullptr)
			{
				continue;
			}
			for (GameObject* right : scene->GetLayer((enums::ELayerType)right)->GetGameObjects())
			{
				ColliderComponent* rightCol = right->GetCompenet<ColliderComponent>();

				if (rightCol == nullptr)
				{
					continue;
				}
				if (left == right)
				{
					continue;
				}
				ColliderCollision(leftCol, rightCol);
			}
		}
	}

	// Call a function according to the Collision state
	void CollisionManager::ColliderCollision(ColliderComponent* left, ColliderComponent* right)
	{
		CollisionID id = {};
		id.left = left->GetID();
		id.right = right->GetID();

		if (mCollisionMap.find(id.id) == mCollisionMap.end())
		{
			mCollisionMap[id.id] = false;
		}

		if (Intersect(left, right))
		{
			if (mCollisionMap[id.id] == true)
			{
				left->OnCollisionStay(right);
				right->OnCollisionStay(left);
				mCollisionMap[id.id] = true;
			}
			else
			{
				left->OnCollisionEnter(right);
				right->OnCollisionEnter(left);
				mCollisionMap[id.id] = true;
			}
		}
		else
		{
			if (mCollisionMap[id.id] == true)
			{
				left->OnCollisionExit(right);
				right->OnCollisionExit(left);
				mCollisionMap[id.id] = false;
			}
		}
	}

	// 	Determine if two objects collided
	bool CollisionManager::Intersect(ColliderComponent* left, ColliderComponent* right)
	{
		math::Vector2 leftCenterPos = left->GetCenterPosition();
		math::Vector2 rightCenterPos = right->GetCenterPosition();
		math::Vector2 leftSize = left->GetSize();
		math::Vector2 rightSize = right->GetSize();
		math::Vector2 leftOffset = left->GetOffset();
		math::Vector2 rightOffset = right->GetOffset();

		leftCenterPos += leftOffset;
		rightCenterPos += rightOffset;

		enums::EColliderType leftType = left->GetColliderType();
		enums::EColliderType rightType = right->GetColliderType();

		if (leftType == enums::EColliderType::Rect2D && rightType == enums::EColliderType::Rect2D)
		{
			return CollisionBetweenRect2DAndRect2D(leftCenterPos, rightCenterPos, leftSize, rightSize);
		}
		else if (leftType == enums::EColliderType::Circle2D && rightType == enums::EColliderType::Circle2D)
		{
			return CollisionBetweenCircle2DAndCircle2D(leftCenterPos, rightCenterPos, leftSize, rightSize);
		}

	}
	bool CollisionManager::CollisionBetweenRect2DAndRect2D(math::Vector2 leftCenterPos, math::Vector2 rightCenterPos, math::Vector2 leftSize, math::Vector2 rightSize )
	{
		if (fabs(leftCenterPos.x - rightCenterPos.x) > fabs(leftSize.x / 2 + rightSize.x / 2)
			|| fabs(leftCenterPos.y - rightCenterPos.y) > fabs(leftSize.y / 2 + rightSize.y / 2))
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	bool CollisionManager::CollisionBetweenCircle2DAndCircle2D(math::Vector2 leftCenterPos, math::Vector2 rightCenterPos, math::Vector2 leftSize, math::Vector2 rightSize)
	{
		if ((leftCenterPos - rightCenterPos).length() > fabs(leftSize.x / 2 + rightSize.x / 2))
		{
			return false;
		}
		else
		{
			return true;
		}
	}
}