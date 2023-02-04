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
	//同じ名前のオブジェクトを全て破壊する。
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
	//Numberhouseのインスタンスを探す。
	numberhouse = FindGO<Numberhouse>("numberhouse");

	//ゲームUI2のインスタンスを探す。
	gameUI2 = FindGO<GameUI2>("gameUI2");

	// 当たり判定の可視化。
	//コメントアウトする。
	//PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();
	
	g_renderingEngine->SetAmbient({ 0.5f,0.5f,0.5f });
	g_renderingEngine->SetDirectionLight
	(0, Vector3{ 0.1f,0.1f,0.1f }, Vector3{ 0.01,0.01,0.01 });
	//ディレクションライト        //カラー
	//BGMの音を読み込む。
	g_soundEngine->ResistWaveFileBank(11, "Assets/sound/battle.wav");
	//UIのオブジェクトを作る。
	gameUI2 = NewGO<GameUI2>(10, "gameUI2");

	//プレイヤーのオブジェクトを作る。
	player = NewGO<Player>(0, "player");
	player->position = { -500.0f,0.0f,0.0f };
	player->firstposition = player->position;

	//Numberhouseのオブジェクトを作る。
	numberhouse = NewGO<Numberhouse>(10, "numberhouse");

	//ゲームカメラのオブジェクトを作る。
	gameCamera = NewGO<GameCamera>(0, "gamecamera");

	//壁のオブジェクトを作る。
	Walls* walls1 = NewGO<Walls>(0, "walls");
	walls1->position = { 0.0f,0.0f,0.0f };
	walls1->firstPosition = walls1->position;


	Walls* walls2 = NewGO<Walls>(0, "walls");
	walls2->position = { 4000.0f,0.0f,0.0f };
	walls2->firstPosition = walls2->position;
	//ステージ1_2を示す値をnumberhouseのstagenumberに代入する。
	numberhouse->stagenumber = stagenumber;

	//プレイヤーのインスタンスを探す。
	player = FindGO<Player>("player");
	
	BGM = NewGO<SoundSource>(11);
	BGM->Init(11);
	BGM->SetVolume(0.8f);
	BGM->Play(true);

	return true;
}

void Game2::Update()
{
	//gamestartが消去されたら。
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

		//時間切れになったら。
		if (gametime == 0)player->timeover = true;

		//ボスがやられたらBGMを停止する。
		if (gameUI2->bossdeath == 1)
		{
			if (BGM->IsPlaying() == true)BGM->Stop();
		}
		
		//プレイヤーが倒されたら。
		if (GameOverFlag == true)
		{
			if (GameOverOK == 0)
			{
				//ゲームオーバーのオブジェクトを作る。
				Gameover* gameover = NewGO<Gameover>(0, "gameover");
				//player、gameUIから値を受け取る。
				player->SetResultDataToGame2();
				gameUI2->SetResultDataToGame();
				//値をゲームオーバーに渡す。
				gameover->Coin_rinzi = coin_rinzi;
				gameover->enemy_rinzi = enemy_rinzi;
				gameover->Timeup_rinzi = time_rinzi;
				//stagenumber(1_2)をgameoverに渡す。
				gameover->stagenumber = stagenumber;
				gameover->rank_1 = rank_1;
				gameover->rank_2 = rank_2;
				gameover->rank_3 = rank_3;
				GameOverOK = 1;
			}
		}

		//ボスが倒されたら。
		if (gameUI2->mc_btime < 0)
		{
			Result* result = NewGO<Result>(0, "result");
			//player、gameUIから値を受け取る。
			player->SetResultDataToGame2();
			gameUI2->SetResultDataToGame();
			//値をresultに渡す。
			result->GetCoin = coin_rinzi;
			result->DownEnemy = enemy_rinzi;
			result->ttt = time_rinzi;
			//stagenumber(1_2)をresultに渡す。
			result->stagenumber = stagenumber;
			result->rank_1 = rank_1;
			result->rank_2 = rank_2;
			result->rank_3 = rank_3;
			//自身を削除する。
			DeleteGO(this);
		}

		//プレイヤーが生きている間。
		if (GameOverFlag == false)
		{
			//リペアが3回生成されたら抜け出す(この関数の処理を行わない)。
			if (limit < 3)
			{
				//リペア生成のク－ルタイム。
				repairtime++;
				//リペア生成。
				Repairspawn();
			}

			//gametimeが35以上なら抜け出す。
			if (gametime >= 165)
			{
				//enemyを出現させる処理。
				Spawn();
			}
		}

		//ボスがいない間。
		if (bossstate == 0)
		{
			if (coincount != 0)
			{
				Item();
			}

		}

		//gametimeが44より大きくなったらボスを生成する。
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

		//何フレームか後に削除する。
		if (gameovertime <= 0)
		{
			//自身を削除する。
			DeleteGO(this);
		}
	}
}

void Game2::Spawn()
{
	//enemy01の出現。
	Count += 1;

	//Countが100で1体生成。
	if (Count == 100)
	{
		//三体まで生成する。
		if (enemyCount < 3)
		{
			//敵のオブジェクトを作る。
			Enemy01* enemy011 = NewGO<Enemy01>(0, "enemy01");
			enemy011->position = { 1100.0f, 9.0f, 0.0f };
			enemy011->firstPosition = enemy011->position;
			enemyCount += 1;

		}
	}
	/////////////////////////////////////////////////////////
	//Enemy02の出現。
	if (Count == 105)
	{
		//出現する確率。
		spawnCount = rand() % 10;
		//上か下ランダムにする。
		updown = rand() % 2;
		//二体までしか生成しない。かつ
		//spawnCountが5より小さかったら。
		if (enemyCount2 < 3 && spawnCount < 5)
		{
			switch (updown)
			{
			case 0:
				//画面上部に1体も生成していなかったら。
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
						//行動パターンを変える。
						enemy021->change = 1;
					}
					enemyCount2 += 2;
					up += 1;
					break;
				}

			case 1:
				//画面下部に1体も生成していなかったら。
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
						//行動パターンを変える。
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
	//もしenemy02が2体倒されたら。	
	if (dead >= 2)
	{
		enemyCount2 = 0;
		up = 0;
		down = 0;
		dead = 0;
	}

	//Countリセット。
	if (Count == 110)
	{
		Count = 0;
		enemyCount = 0;
	}
}

void Game2::Item()
{
		//コインの生成。
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

		//救援(masingan)の生成。
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
	//もしプレイヤーのHPが50か50以下なら。
	if (player->playerHp <= 50 && repairtime >= 300)
	{
		if (player->one <= 0)
		{
			//repairを生成する。
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