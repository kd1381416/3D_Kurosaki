#include "TitleScene.h"

#include"../SceneManager.h"

void TitleScene::Init()
{
	m_Tex.Load("Asset/Textures/title.png");
	m_StartTex.Load("Asset/Textures/Start.png");

	m_StartAlpha = 1.0f;
	m_StartAddAlpha = 0.01f;
}

void TitleScene::Update()
{
	m_StartAlpha += m_StartAddAlpha;

	if (m_StartAlpha > 1.0f)
	{
		m_StartAlpha = 1.0f;
		m_StartAddAlpha *= -1.0f;
	}
	if (m_StartAlpha < 0.0f)
	{
		m_StartAlpha = 0.0f;
		m_StartAddAlpha *= -1.0f;
	}

	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		SceneManager::Instans().SetNextScene(SceneManager::SceneType::Game);
	}
}

void TitleScene::DrawSprite()
{
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_Tex, 0, 0);
	Math::Color color = { 1.0f,1.0f,1.0f,m_StartAlpha };
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_StartTex, 0, -200, nullptr, &color);
}

void TitleScene::Release()
{
}