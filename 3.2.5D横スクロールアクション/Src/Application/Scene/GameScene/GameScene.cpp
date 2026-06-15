#include "GameScene.h"
#include"../SceneManager.h"

#include"../../Object/Ground/Ground.h"
#include"../../Object/BackGround/BackGround.h"
#include"../../Object/Cannon/Cannon.h"
#include"../../Object/Player/Player.h"
#include"../../Object/Enemy/Enemy.h"
#include"../../Object/Ghost/Ghost.h"

void GameScene::Event()
{
//===================================================================
//デバック用
//===================================================================
	//現在のオブジェクト数
	KdDebugGUI::Instance().ClearLog();
	KdDebugGUI::Instance().AddLog("%d", (int)m_objList.size());

	//タイトルに戻る
	if (GetAsyncKeyState('T') & 0x8000)
	{
		SceneManager::Instance().SetNextScene
		(
			SceneManager::SceneType::Title
		);
	}

//===================================================================
//ホーミング(自作)
//===================================================================
	//m_Ghost->SetHoomingPos(m_Player->GetPos());

//===================================================================
//カメラの処理
//===================================================================
	static Math::Vector3 _camerapos = { 0,1,-5 };

	//座標行列
	Math::Matrix _transmat = Math::Matrix::CreateTranslation(_camerapos + m_Player->GetPos());
	//座標作成
	m_camera->SetCameraMatrix(_transmat);

//===================================================================
//被写界深度
//===================================================================
	//				　↓ピントを合わせる距離,手前,奥
	m_camera->SetFocus(5, 3, 8);
}

void GameScene::Init()
{
//===================================================================
//平行光(ディレクショナルライト)
//===================================================================
	//																     ↓光の方向	  ↓色	
	KdShaderManager::Instance().WorkAmbientController().SetDirLight({ 0,-1,0.1 }, { 0,0,0 });

//===================================================================
//Fog(霧)
//===================================================================
	//																  ↓距離 ↓高さ			
	KdShaderManager::Instance().WorkAmbientController().SetFogEnable(false, true);
	//																	   ↓色    ↓密度
	//KdShaderManager::Instance().WorkAmbientController().SetDistanceFog({ 0.3,0,0.5 }, 0.05);
	//																     ↓色  ↓上	↓下 ↓距離
	KdShaderManager::Instance().WorkAmbientController().SetheightFog({ 1,1,1 }, 2,  -2,   0);

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

	for (int i = 0; i < 5; i++)
	{
		//②実体化
		_ground = std::make_shared<Ground>();
		//③初期化
		//※黒崎はコンストラクタでInit関数を呼んでいるので不要
		_ground->SetPos(Math::Vector3(0, 0, i * 5));
		//④ObjectListに追加
		m_objList.push_back(_ground);
	}
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

//===大砲===
	//①ポインタを用意
	std::shared_ptr<Cannon>	_Cannon;
	//②実体化
	_Cannon = std::make_shared<Cannon>();
	//③初期化
	//※黒崎はコンストラクタでInit関数を呼んでいるので不要
	//④ObjectListに追加
	m_objList.push_back(_Cannon);

//===敵===
	//①ポインタを用意
	std::shared_ptr<Enemy>	_enemy;
	
	for (int i = 0; i < 5; i++)
	{
		//②実体化
		_enemy = std::make_shared<Enemy>();
		//③初期化
		//※黒崎はコンストラクタでInit関数を呼んでいるので不要
		_enemy->SetPos({ -20 - float(i),3,0});
		//④ObjectListに追加
		m_objList.push_back(_enemy);
	}

//===================================================================
//敵2(Ghost)(自作)
//===================================================================
	////①実体化
	//m_Ghost = std::make_shared<Ghost>();
	////②ObjectListに追加
	//m_objList.push_back(m_Ghost);

//===================================================================
//敵2(Ghost)(自作)
//===================================================================
	//①ポインタを用意
	std::shared_ptr<Ghost> _ghost;
	//②実体化
	_ghost = std::make_shared<Ghost>();
	//③初期化
	//※黒崎はコンストラクタでInit関数を呼んでいるので不要
	//④ホーミングのターゲットを設定
	_ghost->SetTarget(m_Player);
	//⑤ObjectListに追加
	m_objList.push_back(_ghost);
}