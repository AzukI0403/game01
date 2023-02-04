#include "stdafx.h"
#include "Walls.h"
#include "Game.h"
#include "Game2.h"
#include "Game3.h"
#include "Game_final.h"

Walls::Walls()
{
	
}

Walls::~Walls()
{

}

bool Walls::Start()
{
	//��������I�u�W�F�N�g�̏������y������B
	modelRender.SetRaytracingWorld(false);
	modelRender.Init("Assets/modelData/utyukabe.tkm");

	//�Q�[��1_1�̃C���X�^���X��T���B
	game = FindGO<Game>("game");
	//�Q�[��1_2�̃C���X�^���X��T���B
	game2 = FindGO<Game2>("game2");
	//�Q�[��1_1�̃C���X�^���X��T���B
	game3 = FindGO<Game3>("game3");
	//�Q�[��1_2�̃C���X�^���X��T���B
	game_final = FindGO<Game_final>("game_final");
	return true;
}

void Walls::Update()
{
	 Move();

	if (position.x <= -3600)
	{
		position.x = 4400;
	}

	 modelRender.Update();
}

void Walls::Move()
{
	//�ǂ̈ړ��B
	position.x -= 10.0f;

	modelRender.SetPosition(position);
}

void Walls::Render(RenderContext& rc)
{
	modelRender.Draw(rc);
}