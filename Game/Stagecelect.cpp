#include "stdafx.h"
#include "Stagecelect.h"
#include "Game.h"
#include "Gamestart.h"
#include "Box1_1.h"
#include "Box1_2.h"
#include "Box1_3.h"
#include "GameCamera_sc.h"
#include "Sc_bg.h"
#include "Scoreboard.h"
#include "Game2.h"
#include "Game3.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
#include "SceneChangeDoor.h"

Stagecelect::Stagecelect()
{

}

Stagecelect::~Stagecelect()
{

	DeleteGO(gamecamera_sc);
	DeleteGO(box1_1);
	DeleteGO(box1_2);
	DeleteGO(box1_3);
	DeleteGO(sc_bg);

	QueryGOs<Scoreboard>("scoreboard", [&](Scoreboard* scoreboard_) {
		DeleteGO(scoreboard_);
		return true;
		});
}

bool Stagecelect::Start()
{	
	// 当たり判定の可視化。
	//コメントアウトする。
	//PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();
	
	g_renderingEngine->SetAmbient({ 0.5f,0.5f,0.5f });
	g_renderingEngine->SetDirectionLight
	(0, Vector3{ 0.1f,0.1f,0.1f }, Vector3{ 0.01,0.01,0.01 });
	//ディレクションライト        //カラー

	//扉を閉じるときの音を読み込む。
	g_soundEngine->ResistWaveFileBank(3, "Assets/sound/door_close.wav");

	//選択したときの音を読み込む。
	g_soundEngine->ResistWaveFileBank(7, "Assets/sound/dicision0.wav");

	spriteRender_ura.Init("Assets/sprite/stagecelect02.DDS", 1920.0f, 1080.0f);

	 spriteRender_pointer.Init("Assets/sprite/pointer.DDS", 150.0f, 150.0f);
	 spriteRender_pointer.SetPosition({ 0.0f,0.0f,0.0f });

	//ゲームカメラのオブジェクトを作る。
	gamecamera_sc = NewGO<GameCamera_sc>(0, "gamecamera_sc");
	//背景のオブジェクトを作る。
	sc_bg = NewGO<Sc_bg>(0, "stagecelect_bg");
	sc_bg->position={ 0.0f,0.0f,1200.0f };

	box1_1 = NewGO<Box1_1>(0, "1_1");
	box1_1->position = { -650.0f,-40.0f,0.0f };
	
	box1_2 = NewGO<Box1_2>(0, "1_2");
	box1_2->position = { -20.0f,190.0f,0.0f };
	
	 box1_3 = NewGO<Box1_3>(0, "1_3");
	box1_3->position = { 600.0f,60.0f,0.0f };
	//前回のステージのスコアのランクを代入する。
		box1_1->rank = rank_1;
		box1_2->rank = rank_2;
		box1_3->rank = rank_3;
	
	spriteRender_pointer.Update();
	return true;
}

void Stagecelect::Update()
{
	if (doorstate == 1) {
		//SceneChangeDoorのインスタンスを探す。
		SCD = FindGO<SceneChangeDoor>("SCD");
		doorstate = 2;
	}
	//Aボタンが押されたらコリジョンを作成する。
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		//コリジョンを１フレームの間生成する。
		state = 1;
		colli_pointer = NewGO<CollisionObject>(0);
		colli_pointer->CreateSphere(Vector3(0.0f, 0.0f, 0.0f), Quaternion::Identity, 70.0f);
		colli_pointer->SetIsEnableAutoDelete(true);
		colli_pointer->SetName("pointer");
		colli_pointer->SetPosition(pointerPos);

		Collition();
	}
	//ポインターの移動の処理。
	PMove();

	//Bボタンが押されたら
	if (g_pad[0]->IsTrigger(enButtonB))
	{
		//gamestart(タイトル)に戻る。
		NewGO<Gamestart>(0, "gamestart");
		DeleteGO(this);
	}
	//ステージナンバーに値が入力されたら。
	switch (stagenumber)
	{
	case 1:
		//画面上部下部の扉を移動させる。
		if (doorstate == 0)
		{
			SwitchScreen();
	    }
		
		//扉が閉じ切ったら。
		if (SCD->switchok == 1)
		{
			//ステージ1_1を生成する。
			Game* game = NewGO<Game>(0, "game");
			game->rank_1 = rank_1;
			game->rank_2 = rank_2;
			game->rank_3 = rank_3;
			DeleteGO(this);
		}
		
		break;
	case 2:
		//画面上部下部の扉を移動させる。
		if (doorstate == 0)
		{
			SwitchScreen();
		}
		//扉の移動が完了したら。
		if (SCD->switchok == 1)
		{

			//ステージ1_2を生成する。
			Game2* game2 = NewGO<Game2>(0, "game2");
			game2->rank_1 = rank_1;
			game2->rank_2 = rank_2;
			game2->rank_3 = rank_3;
			DeleteGO(this);
		}
		break;
	case 3:
		//SceneChangeDoorを一度だけ生成する。
		if (doorstate == 0)
		{
			SwitchScreen();
		}
		//扉の移動が完了したら。
		if (SCD->switchok == 1)
		{
			//ステージ1_3を生成する。
			Game3* game3 = NewGO<Game3>(0, "game3");
			game3->rank_1 = rank_1;
			game3->rank_2 = rank_2;
			game3->rank_3 = rank_3;
			DeleteGO(this);
		}
		break;

	default:
		break;
	}

	spriteRender_pointer.Update();
}

