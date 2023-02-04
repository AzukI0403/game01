#include "stdafx.h"
#include "Repair.h"
#include "Game.h"
#include "Player.h"
#include "Game2.h"
#include "Game3.h"
#include "graphics/effect/EffectEmitter.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
#include "Numberhouse.h"


Repair::Repair()
{
	
}

Repair::~Repair()
{
	DeleteGO(colli);
}

bool Repair::Start()
{
	//�v���C���[�̃C���X�^���X��T���B
	player = FindGO<Player>("player");
	//�Q�[��1_1�̃C���X�^���X��T���B
	game = FindGO<Game>("game");
	//�Q�[��1_2�̃C���X�^���X��T���B
	game2 = FindGO<Game2>("game2");
	//�Q�[��1_2�̃C���X�^���X��T���B
	game3 = FindGO<Game3>("game3");
	numberhouse = FindGO<Numberhouse>("numberhouse");

	//��������I�u�W�F�N�g�̏������y������B
	modelRender.SetRaytracingWorld(false);
	modelRender.Init("Assets/modelData/repair.tkm");

	//�I�������Ƃ��̉���ǂݍ��ށB
	g_soundEngine->ResistWaveFileBank(10, "Assets/sound/repair.wav");

	//�G�t�F�N�g��ǂݍ��ށB
	EffectEngine::GetInstance()->ResistEffect(4, u"Assets/effect/effectsprite/Recovery.efk");

	//�R���W�����̍쐬�B
	colli = NewGO<CollisionObject>(0);
	colli->CreateCapsule(Vector3(0.0f, 10.0f, 0.0f), Quaternion(90.0f,-35.0f,0.0f,0.0f), 23.0f,120.0f);
	colli->SetIsEnableAutoDelete(false);
	colli->SetName("repair");
	colli->SetPosition(position);
	
	return true;
}

void Repair::Update()
{
	if (player->repairget >= 1)
	{
		player->playerHp += 50;
		//�G�t�F�N�g�̍Đ��B
		Kaihuku();
		//�v���C���[��HP��100�𒴂���Ȃ�A�����Ȃ��悤�ɂ���B
		if (player->playerHp >= 100)
		{
			player->playerHp = 100;
		}
		player->repairget = 0;
		player->one = 0;

		//���g�������B
		DeleteGO(this);
	}
	
	//�ړ����x�B
	position.x -= 8.0f;

	//������������B
	//��ʊO�ɏo����B
	if (position.x <= -1100)
	{
		player->one = 0;

		int stagenumber=numberhouse->stagenumber;
		//��ʊO�ɏo���Ƃ������Ƃ�HP���񕜂��Ă��Ȃ��̂ŁAlimit���P���炷(���ɖ߂�)�B
		switch (stagenumber)
		{
		case 1:
			game->repairtime = 0;
			game->limit--;
			break;
		case 2:
			game2->repairtime = 0;
			game2->limit--;
			break;
		case 3:
			game3->repairtime = 0;
			game3->limit--;
			break;

		default:
			break;
		}

		DeleteGO(this);
	}

	colli->SetPosition(position);
	//�G�`������ɍ��W��������B
	modelRender.SetPosition(position);
	modelRender.Update();
}



void Repair::Kaihuku()
{
	kaifuku = NewGO<SoundSource>(10);
	kaifuku->Init(10);
	kaifuku->SetVolume(1.2f);
	kaifuku->Play(false);

	EffectEmitter* effectEmitter;
	effectEmitter = NewGO<EffectEmitter>(4);
	effectEmitter->Init(4);
	effectEmitter->SetScale({ 50.0f,40.0f,50.0f });
	effectEmitter->SetPosition(player->position);
	effectEmitter->Play();
}

void Repair::Render(RenderContext& rc)
{
	modelRender.Draw(rc);
}
