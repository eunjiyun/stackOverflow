                                               // File: CStage.cpp
//-----------------------------------------------------------------------------

#include <DirectXMath.h>
#include "stdafx.h"
#include "Stage.h"
ID3D12DescriptorHeap* CStage::m_pd3dCbvSrvDescriptorHeap = NULL;

D3D12_CPU_DESCRIPTOR_HANDLE	CStage::m_d3dCbvCPUDescriptorStartHandle;
D3D12_GPU_DESCRIPTOR_HANDLE	CStage::m_d3dCbvGPUDescriptorStartHandle;
D3D12_CPU_DESCRIPTOR_HANDLE	CStage::m_d3dSrvCPUDescriptorStartHandle;
D3D12_GPU_DESCRIPTOR_HANDLE	CStage::m_d3dSrvGPUDescriptorStartHandle;

D3D12_CPU_DESCRIPTOR_HANDLE	CStage::m_d3dCbvCPUDescriptorNextHandle;
D3D12_GPU_DESCRIPTOR_HANDLE	CStage::m_d3dCbvGPUDescriptorNextHandle;
D3D12_CPU_DESCRIPTOR_HANDLE	CStage::m_d3dSrvCPUDescriptorNextHandle;
D3D12_GPU_DESCRIPTOR_HANDLE	CStage::m_d3dSrvGPUDescriptorNextHandle;

CStage::CStage()
{
}

CStage::~CStage()
{
}

void CStage::BuildShadowLights(LIGHT* pLights)
{
	//m_pShadowLights = new LIGHTS;
	m_pLights = pLights;
	::ZeroMemory(m_pLights, sizeof(LIGHT));

	m_xmf4GlobalAmbient = XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f);

	m_pLights[0].m_bEnable = true;
	m_pLights[0].m_nType = DIRECTIONAL_LIGHT;
	m_pLights[0].m_fRange = 2000.0f;
	m_pLights[0].m_xmf4Ambient = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
	m_pLights[0].m_xmf4Diffuse = XMFLOAT4(0.73f, 0.73f, 0.73f, 1.0f);
	m_pLights[0].m_xmf4Specular = XMFLOAT4(0.3f, 0.3f, 0.3f, 0.0f);
	m_pLights[0].m_xmf3Position = XMFLOAT3(-(_PLANE_WIDTH * 0.5f), 512.0f, 0.0f);
	m_pLights[0].m_xmf3Direction = XMFLOAT3(+1.0f, -1.0f, 0.0f);

	m_pLights[1].m_bEnable = true;
	m_pLights[1].m_nType = SPOT_LIGHT;
	m_pLights[1].m_fRange = 1000.0f;
	m_pLights[1].m_xmf4Ambient = XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f);
	m_pLights[1].m_xmf4Diffuse = XMFLOAT4(0.54f, 0.54f, 0.54f, 1.0f);
	m_pLights[1].m_xmf4Specular = XMFLOAT4(0.13f, 0.13f, 0.13f, 0.0f);
	m_pLights[1].m_xmf3Position = XMFLOAT3(-50.0f, 120.0f, 50.0f);
	m_pLights[1].m_xmf3Direction = XMFLOAT3(0.0f, -1.0f, 1.0f);
	m_pLights[1].m_xmf3Attenuation = XMFLOAT3(1.0f, 0.1f, 0.001f);
	m_pLights[1].m_fFalloff = 16.0f;
	m_pLights[1].m_fPhi = (float)cos(XMConvertToRadians(60.0f));
	m_pLights[1].m_fTheta = (float)cos(XMConvertToRadians(30.0f));

	m_pLights[2].m_bEnable = false;
	m_pLights[2].m_nType = SPOT_LIGHT;
	m_pLights[2].m_fRange = 500.0f;
	m_pLights[2].m_xmf4Ambient = XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f);
	m_pLights[2].m_xmf4Diffuse = XMFLOAT4(0.85f, 0.85f, 0.85f, 1.0f);
	m_pLights[2].m_xmf4Specular = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
	m_pLights[2].m_xmf3Position = XMFLOAT3(0.0f, 256.0f, 0.0f);
	m_pLights[2].m_xmf3Direction = XMFLOAT3(+1.0f, -1.0f, 0.0f);
	m_pLights[2].m_xmf3Attenuation = XMFLOAT3(0.5f, 0.01f, 0.0001f);
	m_pLights[2].m_fFalloff = 4.0f;
	m_pLights[2].m_fPhi = (float)cos(XMConvertToRadians(60.0f));
	m_pLights[2].m_fTheta = (float)cos(XMConvertToRadians(30.0f));

	m_pLights[3].m_bEnable = false;
	m_pLights[3].m_nType = DIRECTIONAL_LIGHT;
	m_pLights[3].m_fRange = 1000.0f;
	m_pLights[3].m_xmf4Ambient = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
	m_pLights[3].m_xmf4Diffuse = XMFLOAT4(0.83f, 0.83f, 0.83f, 1.0f);
	m_pLights[3].m_xmf4Specular = XMFLOAT4(0.3f, 0.3f, 0.3f, 0.0f);
	m_pLights[3].m_xmf3Position = XMFLOAT3(0.0f, 128.0f, 0.0f);
	m_pLights[3].m_xmf3Direction = XMFLOAT3(+1.0f, -1.0f, 0.0f);

	//m_pLights->m_pLights[3].m_bEnable = false;
	//m_pLights->m_pLights[3].m_nType = POINT_LIGHT;
	//m_pLights->m_pLights[3].m_fRange = 100.0f;
	//m_pLights->m_pLights[3].m_xmf4Ambient = XMFLOAT4(0.1f, 0.0f, 0.0f, 1.0f);
	//m_pLights->m_pLights[3].m_xmf4Diffuse = XMFLOAT4(0.8f, 0.0f, 0.0f, 1.0f);
	//m_pLights->m_pLights[3].m_xmf4Specular = XMFLOAT4(0.1f, 0.1f, 0.1f, 0.0f);
	//m_pLights->m_pLights[3].m_xmf3Position = XMFLOAT3(130.0f, 30.0f, 30.0f);
	//m_pLights->m_pLights[3].m_xmf3Direction = XMFLOAT3(0.0f, 0.0f, 0.0f);
	//m_pLights->m_pLights[3].m_xmf3Attenuation = XMFLOAT3(1.0f, 0.001f, 0.0001f);

	m_pMaterials = new MATERIALS;
	::ZeroMemory(m_pMaterials, sizeof(MATERIALS));

	m_pMaterials->m_pReflections[0] = { XMFLOAT4(0.128f, 0.128f, 0.128f, 1.0f), XMFLOAT4(0.8f, 0.18f, 0.18f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 10.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f) };
	m_pMaterials->m_pReflections[1] = { XMFLOAT4(0.28f, 0.28f, 0.28f, 1.0f), XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 10.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f) };
	m_pMaterials->m_pReflections[2] = { XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 15.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f) };
	m_pMaterials->m_pReflections[3] = { XMFLOAT4(0.5f, 0.0f, 1.0f, 1.0f), XMFLOAT4(0.0f, 0.5f, 1.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 20.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f) };
	m_pMaterials->m_pReflections[4] = { XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 25.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f) };
	m_pMaterials->m_pReflections[5] = { XMFLOAT4(0.0f, 0.5f, 0.5f, 1.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 30.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f) };
	m_pMaterials->m_pReflections[6] = { XMFLOAT4(0.5f, 0.5f, 1.0f, 1.0f), XMFLOAT4(0.5f, 0.5f, 1.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 35.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f) };
	m_pMaterials->m_pReflections[7] = { XMFLOAT4(1.0f, 0.5f, 1.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 40.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f) };
}

