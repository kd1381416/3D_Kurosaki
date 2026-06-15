#include "Ghost.h"

#include"../../Scene/SceneManager.h"

void Ghost::Init()
{
//===================================================================
//画像読み込み・初期化
//===================================================================
	//ポインタのままでは使い物にならないので実体化させる
	m_Polygon = std::make_shared<KdSquarePolygon>();
	//画像の読み込み
	m_Polygon->SetMaterial("Asset/Textures/char.png");
	//画像を分割
	m_Polygon->SetSplit(6, 6);
	//初期画像を設定
	m_Polygon->SetUVRect(34);
	//原点を変更
	m_Polygon->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);
}

void Ghost::Update()
{
//===================================================================
//ホーミング処理(自作)
//===================================================================
	////目的地-現在地で現在地から目的地までのベクトル
	//m_Move = m_TargetPos - m_Pos;
	////正規化
	//m_Move.Normalize();
	////移動
	//m_Pos += m_Move * m_Speed;

//===================================================================
//ホーミング処理(お手本)
//===================================================================
	//ターゲット座標
	Math::Vector3	_targetpos = {};
	//ターゲット座標をとる
	if (m_Target.expired() == false)
	{
		//この中に入った = アドレス先に領域がある
		_targetpos = m_Target.lock()->GetPos();
		//					   ↑sharedに変換
	}
	//ターゲットへのベクトルを算出
	Math::Vector3	_dir = _targetpos - m_Pos;
	//正規化
	_dir.Normalize();
	//ターゲットに向かって移動
	m_Pos += _dir * m_Speed;
}

void Ghost::PostUpdate()
{
//===================================================================
//行列作成
//===================================================================
	//拡大
	Math::Matrix	_scale = Math::Matrix::CreateScale(1, 1, 1);
	//移動
	Math::Matrix	_trans = Math::Matrix::CreateTranslation(m_Pos);
	//行列合成
	m_mWorld = _scale * _trans;
}

void Ghost::DrawLit()
{
//===================================================================
//描画
//===================================================================
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_Polygon, m_mWorld);
}