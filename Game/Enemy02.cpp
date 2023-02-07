#include "stdafx.h"
#include "Enemy02.h"
#include "Game.h"
#include "Dangan.h"
#include "Player.h"
#include "Tama.h"
#include "Tama_tuibi.h"
#include "Game2.h"
#include "Game3.h"
#include "Numberhouse.h"
#include "Baria.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
#include "graphics/effect/EffectEmitter.h"

bool Enemy02::Start()
{

	//��������I�u�W�F�N�g�̏������y������B
	modelRender_eye.SetRaytracingWorld(false);
	modelRender_eye.Init("Assets/modelData/shell_eye.tkm");
	modelRender_up.SetRaytracingWorld(false);
	modelRender_up.Init("Assets/modelData/shell_up.tkm");
	modelRender_down.SetRaytracingWorld(false);
	modelRender_down.Init("Assets/modelData/shell_down.tkm");

	//���ꂽ�Ƃ��̉���ǂݍ��ށB
	g_soundEngine->ResistWaveFileBank(2, "Assets/sound/enemy_death.wav");

	//�G�t�F�N�g��ǂݍ��ށB
	EffectEngine::GetInstance()->ResistEffect(0, u"Assets/effect/explosion.efk");

	//�R���W�����̍쐬�B
	colli = NewGO<CollisionObject>(0);
	colli->CreateSphere(Vector3(0.0f, 0.0f, 0.0f), Quaternion::Identity, 30.0f);
	colli->SetIsEnableAutoDelete(false);
	colli->SetName("enemy02");
	colli->SetPosition(position);

	//�Q�[��1_1�̃C���X�^���X��T���B
	game = FindGO<Game>("game");
	//�Q�[��1_2�̃C���X�^���X��T���B
	game2 = FindGO<Game2>("game2");
	player = FindGO<Player>("player");
	//�Q�[��1_3�̃C���X�^���X��T���B
	game3 = FindGO<Game3>("game3");
	//�o���A�̃C���X�^���X��T���B
	baria = FindGO<Baria>("baria");
	//Numberhouse�̃C���X�^���X��T���B
	numberhouse = FindGO<Numberhouse>("numberhouse");
	stagenumber = numberhouse->stagenumber;

	if (numberhouse->stagenumber == 3)
	{
		tamachange = 1;
	}

	position_up = position;
	position_down = position;

	return true;
}

Enemy02::Enemy02()
{

}

Enemy02::~Enemy02()
{
	DeleteGO(colli);
}

void Enemy02::Update()
{
	//��ʍ��Ɉړ�����Ƃ�
	if (change == 1)
	{
		Move2();
	}
	//��ʉE�Ɉړ�����Ƃ�
	else
	{
		Move();
	}

	Rotation();

	if (attackstate == 1)
	{
		Attack();
	}
	
	if(position.x<=900)Collision();

	colli->SetPosition(position);
	modelRender_eye.SetPosition(position);
	modelRender_up.SetPosition(position_up);
	modelRender_down.SetPosition(position_down);
	modelRender_eye.Update();
	modelRender_up.Update();
	modelRender_down.Update();
}

