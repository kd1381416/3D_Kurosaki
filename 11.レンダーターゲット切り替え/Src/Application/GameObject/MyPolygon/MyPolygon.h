#pragma once

class MyPolygon : public KdGameObject
{
public:
	MyPolygon()		{}
	~MyPolygon()	{}

	void Init() override;
	void Update() override;
	void DrawLit() override;

private:

	std::shared_ptr<KdSquarePolygon>	m_spPolygon = nullptr;
};