#include "Tank.h"

#include<Src/Application/Scene/SceneManager.h>

#include"../Camera/CameraBase.h"
#include"../Bullet/Bullet.h"

void Tank::Init()
{
//===================================================================
// モデル読み込み
//===================================================================
	m_Model = std::make_shared<KdModelData>();
	m_Model->Load("Asset/Model/Tank/Tank.gltf");

//===================================================================
//デバック
//===================================================================
	//KdGameObjectにポインタを用意しているので実体化
	m_pDebugWire = std::make_unique<KdDebugWireFrame>();

//===================================================================
// レティクル
//===================================================================
	m_Tex = std::make_shared<KdTexture>();
	m_Tex->Load("Asset/Textures/Reticle/Reticle.png");

}

void Tank::Update()
{
	//方向ベクトル = 長さ1
	Math::Vector3 _dir = { 0,0,0 };

	bool _moveflg = false;

	//前
	if (GetAsyncKeyState('W') & 0x8000) 
	{
		_dir += { 0, 0, 1 }; 
		_moveflg = true;
	}	
	//左
	if (GetAsyncKeyState('A') & 0x8000)
	{
		_dir += {-1, 0, 0 }; 
		_moveflg = true;
	}	
	//後
	if (GetAsyncKeyState('S') & 0x8000) 
	{
		_dir += { 0, 0,-1 };
		_moveflg = true;
	}	
	//右
	if (GetAsyncKeyState('D') & 0x8000) 
	{
		_dir += { 1, 0, 0 }; 
		_moveflg = true;
	}	

//===================================================================
// ADS状態にする
//===================================================================
	bool ads = false;

	//右クリックされていたら
	if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
	{
		ads = true;
	}

//===================================================================
// 攻撃(左クリック)
//===================================================================
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		if(m_ClickFlg)
		{
			std::shared_ptr<Bullet>	_bullet;
			_bullet = std::make_shared<Bullet>();
			_bullet->Init();
			_bullet->SetPos(m_Pos + Math::Vector3{ 0,2.0f,0 });

			Math::Vector3	_bulletdir;

			if (ads)
			{
				//レティクル方向に弾を飛ばす
				Math::Vector3 _camerapos;
				float _range = 0;

				//カメラがあるか
				if (!m_Camera.expired())
				{
					_camerapos = m_Camera.lock()->GetPos();

					//カメラが向いている方向のど真ん中にレイを飛ばしたい
					//									　↑この情報を生成する関数
					m_Camera.lock()->WorkCamera()->GenerateRayInfoFromClientPos
					(
						{ 640,360 },
						_camerapos,
						_bulletdir,
						_range
					);
					//↑この関数の処理が終わると
					//　「どこから」		：_camerapos
					//　「どの方向に」		：_bulletdir
					//　「どのくらいの長さ」：_range
					//　の情報が手に入る
				}

				//例判定
				KdCollider::RayInfo _ray;
				_ray.m_pos		= _camerapos;
				_ray.m_dir		= _bulletdir;
				_ray.m_range	= _range;
				_ray.m_type		= KdCollider::TypeDamage | KdCollider::TypeGround;

				//全オブジェクトと当たり判定
				std::list<KdCollider::CollisionResult>	_hitraylist;

				for (auto& obj : SceneManager::Instance().GetObjList())
				{
					obj->Intersects(_ray, &_hitraylist);
				}

				//一番近いオブジェクトを検出
				float	_overlap = 0;
				
				for (auto& ret : _hitraylist)
				{
					if (_overlap < ret.m_overlapDistance)
					{
						//更新
						_overlap = ret.m_overlapDistance;

						//方向ベクトル
						_bulletdir = ret.m_hitPos - (m_Pos + Math::Vector3{ 0,2.0f,0 });

						_bulletdir.Normalize();
					}
				}
			}
			else
			{
				_bulletdir = m_mWorld.Backward();
			}

			//戦車の向いている方向に弾を飛ばす
			_bullet->SetToDir(_bulletdir);
			SceneManager::Instance().AddObject(_bullet);

			m_ClickFlg = false;
		}
	}
	else { m_ClickFlg = true; }

	Math::Matrix	_rotaty;
	if (ads)
	{
		//カメラを戦車に寄せる
		if (!m_Camera.expired())
		{
			m_Camera.lock()->SetLocalPos({ 2.0f,4.0f,-6.0f });

			//ADS状態ではカメラが回転すると戦車も回転
			_rotaty = m_Camera.lock()->GetRotationYMatrix();
		}
	}
	else
	{
		//カメラを戦車に離す
		if (!m_Camera.expired())
		{
			m_Camera.lock()->SetLocalPos({ 1.0f,4.0f,-10.0f });
		}

		//===================================================================
		//移動中
		//===================================================================
		if (_moveflg)
		{
			//方向ベクトルを強制的に1にする(正規化)
			_dir.Normalize();

			//キャラが向いている方向
			//①キャラの回転行列
			Math::Matrix	_nowrotatmat = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_Angle));
			//②ベクトルを変形させる
			Math::Vector3	_nowdir = Math::Vector3::TransformNormal(Math::Vector3{ 0,0,1 }, _nowrotatmat);
			//                                       ↑トランスフォームノーマル(ベクトルを回転行列を使って変形させる)

			//簡単にオブジェクトの向きを取得する方法
			//_nowdir = m_mWorld.Backward();

			//③向きたい方向
			Math::Vector3	_todir = _dir;

			//内積 = ベクトルA * ベクトルB * cos(なす角)
			//  ＝   _nowdir(1)* _todir(1) * cos(なす角) 
			//  ＝   cos(なす角)
			//※cosをacosで計算すると角度が出る

			//④内積を求める(ベクトルA・ベクトルB)
			float	dot = _nowdir.Dot(_todir);

			//⑤角度に変換
			float	_angle = DirectX::XMConvertToDegrees(acos(dot));

			KdDebugGUI::Instance().ClearLog();
			KdDebugGUI::Instance().AddLog("%f\n", _angle);

			//少しでも開店する必要があった場合
			if (_angle >= 0.1f)
			{
				//回転角度の上限
				if (_angle >= 5.0f)
				{
					_angle = 5.0f;
				}

				//外積 = 2本のベクトルに対して垂直なベクトル
				Math::Vector3	_cross = _nowdir.Cross(_todir);

				if (_cross.y >= 0)	//右回転
				{
					m_Angle += _angle;
					if (m_Angle >= 360) { m_Angle -= 360; }
				}
				else				//左回転 
				{
					m_Angle -= _angle;
					if (m_Angle <= -360) { m_Angle += 360; }
				}
			}

			KdDebugGUI::Instance().AddLog("%f\n", m_Angle);

			std::shared_ptr<CameraBase> _camera = m_Camera.lock();

			if (_camera)
			{
				_dir = _dir.TransformNormal(_dir, _camera->GetRotationYMatrix());
			}

			//===================================================================
			//当たり判定(球)
			//===================================================================
				//球判定用の変数を用意
			KdCollider::SphereInfo _sphere;
			//球の中心座標を設定
			_sphere.m_sphere.Center = GetPos();
			_sphere.m_sphere.Center.y += 1.0f;
			//球の半径設定
			_sphere.m_sphere.Radius = 2.0f;
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

			_rotaty = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_Angle));
		}
	}

	//移動処理
	m_Pos += _dir * 0.3f;

	//行列作成
	Math::Matrix	_trans = Math::Matrix::CreateTranslation(m_Pos);
	m_mWorld = _rotaty * _trans;

}

void Tank::PostUpdate()
{
}

void Tank::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_Model, m_mWorld);
}

void Tank::DrawSprite()
{
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_Tex, 0, 0);
}
