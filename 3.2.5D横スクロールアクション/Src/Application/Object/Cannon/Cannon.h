#pragma once

//↓全てのObjectに継承する
class Cannon : public KdGameObject	//地面
{
public:
	Cannon() { Init(); }
	~Cannon() {};

	void Init()		override;
	void DrawLit()	override;

private:

	//ModelやTextureはポインタで管理
	std::shared_ptr<KdModelData>	m_Model;
};