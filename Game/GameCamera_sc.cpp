#include "stdafx.h"
#include "GameCamera_sc.h"
#include "Player.h"
#include "Numberhouse.h"

GameCamera_sc::GameCamera_sc()
{
}

GameCamera_sc::~GameCamera_sc()
{
}

bool GameCamera_sc::Start()
{

	//プレイヤーのインスタンスを探す。
	//player = FindGO<Player>("player");

	//Vector3 target = player->firstposition;
	//プレイヤからちょっと前を注視点とする。
	//target.x += 500.0f;
	//視点を計算する。
	//キャラクタを遠くから見ているような視点にする。
	Vector3 toPos = { 0.0f,0.0f, -1000.0f };
	//Quaternion rot = { 0.0f,70.0f,0.0f,0.0f };
	Vector3 pos = /*target*/ toPos;
	//メインカメラに注視点と視点を設定する。
	//g_camera3D->SetTarget(target);
	g_camera3D->SetPosition(pos);
	//カメラの更新。
	g_camera3D->Update();

	return true;
}

void GameCamera_sc::Update()
{
	

}