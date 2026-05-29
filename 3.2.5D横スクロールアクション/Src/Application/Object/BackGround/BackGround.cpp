#include "BackGround.h"

void BackGround::Init()
{
	//ポインタのままでは使い物にならないので実体化させる
	m_Polygon = std::make_shared<KdSquarePolygon>();
	//モデルの読み込み
	m_Polygon->SetMaterial("Asset/Textures/Back.png");

	//拡大
	Math::Matrix	_scale = Math::Matrix::CreateScale(300, 100, 1);
	//座標
	Math::Matrix	_trans = Math::Matrix::CreateTranslation(0, 0, 50);

	//行列合成
	m_mWorld = _scale * _trans;
}

void BackGround::DrawUnLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_Polygon, m_mWorld);
}