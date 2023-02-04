#include "stdafx.h"
#include "Game3.h"
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
#include "GameUI3.h"
#include "Coin.h"
#include "Kyuen.h"
#include "Masingan.h"
#include "Baria.h"
#include "Tama_tuibi.h"
#include "Result.h"
#include "Stagecelect.h"
#include "Numberhouse.h"
#include "Tama_big.h"
#include "Game_final.h"
#include "SceneChangeDoor.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"

Game3::Game3()
{

}

Game3::~Game3()
{
	DeleteGO(gameCamera);
	DeleteGO(gameUI3);
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
}

bool Game3::Start()
{
	// �����蔻��̉����B
	//�R�����g�A�E�g����B
	//PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();

	//BGM�̉���ǂݍ��ށB
	g_soundEngine->ResistWaveFileBank(11, "Assets/sound/battle.wav");
	//UI�̃I�u�W�F�N�g�����B
	gameUI3 = NewGO<GameUI3>(10, "gameUI3");
	//�X�e�[�W�̃i���o�[��n���B
	gameUI3->stagenumber = stagenumber;
	
	//Numberhouse�̃I�u�W�F�N�g�����B
	numberhouse = NewGO<Numberhouse>(10, "numberhouse");
	//�X�e�[�W1_3�������l��numberhouse��stagenumber�ɑ������B
	numberhouse->stagenumber = stagenumber;
	//�Q�[���J�����̃I�u�W�F�N�g�����B
	gameCamera = NewGO<GameCamera>(0, "gamecamera");

	//�v���C���[�̃I�u�W�F�N�g�����B
	player = NewGO<Player>(0, "player");
	player->position = { -500.0f,0.0f,0.0f };
	player->firstposition = player->position;

	//�ǂ̃I�u�W�F�N�g�����B
	Walls* walls1 = NewGO<Walls>(0, "walls");
	walls1->position = { 0.0f,0.0f,0.0f };
	walls1->firstPosition = walls1->position;


	Walls* walls2 = NewGO<Walls>(0, "walls");
	walls2->position = { 4000.0f,0.0f,0.0f };
	walls2->firstPosition = walls2->position;
	
	//�v���C���[�̃C���X�^���X��T���B
	player = FindGO<Player>("player");

	BGM = NewGO<SoundSource>(11);
	BGM->Init(11);
	BGM->SetVolume(0.8f);
	BGM->Play(true);

	return true;
}

void Game3::Update()
{
	//missonstart�̕\���������ꂽ��B
	if (gameUI3->ms_btime <= -70)
	{
		//game���̎��Ԃ��o�߂�����B
		time += 1;
		if (time >= 60)
		{
			gametime -= 1;
			time = 0;
		}

		//gametime��45���傫���Ȃ�����game_final�ɐ؂�ւ��邽�߂�
		//SceneChangeDoor�𐶐����Ó]������B
		if (gametime <= 255)
		{
			sceneCount--;
			//��x������������B
			if (SCDok == false)
			{
				SceneChangeDoor* SCD = NewGO< SceneChangeDoor>(0, "SCD");
				//SceneChangeDoor�̃C���X�^���X��T���B
				SCD = FindGO<SceneChangeDoor>("SCD");
				SCD->patten = 1;
				SCDok = true;
			}
			//�Ó]������game_final�𐶐�����B
				if (sceneCount <= 0)
				{
					Final();
					//���g���폜����B
					DeleteGO(this);
				}
		}

		//�v���C���[���|���ꂽ��B
		if (GameOverFlag == true)
		{
			if (GameOverOK == 0)
			{
				//�Q�[���I�[�o�[�̃I�u�W�F�N�g�����B
				Gameover* gameover = NewGO<Gameover>(0, "gameover");
				//player�AgameUI����l���󂯎��B
				player->SetResultDataToGame3();
				gameUI3->SetResultDataToGame();
				//�l���Q�[���I�[�o�[�ɓn���B
				gameover->Coin_rinzi = coin_rinzi;
				gameover->enemy_rinzi = enemy_rinzi;
				gameover->Timeup_rinzi = time_rinzi;
				//stagenumber(1_3)��gameover�ɓn���B
				gameover->stagenumber = stagenumber;
				gameover->rank_1 = rank_1;
				gameover->rank_2 = rank_2;
				gameover->rank_3 = rank_3;
				GameOverOK = 1;
			}
		}
		//�v���C���[�������Ă���ԁB
		if (GameOverFlag == false)
		{
			//37�b�܂�enemy�𐶐�����B
			if (gametime >= 263)
			{
				//enemy���o�������鏈���B
				Spawn();
			}
			//���y�A��3�񐶐����ꂽ�甲���o��(���̊֐��̏������s��Ȃ�)�B
			if (limit < 3)
			{
				//���y�A�����̃N�|���^�C���B
				repairtime++;
				//���y�A�����B
				Repairspawn();
			}
		}

		//�R�C���A�~���J�v�Z���̐����B
		if (coincount != 0)
		{
			Item();
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

void Game3::Spawn()
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
		//spawnCount��6��菬����������B
		if (enemyCount2 < 3 && spawnCount < 6)
		{
			switch (updown)
			{
			case 0:
				//��ʏ㕔��1�̂��������Ă��Ȃ�������B
				if (up <= 0)
				{
					change = rand() % 2;
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

void Game3::Final()
{
	Game_final* game_final = NewGO<Game_final>(0, "game_final");
	//player�AgameUI����l���󂯎��B
	player->SetResultDataToGame3();
	gameUI3->SetResultDataToGame();
	//�l��result�ɓn���B
	game_final->coin_rinzi = coin_rinzi;
	game_final->enemy_rinzi = enemy_rinzi;
	game_final->time_rinzi = time_rinzi;
	game_final->gametime = gametime;
	game_final->masinganGet = masinganGet;
	game_final->SBPoint = SBPoint;
	game_final->rank_1 = rank_1;
	game_final->rank_2 = rank_2;
	game_final->rank_3 = rank_3;
	
}

void Game3::Item()
{
		//�R�C���̐����B
		cointime += 0.1;

		if (cointime >= 40)
		{
			Coin* coin = NewGO<Coin>(0, "coin");
			coin->position.x = 1100.0f;
			coin->position.y = rand() % 501 - 250;
			coin->position.z = 0.0f;
			coincount--;
			cointime = 0;
		}

		//�~��(masingan)�̐����B
		if (gameUI3->time < 283)
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

void Game3::Repairspawn()
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
