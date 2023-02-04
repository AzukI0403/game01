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
	//生成するオブジェクトの処理を軽くする。
	modelRender.SetRaytracingWorld(false);
	modelRender.Init("Assets/modelData/utyukabe.tkm");

	//ゲーム1_1のインスタンスを探す。
	game = FindGO<Game>("game");
	//ゲーム1_2のインスタンスを探す。
	game2 = FindGO<Game2>("game2");
	//ゲーム1_1のインスタンスを探す。
	game3 = FindGO<Game3>("game3");
	//ゲーム1_2のインスタンスを探す。
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
	//壁の移動。
	position.x -= 10.0f;

	modelRender.SetPosition(position);
}

void Walls::Render(RenderContext& rc)
{
	modelRender.Draw(rc);
}