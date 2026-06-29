#include "Ground.h"

void Ground::Init()
{
//===================================================================
// モデル読み込み
//===================================================================
	m_Model = std::make_shared<KdModelData>();
	m_Model->Load("Asset/Model/Ground/Ground.gltf");
}

void Ground::Update()
{}

void Ground::PostUpdate()
{
	Math::Matrix	_scale = Math::Matrix::CreateScale(5.0f);
	Math::Matrix	_trans = Math::Matrix::CreateTranslation(0, 0, 0);
	m_mWorld = _scale * _trans;
}

void Ground::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_Model, m_mWorld);
}
