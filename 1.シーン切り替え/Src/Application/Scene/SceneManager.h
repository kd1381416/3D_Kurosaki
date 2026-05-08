#pragma once

//前方宣言
class BaseScene;

class SceneManager
{
public:
	//シーン情報
	//enum = 列挙型(複数の定数をまとめて管理するための型)
	//入る値は0から順番にint型で割り振られる
	enum SceneType
	{
		Title,
		Game
	};

	//Updateの前に実行するUpdate
	void PreUpdate();

	void Update();
	void Draw();

	//外部から次のシーンをセットする関数
	//※この関数ではシーンは切り替わらない
	void SetNextScene(SceneType _nextscene)
	{
		m_NextSceneType = _nextscene;
	}

	//現在のシーンを取得する関数
	SceneType GetCurrentScene()const
	{
		return m_CurrentSceneType;
	}

private:

	//初期化や解放は自分でする
	void Init();
	void Release();
	//シーン切り替えの関数
	void ChangeScene(SceneType _scenetype);

	//現在のシーンを管理するポインタ変数
	std::shared_ptr<BaseScene> m_CurrentScene;

	//現在のシーンを管理するフラグ変数
	SceneType	m_CurrentSceneType	= SceneType::Title;
	//次のシーンを管理するフラグ変数
	SceneType	m_NextSceneType		= m_CurrentSceneType;

//シングルトンパターン(デザインパターン)
//実体がひとつしかないことを証明するためのパターン
//※何でもかんでもシングルトンにしない
private:

	//外で変数宣言できない
	SceneManager() { Init(); }
	~SceneManager() { Release(); }

public:

	static SceneManager& Instans()
	{
		//自分を自分で作る
		static SceneManager instans;
		return instans;
	}
};
//#define SCENEMANAGER SceneManager::Instans()