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
	//プレイヤーのインスタンスを探す。
	player = FindGO<Player>("player");
	return true;
}

void Numberhouse::Update()
{

}




