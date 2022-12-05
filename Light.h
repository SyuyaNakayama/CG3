#pragma once
#include <DirectXMath.h>
#include <d3dx12.h>
#include <wrl.h>

class Light
{
private:
	// Microsoft::WRL::���ȗ�
	template<class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

	struct ConstBufferData
	{
		XMVECTOR lightv; // ���C�g�ւ̕�����\���x�N�g��
		XMFLOAT3 lightcolor; // ���C�g�̐F
	};

	static ID3D12Device* device;
	ComPtr<ID3D12Resource> constBuff;
	XMVECTOR lightdir = { 1,0,0,0 }; // ���C�g��������
	XMFLOAT3 lightcolor = { 1,1,1 }; // ���C�g�F
	bool dirty = false; // �_�[�e�B�t���O
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