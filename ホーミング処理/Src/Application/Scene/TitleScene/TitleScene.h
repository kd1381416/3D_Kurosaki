#pragma once

//継承の場合のみ.h内での.hインクルード許可
#include"../BaseScene/BaseScene.h"

class TitleScene : public BaseScene
{
public:
	TitleScene() { Init(); }
	~TitleScene(){}
	

	void Init()			override;
	void Update()		override;
	void DrawSprite()	override;
	void Release()		override;

private:

	KdTexture	m_Tex;
	KdTexture	m_StartTex;
	float		m_StartAlpha;
	float		m_StartAddAlpha;
};