#include "GameScene.h"
#include"../SceneManager.h"

#include"../../Object/Ground/Ground.h"
#include"../../Object/BackGround/BackGround.h"
#include"../../Object/Cannon/Cannon.h"
#include"../../Object/Player/Player.h"

void GameScene::Event()
{
	//タイトルに戻る
	if (GetAsyncKeyState('T') & 0x8000)
	{
		SceneManager::Instance().SetNextScene
		(
			SceneManager::SceneType::Title
		);
	}

//===================================================================
//カメラの処理
//===================================================================
	static Math::Vector3 _camerapos = { 0,1,-5 };

	//座標行列
	Math::Matrix _transmat = Math::Matrix::CreateTranslation(_camerapos + m_Player->GetPos());
	//座標作成
	m_camera->SetCameraMatrix(_transmat);
}

void GameScene::Init()
{
//===================================================================
//Object追加
//===================================================================
//===カメラ===
	//実体化
				  //↓Uniqueポインタ(※1)で管理されている
	//(※1)Uniqueポインタは領域をさすことができるポインタを自分だけにする
	m_camera = std::make_unique<KdCamera>();

//===地面===
	//①ポインタを用意
	std::shared_ptr<Ground>	_ground;
	//②実体化
	_ground = std::make_shared<Ground>();
	//③初期化
	//※黒崎はコンストラクタでInit関数を呼んでいるので不要
	//④ObjectListに追加
	m_objList.push_back(_ground);

//===プレイヤー===
	//↓メンバー変数にポインタを用意したため不必要
	//std::shared_ptr<Player>	_player;
	m_Player = std::make_shared<Player>();
	m_objList.push_back(m_Player);

//===背景===
	//①ポインタを用意
	std::shared_ptr<BackGround>	_background;
	//②実体化
	_background = std::make_shared<BackGround>();
	//③初期化
	//※黒崎はコンストラクタでInit関数を呼んでいるので不要
	//④ObjectListに追加
	m_objList.push_back(_background);

//===背景===
	//①ポインタを用意
	std::shared_ptr<Cannon>	_Cannon;
	//②実体化
	_Cannon = std::make_shared<Cannon>();
	//③初期化
	//※黒崎はコンストラクタでInit関数を呼んでいるので不要
	//④ObjectListに追加
	m_objList.push_back(_Cannon);

}