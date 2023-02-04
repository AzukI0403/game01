#include "stdafx.h"
#include "Tama_tuibi.h"
#include "Enemy01.h"
#include "Player.h"
#include "Game.h"
#include "Baria.h"
#include "Game2.h"
#include "Numberhouse.h"

Tama_tuibi::Tama_tuibi()
{

}

Tama_tuibi::~Tama_tuibi()
{
	DeleteGO(colli);
}

bool Tama_tuibi::Start()
{
	baria = FindGO<Baria>("baria");

	modelRender.SetRaytracingWorld(false);
	modelRender.Init("Assets/modelData/tama02.tkm");

	//�Q�[��1_1�̃C���X�^���X��T���B
	game = FindGO<Game>("game");
	//�Q�[��1_2�̃C���X�^���X��T���B
	game2 = FindGO<Game2>("game2");
	//�v���C���[�̃C���X�^���X��T���B
	player = FindGO<Player>("player");

	//�R���W�����̍쐬�B
	colli = NewGO<CollisionObject>(0);
	colli->CreateSphere(Vector3(0.0f, 0.0f, 0.0f), Quaternion::Identity, 20.0f);
	colli->SetIsEnableAutoDelete(false);
	colli->SetName("tama_tuibi");
	colli->SetPosition(position);
	//tama�̑��x�B
	//tama����v���C���[�Ɍ������x�N�g�����v�Z����B
	Vector3 diff = player->position - position;

	//�x�N�g���𐳋K������B
	diff.Normalize();
	//�ړ����x��ݒ肷��B
	moveSpeed = diff * 10.0f;

	return true;
}

void Tama_tuibi::Update()
{
	countdown--;
	//tama�̒ǔ����d����������Ƃ��B
	//change == 1����countdown<=0&����count<=20�̂Ƃ��B
	//20��J��Ԃ��B
	if (change == 1&&countdown<=0&&count<=20)
	{
		//tama�̑��x�B
	//tama����v���C���[�Ɍ������x�N�g�����v�Z����B
		Vector3 diff = player->position - position;

		//�x�N�g���𐳋K������B
		diff.Normalize();
		//�ړ����x��ݒ肷��B
		moveSpeed = diff * 8.0f;

		countdown = 5;
		count++;
	}

	//�ړ����x�����W�ɑ����Ă����B
	position += moveSpeed;

	//��ʊO�ɏo����B
	if (position.x <= -1050||position.x>=1050||position.y>=1000||position.y<=-1000)
	{
		//���g�������B
		DeleteGO(this);
	}

	Collitionb();

	colli->SetPosition(position);

	modelRender.SetPosition(position);

	modelRender.Update();
}

void Tama_tuibi::Collitionb()
{
	//baria�̃R���W�������擾����B
	const auto& collisions = g_collisionObjectManager->FindCollisionObjects("baria");

	//collision�̔z���for���ŉ񂷁B
	for (auto collision : collisions)
	{
		//�ݒ肵���R���W�������Փ˂��������肷��B
		if (collision->IsHit(colli))
		{
			//���g��j�󂷂�B
			DeleteGO(this);
		}
	}

	//player�̃R���W�������擾����B
	const auto& collisions_p = g_collisionObjectManager->FindCollisionObjects("player");

	//collision�̔z���for���ŉ񂷁B
	for (auto collision : collisions_p)
	{
		//�ݒ肵���R���W�������Փ˂��������肷��B
		if (collision->IsHit(colli))
		{
			//���G���Ԃ�70�ȏ�̂Ƃ��B
			if (player->muteki >= 60)
			{
				//player��Hp��10���炷�B
				player->playerHp -= player->damage;
				//�_���[�W���󂯂��B
				player->damagestate = 1;
				//���G���ԃ��Z�b�g�B
				player->muteki = 0;
			}
			//���g��j�󂷂�B
			DeleteGO(this);
		}
	}
}

void Tama_tuibi::Render(RenderContext& rc)
{
	modelRender.Draw(rc);
}
