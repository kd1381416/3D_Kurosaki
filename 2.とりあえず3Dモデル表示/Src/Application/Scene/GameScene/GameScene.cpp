#include"GameScene.h"

#include"../SceneManager.h"

void GameScene::Init()
{
	//===================================================================
	//カメラの初期化
	//===================================================================
	m_Camera.SetProjectionMatrix(60);		//カメラの視野角

	//===================================================================
	//船の初期化
	//===================================================================
	m_Model.Load("Asset/Models/Ship/Ship.gltf");
}

void GameScene::Update()
{
//===================================================================
//カメラ
//===================================================================
	Math::Vector3 _campos = { 0,3,-40 };

//===================================================================
//船の処理
//===================================================================
	if (GetAsyncKeyState('W') & 0x8000)
	{
		m_Pos.z += 1.0f;
	}
	if (GetAsyncKeyState('S') & 0x8000)
	{
		m_Pos.z -= 1.0f;
	}
	if (GetAsyncKeyState('A') & 0x8000)
	{
		m_AngY -= 1.0f;
	}
	if (GetAsyncKeyState('D') & 0x8000)
	{
		m_AngY += 1.0f;
	}

	if(GetAsyncKeyState(VK_SPACE)&0x8000)
	{
		SceneManager::Instans().SetNextScene(SceneManager::SceneType::Title);
	}


//===================================================================
//行列作成
//===================================================================
	//カメラ
	Math::Matrix _transmat = Math::Matrix::CreateTranslation(_campos);
	m_Camera.SetCameraMatrix(_transmat);
}

//===================================================================
//3D描画
//===================================================================
void GameScene::DrawLit()
{
//===================================================================
//カメラ描画
//===================================================================
	m_Camera.SetToShader();

//===================================================================
//船描画
//===================================================================
	//座標行列
	Math::Matrix _transmat = Math::Matrix::CreateTranslation(m_Pos);
	//回転行列
	Math::Matrix _rotatmat = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_AngY));
	//ワールド行列
	Math::Matrix _worldmat = _rotatmat * _transmat;

	KdShaderManager::Instance().m_StandardShader.DrawModel(m_Model,_worldmat);
}

//===================================================================
//2D描画
//===================================================================
void GameScene::DrawSprite()
{
}

void GameScene::Release()
{
}