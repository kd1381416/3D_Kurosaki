#include "Effect.h"

#include"../../Scene/SceneManager.h"

void Effect::Init()
{
//===================================================================
//デバック
//===================================================================
	//KdGameObjectにポインタを用意しているので実体化
	m_pDebugWire = std::make_unique<KdDebugWireFrame>();

//===================================================================
//画像読み込み・初期化
//===================================================================
	//ポインタのままでは使い物にならないので実体化させる
	m_Polygon = std::make_shared<KdSquarePolygon>();
	//画像の読み込み
	m_Polygon->SetMaterial("Asset/Textures/effect.png");
	//画像を分割
	m_Polygon->SetSplit(4, 4);
}

void Effect::Update()
{
//===================================================================
//アニメーション
//===================================================================
	m_Polygon->SetUVRect((int)m_Anime);

	m_Anime += 0.4f;
	if (m_Anime >= 12) 
	{
		//有効期限を切る
		m_isExpired = true;
	}
}

void Effect::PostUpdate()
{
//===================================================================
//当たり判定(球(スフィア)判定)
//===================================================================
	//球判定用の変数を用意
	KdCollider::SphereInfo _sphere;
	//球の中心座標を設定
	_sphere.m_sphere.Center = GetPos();
	//球の半径設定
	_sphere.m_sphere.Radius = 0.3f;
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
	m_pDebugWire->AddDebugSphere(_sphere.m_sphere.Center, _sphere.m_sphere.Radius, kRedColor);

//===================================================================
//行列作成
//===================================================================
	////拡大
	//Math::Matrix	_scale = Math::Matrix::CreateScale(1, 1, 1);
	////移動
	//Math::Matrix	_trans = Math::Matrix::CreateTranslation(0, 0, 5);
	////行列合成
	//m_mWorld = _scale * _trans;
}

void Effect::DrawUnLit()
{
//===================================================================
//描画
//===================================================================
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_Polygon, m_mWorld);
}