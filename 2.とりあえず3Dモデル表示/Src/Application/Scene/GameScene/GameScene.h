#pragma once

//継承の場合のみ.h内での.hインクルード許可
#include"../BaseScene/BaseScene.h"

class GameScene : public BaseScene
{
public:
	GameScene() { Init(); }
	~GameScene(){}

	void Init()			override;
	void Update()		override;
	void DrawLit()		override;
	void DrawSprite()	override;
	void Release()		override;

private:

	//===================================================================
	//船
	//===================================================================
	KdModelData		m_Model;	//3Dデータ
	Math::Vector3	m_Pos;		//座標
	float			m_AngY = 0;

	//===================================================================
	//カメラ
	//===================================================================
	KdCamera	m_Camera;
};