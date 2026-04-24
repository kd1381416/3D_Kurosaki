#pragma once

//前方宣言
class BaseScene;

class SceneManager
{
public:
	enum SceneType
	{
		Title,
		Game
	};

	void PreUpdate();
	void Update();
	void Draw();

	void SetNextScene(SceneType _nextscene)
	{
		m_NextSceneType = _nextscene;
	}

	SceneType GetCurrentScene()const
	{
		return m_CurrentSceneType;
	}

private:

	void Init();
	void Release();
	void ChangeScene(SceneType _scenetype);

	std::shared_ptr<BaseScene> m_CurrentScene;

	//どのシーンにいるかを管理するフラグ変数
	SceneType	m_CurrentSceneType	= SceneType::Title;
	SceneType	m_NextSceneType		= m_CurrentSceneType;

	//シングルトンパターン(デザインパターン)
private:

	SceneManager() { Init(); }
	~SceneManager() { Release(); }

public:

	static SceneManager& Instans()
	{
		static SceneManager instans;
		return instans;
	}
};
//#define SCENEMANAGER SceneManager::Instans()