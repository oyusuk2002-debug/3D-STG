#pragma once
#include "GameObject.h"
#include "TestComponent2.h"

using namespace HyEngine;

class Fighter2 final : public GameObject
{
private  :
	explicit Fighter2(class Scene* scene);

	virtual ~Fighter2() = default;


	public:
		static Fighter2* Create(Scene* scene)
		{
			Fighter2* fighter = new Fighter2(scene);
			fighter->Initialize();
	
			//ObjectManager::Get()->InsertObject(fighter);
			return fighter;
		}

		virtual void Initialize() override;

	// Inherited via GameObject
	virtual void Render() override;

	private:
		IDirect3DVertexBuffer9 * vertexBuffer = nullptr;
	
		IDirect3DIndexBuffer9* indexBuffer = nullptr;
		//class objl::Loader loader;
		UINT vertexNum;
		UINT primCount;
	
		IDirect3DTexture9 * texture = nullptr;
		IDirect3DTexture9* lightMap = nullptr;

};
