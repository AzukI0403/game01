#include "stdafx.h"
#include "Game.h"
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
#include "GameUI.h"
#include "Coin.h"
#include "Kyuen.h"
#include "Masingan.h"
#include "Baria.h"
#include "Tama_tuibi.h"
#include "Boss01.h"
#include "Result.h"
#include "Stagecelect.h"
#include "Numberhouse.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"


Game::Game()
{

}

Game::~Game()
{
	DeleteGO(gameCamera);
	DeleteGO(gameUI);
	DeleteGO(numberhouse);
	DeleteGO(BGM);
	//�������O�̃I�u�W�F�N�g��S�Ĕj�󂷂�B
	//DeleteGO(player);
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

	QueryGOs<Boss01>("boss01", [&](Boss01* boss01_) {
		DeleteGO(boss01_);
		return true;
		});
}

bool Game::Start()
{
	// �����蔻��̉����B
	//�R�����g�A�E�g����B
	//PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();

	//BGM�̉���ǂݍ��ށB
	g_soundEngine->ResistWaveFileBank(11, "Assets/sound/battle.wav");

	g_renderingEngine->SetAmbient({ 0.5f,0.5f,0.5f });
	g_renderingEngine->SetDirectionLight
	(0, Vector3{ 0.1f,0.1f,0.1f }, Vector3{ 0.01,0.01,0.01 });
	//�f�B���N�V�������C�g        //�J���[
	
	//UI�̃I�u�W�F�N�g�����B
	gameUI = NewGO<GameUI>(10, "gameUI");

	//�v���C���[�̃I�u�W�F�N�g�����B
	player = NewGO<Player>(0, "player");
	player->position = { -500.0f,0.0f,0.0f };
	player->firstposition = player->position;

	//�Q�[���J�����̃I�u�W�F�N�g�����B
	gameCamera = NewGO<GameCamera>(0, "gamecamera");

	//Numberhouse�̃I�u�W�F�N�g�����B
	numberhouse = NewGO<Numberhouse>(10, "numberhouse");

	//�ǂ̃I�u�W�F�N�g�����B
	Walls*walls1 = NewGO<Walls>(0,"walls");
	walls1->position = { 0.0f,0.0f,0.0f };
	walls1->firstPosition=walls1->position;


	Walls*walls2 = NewGO<Walls>(0,"walls");
	walls2->position = {4000.0f,0.0f,0.0f};
	walls2->firstPosition = walls2->position;
	//�X�e�[�W1_1�������l��numberhouse��stagenumber�ɑ������B
	numberhouse->stagenumber = stagenumber;
	//�v���C���[�̃C���X�^���X��T���B
	player = FindGO<Player>("player");

	BGM = NewGO<SoundSource>(11);
	BGM->Init(11);
	BGM->SetVolume(0.8f);
	BGM->Play(true);

	return true;
}

void Game::Update()
{
	//gamestart���������ꂽ��B
	if (gameUI->ms_btime <= 0)
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
		if (gameUI->bossdeath == 1)
		{
			if (BGM->IsPlaying() == true)BGM->Stop();
		}
		
		//�v���C���[���|���ꂽ��A�������͎��Ԑ؂�ɂȂ�����B
		if (GameOverFlag == true)
		{
			if (GameOverOK == 0)
			{
				//�Q�[���I�[�o�[�̃I�u�W�F�N�g�����B
				Gameover* gameover = NewGO<Gameover>(0, "gameover");
				//player�AgameUI����l���󂯎��B
				player->SetResultDataToGame();
				gameUI->SetResultDataToGame();
				//�l���Q�[���I�[�o�[�ɓn���B
				gameover->Coin_rinzi = coin_rinzi;
				gameover->enemy_rinzi = enemy_rinzi;
				gameover->Timeup_rinzi = time_rinzi;
				//stagenumber(1_1)��gameover�ɓn���B
				gameover->stagenumber = stagenumber;
				gameover->rank_1 = rank_1;
				gameover->rank_2 = rank_2;
				gameover->rank_3 = rank_3;
				GameOverOK = 1;
			}
				
		}

		//�{�X���|����ă~�b�V�����N���A�̕\�����I�������B
		if (gameUI->mc_btime < 0)
		{

			Result* result = NewGO<Result>(0, "result");
			//player�AgameUI����l���󂯎��B
			player->SetResultDataToGame();
			gameUI->SetResultDataToGame();
			//�l��result�ɓn���B
			result->GetCoin = coin_rinzi;
			result->DownEnemy = enemy_rinzi;
			result->ttt = time_rinzi;
			//stagenumber(1_1)��result�ɓn���B
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

				Eboss01();
				
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
//enemy�̏o���B
void Game::Spawn()
//enemy01�̏o���B
{
	Count += 1;
	//Count��115��1�̐����B
	if (Count == 100)
	{
		//�O�̂܂Ő�������B
		if (enemyCount < 3)
		{
			//�G�̃I�u�W�F�N�g�����B
			Enemy01* enemy011 = NewGO<Enemy01>(0,"enemy01");
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
		//spawnCount���S��菬����������B
		if (enemyCount2 < 3&&spawnCount<7)
		{
			switch (updown)
			{
			case 0:
				if (up <= 0)
				{
					Enemy02* enemy021 = NewGO<Enemy02>(0,"enemy02");
					enemy021->position = { 1100.0f, 370.0f, 0.0f };
					enemy021->firstPosition = enemy021->position;
					enemy021->firstPosition = enemy021->position;
					enemy021->firstPosition_up = enemy021->position;
					enemy021->firstPosition_down = enemy021->position;
					enemyCount2 += 2;
					up += 1;
					break;
				}
				
			case 1:
				if (down <= 0)
				{



					Enemy02* enemy022 = NewGO<Enemy02>(0, "enemy02");
					enemy022->position = { 1100.0f, -370.0f, 0.0f };
					enemy022->firstPosition = enemy022->position;
					enemy022->firstPosition_up = enemy022->position;
					enemy022->firstPosition_down = enemy022->position;
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
	if (Count >= 110)
	{
		Count = 0;
		enemyCount = 0;
		
		
	}
}

void Game::Item()
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

		//�~��(masingan)�̐����B25
		if (gameUI->time <183)
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

void Game::Repairspawn()
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
//�{�X�̐�������B
void Game::Eboss01()
{
	//bosstimer = 200
	bosstimer -= 1;
	if (bosstimer <= 0)
	{
		if (boss == 0)
		{
			Boss01* boss01 = NewGO<Boss01>(0, "boss01");
			boss01->position_up = {1500.0f,0.0f,0.0f};
			boss01->position_down = { 1500.0f,0.0f,0.0f };
			
			boss01->firstPosition_up = boss01->position_up;
			boss01->firstPosition_down = boss01->position_down;
			boss = 1;
			bossstate = 1;
		}
	}
	
}