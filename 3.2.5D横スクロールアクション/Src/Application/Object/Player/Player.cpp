#include "Player.h"

#include"../../Scene/SceneManager.h"

//===================================================================
//初期化
//===================================================================
void Player::Init()
{
	//デバック用:KdGameObjectにポインタを用意しているので実体化
	m_pDebugWire = std::make_unique<KdDebugWireFrame>();
	
//===画像===
	//ポインタのままでは使い物にならないので実体化させる
	m_Polygon = std::make_shared<KdSquarePolygon>();
	//画像の読み込み
	m_Polygon->SetMaterial("Asset/Textures/char.png");
	//画像を分割
	m_Polygon->SetSplit(6, 6);
	//原点を変更
	m_Polygon->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);

//===座標===
	//座標初期化
	m_Pos = { -20.0f, 2.0f,0.0f };
}

//===================================================================
//本更新
//===================================================================
void Player::Update()
{
//アニメーション
	int _run[4] = { 24,25,24,26 };
	m_Polygon->SetUVRect(_run[(int)m_Anime]);

	m_Anime += 0.2f;
	if (m_Anime > 4) { m_Anime = 0; }

//===移動処理===
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) { m_Pos.x += -0.05f; }
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) { m_Pos.x += 0.05f; }

	//ジャンプ処理
	if (GetAsyncKeyState(VK_UP) & 0x8000) { m_Gravity = -0.1f; }

	//重力反映
	m_Pos.y -= m_Gravity;
	m_Gravity += 0.005f;

//===行列作成===
	//座標行列
	Math::Matrix _transmat = Math::Matrix::CreateTranslation(m_Pos);
	//行列作成
	m_mWorld = _transmat;
}

//===================================================================
//後更新
//===================================================================
void Player::PostUpdate()
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
		if(_maxoverlap < ret.m_overlapDistance)
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
}

//===================================================================
//3D描画
//===================================================================
void Player::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_Polygon, m_mWorld);
}