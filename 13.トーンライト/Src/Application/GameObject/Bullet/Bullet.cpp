#include "bullet.h"

#include"../../Scene/SceneManager.h"

void Bullet::Init()
{
	m_Model = std::make_shared<KdModelWork>();
	m_Model->SetModelData("Asset/Model/Bullet/Bullet.gltf");

	m_Pos = { 0,0,0 };

	//トレイルポリゴン初期化
	m_tPolygon = std::make_shared<KdTrailPolygon>();
	m_tPolygon->SetMaterial("Asset/Textures/Jet/jet.png");
	//トレイルポリゴンをビルボード(面をカメラのほうにむける)化
	m_tPolygon->SetPattern(KdTrailPolygon::Trail_Pattern::eBillboard);

	m_pDebugWire = std::make_unique<KdDebugWireFrame>();
}

void Bullet::Update()
{
	m_Pos += m_ToDir * 1.0f;
	m_LifeSpan--;

	if (m_LifeSpan <= 0)
	{
		m_isExpired = true;
	}

	Math::Matrix	_trans = Math::Matrix::CreateTranslation(m_Pos);
	m_mWorld = _trans;

	//トレイルポイントを追加
	m_tPolygon->AddPoint(m_mWorld);
}

void Bullet::PostUpdate()
{
	//===================================================================
	//当たり判定(球)
	//===================================================================
	//球判定用の変数を用意
	KdCollider::SphereInfo _sphere;
	//球の中心座標を設定
	_sphere.m_sphere.Center = GetPos();
	//球の半径設定
	_sphere.m_sphere.Radius = 1.0f;
	//当たり判定をしたいタイプ
	_sphere.m_type = KdCollider::TypeDamage;

	//全てのオブジェクトと当たり判定をする
	for (auto& obj : SceneManager::Instance().GetObjList())
	{
		//敵と当たったら入る
		if (obj->Intersects(_sphere, nullptr))
		{
			obj->OnHit();
		}
	}

	//===================================================================
	//デバック処理
	//===================================================================
	//球判定
	//m_pDebugWire->AddDebugSphere(_sphere.m_sphere.Center, _sphere.m_sphere.Radius, kRedColor);

}

void Bullet::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_Model, m_mWorld);
}

void Bullet::DrawBright()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_Model, m_mWorld);

	//トレイルポリゴン表示(第2引数に行列は不要)
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_tPolygon);
}