LIGHT* CStage::BuildDefaultLightsAndMaterials(LIGHT* pLights)
{
	m_nLights = MAX_LIGHTS;
	//if(!pLights)
	//	m_pLights = new LIGHT[MAX_SHADOW_LIGHTS];
	////pLights = new LIGHT[MAX_SHADOW_LIGHTS];
	//else
		m_pLights = pLights;
	::ZeroMemory(m_pLights, sizeof(LIGHT) * m_nLights);

	m_xmf4GlobalAmbient = XMFLOAT4(0.15f, 0.15f, 0.15f, 1.0f);

	//m_pLights[0].m_bEnable = true;
	//m_pLights[0].m_nType = POINT_LIGHT;
	//m_pLights[0].m_fRange = 300.0f;
	//m_pLights[0].m_xmf4Ambient = XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f);
	//m_pLights[0].m_xmf4Diffuse = XMFLOAT4(0.4f, 0.3f, 0.8f, 1.0f);
	//m_pLights[0].m_xmf4Specular = XMFLOAT4(0.5f, 0.5f, 0.5f, 0.0f);
	//m_pLights[0].m_xmf3Position = XMFLOAT3(230.0f, 330.0f, 480.0f);
	//m_pLights[0].m_xmf3Attenuation = XMFLOAT3(1.0f, 0.001f, 0.0001f);
	////m_pLights[0].m_xmf3Direction = XMFLOAT3(+1.0f, -1.0f, 0.0f);
	//m_pLights[1].m_bEnable = true;
	//m_pLights[1].m_nType = SPOT_LIGHT;
	//m_pLights[1].m_fRange = 500.0f;
	//m_pLights[1].m_xmf4Ambient = XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f);
	//m_pLights[1].m_xmf4Diffuse = XMFLOAT4(0.4f, 0.4f, 0.4f, 1.0f);
	//m_pLights[1].m_xmf4Specular = XMFLOAT4(0.3f, 0.3f, 0.3f, 0.0f);
	//m_pLights[1].m_xmf3Position = XMFLOAT3(-50.0f, 20.0f, -5.0f);
	//m_pLights[1].m_xmf3Direction = XMFLOAT3(0.0f, -1.0f, 1.0f);
	//m_pLights[1].m_xmf3Attenuation = XMFLOAT3(1.0f, 0.01f, 0.0001f);
	//m_pLights[1].m_fFalloff = 8.0f;
	//m_pLights[1].m_fPhi = (float)cos(XMConvertToRadians(40.0f));
	//m_pLights[1].m_fTheta = (float)cos(XMConvertToRadians(20.0f));
	//m_pLights[2].m_bEnable = true;
	//m_pLights[2].m_nType = DIRECTIONAL_LIGHT;
	//m_pLights[2].m_xmf4Ambient = XMFLOAT4(0.3f, 0.3f, 0.3f, 1.0f);
	//m_pLights[2].m_xmf4Diffuse = XMFLOAT4(0.7f, 0.7f, 0.7f, 1.0f);
	//m_pLights[2].m_xmf4Specular = XMFLOAT4(0.4f, 0.4f, 0.4f, 0.0f);
	//m_pLights[2].m_xmf3Direction = XMFLOAT3(1.0f, -1.0f, 0.0f);
	//m_pLights[3].m_bEnable = true;
	//m_pLights[3].m_nType = SPOT_LIGHT;
	//m_pLights[3].m_fRange = 600.0f;
	//m_pLights[3].m_xmf4Ambient = XMFLOAT4(0.3f, 0.3f, 0.3f, 1.0f);
	//m_pLights[3].m_xmf4Diffuse = XMFLOAT4(0.3f, 0.7f, 0.0f, 1.0f);
	//m_pLights[3].m_xmf4Specular = XMFLOAT4(0.3f, 0.3f, 0.3f, 0.0f);
	//m_pLights[3].m_xmf3Position = XMFLOAT3(550.0f, 330.0f, 530.0f);
	//m_pLights[3].m_xmf3Direction = XMFLOAT3(0.0f, -1.0f, 1.0f);
	//m_pLights[3].m_xmf3Attenuation = XMFLOAT3(1.0f, 0.01f, 0.0001f);
	//m_pLights[3].m_fFalloff = 8.0f;
	//m_pLights[3].m_fPhi = (float)cos(XMConvertToRadians(90.0f));
	//m_pLights[3].m_fTheta = (float)cos(XMConvertToRadians(30.0f));


	m_pLights[0].m_bEnable = true;
	m_pLights[0].m_nType = DIRECTIONAL_LIGHT;
	m_pLights[0].m_fRange = 2000.0f;
	m_pLights[0].m_xmf4Ambient = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
	m_pLights[0].m_xmf4Diffuse = XMFLOAT4(0.73f, 0.73f, 0.73f, 1.0f);
	m_pLights[0].m_xmf4Specular = XMFLOAT4(0.3f, 0.3f, 0.3f, 0.0f);
	m_pLights[0].m_xmf3Position = XMFLOAT3(-(_PLANE_WIDTH * 0.5f), 512.0f, 0.0f);
	m_pLights[0].m_xmf3Direction = XMFLOAT3(+1.0f, -1.0f, 0.0f);

	m_pLights[1].m_bEnable = true;
	m_pLights[1].m_nType = SPOT_LIGHT;
	m_pLights[1].m_fRange = 500.0f;
	m_pLights[1].m_xmf4Ambient = XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f);
	m_pLights[1].m_xmf4Diffuse = XMFLOAT4(0.4f, 0.4f, 0.4f, 1.0f);
	m_pLights[1].m_xmf4Specular = XMFLOAT4(0.3f, 0.3f, 0.3f, 0.0f);
	m_pLights[1].m_xmf3Position = XMFLOAT3(-50.0f, 20.0f, -5.0f);
	m_pLights[1].m_xmf3Direction = XMFLOAT3(0.0f, -1.0f, 1.0f);
	m_pLights[1].m_xmf3Attenuation = XMFLOAT3(1.0f, 0.01f, 0.0001f);
	m_pLights[1].m_fFalloff = 8.0f;
	m_pLights[1].m_fPhi = (float)cos(XMConvertToRadians(40.0f));
	m_pLights[1].m_fTheta = (float)cos(XMConvertToRadians(20.0f));

	m_pLights[2].m_bEnable = false;
	m_pLights[2].m_nType = SPOT_LIGHT;
	m_pLights[2].m_fRange = 500.0f;
	m_pLights[2].m_xmf4Ambient = XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f);
	m_pLights[2].m_xmf4Diffuse = XMFLOAT4(0.85f, 0.85f, 0.85f, 1.0f);
	m_pLights[2].m_xmf4Specular = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
	m_pLights[2].m_xmf3Position = XMFLOAT3(0.0f, 256.0f, 0.0f);
	m_pLights[2].m_xmf3Direction = XMFLOAT3(+1.0f, -1.0f, 0.0f);
	m_pLights[2].m_xmf3Attenuation = XMFLOAT3(0.5f, 0.01f, 0.0001f);
	m_pLights[2].m_fFalloff = 4.0f;
	m_pLights[2].m_fPhi = (float)cos(XMConvertToRadians(60.0f));
	m_pLights[2].m_fTheta = (float)cos(XMConvertToRadians(30.0f));

	m_pLights[3].m_bEnable = false;
	m_pLights[3].m_nType = DIRECTIONAL_LIGHT;
	m_pLights[3].m_fRange = 1000.0f;
	m_pLights[3].m_xmf4Ambient = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
	m_pLights[3].m_xmf4Diffuse = XMFLOAT4(0.83f, 0.83f, 0.83f, 1.0f);
	m_pLights[3].m_xmf4Specular = XMFLOAT4(0.3f, 0.3f, 0.3f, 0.0f);
	m_pLights[3].m_xmf3Position = XMFLOAT3(0.0f, 128.0f, 0.0f);
	m_pLights[3].m_xmf3Direction = XMFLOAT3(+1.0f, -1.0f, 0.0f);

	

	if (pLights)
	{
		/*m_pLights[4].m_bEnable = true;
		m_pLights[4].m_nType = POINT_LIGHT;
		m_pLights[4].m_fRange = 200.0f;
		m_pLights[4].m_xmf4Ambient = XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f);
		m_pLights[4].m_xmf4Diffuse = XMFLOAT4(0.8f, 0.3f, 0.3f, 1.0f);
		m_pLights[4].m_xmf4Specular = XMFLOAT4(0.5f, 0.5f, 0.5f, 0.0f);
		m_pLights[4].m_xmf3Position = XMFLOAT3(600.0f, 250.0f, 700.0f);
		m_pLights[4].m_xmf3Attenuation = XMFLOAT3(1.0f, 0.001f, 0.0001f);*/

		m_pLights[4].m_bEnable = true;
		m_pLights[4].m_nType = SPOT_LIGHT;
		m_pLights[4].m_fRange = 500.0f;
		m_pLights[4].m_xmf4Ambient = XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f);
		m_pLights[4].m_xmf4Diffuse = XMFLOAT4(0.4f, 0.4f, 0.4f, 1.0f);
		m_pLights[4].m_xmf4Specular = XMFLOAT4(0.3f, 0.3f, 0.3f, 0.0f);
		m_pLights[4].m_xmf3Position = XMFLOAT3(-50.0f, 20.0f, -5.0f);
		m_pLights[4].m_xmf3Direction = XMFLOAT3(0.0f, -1.0f, 1.0f);
		m_pLights[4].m_xmf3Attenuation = XMFLOAT3(1.0f, 0.01f, 0.0001f);
		m_pLights[4].m_fFalloff = 8.0f;
		m_pLights[4].m_fPhi = (float)cos(XMConvertToRadians(40.0f));
		m_pLights[4].m_fTheta = (float)cos(XMConvertToRadians(20.0f));

		for (int i = 5; i < MAX_LIGHTS; ++i)
		{
			m_pLights[i].m_bEnable = false;
			//m_pLights->m_pLights[i].m_bEnable =wakeUp;//
			//m_pLights->m_pLights[5].m_nType = SPOT_LIGHT;
			m_pLights[i].m_nType = POINT_LIGHT;
			m_pLights[i].m_fRange = 120.0f;

			m_pLights[i].m_xmf4Ambient = XMFLOAT4(0.5f, 0.5f, 0.5f, 5.0f);
			m_pLights[i].m_xmf4Diffuse = XMFLOAT4(0.7f, 0.7f, 0.7f, 7.0f);
			m_pLights[i].m_xmf4Specular = XMFLOAT4(0.7f, 0.7f, 0.7f, 0.0f);
			//m_pLights->m_pLights[5].m_xmf3Position = XMFLOAT3(0.0f, 0.0f, -5.0f);
			m_pLights[i].m_xmf3Direction = XMFLOAT3(0.0f, 0.0f, 1.0f);
			m_pLights[i].m_xmf3Attenuation = XMFLOAT3(1.0f, 0.01f, 0.0001f);
			m_pLights[i].m_fFalloff = 8.0f;
			m_pLights[i].m_fPhi = (float)cos(XMConvertToRadians(40.0f));
			m_pLights[i].m_fTheta = (float)cos(XMConvertToRadians(20.0f));

			//m_pLights[i].m_xmf3Position = XMFLOAT3(mpObjVec[i - 5].x, mpObjVec[i - 5].y + 5, mpObjVec[i - 5].z);
			//m_pLights->m_pLights[5].m_xmf3Position = pos;
		}
	}

	return m_pLights;
}


