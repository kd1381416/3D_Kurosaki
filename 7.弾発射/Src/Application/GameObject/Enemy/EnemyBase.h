#pragma once

class EnemyBase :public KdGameObject
{
public:
	EnemyBase()				= default;
	~EnemyBase()override	= default;

	virtual	void Init()		override;
	virtual void Update()	override;
	virtual void DrawLit()	override;

	void SetPos(Math::Vector3 _pos) { m_Pos = _pos; }

	void SetTarget(std::shared_ptr<KdGameObject> _target) { m_Target = _target; }

	virtual void OnHit() override {};

private:

protected:

	std::shared_ptr<KdModelWork>	m_Model;
	Math::Vector3					m_Pos;
	std::weak_ptr<KdGameObject>		m_Target;

	float	m_Angle = 0.0f;
};