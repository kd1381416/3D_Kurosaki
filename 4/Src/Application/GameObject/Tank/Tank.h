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

	std::shared_ptr<KdModelData>	m_Model;
	float							m_Angle = 0.0f;
};