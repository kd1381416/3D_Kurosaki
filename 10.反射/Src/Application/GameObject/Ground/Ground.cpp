#include "Ground.h"

void Ground::Init()
{
//===================================================================
// モデル読み込み
//===================================================================
	m_Model = std::make_shared<KdModelData>();
	m_Model->Load("Asset/Model/Ground/Ground.gltf");

//当たられる側
//当たり判定を付けたいから実体化
	m_pCollider = std::make_unique<KdCollider>();
	//モデルの形状で当たり判定を登録
	m_pCollider->RegisterCollisionShape(
		"GroundCollision",		//当たり判定の識別名
		m_Model,
		KdCollider::TypeGround	//当たり判定のタイプ
	);
}

void Ground::Update()
{}

void Ground::PostUpdate()
{
	Math::Matrix	_scale = Math::Matrix::CreateScale(100.0f);
	Math::Matrix	_trans = Math::Matrix::CreateTranslation(0, 0, 0);
	m_mWorld = _scale * _trans;
}

void Ground::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_Model, m_mWorld);
}
