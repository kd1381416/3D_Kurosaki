#pragma once

//継承の場合のみ.h内での.hインクルード許可
#include"../BaseScene/BaseScene.h"

class GameScene : public BaseScene
{
public:
	GameScene() { Init(); }
	~GameScene(){}

	void Init()			override;
	void Update()		override;
	void DrawSprite()	override;
	void Release()		override;

private:

	KdTexture	m_PlayerTex;
	KdTexture	m_EnemyTex;

	Math::Vector2	m_PlayerPos;
	Math::Vector2	m_EnemyPos;

	float	m_Anime = 0;
};