void CStage::BuildObjects(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList)
{
	m_pd3dGraphicsRootSignature = CreateGraphicsRootSignature(pd3dDevice);

	m_pLights = new LIGHT[MAX_LIGHTS];
	BuildDefaultLightsAndMaterials(m_pLights);//인형이 까맣게 출력
	
	//23.02.05
	CreateCbvSrvDescriptorHeaps(pd3dDevice, 0, 588); //SuperCobra(17), Gunship(2), Player:Mi24(1), Angrybot()//76
	//DXGI_FORMAT pdxgiRtvFormats[5] = { DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_FORMAT_R32_FLOAT };
	DXGI_FORMAT pdxgiRtvFormats[5] = { DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_FORMAT_R32_FLOAT };
	//

	

	m_nShaders2 = 1;
	m_ppShaders2 = new CShader * [m_nShaders2];
	CObjectsShader* pObjectShader = new CObjectsShader();
	pObjectShader->CreateShader(pd3dDevice, m_pd3dGraphicsRootSignature, 5, pdxgiRtvFormats, DXGI_FORMAT_D32_FLOAT);//
	mpObjVec = pObjectShader->BuildObjects(pd3dDevice, pd3dCommandList, m_d3dCbvGPUDescriptorStartHandle, m_pd3dCbvSrvDescriptorHeap, "Models/Scene.bin");
	m_ppShaders2[0] = pObjectShader;

	/*for (int i = 0; i < m_ppShaders2[0]->m_nObjects; ++i)
	{
		m_ppShaders2[0]->m_ppObjects[i]->Boundingbox_Transform();

	}*/

	CMaterial::PrepareShaders(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature, 5, pdxgiRtvFormats, DXGI_FORMAT_D32_FLOAT);

	/*m_nShaders = 2;
	m_ppShaders = new CShader * [m_nShaders];*/

	//CBoxShader* pBoxShader = new CBoxShader();
	////pBoxShader->CreateShader(pd3dDevice, m_pd3dGraphicsRootSignature, D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE, 5, NULL, DXGI_FORMAT_D32_FLOAT);
	////pBoxShader->CreateShader(pd3dDevice, m_pd3dGraphicsRootSignature, D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE, 5, NULL, DXGI_FORMAT_D24_UNORM_S8_UINT);
	//pBoxShader->BuildObjects(pd3dDevice, pd3dCommandList,2, NULL);//0328
	////CMaterial::PrepareShaders(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature, 5, pdxgiRtvFormats, DXGI_FORMAT_D32_FLOAT);
	////m_xmBoundingBox = pBoxShader->CalculateBoundingBox();
	//m_ppShaders[0] = pBoxShader;

	////CBoxShader* pBoxShader2 = new CBoxShader();
	//////pBoxShader2->CreateShader(pd3dDevice, m_pd3dGraphicsRootSignature, D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE, 5, NULL, DXGI_FORMAT_D32_FLOAT);
	//////pBoxShader->CreateShader(pd3dDevice, m_pd3dGraphicsRootSignature, D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE, 5, NULL, DXGI_FORMAT_D24_UNORM_S8_UINT);
	////pBoxShader2->BuildObjects2(pd3dDevice, pd3dCommandList, 1,NULL);//0328
	//////m_xmBoundingBox = pBoxShader->CalculateBoundingBox();
	////m_ppShaders[1] = pBoxShader2;

	//m_pDepthRenderShader = new CDepthRenderShader(pBoxShader, m_pLights);//0328
	//DXGI_FORMAT RtvFormats[5] = { DXGI_FORMAT_R32_FLOAT,DXGI_FORMAT_R32_FLOAT,DXGI_FORMAT_R32_FLOAT,DXGI_FORMAT_R32_FLOAT,DXGI_FORMAT_R32_FLOAT };
	//m_pDepthRenderShader->CreateShader(pd3dDevice, m_pd3dGraphicsRootSignature, D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE, 5, RtvFormats, DXGI_FORMAT_D32_FLOAT);
	//m_pDepthRenderShader->BuildObjects(pd3dDevice, pd3dCommandList, NULL);
	//

	////m_pDepthRenderObjShader = new CDepthRenderObjShader(pBoxShader2, m_pLights);//0328
	//////DXGI_FORMAT RtvFormats[5] = { DXGI_FORMAT_R32_FLOAT,DXGI_FORMAT_R32_FLOAT,DXGI_FORMAT_R32_FLOAT,DXGI_FORMAT_R32_FLOAT,DXGI_FORMAT_R32_FLOAT };
	////m_pDepthRenderObjShader->CreateShader(pd3dDevice, m_pd3dGraphicsRootSignature, D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE, 5, RtvFormats, DXGI_FORMAT_D32_FLOAT);
	////m_pDepthRenderObjShader->BuildObjects(pd3dDevice, pd3dCommandList, NULL);//

	//m_pShadowShader = new CShadowMapShader(pBoxShader);
	//m_pShadowShader->CreateShader(pd3dDevice, m_pd3dGraphicsRootSignature, D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE, 5, NULL, DXGI_FORMAT_D32_FLOAT);//pipelinestate null
	//m_pShadowShader->BuildObjects(pd3dDevice, pd3dCommandList, m_pDepthRenderShader->GetDepthTexture());
	

	//m_pShadowObjShader = new CShadowMapShader(pBoxShader2);
	//m_pShadowObjShader->CreateShader(pd3dDevice, m_pd3dGraphicsRootSignature, D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE, 5, NULL, DXGI_FORMAT_D32_FLOAT);//pipelinestate null
	//m_pShadowObjShader->BuildObjects(pd3dDevice, pd3dCommandList, m_pDepthRenderObjShader->GetDepthTexture());


	/*m_pShadowMapToViewport = new CTextureToViewportShader();
	m_pShadowMapToViewport->CreateShader(pd3dDevice, m_pd3dGraphicsRootSignature, D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE, 5, NULL, DXGI_FORMAT_D32_FLOAT);
	m_pShadowMapToViewport->BuildObjects(pd3dDevice, pd3dCommandList, m_pDepthRenderShader->GetDepthTexture());*/

	//CMaterial::PrepareShaders(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature, 5, pdxgiRtvFormats, DXGI_FORMAT_D32_FLOAT);
	//CLoadedModelInfo* arrow = CGameObject::LoadGeometryAndAnimationFromFile(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature, "Model/Warlock_weapon2.bin", NULL, 7);
	monsterLight = new CBulletObject(pd3dDevice, pd3dCommandList, m_pd3dGraphicsRootSignature, NULL, 0,1);
	//if (arrow) delete arrow;

	CreateShaderVariables(pd3dDevice, pd3dCommandList);
}

