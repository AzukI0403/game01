#pragma once
class Player;
class Numberhouse;

class GameCamera_sc:public IGameObject
{
public:
	GameCamera_sc();
	~GameCamera_sc();
	bool Start();
	void Update();
	//切り替え判定。
	int playerState = 0;
	/////////////////////////////////////
	//メンバ変数
	/////////////////////////////////////
	//プレイヤー。
	Player* player = nullptr;
	Numberhouse* numberhouse;

	//注視点から視点に向かうベクトル。
	//一人称視点。
	Vector3 toCameraPos = Vector3::One;
	//三人称視点。
	Vector3 m_toCameraPos;
};

