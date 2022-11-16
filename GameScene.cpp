#include "GameScene.h"
#include <cassert>

using namespace DirectX;

GameScene::~GameScene()
{
	delete spriteBG;
	delete particleMan;
}

void GameScene::Initialize(DirectXCommon* dxCommon, Input* input)
{
	// nullptrチェック
	assert(dxCommon);
	assert(input);

	this->dxCommon = dxCommon;
	this->input = input;

	// デバッグテキスト用テクスチャ読み込み
	Sprite::LoadTexture(debugTextTexNumber, L"Resources/debugfont.png");
	// デバッグテキスト初期化
	debugText.Initialize(debugTextTexNumber);

	// テクスチャ読み込み
	Sprite::LoadTexture(1, L"Resources/background.png");
	Sprite::LoadTexture(2, L"Resources/texture.png");

	// 背景スプライト生成
	spriteBG = Sprite::Create(1, { 0.0f,0.0f });

	// 3Dオブジェクト生成
	particleMan = ParticleManager::Create();
	particleMan->Update();

	object.resize(2);
	object[0] = Object3d::Create();
	object[1] = Object3d::Create();
	object[1]->SetPosition({ -2.0f,0,0 });

	objectGrass.resize(15);
	for (size_t i = 0; i < objectGrass.size(); i++)
	{
		objectGrass[i] = Object3d::Create();

		const float md_pos = 4.0f;
		objectGrass[i]->SetPosition({
			(float)rand() / RAND_MAX * md_pos - md_pos / 2.0f, 0,
			(float)rand() / RAND_MAX * md_pos - md_pos / 2.0f });
	}
}

void GameScene::Update()
{
	// カメラ移動
	if (input->PushKey(DIK_W) || input->PushKey(DIK_S) || input->PushKey(DIK_D) || input->PushKey(DIK_A))
	{
		XMFLOAT3 move = {
			(float)(input->PushKey(DIK_D) - input->PushKey(DIK_A)) * 0.8f,
			(float)(input->PushKey(DIK_W) - input->PushKey(DIK_S)) * 0.8f,
			0.0f };

		Object3d::CameraMoveEyeVector(move);
		ParticleManager::CameraMoveEyeVector(move);
	}

	if (input->TriggerKey(DIK_1)) { scene = Billboard; }
	if (input->TriggerKey(DIK_2)) { scene = Grass; }
	if (input->TriggerKey(DIK_3)) { scene = Particle; }

	switch (scene)
	{
	case GameScene::Billboard:
		object[0]->Update(1);
		object[1]->Update(0);
		break;
	case GameScene::Grass:
		for (Object3d* obj : objectGrass) { obj->Update(2); }
		break;
	case GameScene::Particle:
		// -5.0f~+5.0f:xyz
		const float md_pos = 10.0f;
		XMFLOAT3 pos =
		{
			(float)rand() / RAND_MAX * md_pos - md_pos / 2.0f,
			(float)rand() / RAND_MAX * md_pos - md_pos / 2.0f,
			(float)rand() / RAND_MAX * md_pos - md_pos / 2.0f
		};
		// -0.05f~+0.05f:xyz
		const float md_vel = 0.1f;
		XMFLOAT3 vel =
		{
			(float)rand() / RAND_MAX * md_vel - md_vel / 2.0f,
			(float)rand() / RAND_MAX * md_vel - md_vel / 2.0f,
			(float)rand() / RAND_MAX * md_vel - md_vel / 2.0f
		};
		// -0.001f~0:y
		XMFLOAT3 acc{};
		const float md_acc = 0.001f;
		acc.y = -(float)rand() / RAND_MAX * md_acc;

		particleMan->Add(60, pos, {0,-0.1f,0}, {0,-0.01f,0}, 1.0f, 0.0f);
		particleMan->Update();
		break;
	}
}

void GameScene::Draw()
{
	// コマンドリストの取得
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(cmdList);
	// 背景スプライト描画
	spriteBG->Draw();

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	switch (scene)
	{
	case GameScene::Billboard:
		// 3Dオブジェクト描画処理
		Object3d::PreDraw(cmdList);
		object[0]->Draw();
		object[1]->Draw();
		Object3d::PostDraw();
		break;
	case GameScene::Grass:
		Object3d::PreDraw(cmdList);
		for (Object3d* obj : objectGrass) { obj->Draw(); }
		Object3d::PostDraw();
		break;
	case GameScene::Particle:
		// パーティクル描画処理
		ParticleManager::PreDraw(cmdList);
		particleMan->Draw();
		ParticleManager::PostDraw();
		break;
	}

#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(cmdList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// デバッグテキストの描画
	debugText.DrawAll(cmdList);

	// スプライト描画後処理
	Sprite::PostDraw();
#pragma endregion
}
