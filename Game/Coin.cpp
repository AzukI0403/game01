#include "stdafx.h"
#include "Coin.h"
#include "Game.h"
#include "Player.h"
#include "Game2.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"

Coin::Coin()
{

}

Coin::~Coin()
{
	DeleteGO(colli);
}

bool Coin::Start()
{
	//�v���C���[�̃C���X�^���X��T���B
	player = FindGO<Player>("player");
	//�Q�[��1_1�̃C���X�^���X��T���B
	game = FindGO<Game>("game");
	//�Q�[��1_2�̃C���X�^���X��T���B
	game2 = FindGO<Game2>("game2");
	//��������I�u�W�F�N�g�̏������y������B
	modelRender.SetRaytracingWorld(false);
	modelRender.Init("Assets/modelData/coin.tkm");

	//�R�C���̉���ǂݍ��ށB
	g_soundEngine->ResistWaveFileBank(5, "Assets/sound/coin_get.wav");

	//�R���W�����̍쐬�B
	colli = NewGO<CollisionObject>(0);
	colli->CreateSphere(Vector3(0.0f, 0.0f, 0.0f), Quaternion::Identity, 50.0f);
	colli->SetIsEnableAutoDelete(false);
	colli->SetName("coin");
	colli->SetPosition(position);

	return true;
}

void Coin::Update()
{
	//�ړ����x�B
	position.x -= 10.0f;

	if (position.x <= -1500)
	{
		DeleteGO(this);
	}

	//�v���C���[���R�C�����Ƃ����Ƃ��B
	if (player->get==1)
	{
		player->get = 0;
		//�v���C���[���R�C�����Q�b�g������B
			//�R�C���̉����Đ�����B
			Coinget = NewGO<SoundSource>(5);
			Coinget->Init(5);
			Coinget->SetVolume(1.2f);
			Coinget->Play(false);
		DeleteGO(this);
	}

	colli->SetPosition(position);

	modelRender.SetPosition(position);

	modelRender.Update();
}

void Coin::Render(RenderContext& rc)
{
	modelRender.Draw(rc);
}

