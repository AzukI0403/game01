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
	//�I�������Ƃ��̉���ǂݍ��ށB
	g_soundEngine->ResistWaveFileBank(8, "Assets/sound/decision01.wav");
	g_soundEngine->ResistWaveFileBank(9, "Assets/sound/title_BGM.wav");

	//�ǂݍ��ށB
	spriteRender.Init("Assets/sprite/gamestart.DDS", 1920.0f, 1080.0f);
	spriteRender_A.Init("Assets/sprite/bottunA.DDS", 960.0f, 100.0f);
	spriteRender_B.Init("Assets/sprite/bottunB.DDS", 960.0f, 100.0f);

	//����
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
	//�X�e�[�W�I����ʂ�I���B
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		stageselectstate = 1;
		celect = NewGO<SoundSource>(8);
		celect->Init(8);
		celect->SetVolume(1.2f);
		celect->Play(false);
	}
	//���������ʂ�I���B
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

//Explanation(�������)��I�񂾂Ƃ��̏����B
void Gamestart::ExplanationSelect()
{
	//exNotDraw��spriteRender_B��_�ł����鏈���B
	//false�͕\���Atrue�͔�\���B
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

//Stagecelect��I�񂾂Ƃ��̏����B
void Gamestart::StagecelectSelect()
{
	//scNotDraw��spriteRender_A��_�ł����鏈���B
	//false�͕\���Atrue�͔�\���B
	scNotDraw = false;

	count--;

	if (count % 10 == 0)
	{
		scNotDraw = true;
	}

	if (count <= 0)
	{
		Stagecelect* stagecelect = NewGO<Stagecelect>(0, "stagecelect");
		//stagecelect��rank��n���B
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