void Enemy02::Move()
{
	timer--;
	
	if (timer <= -100)
	{
		position.x += 10.0f;
		position_up.x += 10.0f;
		position_down.x += 10.0f;
		if (position.x >= 1300)
		{
			Dead();
			DeleteGO(this);
		}
	}

	//position.x��800���傫���Ȃ�B
	else if (position.x >= 800)
		{
			//�ړ����x�B
			position.x -= 10.0f;
			position_up.x -= 10.0f;
			position_down.x -= 10.0f;
		}
		
		//stopstate��1�̂Ƃ��Ashell���J���Ă���A���Ă����Ԃ��ێ�����B
		if (stopstate == 1)
		{
			opentimer--;
			
			if (opentimer > 0)
			{
				return;
			}
			else if (opentimer <= 0)
			{
				opentimer = 100;
				stopstate = 0;
			}
		}

		//shell_up�̏㉺�ړ��B
		//shell���J���B
		if (upstate == 0)
		{
			gardstate = 0;
			//��Ɉړ�����B
			position_up.y += 2.0f;
			//���Ɉړ�����B
			position_down.y -= 2.0f;
			
		}
		//shell�����B
		if (upstate == 1)
		{
			//���Ɉړ�����B
			position_up.y -= 2.0f;
			//��Ɉړ�����B
			position_down.y += 2.0f;
			
		}

		//shell_up��firstPosition_up.x���傫���Ȃ�����(shell���J������)�B
		if (position_up.y >= firstPosition_up.y + 60)
		{
			upstate = 1;
			stopstate = 1;
			attackstate = 1;
			gardstate = 0;
		}
		//shell_up��firstPosition_up.x��菬�����Ȃ�����(shell��������)�B
		if (position_up.y <= firstPosition_up.y)
		{
			upstate = 0;
			stopstate = 1;
			attackstate = 0;
			gardstate = 1;
		}

	modelRender_eye.SetPosition(position);
	modelRender_up.SetPosition(position_up);
	modelRender_down.SetPosition(position_down);
}

//game2��enemy02�𐶐����Achange=1�������Ƃ��B
void Enemy02::Move2()
{
	timer--;
	if (timer <= 0)
	{
		position.x -= 10.0f;
		position_up.x -= 10.0f;
		position_down.x -= 10.0f;
		if (position.x <= -1200)
		{
			Dead();
			DeleteGO(this);
		}
	}

	//��ʒu�ւ̈ړ��B
	//position.x��800���傫���Ȃ�B
	if (position.x >= -800)
	{
		//�ړ����x�B
		position.x -= 10.0f;
		position_up.x -= 10.0f;
		position_down.x -= 10.0f;
	}

	//stopstate��1�̂Ƃ��Ashell���J���Ă���A���Ă����Ԃ��ێ�����B
	if (position.x <= -750)
	{
		if (stopstate == 1)
		{
			opentimer--;

			if (opentimer > 0)
			{
				return;
			}
			else if (opentimer <= 0)
			{
				opentimer = 100;
				stopstate = 0;
			}
		}

		//shell_up�̏㉺�ړ��B
		//shell���J���B
		if (upstate == 0)
		{
			gardstate = 0;
			//��Ɉړ�����B
			position_up.y += 2.0f;
			//���Ɉړ�����B
			position_down.y -= 2.0f;

		}
		//shell�����B
		if (upstate == 1)
		{
			//���Ɉړ�����B
			position_up.y -= 2.0f;
			//��Ɉړ�����B
			position_down.y += 2.0f;
		}

		//shell_up��firstPosition_up.x���傫���Ȃ�����(shell���J������)�B
		if (position_up.y >= firstPosition_up.y + 60)
		{
			upstate = 1;
			stopstate = 1;
			attackstate = 1;
			gardstate = 0;
		}
		//shell_up��firstPosition_up.x��菬�����Ȃ�����(shell��������)�B
		if (position_up.y <= firstPosition_up.y)
		{
			upstate = 0;
			stopstate = 1;
			attackstate = 0;
			gardstate = 1;
		}
	}

	modelRender_eye.SetPosition(position);
	modelRender_up.SetPosition(position_up);
	modelRender_down.SetPosition(position_down);
}


void Enemy02::Rotation()
{
	if (fabsf(position.x) < 0.001f
		&& fabsf(position.z) < 0.001f) {
		//m_moveSpeed.x��m_moveSpeed.z�̐�Βl���Ƃ���0.001�ȉ��Ƃ������Ƃ�
		//���̃t���[���ł̓L�����͈ړ����Ă��Ȃ��̂Ő��񂷂�K�v�͂Ȃ��B
		return;
	}
	//atan2��tan�Ƃ̒l���p�x(���W�A���P��)�ɕϊ����Ă����֐��B
	//m_moveSpeed.x / m_moveSpeed.z�̌��ʂ�tan�ƂɂȂ�B
	//atan2���g�p���āA�p�x�����߂Ă���B
	//���ꂪ��]�p�x�ɂȂ�B
	float angle = atan2(-position.x, position.z);
	//atan���Ԃ��Ă���p�x�̓��W�A���P�ʂȂ̂�
	//SetRotationDeg�ł͂Ȃ�SetRotation���g�p����B
	rotation.SetRotationY(-angle);

	//��]��ݒ肷��B
	modelRender_eye.SetRotation(rotation);

	//�v���C���[�̑O�x�N�g�����v�Z����B
	forward = Vector3::AxisZ;
	rotation.Apply(forward);
}

