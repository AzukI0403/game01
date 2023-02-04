#include "stdafx.h"
#include "enemy01.h"
#include "Game.h"
#include "Dangan.h"
#include "Tama.h"
#include "Player.h"
#include "Baria.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
#include "Game2.h"
#include "Game3.h"
#include "graphics/effect/EffectEmitter.h"



Enemy01::Enemy01()
{

}

Enemy01::~Enemy01()
{
	DeleteGO(colli);
}

bool Enemy01::Start()
{
	//�v���C���[�̃C���X�^���X��T���B
	player = FindGO<Player>("player");
	//�Q�[��1_1�̃C���X�^���X��T���B
	game = FindGO<Game>("game");
	//�Q�[��1_2�̃C���X�^���X��T���B
	game2 = FindGO<Game2>("game2");
	//�Q�[���̃C���X�^���X��T���B
	baria = FindGO<Baria>("baria");
	//�Q�[��1_3�̃C���X�^���X��T���B
	game3 = FindGO<Game3>("game3");

	//��������I�u�W�F�N�g�̏������y������B
	modelRender.SetRaytracingWorld(false);
	modelRender.Init("Assets/modelData/enemy_eye.tkm");

	//�����̉���ǂݍ��ށB
	g_soundEngine->ResistWaveFileBank(2, "Assets/sound/enemy_death.wav");

	//�G�t�F�N�g��ǂݍ��ށB
	EffectEngine::GetInstance()->ResistEffect(0, u"Assets/effect/effectsprite/explosion.efk");

	//�R���W�����̍쐬�B
	colli = NewGO<CollisionObject>(0);
	colli->CreateSphere(Vector3(0.0f,0.0f, 0.0f), Quaternion::Identity,40.0f);
	colli->SetIsEnableAutoDelete(false);
	colli->SetName("enemy_eye");
	colli->SetPosition(position);


	characterController.Init(10.0f, 0.0f, position);

	//�ŏ��ɏ�Ɉړ����邩���Ɉړ����邩�����_���Ɍ��߂�B
	moveCount = rand() % 2;
	//�Ƃǂ܂邩�i�ނ������_���ɂ��߂�B
	go = rand() % 10;

	return true;
}



void Enemy01::Update()
{
	timeCount += 1;

	Move();
	
	Attack();

	//��ʓ��ɓ������瓖���蔻����s���B
	if (position.x <= 900)
	{
		//�e�ۂƂ̓����蔻��B
		Collisiond();
		//�v���C���[�Ƃ̓����蔻��B
		Collisionp();
		//�o���A�Ƃ̓����蔻��B
		Collisionb();
	}
	
	colli->SetPosition(position);
	modelRender.Update();
	
}

//�ړ������B
void Enemy01::Move()
{
	position = characterController.Execute(moveSpeed, 2.0 / 60.0f);

	//go��9��10�Ȃ�(�ˌ�)�B
	if (go > 8)
	{
		    //���̂܂ܐi�ށB
			moveSpeed.x -= 8.0f;
			if (position.x >= 1100)
			{
				timeCount = 0;

				//���g��j��B
				DeleteGO(this);
			}
		
	}
	//go��8�܂łȂ�(tama��ł�)�B
	else
	{
		//timeCount��340�ȉ��Ȃ�B
		if (timeCount <= 340)
		{
			if (position.x >= 700)
			{
				//x=700�܂ňړ��B
				moveSpeed.x -= 6.0f;
			}
			else
			{
				//x=700���O�ɂ����Ȃ��悤�ɂ���B
				moveSpeed.x = 0.0f;
			}

		}
		//timeCount��340�ȏ�Ȃ�B
		else
		{
			moveSpeed.x -= 12.0f;
			if (position.x >= 1200)
			{
				timeCount = 0;
				//���g��j��B
				DeleteGO(this);
			}
		}
	}
	
	//�㉺�ړ��B
	if (timeCount <= 340)
	{
		if (moveCount == 0)
		{
			//��Ɉړ�����B
			moveSpeed.y += 7.5f;
		}
		if (moveCount == 1)
		{
			//���Ɉړ�����B
			moveSpeed.y -= 7.5f;
		}
		//y���W���������Wy+50.0f�𒴂�����B
		if (position.y >= firstPosition.y + 50.0f)
		{
			//���Ɉړ�����B
			moveCount = 1;
		}
		//y���W���������Wy-50.0f�𒴂�����B
		if (position.y <= firstPosition.y - 50.0f)
		{
			//��Ɉړ�����B
			moveCount = 0;
		}
	}
	//�G�`������ɍ��W��������B
	modelRender.SetPosition(position);
}