//ポインターの移動の処理。
void Stagecelect::PMove()
{
	
	if (g_pad[0]->IsPress(enButtonUp))
	{
		//上
		pointerPos.y += 20;
	}

	if (g_pad[0]->IsPress(enButtonDown))
	{
		//下
		pointerPos.y -= 20;
	}

	if (g_pad[0]->IsPress(enButtonLeft))
	{
		//左
		pointerPos.x -= 20;
	}

	if (g_pad[0]->IsPress(enButtonRight))
	{
		//右
		pointerPos.x += 20;
	}

	if (pointerPos.x > 900)pointerPos.x = 900;
	if (pointerPos.x < -900)pointerPos.x = -900;
	if (pointerPos.y > 500)pointerPos.y = 500;
	if (pointerPos.y < -500)pointerPos.y = -500;

	spriteRender_pointer.SetPosition(pointerPos);
}

void Stagecelect::Collition()
{
	//Box1_1のコリジョンを取得する。
	const auto& collisions_1_1 = g_collisionObjectManager->FindCollisionObjects("1_1");

	//collisionの配列をfor文で回す。
	for (auto collision : collisions_1_1)
	{
		//設定したコリジョンが衝突したか判定する。
		if (collision->IsHit(colli_pointer))
		{
			//決定したときの音を再生する。
			decision = NewGO<SoundSource>(7);
			decision->Init(7);
			decision->SetVolume(1.2f);
			decision->Play(false);
			stagenumber = 1;
		}
	}

	//Box1_2のコリジョンを取得する。
	const auto& collisions_1_2 = g_collisionObjectManager->FindCollisionObjects("1_2");

	//collisionの配列をfor文で回す。
	for (auto collision : collisions_1_2)
	{
		//設定したコリジョンが衝突したか判定する。
		if (collision->IsHit(colli_pointer))
		{
			//決定したときの音を再生する。
			decision = NewGO<SoundSource>(7);
			decision->Init(7);
			decision->SetVolume(1.2f);
			decision->Play(false);
			stagenumber = 2;
		}
	}

	//Box1_3のコリジョンを取得する。
	const auto& collisions_1_3 = g_collisionObjectManager->FindCollisionObjects("1_3");

	//collisionの配列をfor文で回す。
	for (auto collision : collisions_1_3)
	{
		//設定したコリジョンが衝突したか判定する。
		if (collision->IsHit(colli_pointer))
		{
			//決定したときの音を再生する。
			decision = NewGO<SoundSource>(7);
			decision->Init(7);
			decision->SetVolume(1.2f);
			decision->Play(false);
			stagenumber = 3;
		}
	}
}

void Stagecelect::SwitchScreen()
{
	
	SCD = NewGO<SceneChangeDoor>(0, "SCD");
	doorstate = 1;
}

void Stagecelect::Render(RenderContext& rc)
{
	spriteRender_ura.Draw(rc);
	spriteRender_pointer.Draw(rc);
}