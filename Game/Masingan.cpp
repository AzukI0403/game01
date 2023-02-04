#include "stdafx.h"
#include "Masingan.h"
#include "Dangan.h"
#include "Game.h"
#include "Player.h"
#include "Kyuen.h"
#include "Game2.h"

Masingan::Masingan()
{

}

Masingan::~Masingan()
{

}

bool Masingan::Start()
{
	//�v���C���[�̃C���X�^���X��T���B
	player = FindGO<Player>("player");
	//�Q�[��1_1�̃C���X�^���X��T���B
	game = FindGO<Game>("game");
	//�Q�[��1_2�̃C���X�^���X��T���B
	game2 = FindGO<Game2>("game2");
	//��������I�u�W�F�N�g�̏������y������B
	modelRender.SetRaytracingWorld(false);
	modelRender.Init("Assets/modelData/masingan.tkm");
	return true;
}

void Masingan::Update()
{
	position = player->position;
	position.y = player->position.y - 20.0f;

	//�G�`������ɍ��W��������B
	modelRender.SetPosition(position);
	modelRender.SetRotation(rotation);
	modelRender.Update();
}

void Masingan::Render(RenderContext& rc)
{
	modelRender.Draw(rc);
}
