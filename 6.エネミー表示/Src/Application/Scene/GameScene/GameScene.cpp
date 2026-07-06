#include "GameScene.h"
#include"../SceneManager.h"

#include"../../GameObject/Camera/TPSCamera/TPSCamera.h"
#include"../../GameObject/Ground/Ground.h"
#include"../../GameObject/Tank/Tank.h"
//#include"../../GameObject/Enemy/EnemyBase.h"
#include"../../GameObject/Enemy/Yama/Yama.h"
#include"../../GameObject/Enemy/Moto/Moto.h"

void GameScene::Event()
{
	if (GetAsyncKeyState('T') & 0x8000)
	{
		SceneManager::Instance().SetNextScene
		(
			SceneManager::SceneType::Title
		);
	}
}

void GameScene::Init()
{
//===カメラ===
	std::shared_ptr<TPSCamera>	_camera;
	_camera = std::make_shared<TPSCamera>();
	_camera->Init();
	m_objList.push_back(_camera);

//===地面===
	std::shared_ptr<Ground>	_ground;
	_ground = std::make_shared<Ground>();
	_ground->Init();
	m_objList.push_back(_ground);

//===戦車===
	std::shared_ptr<Tank>	_tank;
	_tank = std::make_shared<Tank>();
	_tank->Init();
	m_objList.push_back(_tank);

//===Yama===
	std::shared_ptr<Yama>	_yama;
	_yama = std::make_shared<Yama>();
	_yama->Init();
	_yama->SetPos({ -10,0,20 });
	m_objList.push_back(_yama);

//===Moto===
	std::shared_ptr<Moto>	_moto;
	_moto = std::make_shared<Moto>();
	_moto->Init();
	_moto->SetPos({ 10,0,20 });
	m_objList.push_back(_moto);

	//ターゲットとしてセット
	_camera->SetTarget(_tank);
	_yama->SetTarget(_tank);
	_moto->SetTarget(_tank);

	//カメラを参照するため
	_tank->SetCamera(_camera);

	ShowCursor(false);
}
