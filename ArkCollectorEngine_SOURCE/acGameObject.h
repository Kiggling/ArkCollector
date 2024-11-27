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
		T* GetCompenet()
		{
			T* comp = nullptr;
			for (Component* c : mComponents)
			{
				comp = dynamic_cast<T*>(c);
				if (c)
				{
					break;
				}
			}
			
			return comp;
		}
		template <typename T>
		T* AddCompenet()
		{
			T* comp = new T();
			comp->SetOwner(this);
			comp->Initialize();
			mComponents[(UINT)comp->GetType()] = comp;

			return comp;
		}


	private:
		std::vector<Component*> mComponents;
	};

}	