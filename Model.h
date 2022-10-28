#pragma once
#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dx12.h>
#include <vector>

using namespace std;

class Model
{
private:
	// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;

public:
	// ���_�f�[�^�\����
	struct VertexPosNormalUv
	{
		XMFLOAT3 pos; // xyz���W
		XMFLOAT3 normal; // �@���x�N�g��
		XMFLOAT2 uv;  // uv���W
	};

	// �}�e���A��
	struct Material
	{
		string name;
		XMFLOAT3 ambient;
		XMFLOAT3 diffuse;
		XMFLOAT3 specular;
		float alpha;
		string textureFilename;

		Material()
		{
			ambient = { 0.3f,0.3f,0.3f };
			diffuse = {};
			specular = {};
			alpha = 1.0f;
		}
	};

private:
	// �f�o�C�X
	static ID3D12Device* device;
	// �R�}���h���X�g
	static ID3D12GraphicsCommandList* cmdList;
	// ���_�o�b�t�@
	static ComPtr<ID3D12Resource> vertBuff;
	// �C���f�b�N�X�o�b�t�@
	static ComPtr<ID3D12Resource> indexBuff;
	// ���_�o�b�t�@�r���[
	static D3D12_VERTEX_BUFFER_VIEW vbView;
	// �C���f�b�N�X�o�b�t�@�r���[
	static D3D12_INDEX_BUFFER_VIEW ibView;
	// �e�N�X�`���o�b�t�@
	static ComPtr<ID3D12Resource> texbuff;
	// ���_�f�[�^�z��
	static vector<VertexPosNormalUv> vertices;
	// ���_�C���f�b�N�X�z��
	static vector<unsigned short> indices;
	// �}�e���A��
	static Material material;
	// �V�F�[�_���\�[�X�r���[�̃n���h��(CPU)
	static CD3DX12_CPU_DESCRIPTOR_HANDLE cpuDescHandleSRV;
	// �V�F�[�_���\�[�X�r���[�̃n���h��(CPU)
	static CD3DX12_GPU_DESCRIPTOR_HANDLE gpuDescHandleSRV;
	// �f�X�N���v�^�q�[�v
	static ComPtr<ID3D12DescriptorHeap> descHeap;
	// �f�X�N���v�^�T�C�Y
	static UINT descriptorHandleIncrementSize;
	// �p�C�v���C���X�e�[�g�I�u�W�F�N�g
	static ComPtr<ID3D12PipelineState> pipelinestate;
	// ���[�g�V�O�l�`��
	static ComPtr<ID3D12RootSignature> rootsignature;

public:
	static void StaticInitialize(ID3D12Device* device);
	/// <summary>
	/// �`��O����
	/// </summary>
	/// <param name="cmdList">�`��R�}���h���X�g</param>
	static void PreDraw(ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	/// �`��㏈��
	/// </summary>
	static void PostDraw();
	
	/// <summary>
	/// �f�X�N���v�^�q�[�v�̏�����
	/// </summary>
	static void InitializeDescriptorHeap();

	/// <summary>
	/// �O���t�B�b�N�p�C�v���C������
	/// </summary>
	/// <returns>����</returns>
	static void InitializeGraphicsPipeline();

	/// <summary>
	/// �e�N�X�`���ǂݍ���
	/// </summary>
	static void LoadTexture(const string& DIRECTORY_PATH, const string& FILENAME);

	/// <summary>
	/// �}�e���A���ǂݍ���
	/// </summary>
	void LoadMaterial(const string& DIRECTORY_PATH, const string& FILENAME);
	
	Material GetMaterial() { return material; }

	ID3D12GraphicsCommandList* GetCommandList() { return cmdList; }
	/// <summary>
	/// ���f���쐬
	/// </summary>
	void Initialize();
	 
	void Create(string modelName);

	void Draw();
};