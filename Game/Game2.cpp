#include "stdafx.h"
#include "Game2.h"
#include "BackGround.h"
#include "Player.h"
#include "GameCamera.h"
#include "Enemy01.h"
#include "Enemy02.h"
#include "Walls.h"
#include "Repair.h"
#include "Gameover.h"
#include "Tama.h"
#include "Dangan.h"
#include "Gamestart.h"
#include "GameUI2.h"
#include "Coin.h"
#include "Kyuen.h"
#include "Masingan.h"
#include "Baria.h"
#include "Tama_tuibi.h"
#include "Boss02.h"
#include "Result.h"
#include "Stagecelect.h"
#include "Numberhouse.h"
#include "Tama_big.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"

Game2::Game2()
{

}

Game2::~Game2()
{
	DeleteGO(gameCamera);
	DeleteGO(gameUI2);
	DeleteGO(numberhouse);
	DeleteGO(BGM);
	//�������O�̃I�u�W�F�N�g��S�Ĕj�󂷂�B
	QueryGOs<Player>("player", [&](Player* player_) {
		DeleteGO(player_);
		return true;
		});

	QueryGOs<Coin>("coin", [&](Coin* coin_) {
		DeleteGO(coin_);
		return true;
		});

	QueryGOs<Walls>("walls", [&](Walls* walls_) {
		DeleteGO(walls_);
		return true;
		});

	QueryGOs<Enemy01>("enemy01", [&](Enemy01* enemy01_) {
		DeleteGO(enemy01_);
		return true;
		});

	QueryGOs<Enemy02>("enemy02", [&](Enemy02* enemy02_) {
		DeleteGO(enemy02_);
		return true;
		});

	QueryGOs<Tama>("tama", [&](Tama* tama_) {
		DeleteGO(tama_);
		return true;
		});

	QueryGOs<Dangan>("dangan", [&](Dangan* dangan_) {
		DeleteGO(dangan_);
		return true;
		});

	QueryGOs<Repair>("repair", [&](Repair* repair_) {
		DeleteGO(repair_);
		return true;
		});

	QueryGOs<Kyuen>("kyuen", [&](Kyuen* kyuen_) {
		DeleteGO(kyuen_);
		return true;
		});

	QueryGOs<Masingan>("masingan", [&](Masingan* masingan_) {
		DeleteGO(masingan_);
		return true;
		});

	QueryGOs<Baria>("baria", [&](Baria* baria_) {
		DeleteGO(baria_);
		return true;
		});

	QueryGOs<Tama_tuibi>("tama_tuibi", [&](Tama_tuibi* tama_tuibi_) {
		DeleteGO(tama_tuibi_);
		return true;
		});

	QueryGOs<Tama_big>("tama_big", [&](Tama_big* tama_big_) {
		DeleteGO(tama_big_);
		return true;
		});

	QueryGOs<Boss02>("boss02", [&](Boss02* boss02_) {
		DeleteGO(boss02_);
		return true;
		});
}

bool Game2::Start()
{
	//Numberhouse�̃C���X�^���X��T���B
	numberhouse = FindGO<Numberhouse>("numberhouse");

	//�Q�[��UI2�̃C���X�^���X��T���B
	gameUI2 = FindGO<GameUI2>("gameUI2");

	// �����蔻��̉����B
	//�R�����g�A�E�g����B
	//PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();
	
	g_renderingEngine->SetAmbient({ 0.5f,0.5f,0.5f });
	g_renderingEngine->SetDirectionLight
	(0, Vector3{ 0.1f,0.1f,0.1f }, Vector3{ 0.01,0.01,0.01 });
	//�f�B���N�V�������C�g        //�J���[
	//BGM�̉���ǂݍ��ށB
	g_soundEngine->ResistWaveFileBank(11, "Assets/sound/battle.wav");
	//UI�̃I�u�W�F�N�g�����B
	gameUI2 = NewGO<GameUI2>(10, "gameUI2");

	//�v���C���[�̃I�u�W�F�N�g�����B
	player = NewGO<Player>(0, "player");
	player->position = { -500.0f,0.0f,0.0f };
	player->firstposition = player->position;

	//Numberhouse�̃I�u�W�F�N�g�����B
	numberhouse = NewGO<Numberhouse>(10, "numberhouse");

	//�Q�[���J�����̃I�u�W�F�N�g�����B
	gameCamera = NewGO<GameCamera>(0, "gamecamera");

	//�ǂ̃I�u�W�F�N�g�����B
	Walls* walls1 = NewGO<Walls>(0, "walls");
	walls1->position = { 0.0f,0.0f,0.0f };
	walls1->firstPosition = walls1->position;


	Walls* walls2 = NewGO<Walls>(0, "walls");
	walls2->position = { 4000.0f,0.0f,0.0f };
	walls2->firstPosition = walls2->position;
	//�X�e�[�W1_2�������l��numberhouse��stagenumber�ɑ������B
	numberhouse->stagenumber = stagenumber;

	//�v���C���[�̃C���X�^���X��T���B
	player = FindGO<Player>("player");
	
	BGM = NewGO<SoundSource>(11);
	BGM->Init(11);
	BGM->SetVolume(0.8f);
	BGM->Play(true);

	return true;
}

