#pragma once

class Ground :public KdGameObject
{
public:
	Ground() {};
	~Ground()			override {};

	void Init()			override;
	void Update()		override;
	void PostUpdate()	override;
	void DrawLit()		override;

private:

	std::shared_ptr<KdModelData>	m_Model;
};