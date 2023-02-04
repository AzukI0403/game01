#include "stdafx.h"
#include "Game_final.h"
#include "Player.h"
#include "GameCamera.h"
#include "BackGround.h"
#include "Repair.h"
#include "Gameover.h"
#include "Tama.h"
#include "Dangan.h"
#include "GameUI3.h"
#include "Masingan.h"
#include "Baria.h"
#include "Tama_tuibi.h"
#include "Result.h"
#include "Stagecelect.h"
#include "Numberhouse.h"
#include "Game3.h"
#include "Boss03.h"
#include "Enemy_bomb.h"
#include "Kyuen.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"


Game_final::Game_final()
{

}

Game_final::~Game_final()
{
	DeleteGO(gameCamera);
	DeleteGO(gameUI3);
	DeleteGO(numberhouse);
	DeleteGO(background);
	DeleteGO(BGM);
	//同じ名前のオブジェクトを全て破壊する。
	QueryGOs<Player>("player", [&](Player* player_) {
		DeleteGO(player_);
		return true;
		});

	QueryGOs<Kyuen>("kyuen", [&](Kyuen* kyuen_) {
		DeleteGO(kyuen_);
		return true;
		});

	QueryGOs<Boss03>("boss03", [&](Boss03* boss03_) {
		DeleteGO(boss03_);
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

	QueryGOs<Tama_tuibi>("tama_tuibi", [&](Tama_tuibi* tama_tuibi_) {
		DeleteGO(tama_tuibi_);
		return true;
		});

	QueryGOs<Enemy_bomb>("enemy_bomb", [&](Enemy_bomb* enemy_bomb_) {
		DeleteGO(enemy_bomb_);
		return true;
		});

	QueryGOs<Masingan>("masingan", [&](Masingan* masingan_) {
		DeleteGO(masingan_);
		return true;
		});
}

bool Game_final::Start()
{
	// 当たり判定の可視化。
	//コメントアウトする。
	//PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();
	//BGMの音を読み込む。
	g_soundEngine->ResistWaveFileBank(12, "Assets/sound/bossbattle.wav");
	//Numberhouseのオブジェクトを作る。
	numberhouse = NewGO<Numberhouse>(10, "numberhouse");
	numberhouse->stagenumber = stagenumber;

	g_renderingEngine->SetAmbient({ 0.1f,0.1f,0.1f });
	g_renderingEngine->SetDirectionLight
	(1, Vector3{ 0.1f,0.0f,0.1f }, Vector3{ 0.5,0.5,0.5 });
	//ディレクションライト        //カラー

	//プレイヤーのオブジェクトを作る。
	player = NewGO<Player>(0, "player");
	player->position = { 0.0f,0.0f,0.0f };
	player->rotation.SetRotationDegY(-90.0f);
	player->firstposition = player->position;
	player->stagenumber = stagenumber;
	player->getcount = coin_rinzi;
	player->downcount = enemy_rinzi;
	player->SBPoint = SBPoint;
	//プレイヤーのインスタンスを探す。
	player = FindGO<Player>("player");
	//player->MasinganG();
	if (masinganGet == 1)
	{
		masingan = NewGO<Masingan>(0, "masingan");
		masingan->position = player->position;
		//masingan->position.y += 100.0f;
		masingan->rotation.SetRotationDegY(-90.0f);
		player->MM = 1;
	}
	
	//GameUI3のオブジェクトを作る。
	gameUI3 = NewGO<GameUI3>(0, "gameUI3");
	gameUI3->stagenumber = stagenumber;
	gameUI3->ms_btime = -70;
	gameUI3->time = gametime;
	

	//ゲームカメラのオブジェクトを作る。
	gameCamera = NewGO<GameCamera>(0, "gamecamera");
	//壁のオブジェクトを作る。
	background = NewGO<BackGround>(0, "background");
	background->position = { 0.0f,0.0f,0.0f };

	return true;
}

void Game_final::Update()
{
		//game内の時間を経過させる。
	    //game3から継続している。
	//missonstartの表示が消されたら。
		time += 1;
		if (time >= 60)
		{
			gametime -= 1;
			time = 0;
		}
		//ボスがやられたらBGMを停止する。
		if (gameUI3->bossdeath == 1)
		{
			if (BGM->IsPlaying() == true)BGM->Stop();
		}
		//50秒になったらBGMを再生する。
		if (gametime == 250&&BGMOK==0) {
			BGM = NewGO<SoundSource>(12);
			BGM->Init(12);
			BGM->SetVolume(0.7f);
			BGM->Play(true);
			BGMOK = 1;
		}
		
		//プレイヤーが倒されたら。
		if (GameOverFlag == true)
		{
			if (GameOverOK == 0)
			{
				//ゲームオーバーのオブジェクトを作る。
				Gameover* gameover = NewGO<Gameover>(0, "gameover");
				//player、gameUIから値を受け取る。
				player->SetResultDataToGame4();
				//値をゲームオーバーに渡す。
				gameover->Coin_rinzi = coin_rinzi;
				gameover->enemy_rinzi = enemy_rinzi;
				gameover->Timeup_rinzi = gametime;
				//stagenumber(1_3)をgameoverに渡す。
				stagenumber = 3;
				gameover->stagenumber = stagenumber;
				gameover->rank_1 = rank_1;
				gameover->rank_2 = rank_2;
				gameover->rank_3 = rank_3;
				GameOverOK = 1;
			}
		}

		//ボスが倒されたら。
		if (/*g_pad[0]->IsTrigger(enButtonA)*/gameUI3->mc_btime < 0)
		{
			Result* result = NewGO<Result>(0, "result");
			//player、gameUIから値を受け取る。
			player->SetResultDataToGame4();
			//gameUI3->SetResultDataToGame();
			//値をresultに渡す。
			result->GetCoin = coin_rinzi;
			result->DownEnemy = enemy_rinzi;
			result->ttt = gametime/*time_rinzi*/;
			//stagenumber(1_3)をresultに渡す。
			stagenumber = 3;
			result->stagenumber = stagenumber;
			result->rank_1 = rank_1;
			result->rank_2 = rank_2;
			result->rank_3 = rank_3;
			//自身を削除する。
			DeleteGO(this);
		}

		Atem();

		//gametimeが５より大きくなったらボスを生成する。
		if (gametime <= 245&&boss==0)
		{
			Eboss03();
		}

		if (GameOverOK == 1)
		{
			gameovertime--;

			//100フレーム後に削除する。
			if (gameovertime <= 0)
			{
				//自身を削除する。
				DeleteGO(this);
			}
		}
}

void Game_final::Eboss03()
{
		Boss03* boss03 = NewGO<Boss03>(0, "boss03");
		boss03->position = { 0.0f,-2000.0f,1200.0f };
		boss03->firstposition = boss03->position;
		boss03->position_ring = {0.0f,-2000.0f,1600.0f};
		boss03->firstposition_ring = boss03->position_ring;
		gameUI3->boss = 1;
		boss = 1;
}

void Game_final::Atem()
{
	int PUtime=gametime;
	//救援(masingan)の生成。
	if (PUtime %70 == 0)
	{
		if (kget <= 0) {
			Kyuen* kyuen = NewGO<Kyuen>(0, "kyuen");
			kyuen->position.x = 1100.0f;
			kyuen->position.y = rand() % 501 - 250;
			kyuen->position.z = 0.0f;
			kget += 1;
		}
	}
	if (PUtime % 100 == 0)kget = 0;
}