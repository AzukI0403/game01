#pragma once
class Player;
class Game_final;
class Numberhouse;

class GameCamera:public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	bool Start();
	void Update();
	//切り替え判定。
	int playerState=0;
	/////////////////////////////////////
	//メンバ変数
	/////////////////////////////////////
	//プレイヤー。
	Player* player = nullptr;
	Game_final* game_final;
	Numberhouse* numberhouse;

	//注視点から視点に向かうベクトル。
	//一人称視点。
	Vector3 toCameraPos = Vector3::One;	
	//三人称視点。
	Vector3 m_toCameraPos;

	int stagenumber;
};

