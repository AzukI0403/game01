#pragma once
#include "Level3DRender/LevelRender.h"

class Player;
class GameCamera;
class Repair;
class Gameover;
class BackGround;
class GameUI3;
class Masingan;
class Result;
class Baria;
class Numberhouse;
class Game3;
class Boss03;
class Enemy_bomb;
class Kyuen;

class Game_final:public IGameObject
{
public:
	Game_final();
	~Game_final();

	bool Start();
	void Update();
	void Eboss03();
	void Atem();

	Player* player;			//プレイヤー。
	GameCamera* gameCamera;
	Repair* repair;
	Gameover* gameover;
	BackGround* background;
	GameUI3* gameUI3;
	Masingan* masingan;
	Result* result;
	Baria* baria;
	Numberhouse* numberhouse;
	Game3* game3;
	Enemy_bomb* enemy_bomb;
	Kyuen* kyuen;
	Boss03* boss03;
	SoundSource* BGM;//BGMの音
	Vector3 position;
	ModelRender modelRender;

	int BGMOK = 0;
	//gameoverを生成してから自身を消すまでの時間=100。
	int gameovertime = 100;
	//Gameoverのオブジェクトを生成したかの判定。
	int GameOverOK = 0;

	int coin_rinzi = 0;
	int enemy_rinzi = 0;
	int time_rinzi = 0;

	int boss = 0;

	int SBPoint;

	int kget = 0;

	float time = 0;
	//進んだ時間。
	float gametime = 0;
	bool GameOverFlag = false;

	int masinganGet;

	//1_3_finalを示す値。
	int stagenumber = 4;
	int rank_1 = 0;
	int rank_2 = 0;
	int rank_3 = 0;
};

