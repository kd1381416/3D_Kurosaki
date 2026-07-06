#include "bullet.h"

void Bullet::Init()
{
	m_Model = std::make_shared<KdModelWork>();
	m_Model->SetModelData("Asset/Model/Bullet/Bullet.gltf");

	m_Pos = { 0,0,0 };
}

void Bullet::Update()
{
	m_Pos += m_ToDir * 0.4f;

	m_LifeSpan--;

	if (m_LifeSpan <= 0)
	{
		m_isExpired = true;
	}

	Math::Matrix	_trans = Math::Matrix::CreateTranslation(m_Pos);
	m_mWorld = _trans;
}

void Bullet::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_Model, m_mWorld);
}

void Bullet::DrawBright()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_Model, m_mWorld);
}