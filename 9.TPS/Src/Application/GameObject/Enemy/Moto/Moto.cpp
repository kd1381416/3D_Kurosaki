#include "Moto.h"

void Moto::Init()
{
	m_Model = std::make_shared<KdModelWork>();
	m_Model->SetModelData("Asset/Model/moto/moto.gltf");

	m_Pos = { -10,0,20 };

//===================================================================
//当たり判定(被害者)
//===================================================================
	//当たられる側
	//当たり判定を付けたいから実体化
	m_pCollider = std::make_unique<KdCollider>();
	//モデルの形状で当たり判定を登録
	m_pCollider->RegisterCollisionShape(
		"EnemyCollision",		//当たり判定の識別名
		m_Model,
		KdCollider::TypeDamage	//当たり判定のタイプ
	);

}

//void Moto::Update()
//{
//	Math::Matrix	_trans = Math::Matrix::CreateTranslation(m_Pos);
//	m_mWorld = _trans;
//}
//
//void Moto::DrawLit()
//{
//	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_Model, m_mWorld);
//}
