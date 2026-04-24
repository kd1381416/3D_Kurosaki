#include"GameScene.h"

#include"../SceneManager.h"

void GameScene::Init()
{
}

void GameScene::Update()
{
	if(GetAsyncKeyState(VK_SPACE)&0x8000)
	{
		SceneManager::Instans().SetNextScene(SceneManager::SceneType::Title);
	}
}

void GameScene::DrawSprite()
{
	Math::Color color = { 1,1,1,1 };
	KdShaderManager::Instance().m_spriteShader.DrawCircle(0, 0, 100);
}

void GameScene::Release()
{
}