void CStage::ReleaseObjects()
{
	if (m_pd3dGraphicsRootSignature) m_pd3dGraphicsRootSignature->Release();
	if (m_pd3dCbvSrvDescriptorHeap) m_pd3dCbvSrvDescriptorHeap->Release();

	if (m_ppGameObjects)
	{
		for (int i = 0; i < m_nGameObjects; i++) if (m_ppGameObjects[i]) m_ppGameObjects[i]->Release();
		delete[] m_ppGameObjects;
	}


	if (m_ppShaders2)
	{
		for (int i = 0; i < m_nShaders2; i++)
		{
			m_ppShaders2[i]->ReleaseShaderVariables();
			m_ppShaders2[i]->ReleaseObjects();
			m_ppShaders2[i]->Release();
		}
		delete[] m_ppShaders2;
	}
	if (m_pShadowShader)
	{
		m_pShadowShader->ReleaseShaderVariables();
		m_pShadowShader->ReleaseObjects();
		m_pShadowShader->Release();
	}

	/*if (m_pShadowMapToViewport)
	{
		m_pShadowMapToViewport->ReleaseShaderVariables();
		m_pShadowMapToViewport->ReleaseObjects();
		m_pShadowMapToViewport->Release();
	}*/

	ReleaseShaderVariables();

	if (m_pLights) delete[] m_pLights;
}

