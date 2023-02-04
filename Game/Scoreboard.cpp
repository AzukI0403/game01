#include "stdafx.h"
#include "Scoreboard.h"
#include "Box1_1.h"
#include "Box1_2.h"
#include "Box1_3.h"

Scoreboard::Scoreboard()
{

}

Scoreboard::~Scoreboard()
{

}

bool Scoreboard::Start()
{
	modelRender.SetRaytracingWorld(false);
	modelRender.Init("Assets/modelData/scoreboard.tkm");
	
	//�O��̃����N(oldrank)�ƍ���̃����N(rank)���Ⴄ
	//���O��̃����N(oldrank)��荡��̃����N(rank)�������Ȃ�B
	if (oldrank != rank && oldrank < rank)
	{
		switch (rank)
		{
		case 1:
			modelRender_rank.SetRaytracingWorld(false);
			modelRender_rank.Init("Assets/modelData/rank_C.tkm");
			break;

		case 2:
			modelRender_rank.SetRaytracingWorld(false);
			modelRender_rank.Init("Assets/modelData/rank_B.tkm");
			break;

		case 3:
			modelRender_rank.SetRaytracingWorld(false);
			modelRender_rank.Init("Assets/modelData/rank_A.tkm");
			break;

		case 4:
			modelRender_rank.SetRaytracingWorld(false);
			modelRender_rank.Init("Assets/modelData/rank_S.tkm");
			break;

		case 5:
			modelRender_rank.SetRaytracingWorld(false);
			modelRender_rank.Init("Assets/modelData/rank_U.tkm");
			break;

		default:
			break;
		}
	}
	oldrank = rank;
	return true;
}

void Scoreboard::Update()
{
	//�����N��C�ȏ�Ȃ�(��x�X�e�[�W�ɒ��킵����)�B
	if (rank >= 1)
	{
		modelRender_rank.SetPosition(position_rank);
		modelRender_rank.Update();
	}
	modelRender.SetPosition(position);
	modelRender.Update();
}



void Scoreboard::Render(RenderContext& rc)
{
	modelRender.Draw(rc);
	//�Q�[�����N���A����ă����N�����肳�ꂽ��B
	if (rank >= 1)
	{
		modelRender_rank.Draw(rc);
	}
}