void Game2::Update()
{
	//gamestart���������ꂽ��B
	if (gameUI2->ms_btime <= 0)
	{
		if (gametime != 0) {
			time += 1;
			if (time >= 60)
			{
				gametime -= 1;
				time = 0;
			}
		}

		//���Ԑ؂�ɂȂ�����B
		if (gametime == 0)player->timeover = true;

		//�{�X�����ꂽ��BGM���~����B
		if (gameUI2->bossdeath == 1)
		{
			if (BGM->IsPlaying() == true)BGM->Stop();
		}
		
		//�v���C���[���|���ꂽ��B
		if (GameOverFlag == true)
		{
			if (GameOverOK == 0)
			{
				//�Q�[���I�[�o�[�̃I�u�W�F�N�g�����B
				Gameover* gameover = NewGO<Gameover>(0, "gameover");
				//player�AgameUI����l���󂯎��B
				player->SetResultDataToGame2();
				gameUI2->SetResultDataToGame();
				//�l���Q�[���I�[�o�[�ɓn���B
				gameover->Coin_rinzi = coin_rinzi;
				gameover->enemy_rinzi = enemy_rinzi;
				gameover->Timeup_rinzi = time_rinzi;
				//stagenumber(1_2)��gameover�ɓn���B
				gameover->stagenumber = stagenumber;
				gameover->rank_1 = rank_1;
				gameover->rank_2 = rank_2;
				gameover->rank_3 = rank_3;
				GameOverOK = 1;
			}
		}

		//�{�X���|���ꂽ��B
		if (gameUI2->mc_btime < 0)
		{
			Result* result = NewGO<Result>(0, "result");
			//player�AgameUI����l���󂯎��B
			player->SetResultDataToGame2();
			gameUI2->SetResultDataToGame();
			//�l��result�ɓn���B
			result->GetCoin = coin_rinzi;
			result->DownEnemy = enemy_rinzi;
			result->ttt = time_rinzi;
			//stagenumber(1_2)��result�ɓn���B
			result->stagenumber = stagenumber;
			result->rank_1 = rank_1;
			result->rank_2 = rank_2;
			result->rank_3 = rank_3;
			//���g���폜����B
			DeleteGO(this);
		}

		//�v���C���[�������Ă���ԁB
		if (GameOverFlag == false)
		{
			//���y�A��3�񐶐����ꂽ�甲���o��(���̊֐��̏������s��Ȃ�)�B
			if (limit < 3)
			{
				//���y�A�����̃N�|���^�C���B
				repairtime++;
				//���y�A�����B
				Repairspawn();
			}

			//gametime��35�ȏ�Ȃ甲���o���B
			if (gametime >= 165)
			{
				//enemy���o�������鏈���B
				Spawn();
			}
		}

		//�{�X�����Ȃ��ԁB
		if (bossstate == 0)
		{
			if (coincount != 0)
			{
				Item();
			}

		}

		//gametime��44���傫���Ȃ�����{�X�𐶐�����B
		if (gametime <= 156)
		{
			if (bossstate == 0)
			{
				Eboss02();
			}
		}
	}
	if (GameOverOK == 1)
	{
		gameovertime--;

		//���t���[������ɍ폜����B
		if (gameovertime <= 0)
		{
			//���g���폜����B
			DeleteGO(this);
		}
	}
}

