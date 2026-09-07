#pragma once

class CameraBase;

class Tank :public KdGameObject
{
public:
	Tank() {};
	~Tank()override {};

	void Init()override;
	void Update()override;
	void PostUpdate()override;
	void DrawLit()override;
	void DrawSprite()	override;

	void SetCamera(std::shared_ptr<CameraBase> _camera) { m_Camera = _camera; }
private:

	//モデル
	std::shared_ptr<KdModelData>	m_Model;

	//向いてる方向
	float	m_Angle = 0.0f;

	//座標
	Math::Vector3	m_Pos = Math::Vector3::Zero;

	//キーフラグ
	bool	m_ClickFlg = false;

	//カメラ
	std::weak_ptr<CameraBase>	m_Camera;

	//レティクル
	std::shared_ptr<KdTexture>	m_Tex;
};