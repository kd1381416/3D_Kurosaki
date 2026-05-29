#pragma once

//↓全てのObjectに継承する
class BackGround : public KdGameObject	//背景
{
public:
	BackGround() { Init(); }
	~BackGround() {};

	void Init()		override;
	void DrawUnLit()	override;

private:

	//ModelやTextureはポインタで管理
	std::shared_ptr<KdSquarePolygon>	m_Polygon;
};