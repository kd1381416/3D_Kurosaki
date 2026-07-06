#pragma once

#include"../EnemyBase.h"

class Moto :public EnemyBase
{
public:
	Moto() = default;
	~Moto()override = default;

	void Init()		override;
	//void Update()	override;
	//void DrawLit()	override;

	void OnHit()override { m_isExpired = true; }

private:
};