//�U���B
void Enemy01::Attack()
{
	if (position.x <= 800)
	{
		tamatime += 1;
			if (tamatime == 80)
			{
				if (tamaCount <= 4)
				{
					tamaCount += 1;
					Tama* tama = NewGO<Tama>(0,"tama");
					tama->position = position;
					tama->firstposition = tama->position;
					
					tamatime = 0;
				}

			}
	}
}

//�e�ۂƂ̓����蔻��B
void Enemy01::Collisiond()
{
	//dangan�̃R���W�������擾����B
	const auto& collisions=g_collisionObjectManager->FindCollisionObjects("dangan");
	                       
	//collision�̔z���for���ŉ񂷁B
	for (auto collision : collisions)
	{
		//�ݒ肵���R���W�������Փ˂��������肷��B
		if (collision->IsHit(colli))
		{
			//�|�����G�̃J�E���g�𑝂₷�B
			player->downcount += 1;
			//���ʉ��ƃG�t�F�N�g���Đ�����B
			Dead();
			//���g��j�󂷂�B
			DeleteGO(this);
		}
	}
	
	
}
//�v���C���[�ɂԂ��������̔���B
void Enemy01::Collisionp()
{
	//player�̃R���W�������擾����B
	const auto& collisions = g_collisionObjectManager->FindCollisionObjects("player");

	//collision�̔z���for���ŉ񂷁B
	for (auto collision : collisions)
	{
		//�ݒ肵���R���W�������Փ˂��������肷��B
		if (collision->IsHit(colli))
		{
			//�Ԃ����������Ȃ�X�R�A�ɂ͉����Ȃ��B
			//player->downcount += 1;
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
			//���ʉ��ƃG�t�F�N�g���Đ�����B
			Dead();
			//���g��j�󂷂�B
			DeleteGO(this);
		}
	}
}
//baria�Ƃ̓����蔻��B
void Enemy01::Collisionb()
{
	//baria�̃R���W�������擾����B
	const auto& collisions = g_collisionObjectManager->FindCollisionObjects("baria");

	//collision�̔z���for���ŉ񂷁B
	for (auto collision : collisions)
	{
		//�ݒ肵���R���W�������Փ˂��������肷��B
		if (collision->IsHit(colli))
		{
			player->downcount += 1;
			//���ʉ��ƃG�t�F�N�g���Đ�����B
			Dead();
			//���g��j�󂷂�B
			DeleteGO(this);
		}
	}


}

//�G�l�~�[�����ꂽ�Ƃ��̏����B
void Enemy01::Dead()
{
	//���ꂽ�Ƃ��̉����Đ�����B
	death = NewGO<SoundSource>(2);
	death->Init(2);
	death->SetVolume(1.2f);
	death->Play(false);
	//���ꂽ�Ƃ��̃G�t�F�N�g���Đ�����B
	EffectEmitter* effectEmitter = NewGO<EffectEmitter>(0);
	effectEmitter->Init(0);
	effectEmitter->SetScale({ 10.0f,10.0f,10.0f });
	effectEmitter->SetPosition(position);
	effectEmitter->Play();
}

void Enemy01::Render(RenderContext& rc)
{
	modelRender.Draw(rc);
}