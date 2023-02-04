#include "stdafx.h"
#include "Timeup.h"
#include "Game.h"
#include "Result.h"

Timeup::Timeup()
{

}

Timeup::~Timeup()
{

}

bool Timeup::Start()
{
	//“Ç‚Ýž‚ÞB
	spriteRender.Init("Assets/sprite/timeup.DDS", 1920.0f, 1080.0f);

	return true;
}

void Timeup::Update()
{
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		Result* result = NewGO<Result>(0, "result");
		result->GetCoin = Coin_rinzi;
		result->DownEnemy = enemy_rinzi;
		result->ttt = Timeup_rinzi;


		DeleteGO(this);
	}
}

void Timeup::Render(RenderContext& rc)
{
	spriteRender.Draw(rc);
}