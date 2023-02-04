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
	
	//�v���C���[�̃C���X�^���X��T���B
	player = FindGO<Player>("player");
	numberhouse = FindGO<Numberhouse>("numberhouse");
	//game_final = FindGO<Game_final>("game_final");
	stagenumber = numberhouse->stagenumber;

	


	return true;
}

void GameCamera::Update()
{
	//game_final�̂Ƃ��B
	if (stagenumber == 4)
	{
        //�L�����N�^���������猩�Ă���悤�Ȏ��_�ɂ���B
		Vector3 toPos = { 0.0f,0.0f, -800.0f };
		Vector3 pos = toPos;
		//���C���J�����ɒ����_�Ǝ��_��ݒ肷��B
		g_camera3D->SetPosition(pos);
		//200
		g_camera3D->SetNear(200.0f);
		g_camera3D->SetFar(4100.0f);

		//�J�����̍X�V�B
		g_camera3D->Update();
	}

	else
	{
		
        //�L�����N�^���������猩�Ă���悤�Ȏ��_�ɂ���B
		Vector3 toPos = { 0.0f,0.0f, -1000.0f };
		Vector3 pos =toPos;
		//���C���J�����ɒ����_�Ǝ��_��ݒ肷��B
		g_camera3D->SetPosition(pos);
		g_camera3D->SetFar(1500.0f);
	}
}