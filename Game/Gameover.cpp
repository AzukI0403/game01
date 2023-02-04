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
	//�̉���ǂݍ��ށB
	g_soundEngine->ResistWaveFileBank(6, "Assets/sound/gameover.wav");

	//�ǂݍ��ށB
	spriteRender.Init("Assets/sprite/gameover.DDS", 1920.0f, 1080.0f);
	spriteRender_A.Init("Assets/sprite/gameover_A.DDS", 1200.0f, 300.0f);
	spriteRender_B.Init("Assets/sprite/gameover_B.DDS", 1200.0f, 300.0f);

	//�����̏��
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
		//SceneChangeDoor�̃C���X�^���X��T���B
		SCD = FindGO<SceneChangeDoor>("SCD");
		doorstate = 2;
	}

	GOtime--;

	if (GOtime == -50)
	{
		//�Q�[���I�[�o�[�̉����Đ�����B
		gover = NewGO<SoundSource>(6);
		gover->Init(6);
		gover->SetVolume(1.2f);
		gover->Play(false);
	}

	if (GOtime <= 0)
	{
		//�Q�[���I�[�o�[�̕\���B
		if (color <= 1)
		{
			color += 0.01f;
			spriteRender.SetMulColor({ 1.0f, 1.0f, 1.0f, color });
		}

		//���U���g�A���g���C�̕\���B
		if (GOtime <= -50)
		{
			color_AB += 0.01f;
			spriteRender_A.SetMulColor({ 1.0f, 1.0f, 1.0f, color_AB });
			spriteRender_B.SetMulColor({ 1.0f, 1.0f, 1.0f, color_AB });
		}

		if (color >= 0.9)
		{
			//���U���g�B
			//����A�{�^���������ꂽ��B
			if (g_pad[0]->IsTrigger(enButtonA))
			{
				resultstate = 1;
			}

			//���g���C�B
			//����B�{�^���������ꂽ��B
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
//���U���g�̏����B
void Gameover::ResultGO()
{

	//resultNotDraw��spriteRender_A��_�ł����鏈���B
	//false�͕\���Atrue�͔�\���B
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
//���g���C�̏����B
void Gameover::RetryGO()
{
	//SceneChangeDoor����x������������B
	if (doorstate == 0)
	{
		SwitchScreen();
	}
	//retryNotDraw��spriteRender_B��_�ł����鏈���B
	//false�͕\���Atrue�͔�\���B
	retryNotDraw = false;

	count--;

	if (count % 10 == 0)
	{
		retryNotDraw = true;
	}

	//�������؂�����B
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
