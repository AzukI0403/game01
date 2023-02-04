#include "stdafx.h"
#include "Gameover.h"
#include "Game.h"
#include "Game2.h"
#include "Game3.h"
#include "Game_final.h"
#include "Gamestart.h"
#include "Result.h"
#include "Numberhouse.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
#include "SceneChangeDoor.h"

Gameover::Gameover()
{

}

Gameover::~Gameover()
{

}

bool Gameover::Start()
{
	//の音を読み込む。
	g_soundEngine->ResistWaveFileBank(6, "Assets/sound/gameover.wav");

	//読み込む。
	spriteRender.Init("Assets/sprite/gameover.DDS", 1920.0f, 1080.0f);
	spriteRender_A.Init("Assets/sprite/gameover_A.DDS", 1200.0f, 300.0f);
	spriteRender_B.Init("Assets/sprite/gameover_B.DDS", 1200.0f, 300.0f);

	//透明の状態
	spriteRender.SetMulColor({ 0.0f, 0.0f, 0.0f, 0.0f });
	spriteRender_A.SetMulColor({ 0.0f, 0.0f, 0.0f, 0.0f });
	spriteRender_B.SetMulColor({ 0.0f, 0.0f, 0.0f, 0.0f });

	spriteRender_A.SetPosition({ 0.0f,-300.0f,0.0f });
	spriteRender_B.SetPosition({ 0.0f,-390.0f,0.0f });

	spriteRender_A.Update();
	spriteRender_B.Update();

	return true;
}

void Gameover::Update()
{
	if (doorstate == 1) {
		//SceneChangeDoorのインスタンスを探す。
		SCD = FindGO<SceneChangeDoor>("SCD");
		doorstate = 2;
	}

	GOtime--;

	if (GOtime == -50)
	{
		//ゲームオーバーの音を再生する。
		gover = NewGO<SoundSource>(6);
		gover->Init(6);
		gover->SetVolume(1.2f);
		gover->Play(false);
	}

	if (GOtime <= 0)
	{
		//ゲームオーバーの表示。
		if (color <= 1)
		{
			color += 0.01f;
			spriteRender.SetMulColor({ 1.0f, 1.0f, 1.0f, color });
		}

		//リザルト、リトライの表示。
		if (GOtime <= -50)
		{
			color_AB += 0.01f;
			spriteRender_A.SetMulColor({ 1.0f, 1.0f, 1.0f, color_AB });
			spriteRender_B.SetMulColor({ 1.0f, 1.0f, 1.0f, color_AB });
		}

		if (color >= 0.9)
		{
			//リザルト。
			//もしAボタンが押されたら。
			if (g_pad[0]->IsTrigger(enButtonA))
			{
				resultstate = 1;
			}

			//リトライ。
			//もしBボタンが押されたら。
			if (g_pad[0]->IsTrigger(enButtonB))
			{
				retrystate = 1;
			}
		}
	}
	
	if (resultstate == 1)ResultGO();

	if (retrystate == 1)RetryGO();


	spriteRender.Update();
	spriteRender_A.Update();
	spriteRender_B.Update();
}
//リザルトの処理。
void Gameover::ResultGO()
{

	//resultNotDrawはspriteRender_Aを点滅させる処理。
	//falseは表示、trueは非表示。
	resultNotDraw = false;

	count--;

	if (count % 10 == 0)
	{
		resultNotDraw = true;
	}

		if (count <= 0)
		{
			Result* result = NewGO<Result>(0, "result");
			result->GetCoin = Coin_rinzi;
			result->DownEnemy = enemy_rinzi;
			result->ttt = Timeup_rinzi;
			result->stagenumber = stagenumber;
			result->rank_1 = rank_1;
			result->rank_2 = rank_2;
			result->rank_3 = rank_3;
			DeleteGO(this);
		}
}
//リトライの処理。
void Gameover::RetryGO()
{
	//SceneChangeDoorを一度だけ生成する。
	if (doorstate == 0)
	{
		SwitchScreen();
	}
	//retryNotDrawはspriteRender_Bを点滅させる処理。
	//falseは表示、trueは非表示。
	retryNotDraw = false;

	count--;

	if (count % 10 == 0)
	{
		retryNotDraw = true;
	}

	//扉が閉じ切ったら。
	if (SCD->switchok == 1) {
		if (count <= 0)
		{
			switch (stagenumber)
			{
			case 1:
				NewGO<Game>(0, "game");
				DeleteGO(this);
				break;

			case 2:
				NewGO<Game2>(0, "game2");
				DeleteGO(this);
				break;

			case 3:
				NewGO<Game3>(0, "game3");
				DeleteGO(this);
				break;

			default:
				break;
			}
		}
	}
	
}

void Gameover::SwitchScreen()
{

	SCD = NewGO<SceneChangeDoor>(0, "SCD");
	doorstate = 1;
}

void Gameover::Render(RenderContext& rc)
{
	spriteRender.Draw(rc);

	if(resultNotDraw==false)spriteRender_A.Draw(rc);

	if(retryNotDraw==false)spriteRender_B.Draw(rc);

}
