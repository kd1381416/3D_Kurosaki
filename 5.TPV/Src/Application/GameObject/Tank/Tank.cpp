#include "Tank.h"

#include"../Camera/CameraBase.h"

void Tank::Init()
{
//===================================================================
// モデル読み込み
//===================================================================
	m_Model = std::make_shared<KdModelData>();
	m_Model->Load("Asset/Model/Tank/Tank.gltf");

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

	//移動中
	if(_moveflg)
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

		//移動処理
		std::shared_ptr<CameraBase> _camera = m_Camera.lock();

		if(_camera)
		{
			_dir = _dir.TransformNormal(_dir, _camera->GetRotationYMatrix());
		}
		m_Pos += _dir * 0.3f;

		Math::Matrix	_scale = Math::Matrix::CreateScale(1);
		Math::Matrix	_trans = Math::Matrix::CreateTranslation(m_Pos);
		Math::Matrix	_rotaty = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_Angle));
		m_mWorld = _scale * _rotaty * _trans;
	}
}

void Tank::PostUpdate()
{
}

void Tank::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_Model, m_mWorld);
}
