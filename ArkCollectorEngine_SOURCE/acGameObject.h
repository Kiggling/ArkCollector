#pragma once
#include "CommonInclude.h"
#include "acEntity.h"
#include "acComponent.h"

namespace ac
{
	class GameObject : public Entity
	{
	public:
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

		void SetLayerType(enums::ELayerType InLayerType) { mLayerType = InLayerType; }
		void SetIsDead(bool InState) { mbIsDead = InState; }
		bool GetIsDead() { return mbIsDead; }
	private:
		void initializeTransform();
	private:
		std::vector<Component*> mComponents;
		enums::ELayerType mLayerType;
		bool mbIsDead;
	};

}	
