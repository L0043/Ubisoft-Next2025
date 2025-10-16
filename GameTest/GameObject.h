#pragma once
#include <vector>

// for now including but it should be pointers i thinks
#include <Components/ComponentBase.h>

//class ComponentBase;

class GameObject
{
public:
	GameObject();
	~GameObject();
	// Game Objects need meshes, colliders, transforms

	void AddComponent(ComponentBase* pComponent)
	{
		// add check for specific types to prevent multiples being added to the object (ex: multiple transforms)
		//switch(pComponent->GetType())
		//{
		//	
		//}

		m_Components.push_back(pComponent);
	}

	template <typename T> T GetComponent() 
	{
		for(std::vector<ComponentBase>::iterator it = m_Components.begin(); it != m_Components.end(); ++it)
		{
			if (it->GetType() == T)
				return *it;
		}
	}

private:
	std::vector<ComponentBase*> m_Components;
};
