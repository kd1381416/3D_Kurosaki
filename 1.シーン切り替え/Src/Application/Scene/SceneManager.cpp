#include "SceneManager.h"

//各シーンの.hをインクルード
#include"GameScene/GameScene.h"
#include"TitleScene/TitleScene.h"

void SceneManager::PreUpdate()
{
	//シーン切り替え
	if (m_CurrentSceneType != m_NextSceneType)
	{
		ChangeScene(m_NextSceneType);
	}
}

void SceneManager::Update()
{
	m_CurrentScene->Update();
}

void SceneManager::Draw()
{
	m_CurrentScene->DrawSprite();
}

void SceneManager::Init()
{
	ChangeScene(m_CurrentSceneType);
}

void SceneManager::Release()
{
}

void SceneManager::ChangeScene(SceneType _scenetype)
{
	//1.次のシーンを作成
	switch (_scenetype)
	{
	case SceneManager::Title:
		m_CurrentScene = std::make_shared<TitleScene>();
		break;
	case SceneManager::Game:
		m_CurrentScene = std::make_shared<GameScene>();
		break;
	}

	//2.フラグを更新
	m_CurrentSceneType = _scenetype;
}
