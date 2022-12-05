#pragma once
#include <DirectXMath.h>
#include <d3dx12.h>
#include <wrl.h>

class Light
{
private:
	// Microsoft::WRL::を省略
	template<class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

	struct ConstBufferData
	{
		XMVECTOR lightv; // ライトへの方向を表すベクトル
		XMFLOAT3 lightcolor; // ライトの色
	};

	static ID3D12Device* device;
	ComPtr<ID3D12Resource> constBuff;
	XMVECTOR lightdir = { 1,0,0,0 }; // ライト光線方向
	XMFLOAT3 lightcolor = { 1,1,1 }; // ライト色
	bool dirty = false; // ダーティフラグ
	void Initialize();
public:
	static void StaticInitialize(ID3D12Device* device);
	static Light* Create();
	void TransferConstBuffer();
	void Update();
	void Draw(ID3D12GraphicsCommandList* cmdList, UINT rootParameterIndex);
	void SetLightDir(const XMVECTOR& lightdir);
	void SetLightColor(const XMFLOAT3& lightcolor);
};