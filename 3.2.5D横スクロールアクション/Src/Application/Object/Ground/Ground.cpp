#include "Ground.h"

//===================================================================
//初期化
//===================================================================
void Ground::Init()
{
	//ポインタのままでは使い物にならないので実体化させる
	m_Model = std::make_shared<KdModelData>();
	//モデルの読み込み
	m_Model->Load("Asset/Models/SideViewMap/SideViewMap.gltf");

	//拡縮行列
	Math::Matrix _scalemat = Math::Matrix::CreateScale(5, 1, 1);
	m_mWorld = _scalemat;

//===当たり判定(レイ(光線)判定)===
	//当たられる側(被害者(レイを受ける側))
	//当たり判定を付けたいから実体化
	m_pCollider = std::make_unique<KdCollider>();
	//モデルの形状で当たり判定を登録
	m_pCollider->RegisterCollisionShape(
		"GroundCollision",
		m_Model,
		KdCollider::TypeGround
	);
}

//===================================================================
//3D描画
//===================================================================
void Ground::DrawLit()
{
	static float d = 0;
	float _range = 0.1f;
	Math::Vector3 _color = { 1,0.3,0.3 };

	if (GetAsyncKeyState('Q') & 0x8000)
	{
		d += 0.01;
		if (d > 1) { d = 1; }
	}

	if (GetAsyncKeyState('W') & 0x8000)
	{
		d -= 0.01;
		if (d < 0) { d = 0; }
	}

	KdShaderManager::Instance().m_StandardShader.SetDissolve(d, &_range, &_color);


	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_Model,m_mWorld);
}