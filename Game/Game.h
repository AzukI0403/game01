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
	//��x�����ǂݍ��ށB
	bool Start();
	//�X�V�����B
	void Update();
	//�G�̏o���B
	void Spawn();
	//�A�C�e���̏o���B
	void Item();

	void Repairspawn();
	//�{�X(�P�|�P)�̐����B
	void Eboss01();


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
	float cointime=0;
	//�R�C���𐶐����鐔�B
	int coincount = 5;

	int kget=0;

	int Hp;
	//�v���C���[���Ȃ��Ȃ������̔���B
	int pd;
	
	float time=0;
	//��������200�b�B
	float gametime=200;
	//�v���C���[�����ꂽ���̔���B
	bool GameOverFlag = false;

	int boss=0;
	int bossstate = 0;
	int bosstimer = 200;

	//�󂯎��l�B
	int coin_rinzi = 0;
	int enemy_rinzi = 0;
	int time_rinzi = 0;

	//repair
	int one = 0;
	int repairtime = 500;
	int limit = 0;

	//gameover�𐶐����Ă��玩�g�������܂ł̎��ԁB
	int gameovertime=100;
	//Gameover�̃I�u�W�F�N�g�𐶐��������̔���B
	int GameOverOK = 0;

	//�X�e�[�W1_1�������l�B
	int stagenumber=1;
	int rank_1 = 0;
	int rank_2 = 0;
	int rank_3 = 0;
};

