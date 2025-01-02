#pragma once
#include "CommonInclude.h"
#include "acEntity.h"
#include "acComponent.h"

namespace ac
{
	class GameObject : public Entity
	{
	public:
		enum class eState
		{
			Active,
			Paused,
			Dead,
			End
		};

		GameObject();
		~GameObject();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render(HDC InHdc);

		template <typename T>
		T* GetComponent()
		{
			T* comp = nullptr;
			for (Component* c : mComponents)
			{
				comp = dynamic_cast<T*>(c);
				if (comp)
				{
					break;
				}
			}
			
			return comp;
		}
		template <typename T>
		T* AddComponent()
		{
			T* comp = new T();
			comp->SetOwner(this);
			comp->Initialize();
			mComponents[(UINT)comp->GetType()] = comp;

			return comp;
		}

		eState GetActive() { return mState; }
		void SetActive(bool power)
		{
			if (power == true) mState = eState::Active;
			if (power == false) mState = eState::Paused;
		}
		void Death() { mState = eState::Dead; }

		enums::ELayerType GetLayerType() { return mLayerType; }
		void SetLayerType(enums::ELayerType layerType) { mLayerType = layerType; }

		/* TileMap 만들 때 사용*/
		void SetIsDead(bool InState) { mbIsDead = InState; }
		bool GetIsDead() { return mbIsDead; }
	private:
		void initializeTransform();
	private:
		eState mState;
		std::vector<Component*> mComponents;
		enums::ELayerType mLayerType;
		
		/* TileMap 만들 때 사용 */
		bool mbIsDead;
	};

}	
