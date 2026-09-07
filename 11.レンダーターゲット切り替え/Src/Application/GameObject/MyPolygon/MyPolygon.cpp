#include "MyPolygon.h"

#include <Application/Scene/SceneManager.h>

void MyPolygon::Init()
{
	m_spPolygon = std::make_shared<KdSquarePolygon>();

	//行列作成
	Math::Matrix	_scale = Math::Matrix::CreateScale(50);
	Math::Matrix	_trans = Math::Matrix::CreateTranslation(0, 25, 0);
	m_mWorld = _scale * _trans;
}

void MyPolygon::Update()
{
	if (!m_spPolygon->GetMaterial())
	{
		m_spPolygon->SetMaterial(SceneManager::Instance().GetRenderTargetTexture());
	}
}

void MyPolygon::DrawLit()
{
	if (!m_spPolygon)return;

	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_spPolygon, m_mWorld);
}