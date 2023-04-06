#include "stdafx.h"
#include "Monster.h"

CMonster::CMonster(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList, ID3D12RootSignature* pd3dGraphicsRootSignature, CLoadedModelInfo* pModel,
	int nAnimationTracks, int whatMonster)
{
	CLoadedModelInfo* pMonsterModel = pModel;

	//23.02.05
	//if (!pMonsterModel) pMonsterModel = CGameObject::LoadGeometryAndAnimationFromFile(pd3dDevice, pd3dCommandList, pd3dGraphicsRootSignature, "Model/Voodoo5.bin", NULL);
	switch (whatMonster)
	{
	case 1:
		if (!pMonsterModel) pMonsterModel = CGameObject::LoadGeometryAndAnimationFromFile(pd3dDevice, pd3dCommandList, pd3dGraphicsRootSignature, "Model/Voodoo19.bin", NULL, 1);
		break;
	case 2:
		if (!pMonsterModel) pMonsterModel = CGameObject::LoadGeometryAndAnimationFromFile(pd3dDevice, pd3dCommandList, pd3dGraphicsRootSignature, "Model/Voodoo23.bin", NULL, 2);
		break;
	case 3:
		if (!pMonsterModel) pMonsterModel = CGameObject::LoadGeometryAndAnimationFromFile(pd3dDevice, pd3dCommandList, pd3dGraphicsRootSignature, "Model/Voodoo31.bin", NULL, 3);
		break;
	case 4:
		if (!pMonsterModel) pMonsterModel = CGameObject::LoadGeometryAndAnimationFromFile(pd3dDevice, pd3dCommandList, pd3dGraphicsRootSignature, "Model/Voodoo41.bin", NULL, 4);
		break;
	case 5:
		if (!pMonsterModel) pMonsterModel = CGameObject::LoadGeometryAndAnimationFromFile(pd3dDevice, pd3dCommandList, pd3dGraphicsRootSignature, "Model/Voodoo52.bin", NULL, 5);//2
		break;
	case 6:
		if (!pMonsterModel) pMonsterModel = CGameObject::LoadGeometryAndAnimationFromFile(pd3dDevice, pd3dCommandList, pd3dGraphicsRootSignature, "Model/Voodoo62.bin", NULL, 6);
		break;

	case 7:
		if (!pMonsterModel) pMonsterModel = CGameObject::LoadGeometryAndAnimationFromFile(pd3dDevice, pd3dCommandList, pd3dGraphicsRootSignature, "Model/body26.bin", NULL, 7);
		break;

	case 8:
		if (!pMonsterModel) pMonsterModel = CGameObject::LoadGeometryAndAnimationFromFile(pd3dDevice, pd3dCommandList, pd3dGraphicsRootSignature, "Model/body27.bin", NULL, 7);
		break;

	case 9:
		if (!pMonsterModel) pMonsterModel = CGameObject::LoadGeometryAndAnimationFromFile(pd3dDevice, pd3dCommandList, pd3dGraphicsRootSignature, "Model/body28.bin", NULL, 7);
		break;

	case 10:
		if (!pMonsterModel) pMonsterModel = CGameObject::LoadGeometryAndAnimationFromFile(pd3dDevice, pd3dCommandList, pd3dGraphicsRootSignature, "Model/body.bin", NULL, 7);
		break;
	}
	//

	SetChild(pMonsterModel->m_pModelRootObject, true);
	m_pSkinnedAnimationController = new CAnimationController(pd3dDevice, pd3dCommandList, nAnimationTracks, pMonsterModel);
}

CMonster::~CMonster()
{
}
