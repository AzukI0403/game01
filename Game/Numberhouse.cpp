#include "stdafx.h"
#include "Numberhouse.h"
#include "Game.h"
#include "Game2.h"
#include "Player.h" 

Numberhouse::Numberhouse()
{

}

Numberhouse::~Numberhouse()
{

}

bool Numberhouse::Start()
{
	//�v���C���[�̃C���X�^���X��T���B
	player = FindGO<Player>("player");
	return true;
}

void Numberhouse::Update()
{

}




