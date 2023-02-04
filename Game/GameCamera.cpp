#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"
#include "Game_final.h"
#include "Numberhouse.h"

GameCamera::GameCamera()
{
}

GameCamera::~GameCamera()
{
}

bool GameCamera::Start()
{
	
	//プレイヤーのインスタンスを探す。
	player = FindGO<Player>("player");
	numberhouse = FindGO<Numberhouse>("numberhouse");
	//game_final = FindGO<Game_final>("game_final");
	stagenumber = numberhouse->stagenumber;

	


	return true;
}

void GameCamera::Update()
{
	//game_finalのとき。
	if (stagenumber == 4)
	{
        //キャラクタを遠くから見ているような視点にする。
		Vector3 toPos = { 0.0f,0.0f, -800.0f };
		Vector3 pos = toPos;
		//メインカメラに注視点と視点を設定する。
		g_camera3D->SetPosition(pos);
		//200
		g_camera3D->SetNear(200.0f);
		g_camera3D->SetFar(4100.0f);

		//カメラの更新。
		g_camera3D->Update();
	}

	else
	{
		
        //キャラクタを遠くから見ているような視点にする。
		Vector3 toPos = { 0.0f,0.0f, -1000.0f };
		Vector3 pos =toPos;
		//メインカメラに注視点と視点を設定する。
		g_camera3D->SetPosition(pos);
		g_camera3D->SetFar(1500.0f);
	}
}