ID3D12RootSignature* CStage::CreateGraphicsRootSignature(ID3D12Device* pd3dDevice)
{
	ID3D12RootSignature* pd3dGraphicsRootSignature = NULL;

	D3D12_DESCRIPTOR_RANGE pd3dDescriptorRanges[8];

	pd3dDescriptorRanges[0].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	pd3dDescriptorRanges[0].NumDescriptors = 1;
	pd3dDescriptorRanges[0].BaseShaderRegister = 6; //t6: gtxtAlbedoTexture
	pd3dDescriptorRanges[0].RegisterSpace = 0;
	pd3dDescriptorRanges[0].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	pd3dDescriptorRanges[1].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	pd3dDescriptorRanges[1].NumDescriptors = 1;
	pd3dDescriptorRanges[1].BaseShaderRegister = 7; //t7: gtxtSpecularTexture
	pd3dDescriptorRanges[1].RegisterSpace = 0;
	pd3dDescriptorRanges[1].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	pd3dDescriptorRanges[2].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	pd3dDescriptorRanges[2].NumDescriptors = 1;
	pd3dDescriptorRanges[2].BaseShaderRegister = 8; //t8: gtxtNormalTexture
	pd3dDescriptorRanges[2].RegisterSpace = 0;
	pd3dDescriptorRanges[2].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	pd3dDescriptorRanges[3].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	pd3dDescriptorRanges[3].NumDescriptors = 1;
	pd3dDescriptorRanges[3].BaseShaderRegister = 9; //t9: gtxtMetallicTexture
	pd3dDescriptorRanges[3].RegisterSpace = 0;
	pd3dDescriptorRanges[3].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	pd3dDescriptorRanges[4].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	pd3dDescriptorRanges[4].NumDescriptors = 1;
	pd3dDescriptorRanges[4].BaseShaderRegister = 10; //t10: gtxtEmissionTexture
	pd3dDescriptorRanges[4].RegisterSpace = 0;
	pd3dDescriptorRanges[4].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	pd3dDescriptorRanges[5].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	pd3dDescriptorRanges[5].NumDescriptors = 1;
	pd3dDescriptorRanges[5].BaseShaderRegister = 11; //t11: gtxtEmissionTexture
	pd3dDescriptorRanges[5].RegisterSpace = 0;
	pd3dDescriptorRanges[5].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	pd3dDescriptorRanges[6].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	pd3dDescriptorRanges[6].NumDescriptors = 1;
	pd3dDescriptorRanges[6].BaseShaderRegister = 12; //t12: gtxtEmissionTexture
	pd3dDescriptorRanges[6].RegisterSpace = 0;
	pd3dDescriptorRanges[6].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	pd3dDescriptorRanges[7].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	pd3dDescriptorRanges[7].NumDescriptors = MAX_DEPTH_TEXTURES;
	pd3dDescriptorRanges[7].BaseShaderRegister = 2; //Depth Buffer
	pd3dDescriptorRanges[7].RegisterSpace = 0;
	pd3dDescriptorRanges[7].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;


	D3D12_ROOT_PARAMETER pd3dRootParameters[14];

	pd3dRootParameters[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
	pd3dRootParameters[0].Descriptor.ShaderRegister = 1; //Camera
	pd3dRootParameters[0].Descriptor.RegisterSpace = 0;
	pd3dRootParameters[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;

	pd3dRootParameters[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_32BIT_CONSTANTS;
	pd3dRootParameters[1].Constants.Num32BitValues = 33;
	pd3dRootParameters[1].Constants.ShaderRegister = 2; //GameObject
	pd3dRootParameters[1].Constants.RegisterSpace = 0;
	pd3dRootParameters[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;

	pd3dRootParameters[2].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
	pd3dRootParameters[2].Descriptor.ShaderRegister = 4; //Lights
	pd3dRootParameters[2].Descriptor.RegisterSpace = 0;
	pd3dRootParameters[2].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;


	pd3dRootParameters[3].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	pd3dRootParameters[3].DescriptorTable.NumDescriptorRanges = 1;
	pd3dRootParameters[3].DescriptorTable.pDescriptorRanges = &(pd3dDescriptorRanges[0]);
	pd3dRootParameters[3].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;

	pd3dRootParameters[4].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	pd3dRootParameters[4].DescriptorTable.NumDescriptorRanges = 1;
	pd3dRootParameters[4].DescriptorTable.pDescriptorRanges = &(pd3dDescriptorRanges[1]);
	pd3dRootParameters[4].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;

	pd3dRootParameters[5].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	pd3dRootParameters[5].DescriptorTable.NumDescriptorRanges = 1;
	pd3dRootParameters[5].DescriptorTable.pDescriptorRanges = &(pd3dDescriptorRanges[2]);
	pd3dRootParameters[5].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;

	pd3dRootParameters[6].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	pd3dRootParameters[6].DescriptorTable.NumDescriptorRanges = 1;
	pd3dRootParameters[6].DescriptorTable.pDescriptorRanges = &(pd3dDescriptorRanges[3]);
	pd3dRootParameters[6].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;

	pd3dRootParameters[7].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	pd3dRootParameters[7].DescriptorTable.NumDescriptorRanges = 1;
	pd3dRootParameters[7].DescriptorTable.pDescriptorRanges = &(pd3dDescriptorRanges[4]);
	pd3dRootParameters[7].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;

	pd3dRootParameters[8].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	pd3dRootParameters[8].DescriptorTable.NumDescriptorRanges = 1;
	pd3dRootParameters[8].DescriptorTable.pDescriptorRanges = &(pd3dDescriptorRanges[5]);
	pd3dRootParameters[8].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;


	pd3dRootParameters[9].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	pd3dRootParameters[9].DescriptorTable.NumDescriptorRanges = 1;
	pd3dRootParameters[9].DescriptorTable.pDescriptorRanges = &(pd3dDescriptorRanges[6]);
	pd3dRootParameters[9].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;





	pd3dRootParameters[10].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	pd3dRootParameters[10].DescriptorTable.NumDescriptorRanges = 1;
	pd3dRootParameters[10].DescriptorTable.pDescriptorRanges = &pd3dDescriptorRanges[7]; //Depth Buffer
	pd3dRootParameters[10].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;

	pd3dRootParameters[11].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
	pd3dRootParameters[11].Descriptor.ShaderRegister = 7; //Skinned Bone Offsets
	pd3dRootParameters[11].Descriptor.RegisterSpace = 0;
	pd3dRootParameters[11].ShaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;

	pd3dRootParameters[12].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
	pd3dRootParameters[12].Descriptor.ShaderRegister = 8; //Skinned Bone Transforms
	pd3dRootParameters[12].Descriptor.RegisterSpace = 0;
	pd3dRootParameters[12].ShaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;


	pd3dRootParameters[13].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
	pd3dRootParameters[13].Descriptor.ShaderRegister = 6; //ToLight
	pd3dRootParameters[13].Descriptor.RegisterSpace = 0;
	pd3dRootParameters[13].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
	

	D3D12_STATIC_SAMPLER_DESC pd3dSamplerDescs[4];

	pd3dSamplerDescs[0].Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;
	pd3dSamplerDescs[0].AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	pd3dSamplerDescs[0].AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	pd3dSamplerDescs[0].AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	pd3dSamplerDescs[0].MipLODBias = 0;
	pd3dSamplerDescs[0].MaxAnisotropy = 1;
	pd3dSamplerDescs[0].ComparisonFunc = D3D12_COMPARISON_FUNC_ALWAYS;
	pd3dSamplerDescs[0].MinLOD = 0;
	pd3dSamplerDescs[0].MaxLOD = D3D12_FLOAT32_MAX;
	pd3dSamplerDescs[0].ShaderRegister = 0;
	pd3dSamplerDescs[0].RegisterSpace = 0;
	pd3dSamplerDescs[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;

	pd3dSamplerDescs[1].Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;
	pd3dSamplerDescs[1].AddressU = D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
	pd3dSamplerDescs[1].AddressV = D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
	pd3dSamplerDescs[1].AddressW = D3D12_TEXTURE_ADDRESS_MODE_CLAMP;
	pd3dSamplerDescs[1].MipLODBias = 0;
	pd3dSamplerDescs[1].MaxAnisotropy = 1;
	pd3dSamplerDescs[1].ComparisonFunc = D3D12_COMPARISON_FUNC_ALWAYS;
	pd3dSamplerDescs[1].MinLOD = 0;
	pd3dSamplerDescs[1].MaxLOD = D3D12_FLOAT32_MAX;
	pd3dSamplerDescs[1].ShaderRegister = 1;
	pd3dSamplerDescs[1].RegisterSpace = 0;
	pd3dSamplerDescs[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;

	pd3dSamplerDescs[2].Filter = D3D12_FILTER_COMPARISON_MIN_MAG_LINEAR_MIP_POINT;
	pd3dSamplerDescs[2].AddressU = D3D12_TEXTURE_ADDRESS_MODE_BORDER;
	pd3dSamplerDescs[2].AddressV = D3D12_TEXTURE_ADDRESS_MODE_BORDER;
	pd3dSamplerDescs[2].AddressW = D3D12_TEXTURE_ADDRESS_MODE_BORDER;
	pd3dSamplerDescs[2].MipLODBias = 0.0f;
	pd3dSamplerDescs[2].MaxAnisotropy = 1;
	pd3dSamplerDescs[2].ComparisonFunc = D3D12_COMPARISON_FUNC_LESS_EQUAL; //D3D12_COMPARISON_FUNC_LESS
	pd3dSamplerDescs[2].BorderColor = D3D12_STATIC_BORDER_COLOR_OPAQUE_WHITE; // D3D12_STATIC_BORDER_COLOR_OPAQUE_BLACK;
	pd3dSamplerDescs[2].MinLOD = 0;
	pd3dSamplerDescs[2].MaxLOD = D3D12_FLOAT32_MAX;
	pd3dSamplerDescs[2].ShaderRegister = 2;//
	pd3dSamplerDescs[2].RegisterSpace = 0;
	pd3dSamplerDescs[2].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;

	pd3dSamplerDescs[3].Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;
	pd3dSamplerDescs[3].AddressU = D3D12_TEXTURE_ADDRESS_MODE_BORDER;
	pd3dSamplerDescs[3].AddressV = D3D12_TEXTURE_ADDRESS_MODE_BORDER;
	pd3dSamplerDescs[3].AddressW = D3D12_TEXTURE_ADDRESS_MODE_BORDER;
	pd3dSamplerDescs[3].MipLODBias = 0.0f;
	pd3dSamplerDescs[3].MaxAnisotropy = 1;
	pd3dSamplerDescs[3].ComparisonFunc = D3D12_COMPARISON_FUNC_ALWAYS;
	pd3dSamplerDescs[3].BorderColor = D3D12_STATIC_BORDER_COLOR_OPAQUE_BLACK;
	pd3dSamplerDescs[3].MinLOD = 0;
	pd3dSamplerDescs[3].MaxLOD = D3D12_FLOAT32_MAX;
	pd3dSamplerDescs[3].ShaderRegister = 3;//
	pd3dSamplerDescs[3].RegisterSpace = 0;
	pd3dSamplerDescs[3].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;

	D3D12_ROOT_SIGNATURE_FLAGS d3dRootSignatureFlags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT | D3D12_ROOT_SIGNATURE_FLAG_DENY_HULL_SHADER_ROOT_ACCESS | D3D12_ROOT_SIGNATURE_FLAG_DENY_DOMAIN_SHADER_ROOT_ACCESS | D3D12_ROOT_SIGNATURE_FLAG_DENY_GEOMETRY_SHADER_ROOT_ACCESS;
	D3D12_ROOT_SIGNATURE_DESC d3dRootSignatureDesc;
	::ZeroMemory(&d3dRootSignatureDesc, sizeof(D3D12_ROOT_SIGNATURE_DESC));
	d3dRootSignatureDesc.NumParameters = _countof(pd3dRootParameters);
	d3dRootSignatureDesc.pParameters = pd3dRootParameters;
	d3dRootSignatureDesc.NumStaticSamplers = _countof(pd3dSamplerDescs);
	d3dRootSignatureDesc.pStaticSamplers = pd3dSamplerDescs;
	d3dRootSignatureDesc.Flags = d3dRootSignatureFlags;

	ID3DBlob* pd3dSignatureBlob = NULL;
	ID3DBlob* pd3dErrorBlob = NULL;
	D3D12SerializeRootSignature(&d3dRootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1, &pd3dSignatureBlob, &pd3dErrorBlob);
	pd3dDevice->CreateRootSignature(0, pd3dSignatureBlob->GetBufferPointer(), pd3dSignatureBlob->GetBufferSize(), __uuidof(ID3D12RootSignature), (void**)&pd3dGraphicsRootSignature);
	if (pd3dSignatureBlob) pd3dSignatureBlob->Release();
	if (pd3dErrorBlob) pd3dErrorBlob->Release();

	return(pd3dGraphicsRootSignature);
}

void CStage::CreateShaderVariables(ID3D12Device* pd3dDevice, ID3D12GraphicsCommandList* pd3dCommandList)
{
	UINT ncbElementBytes = ((sizeof(LIGHTS) + 255) & ~255); //256의 배수
	m_pd3dcbLights = ::CreateBufferResource(pd3dDevice, pd3dCommandList, NULL, ncbElementBytes, D3D12_HEAP_TYPE_UPLOAD, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER, NULL);

	m_pd3dcbLights->Map(0, NULL, (void**)&m_pcbMappedLights);
}

void CStage::UpdateShaderVariables(ID3D12GraphicsCommandList* pd3dCommandList)
{
	::memcpy(m_pcbMappedLights->m_pLights, m_pLights, sizeof(LIGHT) * m_nLights);
	::memcpy(&m_pcbMappedLights->m_xmf4GlobalAmbient, &m_xmf4GlobalAmbient, sizeof(XMFLOAT4));
	::memcpy(&m_pcbMappedLights->m_nLights, &m_nLights, sizeof(int));
}

void CStage::ReleaseShaderVariables()
{
	if (m_pd3dcbLights)
	{
		m_pd3dcbLights->Unmap(0, NULL);
		m_pd3dcbLights->Release();
	}
}

void CStage::ReleaseUploadBuffers()
{
	for (int i = 0; i < m_nShaders2; i++)
		m_ppShaders2[i]->ReleaseUploadBuffers();

	if (m_pShadowShader) 
		m_pShadowShader->ReleaseUploadBuffers();
}

void CStage::CreateCbvSrvDescriptorHeaps(ID3D12Device* pd3dDevice, int nConstantBufferViews, int nShaderResourceViews)
{
	D3D12_DESCRIPTOR_HEAP_DESC d3dDescriptorHeapDesc;
	d3dDescriptorHeapDesc.NumDescriptors = nConstantBufferViews + nShaderResourceViews; //CBVs + SRVs 
	d3dDescriptorHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	d3dDescriptorHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	d3dDescriptorHeapDesc.NodeMask = 0;
	pd3dDevice->CreateDescriptorHeap(&d3dDescriptorHeapDesc, __uuidof(ID3D12DescriptorHeap), (void**)&m_pd3dCbvSrvDescriptorHeap);

	m_d3dCbvCPUDescriptorNextHandle = m_d3dCbvCPUDescriptorStartHandle = m_pd3dCbvSrvDescriptorHeap->GetCPUDescriptorHandleForHeapStart();
	m_d3dCbvGPUDescriptorNextHandle = m_d3dCbvGPUDescriptorStartHandle = m_pd3dCbvSrvDescriptorHeap->GetGPUDescriptorHandleForHeapStart();
	m_d3dSrvCPUDescriptorNextHandle.ptr = m_d3dSrvCPUDescriptorStartHandle.ptr = m_d3dCbvCPUDescriptorStartHandle.ptr + (::gnCbvSrvDescriptorIncrementSize * nConstantBufferViews);
	m_d3dSrvGPUDescriptorNextHandle.ptr = m_d3dSrvGPUDescriptorStartHandle.ptr = m_d3dCbvGPUDescriptorStartHandle.ptr + (::gnCbvSrvDescriptorIncrementSize * nConstantBufferViews);
}

D3D12_GPU_DESCRIPTOR_HANDLE CStage::CreateConstantBufferViews(ID3D12Device* pd3dDevice, int nConstantBufferViews, ID3D12Resource* pd3dConstantBuffers, UINT nStride)
{
	D3D12_GPU_DESCRIPTOR_HANDLE d3dCbvGPUDescriptorHandle = m_d3dCbvGPUDescriptorNextHandle;
	D3D12_GPU_VIRTUAL_ADDRESS d3dGpuVirtualAddress = pd3dConstantBuffers->GetGPUVirtualAddress();
	D3D12_CONSTANT_BUFFER_VIEW_DESC d3dCBVDesc;
	d3dCBVDesc.SizeInBytes = nStride;
	for (int j = 0; j < nConstantBufferViews; j++)
	{
		d3dCBVDesc.BufferLocation = d3dGpuVirtualAddress + (nStride * j);
		m_d3dCbvCPUDescriptorNextHandle.ptr = m_d3dCbvCPUDescriptorNextHandle.ptr + ::gnCbvSrvDescriptorIncrementSize;
		pd3dDevice->CreateConstantBufferView(&d3dCBVDesc, m_d3dCbvCPUDescriptorNextHandle);
		m_d3dCbvGPUDescriptorNextHandle.ptr = m_d3dCbvGPUDescriptorNextHandle.ptr + ::gnCbvSrvDescriptorIncrementSize;
	}
	return(d3dCbvGPUDescriptorHandle);
}

void CStage::CreateShaderResourceViews(ID3D12Device* pd3dDevice, CTexture* pTexture, UINT nDescriptorHeapIndex, UINT nRootParameterStartIndex)
{
	m_d3dSrvCPUDescriptorNextHandle.ptr += (::gnCbvSrvDescriptorIncrementSize * nDescriptorHeapIndex);
	m_d3dSrvGPUDescriptorNextHandle.ptr += (::gnCbvSrvDescriptorIncrementSize * nDescriptorHeapIndex);

	if (pTexture)
	{
		int nTextures = pTexture->GetTextures();
		for (int i = 0; i < nTextures; i++)
		{
			ID3D12Resource* pShaderResource = pTexture->GetResource(i);
			D3D12_SHADER_RESOURCE_VIEW_DESC d3dShaderResourceViewDesc = pTexture->GetShaderResourceViewDesc(i);
			pd3dDevice->CreateShaderResourceView(pShaderResource, &d3dShaderResourceViewDesc, m_d3dSrvCPUDescriptorNextHandle);//0307 pShaderResource가 null
			m_d3dSrvCPUDescriptorNextHandle.ptr += ::gnCbvSrvDescriptorIncrementSize;
			pTexture->SetGpuDescriptorHandle(i, m_d3dSrvGPUDescriptorNextHandle);
			m_d3dSrvGPUDescriptorNextHandle.ptr += ::gnCbvSrvDescriptorIncrementSize;
		}
	}
	int nRootParameters = pTexture->GetRootParameters();
	for (int j = 0; j < nRootParameters; j++)
		pTexture->SetRootParameterIndex(j, nRootParameterStartIndex + j);
}

bool CStage::OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	return(false);
}

bool CStage::OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	switch (nMessageID)
	{
	case WM_KEYDOWN:
		break;
	default:
		break;
	}
	return(false);
}

bool CStage::ProcessInput(UCHAR* pKeysBuffer)
{
	return(false);
}

void CStage::AnimateObjects(float fTimeElapsed)
{
	m_fElapsedTime = fTimeElapsed;

	m_pPlayer->boundingAnimate(fTimeElapsed);
	m_ppShaders2[0]->AnimateObjects(fTimeElapsed);

	

	if (m_pLights)
	{
		m_pLights[4].m_xmf3Position = m_pPlayer->GetPosition();
		m_pLights[4].m_xmf3Position.y = m_pPlayer->GetPosition().y + 10;
		m_pLights[4].m_xmf3Direction = m_pPlayer->GetLookVector();

		/*m_fLightRotationAngle += fTimeElapsed * 0.25f;
		XMMATRIX xmmtxRotation = XMMatrixRotationY(fTimeElapsed * 0.25f);
		XMStoreFloat3(&m_pLights[1].m_xmf3Direction, XMVector3TransformNormal(XMLoadFloat3(&m_pLights[1].m_xmf3Direction), xmmtxRotation));*/
		m_pLights[1].m_bEnable = false;

		//23.02.12
		for (int i = 5; i < MAX_LIGHTS; ++i)
			m_pLights[i].m_bEnable = wakeUp;
		//
	}

	static float fAngle = 0.0f;
	fAngle += 1.50f;
	XMFLOAT4X4 xmf4x4Rotate = Matrix4x4::Rotate(0.0f, -fAngle, 0.0f);
	XMFLOAT3 xmf3Position = Vector3::TransformCoord(XMFLOAT3(50.0f, 0.0f, 0.0f), xmf4x4Rotate);
}
void CStage::OnPreRender(ID3D12GraphicsCommandList* pd3dCommandList,LIGHT* light, ID3D12DescriptorHeap* m_pd3dCbvSrvDescriptorHeap,int num)
{
	if (1 == num)
	{
		if (m_pDepthRenderShader)
		{
			m_pDepthRenderShader->m_pd3dCbvSrvDescriptorHeap = m_pd3dCbvSrvDescriptorHeap;
			m_pDepthRenderShader->PrepareShadowMap(pd3dCommandList, light);
		}
	}
	else if(2==num)
	{
		if (m_pDepthRenderPlShader)
		{
			m_pDepthRenderPlShader->m_pd3dCbvSrvDescriptorHeap = m_pd3dCbvSrvDescriptorHeap;
			m_pDepthRenderPlShader->PrepareShadowMap(pd3dCommandList, light);
		}
	}
	else if (3== num)
	{
		if (m_pDepthRenderObjShader)
		{
			m_pDepthRenderObjShader->m_pd3dCbvSrvDescriptorHeap = m_pd3dCbvSrvDescriptorHeap;
			m_pDepthRenderObjShader->PrepareShadowMap(pd3dCommandList, light);
		}
	}

	/*m_pDepthRenderObjShader->m_pd3dCbvSrvDescriptorHeap = m_pd3dCbvSrvDescriptorHeap;
	m_pDepthRenderObjShader->PrepareShadowMap(pd3dCommandList, light);*/
}
void CStage::OnPrepareRender(ID3D12GraphicsCommandList* pd3dCommandList)
{
	pd3dCommandList->SetGraphicsRootSignature(m_pd3dGraphicsRootSignature);

	UpdateShaderVariables(pd3dCommandList);

	//if (m_pd3dcbMaterials)
	//{
	//	D3D12_GPU_VIRTUAL_ADDRESS d3dcbMaterialsGpuVirtualAddress = m_pd3dcbMaterials->GetGPUVirtualAddress();
	//	pd3dCommandList->SetGraphicsRootConstantBufferView(3, d3dcbMaterialsGpuVirtualAddress); //Materials
	//}
	if (m_pd3dcbLights)
	{
		D3D12_GPU_VIRTUAL_ADDRESS d3dcbLightsGpuVirtualAddress = m_pd3dcbLights->GetGPUVirtualAddress();
		pd3dCommandList->SetGraphicsRootConstantBufferView(ROOT_PARAMETER_LIGHT, d3dcbLightsGpuVirtualAddress); //Lights
	}
}


void CStage::Render(ID3D12GraphicsCommandList* pd3dCommandList, CCamera* pCamera)
{

	if (m_pd3dGraphicsRootSignature)
		pd3dCommandList->SetGraphicsRootSignature(m_pd3dGraphicsRootSignature);

	//OnPrepareRender(pd3dCommandList);

	if(m_pDepthRenderShader)
		m_pDepthRenderShader->UpdateShaderVariables(pd3dCommandList);
	if (m_pDepthRenderPlShader)
		m_pDepthRenderPlShader->UpdateShaderVariables(pd3dCommandList);
	if (m_pDepthRenderObjShader)
		m_pDepthRenderObjShader->UpdateShaderVariables(pd3dCommandList);

	if (m_pd3dCbvSrvDescriptorHeap)
		pd3dCommandList->SetDescriptorHeaps(1, &m_pd3dCbvSrvDescriptorHeap);

	pCamera->SetViewportsAndScissorRects(pd3dCommandList);
	pCamera->UpdateShaderVariables(pd3dCommandList);

	UpdateShaderVariables(pd3dCommandList);//인형이 까맣게

	D3D12_GPU_VIRTUAL_ADDRESS d3dcbLightsGpuVirtualAddress = m_pd3dcbLights->GetGPUVirtualAddress();
	pd3dCommandList->SetGraphicsRootConstantBufferView(ROOT_PARAMETER_LIGHT, d3dcbLightsGpuVirtualAddress); //Lights


	monsterLight->lightRender(pd3dCommandList, m_pd3dGraphicsRootSignature, m_pd3dPipelineState, pCamera);

	m_ppShaders2[0]->Render(pd3dCommandList, pCamera);

	if (m_pShadowShader)
		m_pShadowShader->Render(pd3dCommandList, pCamera);
	if (m_pShadowPlShader)
		m_pShadowPlShader->Render(pd3dCommandList, pCamera);
	if (m_pShadowObjShader)
		m_pShadowObjShader->Render(pd3dCommandList, pCamera);

	/*if (m_pShadowMapToViewport) 
		m_pShadowMapToViewport->Render(pd3dCommandList, pCamera);

	pCamera->SetViewportsAndScissorRects(pd3dCommandList);
	pCamera->UpdateShaderVariables(pd3dCommandList);*/
}

void CStage::UpdateBoundingBox()
{

}

void CStage::CheckObjectByObjectCollisions(float fTimeElapsed)
{
	XMFLOAT3 Vel = m_pPlayer->GetVelocity();
	XMFLOAT3 MovVec = Vector3::ScalarProduct(Vel, fTimeElapsed, false);
	BoundingBox pBox = m_pPlayer->m_xmOOBB;

	for (int i = 0; i < m_ppShaders2[0]->m_nObjects - 1; i++)
	{
		BoundingBox oBox = m_ppShaders2[0]->m_ppObjects[i]->m_xmOOBB;

		if (pBox.Intersects(oBox))
		{
			if (0 == strncmp(m_ppShaders2[0]->m_ppObjects[i]->m_pstrName, "Dense_Floor_mesh", 16) || 0 == strncmp(m_ppShaders2[0]->m_ppObjects[i]->m_pstrName, "Ceiling_base_mesh", 17)) {
				// if (pBox.Center.y > oBox.Center.y) {
				XMFLOAT3 Pos = m_pPlayer->GetPosition();
				Pos.y = oBox.Center.y + oBox.Extents.y + pBox.Extents.y;
				m_pPlayer->SetPosition(Pos);
				continue;
			}

			//cout << Calculate_Direction(oBox, pBox).x << ", " << Calculate_Direction(oBox, pBox).y << ", " << Calculate_Direction(oBox, pBox).z << endl; // 충돌한 방향 벡터 출력 

			/*cout << "Name: " << m_ppShaders2[0]->m_ppObjects[i]->m_pstrName << "\nCenter: " << oBox.Center.x << ", " << oBox.Center.y << ", " << oBox.Center.z <<
				"\nExtents: " << oBox.Extents.x << ", " << oBox.Extents.y << ", " << oBox.Extents.z << endl;*/

			XMFLOAT3 ObjLook = { 0,0,0 };
			if (oBox.Center.x - oBox.Extents.x < pBox.Center.x && oBox.Center.x + oBox.Extents.x > pBox.Center.x) {
				if (oBox.Center.z < pBox.Center.z) ObjLook = { 0,0,1 };
				else ObjLook = { 0, 0, -1 };
			}
			else if (oBox.Center.x < pBox.Center.x) ObjLook = { 1,0,0 };
			else ObjLook = { -1, 0, 0 };

			if (Vector3::DotProduct(MovVec, ObjLook) > 0)
				continue;

			XMFLOAT3 ReflectVec = Vector3::ScalarProduct(MovVec, -1, false);

			m_pPlayer->Move(ReflectVec, false);

			MovVec = GetReflectVec(ObjLook, MovVec);
			m_pPlayer->Move(MovVec, false);

		}
	}
}

XMFLOAT3 CStage::GetReflectVec(XMFLOAT3 ObjLook, XMFLOAT3 MovVec)
{
	float Dot = Vector3::DotProduct(MovVec, ObjLook);
	XMFLOAT3 Nor = Vector3::ScalarProduct(ObjLook, Dot, false);
	XMFLOAT3 SlidingVec = Vector3::Subtract(MovVec, Nor);
	return SlidingVec;
}


XMFLOAT3 CStage::Calculate_Direction(BoundingBox& pBouningBoxA, BoundingBox& pBouningBoxB)
{
	XMVECTOR xmV1min = XMLoadFloat3(&pBouningBoxA.Center) - XMLoadFloat3(&pBouningBoxA.Extents);
	XMVECTOR xmV1max = XMLoadFloat3(&pBouningBoxA.Center) + XMLoadFloat3(&pBouningBoxA.Extents);
	XMVECTOR xmV2min = XMLoadFloat3(&pBouningBoxB.Center) - XMLoadFloat3(&pBouningBoxB.Extents);
	XMVECTOR xmV2max = XMLoadFloat3(&pBouningBoxB.Center) + XMLoadFloat3(&pBouningBoxB.Extents);

	bool bIntersect = XMVector3GreaterOrEqual(xmV1min, xmV2max) || XMVector3GreaterOrEqual(xmV2min, xmV1max);

	if (bIntersect)
	{
		return XMFLOAT3(0, 0, 0); // 충돌하지 않음
	}

	XMFLOAT3 xmf3Direction = { 0,0,0 };
	XMFLOAT3 xmf3Subtraction = { 0,0,0 };

	XMStoreFloat3(&xmf3Subtraction, XMVectorSubtract(xmV2max, xmV1min));
	if (fabs(xmf3Subtraction.x) < fabs(xmf3Direction.x) || xmf3Direction.x == 0)
	{
		xmf3Direction.x = xmf3Subtraction.x;
	}
	XMStoreFloat3(&xmf3Subtraction, XMVectorSubtract(xmV1max, xmV2min));
	if (fabs(xmf3Subtraction.x) < fabs(xmf3Direction.x) || xmf3Direction.x == 0)
	{
		xmf3Direction.x = -xmf3Subtraction.x;
	}

	XMStoreFloat3(&xmf3Subtraction, XMVectorSubtract(xmV2max, xmV1min));
	if (fabs(xmf3Subtraction.y) < fabs(xmf3Direction.y) || xmf3Direction.y == 0)
	{
		xmf3Direction.y = xmf3Subtraction.y;
	}
	XMStoreFloat3(&xmf3Subtraction, XMVectorSubtract(xmV1max, xmV2min));
	if (fabs(xmf3Subtraction.y) < fabs(xmf3Direction.y) || xmf3Direction.y == 0)
	{
		xmf3Direction.y = -xmf3Subtraction.y;
	}

	XMStoreFloat3(&xmf3Subtraction, XMVectorSubtract(xmV2max, xmV1min));
	if (fabs(xmf3Subtraction.z) < fabs(xmf3Direction.z) || xmf3Direction.z == 0)
	{
		xmf3Direction.z = xmf3Subtraction.z;
	}
	XMStoreFloat3(&xmf3Subtraction, XMVectorSubtract(xmV1max, xmV2min));
	if (fabs(xmf3Subtraction.z) < fabs(xmf3Direction.z) || xmf3Direction.z == 0)
	{
		xmf3Direction.z = -xmf3Subtraction.z;
	}

	XMStoreFloat3(&xmf3Direction, XMVector3Normalize(XMLoadFloat3(&xmf3Direction)));
	return xmf3Direction;
}

XMFLOAT3 CStage::Get_BoundingBoxVertex(BoundingBox& pBoundingbox, int nIndex)
{
	assert(nIndex >= 0 && nIndex <= 7);
	XMFLOAT3		xmfVertex;
	XMVECTOR	xmvCenter = XMLoadFloat3(&pBoundingbox.Center);
	XMVECTOR	xmvExtents = XMLoadFloat3(&pBoundingbox.Extents);

	static const XMVECTORF32 s_vCorners[] =
	{
		{ -1.0f, -1.0f, -1.0f, 0.0f },
		{ -1.0f, -1.0f,  1.0f, 0.0f },
		{ -1.0f,  1.0f, -1.0f, 0.0f },
		{ -1.0f,  1.0f,  1.0f, 0.0f },
		{  1.0f, -1.0f, -1.0f, 0.0f },
		{  1.0f, -1.0f,  1.0f, 0.0f },
		{  1.0f,  1.0f, -1.0f, 0.0f },
		{  1.0f,  1.0f,  1.0f, 0.0f }
	};

	xmvCenter = XMVectorAdd(xmvCenter, XMVectorMultiply(xmvExtents, s_vCorners[nIndex]));

	XMStoreFloat3(&xmfVertex, xmvCenter);
	return xmfVertex;
}