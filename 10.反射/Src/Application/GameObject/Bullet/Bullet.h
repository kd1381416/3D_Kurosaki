#pragma once

class Bullet :public KdGameObject
{
public:
	Bullet() {};
	~Bullet()override {};

	void Init()			override;
	void Update()		override;
	void PostUpdate()	override;
	void DrawLit()		override;
	void DrawBright()	override;

	void SetPos(Math::Vector3 _pos){ m_Pos = _pos; }
	void SetToDir(Math::Vector3 _todir) { m_ToDir = _todir; }

private:

	std::shared_ptr<KdModelWork>	m_Model;
	Math::Vector3					m_Pos;
	Math::Vector3					m_ToDir;

	//弾の寿命
	int		m_LifeSpan = 300;

	//トレイル(軌跡)ポリゴン
	std::shared_ptr<KdTrailPolygon>	m_tPolygon;
};