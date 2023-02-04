#include "stdafx.h"
#include "Tama_big.h"
#include "Boss02.h"
#include "Game2.h"
#include "Player.h"
#include "Baria.h"

Tama_big::Tama_big()
{

}

Tama_big::~Tama_big()
{
	DeleteGO(colli);
}

bool Tama_big::Start()
{
	modelRender.SetRaytracingWorld(false);
	modelRender.Init("Assets/modelData/tama_big.tkm");

	//�Q�[��1_2�̃C���X�^���X��T���B
	game2 = FindGO<Game2>("game2");
	//�v���C���[�̃C���X�^���X��T���B
	player = FindGO<Player>("player");
	//�o���A�̃C���X�^���X��T���B
	baria = FindGO<Baria>("baria");

	//�R���W�����̍쐬�B
	colli = NewGO<CollisionObject>(0);
	colli->CreateSphere(Vector3(0.0f, 0.0f, 0.0f), Quaternion::Identity, 138.0f);
	colli->SetIsEnableAutoDelete(false);
	colli->SetName("tama_big");
	colli->SetPosition(position);

	return true;
}

void Tama_big::Update()
{
	position.x -= 8.0f;

	if (position.x <= -1200)
	{
		//���g�������B
		DeleteGO(this);
	}

	Collition();

	colli->SetPosition(position);

	modelRender.SetPosition(position);

	modelRender.Update();
}

void Tama_big::Collition()
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
		}
	}
}

void Tama_big::Render(RenderContext& rc)
{
	modelRender.Draw(rc);
}