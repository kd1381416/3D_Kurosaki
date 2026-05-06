#include"GameScene.h"

#include"../SceneManager.h"

void GameScene::Init()
{
	m_PlayerTex.Load("Asset/Textures/player.png");
	m_EnemyTex.Load("Asset/Textures/enemy.png");
}

void GameScene::Update()
{
	// キャラ制御
	float			_moveSpd = 5.0f;

	Math::Vector2	_moveVec = Math::Vector2::Zero;
	if (GetAsyncKeyState(VK_UP))_moveVec.y = 1.0f;
	if (GetAsyncKeyState(VK_LEFT))_moveVec.x = -1.0f;
	if (GetAsyncKeyState(VK_DOWN))_moveVec.y = -1.0f;
	if (GetAsyncKeyState(VK_RIGHT))_moveVec.x = 1.0f;

	//正規化(あらゆる矢印の長さを{1.0}にする)
	_moveVec.Normalize();

	m_PlayerPos += _moveVec * _moveSpd;

	//ホーミング
	//目的地-現在地で現在地から目的地までのベクトル
	Math::Vector2	enemymove = m_PlayerPos - m_EnemyPos;

	//ベクトルの長さが出る(自機から敵までも距離)
	//enemymove.Length();

	//正規化(ベクトルの長さを1にする)
	enemymove.Normalize();

	m_EnemyPos += enemymove;

	//アニメーション制御
	m_Anime += 1;
	if (m_Anime >= 6)
	{
		m_Anime = 0;
	}
}

void GameScene::DrawSprite()
{
	int burneranime[6] = {0,64,128,192,128,64};
	Math::Rectangle playerrec = { burneranime,0,64,64 };
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_PlayerTex, m_PlayerPos.x, m_PlayerPos.y,64,64,&playerrec);

	Math::Rectangle enemyrec = { 0,0,64,64 };
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_EnemyTex, m_EnemyPos.x, m_EnemyPos.y,64,64,&enemyrec);
}

void GameScene::Release()
{
}