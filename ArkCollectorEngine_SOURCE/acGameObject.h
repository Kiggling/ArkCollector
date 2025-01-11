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

		eState GetActive() { return mEffectType; }
		void SetActive(bool power)
		{
			if (power == true) mEffectType = eState::Active;
			if (power == false) mEffectType = eState::Paused;
		}
		void Death() { mEffectType = eState::Dead; }

		enums::ELayerType GetLayerType() { return mLayerType; }
		void SetLayerType(enums::ELayerType layerType) { mLayerType = layerType; }

		/* TileMap 만들 때 사용*/
		void SetIsDead(bool InState) { mbIsDead = InState; }
		bool GetIsDead() { return mbIsDead; }
	private:
		void initializeTransform();
	private:
		eState mEffectType;
		std::vector<Component*> mComponents;
		enums::ELayerType mLayerType;
		
		/* TileMap 만들 때 사용 */
		bool mbIsDead;
	};

}	
