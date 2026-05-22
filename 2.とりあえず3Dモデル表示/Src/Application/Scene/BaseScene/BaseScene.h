#pragma once

//全てのシーンの親クラス(基底クラス)

class BaseScene
{
public:
	BaseScene() {}
	virtual ~BaseScene(){}

	//virtual = 仮想関数(上書きを前提とする関数)
	
	//純粋仮想関数(絶対に上書きしなければならない)
	//virtual void Init() = 0; 

	virtual void Init();
	virtual void Update();
	virtual void DrawLit();
	virtual void DrawSprite();
	virtual void Release();

private:

};