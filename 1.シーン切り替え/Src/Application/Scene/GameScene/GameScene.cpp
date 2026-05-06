#include"GameScene.h"

#include"../SceneManager.h"

void GameScene::Init()
{
	m_Tex.Load("Asset/Textures/Numbers.png");
}

void GameScene::Update()
{
	if(GetAsyncKeyState(VK_SPACE)&0x8000)
	{
		SceneManager::Instans().SetNextScene(SceneManager::SceneType::Title);
	}

	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		m_Score += 100;
		if (m_Score > 9999999999)
		{
			m_Score = 9999999999;
		}
	}

	//配列に各桁の数値を格納
	unsigned long tmp = m_Score;
	for (int i = MaxDigits - 1; i >= 0; i--)
	{
		//下位の桁から抽出し配列に格納
		m_Digits[i] = tmp % 10;		// % -> 余りを求める演算子
		tmp /= 10;					//一桁ずらす
	}
}

void GameScene::DrawSprite()
{
	//スコア表示
	for (int i = 0; i < MaxDigits; i++)
	{
		Math::Rectangle	rc = { 7 * m_Digits[i],0,7,10};

		float posX = -300;

		//表示(サイズ10倍)											 X              Y  幅　高さ 矩形データ
		KdShaderManager::Instance().m_spriteShader.DrawTex(&m_Tex, posX + (i * 70), 0, 70, 100, &rc);
	}
}

void GameScene::Release()
{
}