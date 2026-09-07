#pragma once

#include"../EnemyBase.h"

class Yama :public EnemyBase
{
public:
	Yama()			= default;
	~Yama()override = default;

	void Init()		override;
	void Update()	override;
	//void DrawLit()	override;

	//void OnHit()override { m_isExpired = true; }

private:
};