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
class GameUI;
class Coin;
class Timeup;
class Kyuen;
class Masingan;
class Result;
class Baria;
class Tama_tuibi;
class Boss01;
class Numberhouse;

class Game : public IGameObject
{
public:
	Game();
	~Game();
	//一度だけ読み込む。
	bool Start();
	//更新処理。
	void Update();
	//敵の出現。
	void Spawn();
	//アイテムの出現。
	void Item();

	void Repairspawn();
	//ボス(１－１)の生成。
	void Eboss01();


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
	GameUI* gameUI;
	Coin* coin;
	Timeup* timeup;
	Kyuen* kyuen;
	Masingan* masingan;
	Result* result;
	Baria* baria;
	Tama_tuibi* tama_tuibi;
	Boss01* boss01;
	Numberhouse* numberhouse;

	Vector3 position;

	SoundSource* BGM;//BGMの音

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
	float cointime=0;
	//コインを生成する数。
	int coincount = 5;

	int kget=0;

	int Hp;
	//プレイヤーがなくなったかの判定。
	int pd;
	
	float time=0;
	//制限時間200秒。
	float gametime=200;
	//プレイヤーがやられたかの判定。
	bool GameOverFlag = false;

	int boss=0;
	int bossstate = 0;
	int bosstimer = 200;

	//受け取る値。
	int coin_rinzi = 0;
	int enemy_rinzi = 0;
	int time_rinzi = 0;

	//repair
	int one = 0;
	int repairtime = 500;
	int limit = 0;

	//gameoverを生成してから自身を消すまでの時間。
	int gameovertime=100;
	//Gameoverのオブジェクトを生成したかの判定。
	int GameOverOK = 0;

	//ステージ1_1を示す値。
	int stagenumber=1;
	int rank_1 = 0;
	int rank_2 = 0;
	int rank_3 = 0;
};

