#include "Player.h"

#include"../../Scene/SceneManager.h"

//===================================================================
//初期化
//===================================================================
void Player::Init()
{
	//デバック用:KdGameObjectにポインタを用意しているので実体化
	m_pDebugWire = std::make_unique<KdDebugWireFrame>();
	
	//ポインタのままでは使い物にならないので実体化させる
	m_Polygon = std::make_shared<KdSquarePolygon>();
	//画像の読み込み
	m_Polygon->SetMaterial("Asset/Textures/char.png");
	//画像を分割
	m_Polygon->SetSplit(6, 6);
	//原点を変更
	m_Polygon->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);

	//座標初期化
	m_Pos = {-53.5f, 2.0f,0};


}

//===================================================================
//本更新
//===================================================================
void Player::Update()
{
	static bool	_move = false;
//アニメーション
	int _run[4] = { 24,25,24,26 };
	m_Polygon->SetUVRect(_run[(int)m_Anime]);

	m_Anime += 0.2f;
	if (m_Anime > 4) { m_Anime = 0; }

//===移動処理===
	Math::Vector3 _movepow = {};

	if (GetAsyncKeyState(VK_LEFT) & 0x8000) { _movepow.x = -0.05f; }
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) { _movepow.x = 0.05f; }
	if (GetAsyncKeyState(VK_UP) & 0x8000) { _movepow.y = 0.05f; }
	if (GetAsyncKeyState(VK_DOWN) & 0x8000) { _movepow.y = -0.05f; }
	if (GetAsyncKeyState(VK_SPACE) & 0x8000) { _movepow.y = 1.0f; }

	m_Pos += _movepow;

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
//===当たり判定(レイ(光線)判定)===
	//当たる側(加害者側(レイを出す側))
	KdCollider::RayInfo _ray;
	//レイの発射位置を測定
	_ray.m_pos = m_Pos;
	//レイの発射位置を設定
	_ray.m_dir = { 0,-1,0 };
	//レイの長さを設定
	_ray.m_range = 1;
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
		m_Pos = _hitpos;
	}
	else { m_Pos.y -= 0.1f; }

	//デバック処理
	m_pDebugWire->AddDebugLine(_ray.m_pos, _ray.m_dir, _ray.m_range);
}

//===================================================================
//3D描画
//===================================================================
void Player::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_Polygon, m_mWorld);
}