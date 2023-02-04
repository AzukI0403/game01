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
	//プレイヤーのインスタンスを探す。
	player = FindGO<Player>("player");
	//ゲーム1_1のインスタンスを探す。
	game = FindGO<Game>("game");
	//ゲーム1_2のインスタンスを探す。
	game2 = FindGO<Game2>("game2");
	//生成するオブジェクトの処理を軽くする。
	modelRender.SetRaytracingWorld(false);
	modelRender.Init("Assets/modelData/masingan.tkm");
	return true;
}

void Masingan::Update()
{
	position = player->position;
	position.y = player->position.y - 20.0f;

	//絵描きさんに座標を教える。
	modelRender.SetPosition(position);
	modelRender.SetRotation(rotation);
	modelRender.Update();
}

void Masingan::Render(RenderContext& rc)
{
	modelRender.Draw(rc);
}
