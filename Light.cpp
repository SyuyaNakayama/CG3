#include "Light.h"
#include <cassert>
using namespace DirectX;

ID3D12Device* Light::device = nullptr;

void Light::StaticInitialize(ID3D12Device* device)
{
	assert(!Light::device);
	assert(device);
	Light::device = device;
}

Light* Light::Create()
{
	Light* instance = new Light();
	instance->Initialize();
	return instance;
}

void Light::TransferConstBuffer()
{
	// 定数バッファのマッピング
	ConstBufferData* constMap = nullptr;
	HRESULT result = constBuff->Map(0, nullptr, (void**)&constMap);
	assert(SUCCEEDED(result));

	constMap->lightv = -lightdir;
	constMap->lightcolor = lightcolor;
	constBuff->Unmap(0, nullptr);
}

void Light::Initialize()
{
	// ヒーププロパティ
	CD3DX12_HEAP_PROPERTIES heapProps = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	// リソース設定
	CD3DX12_RESOURCE_DESC resourceDesc =
		CD3DX12_RESOURCE_DESC::Buffer((sizeof(ConstBufferData) + 0xff) & ~0xff);

	// 定数バッファの生成
	HRESULT result = device->CreateCommittedResource(
		&heapProps, D3D12_HEAP_FLAG_NONE, &resourceDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr,
		IID_PPV_ARGS(&constBuff));
	assert(SUCCEEDED(result));

	TransferConstBuffer();
}

void Light::Update()
{
	if (dirty)
	{
		TransferConstBuffer();
		dirty = false;
	}
}

void Light::Draw(ID3D12GraphicsCommandList* cmdList, UINT rootParameterIndex)
{
	cmdList->SetGraphicsRootConstantBufferView(rootParameterIndex,
		constBuff->GetGPUVirtualAddress());
}

void Light::SetLightDir(const XMVECTOR& lightdir)
{
	this->lightdir = XMVector3Normalize(lightdir);
	dirty = true;
}

void Light::SetLightColor(const XMFLOAT3& lightcolor)
{
	this->lightcolor = lightcolor;
	dirty = true;
}