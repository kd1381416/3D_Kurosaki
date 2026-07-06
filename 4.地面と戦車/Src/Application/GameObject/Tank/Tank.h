#pragma once

class Tank :public KdGameObject
{
public:
	Tank() {};
	~Tank()override {};

	void Init()override;
	void Update()override;
	void PostUpdate()override;
	void DrawLit()override;

private:

	//モデル
	std::shared_ptr<KdModelData>	m_Model;

	//向いてる方向
	float							m_Angle = 0.0f;
};