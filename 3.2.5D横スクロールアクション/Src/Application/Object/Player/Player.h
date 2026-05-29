#pragma once

//						↓全てのObjectに継承する
class Player : public KdGameObject	//地面
{
public:
	Player() { Init(); }
	~Player() {};

	void Init()			override;
	void Update()		override;
	void PostUpdate()	override;
	void DrawLit()		override;

private:

	//ModelやTextureはポインタで管理
	std::shared_ptr<KdSquarePolygon>	m_Polygon;

	//座標
	Math::Vector3	m_Pos;

	//アニメーション用
	float			m_Anime = 0.0f;

	//重力
	float			m_Gravity = 0;
};