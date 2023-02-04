#pragma once

#include "Level3DRender/LevelRender.h"

class Player;
class BackGround;
class GameCamera;
class Enemy01;
class Enemy02;
class Repair;
class Gameover;
class Walls;
class Tama;
class Dangan;
class GameUI3;
class Coin;
class Timeup;
class Kyuen;
class Masingan;
class Result;
class Baria;
class Tama_tuibi;
//class Boss02;
class Numberhouse;
class Tama_big;

class Game3 : public IGameObject
{
public:
	Game3();
	~Game3();
	//一度だけ読み込む。
	bool Start();
	//更新処理。
	void Update();
	//敵の出現。
	void Spawn();
	//アイテムの出現。
	void Item();
	//ボス(1_3)のステージの生成。
	void Final();
	//画面を暗転させる処理。
	void BrackOut();
	void Repairspawn();
	
	//メンバ変数。
	Player* player;			//プレイヤー。
	GameCamera* gameCamera;
	BackGround* backGround;
	Enemy01* enemy01;
	Enemy02* enemy02;
	Repair* repair;
	Dangan* dangan;
	Gameover* gameover;
	Walls* walls;
	Tama* tama;
	GameUI3* gameUI3;
	Coin* coin;
	Timeup* timeup;
	Kyuen* kyuen;
	Masingan* masingan;
	Result* result;
	Baria* baria;
	Tama_tuibi* tama_tuibi;
	Numberhouse* numberhouse;
	Tama_big* tama_big;
	
	SoundSource* BGM;//BGMの音
	Vector3 position;

	//敵の生成の条件。
	int Count = 0;
	int timeCount = 0;
	//enemy01用。敵の生成の制限。
	int enemyCount = 0;
	//////////////////////////////////////////////////////
	//enemy02用。敵の生成の制限。
	int enemyCount2 = 0;
	int updown;
	int up;
	int down;
	int spawnCount;
	int dead;
	/// ///////////////////////////////////////////////////
	//アイテム。
	float cointime = 0;
	int kget = 0;
	
	//コインを生成する数。
	int coincount = 5;

	int Hp;
	//プレイヤーがなくなったかの判定。
	int pd;
	//
	float time = 0;
	//制限時間300秒。
	float gametime = 300;
	bool GameOverFlag = false;

	int boss = 0;
	int bosstimer = 200;

	int change;

	int coin_rinzi = 0;
	int enemy_rinzi = 0;
	int time_rinzi = 0;
	//1_3を示す値。
	int stagenumber = 3;
	int rank_1 = 0;
	int rank_2 = 0;
	int rank_3 = 0;
	int sendstate = 0;

	int masinganGet;
	//
	bool SCDok = false;
	int sceneCount = 100;

	//gameoverを生成してから自身を消すまでの時間。
	int gameovertime = 100;
	//Gameoverのオブジェクトを生成したかの判定。
	int GameOverOK = 0;

	//repair
	int one=0;
	int repairtime = 500;
	int limit = 0;

	int SBPoint;
};

