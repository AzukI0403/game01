#include "stdafx.h"
#include "Explanation.h"
#include "Game.h"
#include "Gamestart.h"

Explanation::Explanation()
{

}

Explanation::~Explanation()
{

}

bool Explanation::Start()
{
	//読み込む。
	spriteRender.Init("Assets/sprite/sousasetumei.DDS", 1920.0f, 1080.0f);
	spriteRender_atem.Init("Assets/sprite/atemsetumei.DDS", 1920.0f, 1080.0f);

	return true;
}

void Explanation::Update()
{
	//gamestart画面に戻る。
	if (g_pad[0]->IsTrigger(enButtonB)&& atemscreenON==0)
	{
		NewGO<Gamestart>(0,"gamestart");
		DeleteGO(this);
	}

	//アイテム説明画面に進む。
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		atemscreenON = 1;
	}

	//gamestart画面に戻る。
	if (g_pad[0]->IsTrigger(enButtonB))
	{
		atemscreenON = 0;
	}
}

void Explanation::Render(RenderContext& rc)
{
	spriteRender.Draw(rc);
	if (atemscreenON == 1)
	{
		spriteRender_atem.Draw(rc);
	}
}