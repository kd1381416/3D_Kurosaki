#pragma once

class GameScene;

//↓全てのObjectに継承する
class Ghost : public KdGameObject	//背景
{
public:
	Ghost() { Init(); }
	~Ghost() {};

	void Init()			override;
	void Update()		override;
	void PostUpdate()	override;
	void DrawLit()		override;

	//				↓コンスト参照型
	//void SetHoomingPos(const Math::Vector3& _pos) { m_TargetPos = _pos; }

	void SetTarget(std::shared_ptr<KdGameObject> _target) { m_Target = _target; }

private:

	//ModelやTextureはポインタで管理
	std::shared_ptr<KdSquarePolygon>	m_Polygon;

	Math::Vector3	m_Pos = {};			//座標

	//===移動処理(自作)===
	//Math::Vector3	m_TargetPos = {};	//ターゲットの座標
	//Math::Vector3	m_Move = {};
	float	m_Speed = 0.03f;				//移動量

	//===移動処理(お手本)===
	//ターゲットとなるObjectのポインタ
	std::weak_ptr<KdGameObject>	m_Target;
	//	   ↑ウィークポインタ:参照カウンタを増やさないポインタ
};