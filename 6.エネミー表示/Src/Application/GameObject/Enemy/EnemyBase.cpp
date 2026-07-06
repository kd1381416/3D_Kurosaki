#include "EnemyBase.h"

#include<Src/Application/Scene/SceneManager.h>

void EnemyBase::Init()
{
//===================================================================
//デバック
//===================================================================
	//KdGameObjectにポインタを用意しているので実体化
	m_pDebugWire = std::make_unique<KdDebugWireFrame>();
}

void EnemyBase::Update()
{
	//ターゲットへの方向ベクトル算出
	Math::Vector3 _dir = m_Target.lock()->GetPos() - m_Pos;

	//距離が15より小さかったら追尾してくる
	if(_dir.Length() < 15)
	{
		//正規化
		_dir.Normalize();

		//移動処理
		m_Pos += _dir * 0.1f;
	}

//===敵を移動方向に回転させる===
	//今、向いている方向
	Math::Vector3	_nowdir = m_mWorld.Backward();
	//向きたい方向
	Math::Vector3	_todir = _dir;
	//内積
	float	_dot = _nowdir.Dot(_todir);
	//角度に変換
	float	_angle = DirectX::XMConvertToDegrees(acos(_dot));

	if (_angle >= 0.1f)
	{
		//回転角度の上限
		if (_angle > 5.0f) { _angle = 5.0f; }
		
		//外積(回転軸を求める)
		Math::Vector3	_cross = _nowdir.Cross(_todir);

		if(_cross.y >= 0.0f)
		{
			//右回転
			m_Angle += _angle;

			if (m_Angle > 360)
			{
				m_Angle -= 360;
			}
		}
		else
		{
			//左回転
			m_Angle -= _angle;

			if (m_Angle < 360)
			{
				m_Angle += 360;
			}
		}
	}

	Math::Matrix	_trans = Math::Matrix::CreateTranslation(m_Pos);
	m_mWorld = _trans;
}

void EnemyBase::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_Model, m_mWorld);
}