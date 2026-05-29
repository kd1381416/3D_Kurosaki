#include "Cannon.h"

void Cannon::Init()
{
	//ポインタのままでは使い物にならないので実体化させる
	m_Model = std::make_shared<KdModelData>();
	//モデルの読み込み
	m_Model->Load("Asset/Models/NewCannon/NewCannon.gltf");

//===当たり判定(レイ(光線)判定)===
	//当たられる側(被害者(レイを受ける側))
	//当たり判定を付けたいから実体化
	m_pCollider = std::make_unique<KdCollider>();
	//モデルの形状で当たり判定を登録
	m_pCollider->RegisterCollisionShape(
		"CannonCollision",		//当たり判定の識別名
		m_Model,
		KdCollider::TypeGround
	);

	//拡縮
	Math::Matrix	_scale = Math::Matrix::CreateScale(2.0f);
	//座標
	Math::Matrix	_trans = Math::Matrix::CreateTranslation(0.0f, -2.5f, 0.0f);
	//Y軸回転
	Math::Matrix	_rotatY = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(90));

	//行列合成
	m_mWorld = _scale * _rotatY * _trans;
}

void Cannon::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_Model, m_mWorld);
}