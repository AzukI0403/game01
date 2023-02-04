#include "stdafx.h"
#include "SceneChangeDoor.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"

SceneChangeDoor::SceneChangeDoor()
{

}

SceneChangeDoor::~SceneChangeDoor()
{

}

bool SceneChangeDoor::Start()
{
	//扉を閉じるときの音を読み込む。
	g_soundEngine->ResistWaveFileBank(3, "Assets/sound/door_close.wav");

	//黒画面の設定。
	spriteRender_brack.Init("Assets/sprite/brackout.DDS", 1920.0f, 1080.0f);
	//透明の状態
	spriteRender_brack.SetMulColor({ 0.0f, 0.0f, 0.0f, 0.0f });

	spriteRender_switch_ue.Init("Assets/sprite/switchscreen_ue.DDS", 1940.0f, 1100.0f);
	spriteRender_switch_sita.Init("Assets/sprite/switchscreen_sita.DDS", 1940.0f, 1100.0f);

	spriteRender_switch_ue.SetPosition({ 0.0f,1190.0f,0.0f });
	spriteRender_switch_sita.SetPosition({ 0.0f,-1250.0f,0.0f });
	//0.0f,1190.0f,0.0f
	position_sc_ue = { 0.0f,990.0f,0.0f };
	//0.0f,-1235.0f,0.0f 
	position_sc_sita = { 0.0f,-1060.0f,0.0f };

	if (patten == 0)
	{
		//扉を閉めるときの音を再生する。
		doorclose = NewGO<SoundSource>(3);
		doorclose->Init(3);
		doorclose->SetVolume(1.2f);
		doorclose->Play(false);
	}

	return true;
}

void SceneChangeDoor::Update()
{
	switch (patten)
	{
	case 0:
		//stagecelectのときの処理。
		Door();

		spriteRender_switch_ue.Update();
		spriteRender_switch_sita.Update();
		break;
	case 1:
		//ステージ1_3からステージ_finalに移るときの処理。
		Brackout();

		spriteRender_brack.Update();
	default:
		break;
	}

	
}

void SceneChangeDoor::Door()
{
	if (position_sc_ue.y <= 217)
	{
		//扉を閉じきったら。
		closestate = false;
		//閉じたことを示す。
		switchok = 1;
		count--;
		if (count <= 0)
		{
			openstate = true;
		}
	}

	if (closestate == true)
	{
		position_sc_ue.y -= 10.0f;
		position_sc_sita.y += 10.0f;
	}

	if (count <= 0 && openstate == true)
	{
		position_sc_ue.y += 10.0f;
		position_sc_sita.y -= 10.0f;
	}

	if (position_sc_ue.y >= 1000)
	{
		DeleteGO(this);
	}


	spriteRender_switch_ue.SetPosition(position_sc_ue);
	spriteRender_switch_sita.SetPosition(position_sc_sita);
}

void SceneChangeDoor::Brackout()
{
	if (clear == true)blacktime--;

	//0.02ずつ暗くする。
	if (clear==false)
	{
		color += 0.01;
	}
	//0.02ずつ明るくする。
	if (blacktime<=0)
	{
		color -= 0.01;
	}

	//画面が暗くなったら。
	if (color >= 1)
	{
		clear = true;
	}
	

	spriteRender_brack.SetMulColor({ 0.0f, 0.0f, 0.0f, color });

	if (clear == true&&color <= 0.01)
	{
		DeleteGO(this);
	}
}

void SceneChangeDoor::Render(RenderContext& rc)
{
	if (patten == 0)
	{
		spriteRender_switch_ue.Draw(rc);
		spriteRender_switch_sita.Draw(rc);
	}
	if (patten == 1)
	{
		spriteRender_brack.Draw(rc);
	}
	


}