void Game2::Spawn()
{
	//enemy01�̏o���B
	Count += 1;

	//Count��100��1�̐����B
	if (Count == 100)
	{
		//�O�̂܂Ő�������B
		if (enemyCount < 3)
		{
			//�G�̃I�u�W�F�N�g�����B
			Enemy01* enemy011 = NewGO<Enemy01>(0, "enemy01");
			enemy011->position = { 1100.0f, 9.0f, 0.0f };
			enemy011->firstPosition = enemy011->position;
			enemyCount += 1;

		}
	}
	/////////////////////////////////////////////////////////
	//Enemy02�̏o���B
	if (Count == 105)
	{
		//�o������m���B
		spawnCount = rand() % 10;
		//�ォ�������_���ɂ���B
		updown = rand() % 2;
		//��̂܂ł����������Ȃ��B����
		//spawnCount��5��菬����������B
		if (enemyCount2 < 3 && spawnCount < 5)
		{
			switch (updown)
			{
			case 0:
				//��ʏ㕔��1�̂��������Ă��Ȃ�������B
				if (up <= 0)
				{
					change= rand() % 2;
					Enemy02* enemy021 = NewGO<Enemy02>(0, "enemy02");
					enemy021->position = { 1100.0f, 350.0f, 0.0f };
					enemy021->firstPosition = enemy021->position;
					enemy021->firstPosition = enemy021->position;
					enemy021->firstPosition_up = enemy021->position;
					enemy021->firstPosition_down = enemy021->position;
					if (change >= 1)
					{
						//�s���p�^�[����ς���B
						enemy021->change = 1;
					}
					enemyCount2 += 2;
					up += 1;
					break;
				}

			case 1:
				//��ʉ�����1�̂��������Ă��Ȃ�������B
				if (down <= 0)
				{
					change = rand() % 2;
					Enemy02* enemy022 = NewGO<Enemy02>(0, "enemy02");
					enemy022->position = { 1100.0f, -350.0f, 0.0f };
					enemy022->firstPosition = enemy022->position;
					enemy022->firstPosition_up = enemy022->position;
					enemy022->firstPosition_down = enemy022->position;
					if (change >= 1)
					{
						//�s���p�^�[����ς���B
						enemy022->change = 1;
					}
					down += 1;
					enemyCount2 += 2;
			    	break;
				}
			default:
				break;
			}
		}
	}
	//����enemy02��2�̓|���ꂽ��B	
	if (dead >= 2)
	{
		enemyCount2 = 0;
		up = 0;
		down = 0;
		dead = 0;
	}

	//Count���Z�b�g�B
	if (Count == 110)
	{
		Count = 0;
		enemyCount = 0;
	}
}

void Game2::Item()
{
		//�R�C���̐����B
		cointime += 0.1;

		if (cointime >= 41)
		{
			Coin* coin = NewGO<Coin>(0, "coin");
			coin->position.x = 1100.0f;
			coin->position.y = rand() % 501 - 250;
			coin->position.z = 0.0f;
			coincount--;
			cointime = 0;
		}

		//�~��(masingan)�̐����B
		if (gameUI2->time < 183)
		{
			if (kget <= 0) {
				Kyuen* kyuen = NewGO<Kyuen>(0, "kyuen");
				kyuen->position.x = 1100.0f;
				kyuen->position.y = rand() % 501 - 250;
				kyuen->position.z = 0.0f;
				kget += 1;
			}
		}
}

void Game2::Repairspawn()
{
	//�����v���C���[��HP��50��50�ȉ��Ȃ�B
	if (player->playerHp <= 50 && repairtime >= 300)
	{
		if (player->one <= 0)
		{
			//repair�𐶐�����B
			Repair* repair = NewGO<Repair>(0, "repair");
			repair->position.x = 1100.0f;
			repair->position.y = rand() % 501 - 250;
			repair->position.z = 0.0f;
			repairtime = 0;
			player->one += 1;
			limit += 1;

		}
	}
}

void Game2::Eboss02()
{
	bosstimer -= 1;
	if (bosstimer <= 0)
	{
		if (boss == 0)
		{
			Boss02* boss02 = NewGO<Boss02>(0, "boss02");
			boss02->position_center = { 2000.0f,60.0f,0.0f };
			boss02->firstPosition_center = boss02->position_center;

			boss02->position_up = { 2000.0f,410.0f,0.0f };
			boss02->firstPosition_up = boss02->position_up;

			boss02->position_down = { 2000.0f,-290.0f,0.0f };
			boss02->firstPosition_down = boss02->position_down;
			

			boss = 1;
			bossstate = 1;
		}
	}
}