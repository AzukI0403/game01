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

	//�v���C���[�̃C���X�^���X��T���B
	//player = FindGO<Player>("player");

	//Vector3 target = player->firstposition;
	//�v���C�����炿����ƑO�𒍎��_�Ƃ���B
	//target.x += 500.0f;
	//���_���v�Z����B
	//�L�����N�^���������猩�Ă���悤�Ȏ��_�ɂ���B
	Vector3 toPos = { 0.0f,0.0f, -1000.0f };
	//Quaternion rot = { 0.0f,70.0f,0.0f,0.0f };
	Vector3 pos = /*target*/ toPos;
	//���C���J�����ɒ����_�Ǝ��_��ݒ肷��B
	//g_camera3D->SetTarget(target);
	g_camera3D->SetPosition(pos);
	//�J�����̍X�V�B
	g_camera3D->Update();

	return true;
}

void GameCamera_sc::Update()
{
	

}