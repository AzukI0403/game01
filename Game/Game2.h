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
class GameUI2;
class Coin;
class Timeup;
class Kyuen;
class Masingan;
class Result;
class Baria;
class Tama_tuibi;
class Boss02;
class Numberhouse;
class Tama_big;

class Game2 : public IGameObject
{
public:
	Game2();
	~Game2();
	//��x�����ǂݍ��ށB
	bool Start();
	//�X�V�����B
	void Update();
	//�G�̏o���B
	void Spawn();
	//�A�C�e���̏o���B
	void Item();

	void Repairspawn();
	//�{�X(1_2)�̐����B
	void Eboss02();

	//�����o�ϐ��B
	Player* player;			//�v���C���[�B
	GameCamera* gameCamera;
	BackGround* backGround;
	Enemy01* enemy01;
	Enemy02* enemy02;
	Repair* repair;
	Dangan* dangan;
	Gameover* gameover;
	Walls* walls;
	Tama* tama;
	GameUI2* gameUI2;
	Coin* coin;
	Timeup* timeup;
	Kyuen* kyuen;
	Masingan* masingan;
	Result* result;
	Baria* baria;
	Tama_tuibi* tama_tuibi;
	Boss02* boss02;
	Numberhouse* numberhouse;
	Tama_big* tama_big;

	Vector3 position;
	SoundSource* BGM;//BGM�̉�

	//�G�̐����̏����B
	int Count = 0;
	int timeCount = 0;
	//enemy01�p�B�G�̐����̐����B
	int enemyCount = 0;
	//////////////////////////////////////////////////////
	//enemy02�p�B�G�̐����̐����B
	int enemyCount2 = 0;
	int updown;
	int up;
	int down;
	int spawnCount;
	int dead;
	/// ///////////////////////////////////////////////////
	//�A�C�e���B
	float cointime = 0;
	int kget = 0;

	int Hp;
	//�v���C���[���Ȃ��Ȃ������̔���B
	int pd;
	//
	float time = 0;
	//��������200�b�B
	float gametime = 200;
	bool GameOverFlag = false;

	int boss = 0;
	int bossstate = 0;
	int bosstimer = 200;

	int change;

	int coin_rinzi = 0;
	int enemy_rinzi = 0;
	int time_rinzi = 0;

	//�R�C���𐶐����鐔�B
	int coincount = 5;

	//repair
	int one = 0;
	int repairtime = 500;
	int limit = 0;

	//gameover�𐶐����Ă��玩�g�������܂ł̎��ԁB
	int gameovertime = 100;
	//Gameover�̃I�u�W�F�N�g�𐶐��������̔���B
	int GameOverOK = 0;


	//1_2�������l�B
	int stagenumber = 2;
	int sendstate=0;
	int rank_1 = 0;
	int rank_2 = 0;
	int rank_3 = 0;
};



