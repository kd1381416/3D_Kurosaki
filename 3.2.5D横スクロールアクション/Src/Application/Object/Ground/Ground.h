#pragma once
					//↓全てのObjectに継承する
class Ground : public KdGameObject	//地面
{
public:
	Ground() { Init(); }
	~Ground() {};

	void Init()		override;
	void DrawLit()	override;

private:

	//ModelやTextureはポインタで管理
	std::shared_ptr<KdModelData>	m_Model;
};