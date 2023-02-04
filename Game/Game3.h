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
	//��x�����ǂݍ��ށB
	bool Start();
	//�X�V�����B
	void Update();
	//�G�̏o���B
	void Spawn();
	//�A�C�e���̏o���B
	void Item();
	//�{�X(1_3)�̃X�e�[�W�̐����B
	void Final();
	//��ʂ��Ó]�����鏈���B
	void BrackOut();
	void Repairspawn();
	
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
	
	SoundSource* BGM;//BGM�̉�
	Vector3 position;

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
	
	//�R�C���𐶐����鐔�B
	int coincount = 5;

	int Hp;
	//�v���C���[���Ȃ��Ȃ������̔���B
	int pd;
	//
	float time = 0;
	//��������300�b�B
	float gametime = 300;
	bool GameOverFlag = false;

	int boss = 0;
	int bosstimer = 200;

	int change;

	int coin_rinzi = 0;
	int enemy_rinzi = 0;
	int time_rinzi = 0;
	//1_3�������l�B
	int stagenumber = 3;
	int rank_1 = 0;
	int rank_2 = 0;
	int rank_3 = 0;
	int sendstate = 0;

	int masinganGet;
	//
	bool SCDok = false;
	int sceneCount = 100;

	//gameover�𐶐����Ă��玩�g�������܂ł̎��ԁB
	int gameovertime = 100;
	//Gameover�̃I�u�W�F�N�g�𐶐��������̔���B
	int GameOverOK = 0;

	//repair
	int one=0;
	int repairtime = 500;
	int limit = 0;

	int SBPoint;
};

