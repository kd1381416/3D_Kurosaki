#include "Enemy.h"

#include"../../Scene/SceneManager.h"

void Enemy::Init()
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
	m_Polygon->SetMaterial("Asset/Textures/char.png");
	//画像を分割
	m_Polygon->SetSplit(6, 6);
	//原点を変更
	m_Polygon->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);

//===================================================================
//当たり判定(被害者)
//===================================================================
	//当たられる側
	//当たり判定を付けたいから実体化
	m_pCollider = std::make_unique<KdCollider>();
	//モデルの形状で当たり判定を登録
	m_pCollider->RegisterCollisionShape(
		"EnemyCollision",		//当たり判定の識別名
		{0,0.5,0},				//球の中心点
		0.2,					//球の半径
		KdCollider::TypeDamage	//当たり判定のタイプ
	);
}

void Enemy::Update()
{
//===================================================================
//ポイントライト(Max100個)
//===================================================================
	KdShaderManager::Instance().WorkAmbientController().AddPointLight
	(
		{ 3,3,3 },							//色
		5,									//半径
		m_Pos + Math::Vector3(0, 0.5, 0)	//位置
	);

//===================================================================
//死亡時
//===================================================================
	//if (m_OutoroFlg)
	//{
	//	OutroUpdate();
	//	return;
	//}

//===================================================================
//デバック
//===================================================================
	m_pDebugWire->AddDebugSphere(m_Pos + Math::Vector3(0.0f, 0.5f, 0.0f), 0.2f, kRedColor);

//===================================================================
//アニメーション
//===================================================================
	int _walk[4] = { 3,4,3,5 };
	m_Polygon->SetUVRect(_walk[(int)m_Anime]);

	m_Anime += 0.1f;
	if (m_Anime > 4) { m_Anime = 0.0f; }

//===================================================================
//移動処理
//===================================================================
	//座標を(移動量*方向)で動かす
	m_Pos.x += (m_Speed * m_Dir);
	//移動した分目標値に近づける
	m_Goal += m_Speed;
	//目標地点についたら反転させる
	if (m_Goal >= 5.0f) 
	{
		m_Dir *= -1; 
		m_Goal = 0;
	}

//===================================================================
//重力
//===================================================================
	m_Pos.y -= m_Gravity;
	m_Gravity += 0.005f;

}

void Enemy::PostUpdate()
{
//===================================================================
//当たり判定(レイ(光線)判定)
//===================================================================
	//当たる側(加害者側(レイを出す側))
	KdCollider::RayInfo _ray;
	//レイの発射位置を測定
	_ray.m_pos = m_Pos;
	//ちょっと上からの位置にする
	_ray.m_pos.y += 0.1f;
	//段差の許容範囲
	float _eneblestephigh = 0.2f;
	_ray.m_pos.y += _eneblestephigh;
	//レイの発射位置を設定
	_ray.m_dir = { 0,-1,0 };
	//レイの長さを設定
	_ray.m_range = m_Gravity + _eneblestephigh;
	//当たり判定を行いたいタイプを設定
	_ray.m_type = KdCollider::TypeGround;

	//_rayに当たったオブジェクト情報を格納するリスト
	std::list<KdCollider::CollisionResult> _retraylist;
	//当たり判定(全オブジェクト)
	for (auto& obj : SceneManager::Instance().GetObjList())
	{
		//全オブジェクトに対してレイ判定をする関数を呼び出す
		obj->Intersects(_ray, &_retraylist);
	}

	//_retraylistから一番近いオブジェクトを探す
	float _maxoverlap = 0;
	Math::Vector3 _hitpos;
	bool _hit = false;

	//レイを遮断しオーバーした長さが一番長いものを探す
	for (auto& ret : _retraylist)
	{
		if (_maxoverlap < ret.m_overlapDistance)
		{
			//更新
			_maxoverlap = ret.m_overlapDistance;
			_hitpos = ret.m_hitPos;
			_hit = true;
		}
	}

	if (_hit)
	{
		//当たっていたらその座標をプレイヤー座標にセット
		m_Pos = _hitpos += Math::Vector3(0, -0.1f, 0);
		m_Gravity = 0;
	}

//===================================================================
//当たり判定(球(スフィア)判定)
//===================================================================
	//球判定用の変数を用意
	KdCollider::SphereInfo _sphere;
	//球の中心座標を設定
	_sphere.m_sphere.Center = m_Pos;
	_sphere.m_sphere.Center.y += 0.5f;
	//球の半径設定
	_sphere.m_sphere.Radius = 0.3f;
	//当たり判定をしたいTypeを設定
	_sphere.m_type = KdCollider::TypeGround;
	//球に当たったオブジェクトの情報を格納するリスト
	std::list<KdCollider::CollisionResult>	_resultspherelist;
	//当たり判定(全オブジェクト)
	for (auto& obj : SceneManager::Instance().GetObjList())
	{
		//全オブジェクトに対して球判定をする関数を呼び出す
		obj->Intersects(_sphere, &_resultspherelist);
	}
	//球に当たったリストから一番近いオブジェクトを探す
	_maxoverlap = 0;			//←使いまわし
	_hit = false;				//←使いまわし
	Math::Vector3	_hitdir;	//当たった方向

	for (auto& _result : _resultspherelist)
	{
		//球にめり込んだ長さが一番長いものを探す
		if (_maxoverlap < _result.m_overlapDistance)
		{
			//更新
			_maxoverlap = _result.m_overlapDistance;
			_hitdir = _result.m_hitDir;
			_hit = true;
		}
	}

	if (_hit)
	{
		//Z方向への押し戻しを無効にする
		_hitdir.z = 0;
		//※方向ベクトルは絶対に長さ「1」
		//正規化(長さは１)
		_hitdir.Normalize();

		//押し戻し処理
		m_Pos += _hitdir * _maxoverlap;
	}

//===================================================================
//デバック処理
//===================================================================
	//レイ判定
	m_pDebugWire->AddDebugLine(_ray.m_pos, _ray.m_dir, _ray.m_range);
	//球判定
	m_pDebugWire->AddDebugSphere(_sphere.m_sphere.Center, _sphere.m_sphere.Radius);

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

void Enemy::DrawLit()
{
//===================================================================
//描画
//===================================================================
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_Polygon, m_mWorld);
}

void Enemy::OnHit()
{
	//m_OutoroFlg = true;

	m_isExpired = true;
}

void Enemy::OutroUpdate()
{
}