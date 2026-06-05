#pragma once

//↓全てのObjectに継承する
class Effect : public KdGameObject	//背景
{
public:
	Effect() { Init(); }
	~Effect() {};

	void Init()			override;
	void Update()		override;
	void PostUpdate()	override;
	void DrawUnLit()	override;

private:

	//ModelやTextureはポインタで管理
	std::shared_ptr<KdSquarePolygon>	m_Polygon;

	float			m_Anime = 0.0f;		//アニメーション用
};