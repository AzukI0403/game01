#include "stdafx.h"
#include "Gamestart.h"
#include "Game.h"
#include "Explanation.h"
#include "Stagecelect.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"

Gamestart::Gamestart()
{

}

Gamestart::~Gamestart()
{
	DeleteGO(BGM);
}

bool Gamestart::Start()
{
	//選択したときの音を読み込む。
	g_soundEngine->ResistWaveFileBank(8, "Assets/sound/decision01.wav");
	g_soundEngine->ResistWaveFileBank(9, "Assets/sound/title_BGM.wav");

	//読み込む。
	spriteRender.Init("Assets/sprite/gamestart.DDS", 1920.0f, 1080.0f);
	spriteRender_A.Init("Assets/sprite/bottunA.DDS", 960.0f, 100.0f);
	spriteRender_B.Init("Assets/sprite/bottunB.DDS", 960.0f, 100.0f);

	//文字
	spriteRender_A.SetPosition({ 300.0f, -150.0f, 0.0f });
	spriteRender_B.SetPosition({ 322.0f, -240.0f, 0.0f });

	spriteRender_A.Update();
	spriteRender_B.Update();

	BGM = NewGO<SoundSource>(9);
	BGM->Init(9);
	BGM->SetVolume(1.2f);
	BGM->Play(true);

	return true;
}

void Gamestart::Update()
{
	//ステージ選択画面を選択。
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		stageselectstate = 1;
		celect = NewGO<SoundSource>(8);
		celect->Init(8);
		celect->SetVolume(1.2f);
		celect->Play(false);
	}
	//操作説明画面を選択。
	if (g_pad[0]->IsTrigger(enButtonB))
	{
		explanationstate = 1;
		celect = NewGO<SoundSource>(8);
		celect->Init(8);
		celect->SetVolume(1.2f);
		celect->Play(false);
	}

	if (explanationstate == 1)
	{
		ExplanationSelect();
	}

	if (stageselectstate == 1)
	{
		StagecelectSelect();
	}

	spriteRender_A.Update();
	spriteRender_B.Update();
}

//Explanation(操作説明)を選んだときの処理。
void Gamestart::ExplanationSelect()
{
	//exNotDrawはspriteRender_Bを点滅させる処理。
	//falseは表示、trueは非表示。
	exNotDraw = false;

		count--;

		if (count % 10 == 0)
		{
			exNotDraw = true;
		}
	if (count <= 0)
	{
		NewGO<Explanation>(0, "explanation");
		DeleteGO(this);
	}
}

//Stagecelectを選んだときの処理。
void Gamestart::StagecelectSelect()
{
	//scNotDrawはspriteRender_Aを点滅させる処理。
	//falseは表示、trueは非表示。
	scNotDraw = false;

	count--;

	if (count % 10 == 0)
	{
		scNotDraw = true;
	}

	if (count <= 0)
	{
		Stagecelect* stagecelect = NewGO<Stagecelect>(0, "stagecelect");
		//stagecelectにrankを渡す。
		stagecelect->rank = rank;
		stagecelect->rank_1 = rank_1;
		stagecelect->rank_2 = rank_2;
		stagecelect->rank_3 = rank_3;
		stagecelect->StageNumber = stagenumber;
		DeleteGO(this);
	}
}

void Gamestart::Render(RenderContext& rc)
{
	spriteRender.Draw(rc);

	if (scNotDraw == false)spriteRender_A.Draw(rc);

	if (exNotDraw == false)spriteRender_B.Draw(rc);
}