//�ʂ�ł����B
void Enemy02::Attack()
{
	if (position.x <= 800)
	{
		tamatime += 1;
		if (tamatime == 70)
		{
				Tama_tuibi* tama_tuibi = NewGO<Tama_tuibi>(0, "tama_tuibi");
				tama_tuibi->position = position;
				tama_tuibi->firstposition = tama_tuibi->position;
				if (tamachange == 1)
				{
					//�ʂ̃p�^�[����ς���B
					tama_tuibi->change = 1;
				}
				tamatime = 0;
		}
	}

}

//�e�ۂƂ̓����蔻��̏����B
 void Enemy02::Collision()
{
	//dangan�̃R���W�������擾����B
	const auto& collisions = g_collisionObjectManager->FindCollisionObjects("dangan");
	//collision�̔z���for���ŉ񂷁B
	for (auto collision : collisions)
	{
		//�ݒ肵���R���W�����ƏՓ˂��������肷��B
		if (collision->IsHit(colli))
		{
			if (gardstate == 0)
			{
				//�G��|�������𑝂₷�B
				player->downcount += 1;
				Dead();
				//���ꂽ�Ƃ��̉����Đ�����B
				death = NewGO<SoundSource>(2);
				death->Init(2);
				death->SetVolume(1.2f);
				death->Play(false);

				EffectEmitter* effectEmitter = NewGO<EffectEmitter>(0);
				effectEmitter->Init(0);
				effectEmitter->SetScale({ 10.0f,10.0f,10.0f });
				effectEmitter->SetPosition(position);
				effectEmitter->Play();
				//���g��j�󂷂�B
				DeleteGO(this);
			}
			
		}
	}

	//dangan�̃R���W�������擾����B
	const auto& collisions_p = g_collisionObjectManager->FindCollisionObjects("player");
	//collision�̔z���for���ŉ񂷁B
	for (auto collision : collisions_p)
	{
		//�ݒ肵���R���W�����ƏՓ˂��������肷��B
		if (collision->IsHit(colli))
		{
			if (gardstate == 0)
			{
				//�Ԃ����������Ȃ�X�R�A�ɂ͉����Ȃ��B
				//player->downcount += 1;
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

	//baria�̃R���W�������擾����B
	const auto& collisions_b = g_collisionObjectManager->FindCollisionObjects("baria");
	//collision�̔z���for���ŉ񂷁B
	for (auto collision : collisions_b)
	{
		//�ݒ肵���R���W�����ƏՓ˂��������肷��B
		if (collision->IsHit(colli))
		{
			if (gardstate == 0)
			{
				//�G��|�������𑝂₷�B
				//player->downcount += 1;
				Dead();
				//���ꂽ�Ƃ��̉����Đ�����B
				death = NewGO<SoundSource>(2);
				death->Init(2);
				death->SetVolume(1.2f);
				death->Play(false);

				EffectEmitter* effectEmitter = NewGO<EffectEmitter>(0);
				effectEmitter->Init(0);
				effectEmitter->SetScale({ 10.0f,10.0f,10.0f });
				effectEmitter->SetPosition(position);
				effectEmitter->Play();
				//���g��j�󂷂�B
				DeleteGO(this);
			}

		}
	}
}

//�|���ꂽ�Ƃ��̏����B
void Enemy02::Dead()
{
	switch (stagenumber)
	{
	case 1:
			game->dead++;
		break;
	case 2:
			game2->dead++;
		break;
	case 3:
			game3->dead++;
		break;

	default:
		break;
	}
}

void Enemy02::Render(RenderContext& rc)
{
	modelRender_up.Draw(rc);
	modelRender_eye.Draw(rc);
	modelRender_down.Draw(rc);
}