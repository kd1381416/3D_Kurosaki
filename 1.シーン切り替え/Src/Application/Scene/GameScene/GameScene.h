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
	void DrawSprite()	override;
	void Release()		override;

private:

};