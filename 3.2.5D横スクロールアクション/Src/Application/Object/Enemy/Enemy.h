#pragma once

//↓全てのObjectに継承する
class Enemy : public KdGameObject	//背景
{
public:
	Enemy() { Init(); }
	~Enemy() {};

	void Init()			override;
	void Update()		override;
	void PostUpdate()	override;
	void DrawLit()		override;

	void OnHit()		override;

	//				↓コンスト参照型
	void SetPos(const Math::Vector3& _pos) override { m_Pos = _pos; }

private:

	//ModelやTextureはポインタで管理
	std::shared_ptr<KdSquarePolygon>	m_Polygon;

	float			m_Anime = 0.0f;		//アニメーション用
	Math::Vector3	m_Pos = {};			//座標
	float			m_Gravity = 0;		//重力

//===移動処理===
	int		m_Dir = 1;			//移動方向(1:右,-1:左)
	float	m_Goal = 0;			//目標地点までの距離
	float	m_Speed = 0.01f;	//移動量
};