#include "stdafx.h"
#include "Boss02.h"
#include "Game2.h"
#include "Player.h"
#include "Baria.h"
#include "Tama_big.h"
#include "Tama_tuibi.h"
#include "GameUI2.h"
#include "graphics/effect/EffectEmitter.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"

Boss02::Boss02()
{

}

Boss02::~Boss02()
{
	DeleteGO(colli_center);
	DeleteGO(colli_up);
	DeleteGO(colli_down);

	QueryGOs<Tama_tuibi>("tama_tuibi", [&](Tama_tuibi* tama_tuibi_) {
		DeleteGO(tama_tuibi_);
		return true;
		});

	QueryGOs<Tama_big>("tama_big", [&](Tama_big* tama_big_) {
		DeleteGO(tama_big_);
		return true;
		});
}

bool Boss02::Start()
{
	//�v���C���[�̃C���X�^���X��T���B
	player = FindGO<Player>("player");
	//�Q�[���̃C���X�^���X��T���B
	game2 = FindGO<Game2>("game2");
	//�Q�[���̃C���X�^���X��T���B
	baria = FindGO<Baria>("baria");
	//�Q�[���̃C���X�^���X��T���B
	gameUI2 = FindGO<GameUI2>("gameUI2");

	//��������Ƃ��̉���ǂݍ��ށB
	g_soundEngine->ResistWaveFileBank(18, "Assets/sound/boss_dead.wav");
	//�G�t�F�N�g��ǂݍ��ށB
	EffectEngine::GetInstance()->ResistEffect(9, u"Assets/effect/effectsprite/boss_dead.efk");

	modelRender_up.SetRaytracingWorld(false);
	modelRender_up.Init("Assets/modelData/enemy_boss02_up.tkm");
	modelRender_center.SetRaytracingWorld(false);
	modelRender_center.Init("Assets/modelData/enemy_boss02_center.tkm");
	modelRender_down.SetRaytracingWorld(false);
	modelRender_down.Init("Assets/modelData/enemy_boss02_down.tkm");

	//up�̃R���W�����̍쐬�B
	colli_up = NewGO<CollisionObject>(0);
	colli_up->CreateSphere(Vector3(0.0f, 0.0f, 0.0f), Quaternion::Identity, 160.0f);
	colli_up->SetIsEnableAutoDelete(false);
	colli_up->SetName("up");

	//center�̃R���W�����̍쐬�B
	colli_center = NewGO<CollisionObject>(0);
	colli_center->CreateSphere(Vector3(0.0f, 0.0f, 0.0f), Quaternion::Identity, 160.0f);
	colli_center->SetIsEnableAutoDelete(false);
	colli_center->SetName("center");

	//down�̃R���W�����̍쐬�B
	colli_down = NewGO<CollisionObject>(0);
	colli_down->CreateSphere(Vector3(0.0f, 0.0f, 0.0f), Quaternion::Identity, 160.0f);
	colli_down->SetIsEnableAutoDelete(false);
	colli_down->SetName("down");

	return true;
}

void Boss02::Update()
{
	muteki--;

	Move();

	//��ʒu�ɒ�������B
	if (position_up.x <= 700)
	{
		count--;
		//count��0�̂Ƃ��B
			//count��0�ɂȂ�܂ł̓p�^�[����ێ�����B
		if (count == 0)
		{
			//�U���p�^�[�������߂�B
			pattern = rand() % 3;
			attack = 0;
			targetstate = 0;
			attackcounter = 0;
			attackcomplete = 0;
			sarchtime = 100;
		}
		//count��-500�ȉ��ɂȂ�����B
		if (count <= -500)
		{
				if (pattern == 2)
				{
					count = 150;
				}
				else
				{
					//count��200�ɖ߂��B
					count = 250;
				}
		}
		//�傫�ȋʂ�łB
		if (pattern == 0)
		{
			Tama();
		}
		//�ǔ�����ʂ�łB
		if (pattern == 1)
		{
			Tuibi();
		}
		//���ԂɃv���C���[�ɓˌ�����B
		if (pattern == 2)
		{
			if (targetstate == 0)
			{
				//�v���C���[�̈ʒu����肷��B
				switch (attack)
				{
					//up
				case 0:
					Target_up();
					break;
					//center
				case 1:
					Target_center();
					break;
					//down
				case 2:
					Target_down();
					break;

				default:
					break;
				}
				
			}
			Totugeki();
		}
	}

	Collision_center();
	Collision_up();
	Collision_down();

	modelRender_center.SetPosition(position_center);
	modelRender_up.SetPosition(position_up);
	modelRender_down.SetPosition(position_down);

	colli_center->SetPosition(position_center);
	colli_up->SetPosition(position_up);
	colli_down->SetPosition(position_down);

	modelRender_center.Update();
	modelRender_up.Update();
	modelRender_down.Update();

}

void Boss02::Move()
{
	if (attack<=0)
	{
		if (position_up.x >= 600)
		{
			position_up.x -= 10.0f;
		}
		if (position_center.x >= 600)
		{
			position_center.x -= 10.0f;
		}
		if (position_down.x >= 600)
		{
			position_down.x -= 10.0f;
		}
	}

	//��ʊO�ɏo����ʒu��߂��B
	if (attack==-1)
	{
			position_up.x = 2000;
			position_up.y = 410;
	
			position_center.x = 2000;
			position_center.y = 60;
		
			position_down.x = 2000;
			position_down.y = -290;
	
			attack = 0;
			attackcomplete = 0;
			sarchtime = 70;
	}
}

void Boss02::Collision_center()
{
	//dangan�̃R���W�������擾����B
	const auto& collisions = g_collisionObjectManager->FindCollisionObjects("dangan");
	//collision�̔z���for���ŉ񂷁B
	for (auto collision : collisions)
	{
		//�ݒ肵���R���W�����ƃL�����N�^�[�R���g���[���[���Փ˂��������肷��B
		if (collision->IsHit(colli_center))
		{
			//muteki��0�ȉ��ɂȂ�����B
			if (muteki <= 0)
			{
				//�{�X��hp��2���炷�B
				bosshp -= 2;
				muteki = 40;
			}
			//�{�X��hp��0�ȉ��ɂȂ�����B
			if (bosshp <= 0)
			{
				Dead();
			}
		}
	}
	//player�̃R���W�������擾����B
	const auto& collisions_p = g_collisionObjectManager->FindCollisionObjects("player");
	//collision�̔z���for���ŉ񂷁B
	for (auto collision : collisions_p)
	{
		//�ݒ肵���R���W�������Փ˂��������肷��B
		if (collision->IsHit(colli_center))
		{
			//���G���Ԃ�60�ȏ�̂Ƃ��B
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

void Boss02::Collision_up()
{
	//dangan�̃R���W�������擾����B
	const auto& collisions = g_collisionObjectManager->FindCollisionObjects("dangan");
	//collision�̔z���for���ŉ񂷁B
	for (auto collision : collisions)
	{
		//�ݒ肵���R���W�����ƃL�����N�^�[�R���g���[���[���Փ˂��������肷��B
		if (collision->IsHit(colli_up))
		{
			//muteki��0�ȉ��ɂȂ�����B
			if (muteki <= 0)
			{
				//�{�X��hp��2���炷�B
				bosshp -= 2;
				muteki = 40;
			}
			//�{�X��hp��0�ȉ��ɂȂ�����B
			if (bosshp <= 0)
			{
				Dead();
			}
		}
	}

	//player�̃R���W�������擾����B
	const auto& collisions_p = g_collisionObjectManager->FindCollisionObjects("player");
	//collision�̔z���for���ŉ񂷁B
	for (auto collision : collisions_p)
	{
		//�ݒ肵���R���W�������Փ˂��������肷��B
		if (collision->IsHit(colli_up))
		{
			//���G���Ԃ�60�ȏ�̂Ƃ��B
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

void Boss02::Collision_down()
{
	//dangan�̃R���W�������擾����B
	const auto& collisions = g_collisionObjectManager->FindCollisionObjects("dangan");
	//collision�̔z���for���ŉ񂷁B
	for (auto collision : collisions)
	{
		//�ݒ肵���R���W�����ƃL�����N�^�[�R���g���[���[���Փ˂��������肷��B
		if (collision->IsHit(colli_down))
		{
			//muteki��0�ȉ��ɂȂ�����B
			if (muteki <= 0)
			{
				//�{�X��hp��2���炷�B
				bosshp -= 2;
				muteki = 40;
			}
			//�{�X��hp��0�ȉ��ɂȂ�����B
			if (bosshp <= 0)
			{
				Dead();
			}
		}
	}
	//player�̃R���W�������擾����B
	const auto& collisions_p = g_collisionObjectManager->FindCollisionObjects("player");
	//collision�̔z���for���ŉ񂷁B
	for (auto collision : collisions_p)
	{
		//�ݒ肵���R���W�������Փ˂��������肷��B
		if (collision->IsHit(colli_down))
		{
			//���G���Ԃ�60�ȏ�̂Ƃ��B
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

void Boss02::Tama()
{
	countdown--;
	attack = rand() % 3;
	
	//�����O��ł���tama�ƍ���ł�tama�������ꏊ�Ȃ�B
	if (attack == oldattack)
	{
		attack = rand() % 3;
		//������x�����_���Ɍ��߂Ă��O��ł���tama�ƍ���ł�tama�������ꏊ�Ȃ�B
		if (attack == oldattack)
		{
			switch (attack)
			{
			case 0:
				//center�Ɍ��߂�B
				attack = 1;
				break;

			case 1:
				//up�Ɍ��߂�B
				attack = 0;
				break;

			case 2:
				//up��center���烉���_���Ɍ��߂�B
				attack = rand() % 2;
				break;
			}
		}
	}

	//70�b���Ƃɐ�������B
	if (countdown <= 0)
	{
		if (attack == 0)
		{
			//center����ʂ�łB
			Tama_big* tama_big_u = NewGO<Tama_big>(0, "tama_big");
			tama_big_u->position = position_up;
			tama_big_u->position.x = position_up.x - 130.0f;
		}
		if (attack == 1)
		{
			//center����ʂ�łB
			Tama_big* tama_big_c = NewGO<Tama_big>(0, "tama_big");
			tama_big_c->position = position_center;
			tama_big_c->position.x = position_center.x - 130.0f;
		}

		if (attack == 2)
		{
			//center����ʂ�łB
			Tama_big * tama_big_d = NewGO<Tama_big>(0, "tama_big");
			tama_big_d->position = position_down;
			tama_big_d->position.x = position_down.x - 130.0f;
		}
		oldattack = attack;
		countdown = 70;
	}
}

void Boss02::Tuibi()
{
	countdown--;
	//90�b���Ƃɐ�������B
	if (countdown <= 0)
	{
		if (attack == 0)
		{
			//center����ǔ�����ʂ�łB
			Tama_tuibi* tama_tuibi_u = NewGO<Tama_tuibi>(0, "tama_tuibi");
			tama_tuibi_u->position = position_up;
			tama_tuibi_u->position.x = position_up.x - 130.0f;
		}
		if (attack == 1)
		{
			//center����ǔ�����ʂ�łB
			Tama_tuibi* tama_tuibi_c = NewGO<Tama_tuibi>(0, "tama_tuibi");
			tama_tuibi_c->position = position_center;
			tama_tuibi_c->position.x = position_center.x - 130.0f;
		}

		if (attack == 2)
		{
			//center����ǔ�����ʂ�łB
			Tama_tuibi* tama_tuibi_d = NewGO<Tama_tuibi>(0, "tama_tuibi");
			tama_tuibi_d->position = position_down;
			tama_tuibi_d->position.x = position_down.x - 130.0f;
			tama_tuibi_d->change = 1;

		}
		countdown = 70;

		attack++;

		//up����down�܂ŋʂ�ł�����B
		if (attack >= 4)
		{
			//���Z�b�g�B
			attack = 0;
		}
	}
}

void Boss02::Totugeki()
{
	//sarchtime=50
	if (sarchtime >= 0)
	{
		sarchtime--;
	}

	if (sarchtime <= 0)
	{
		//totugekicount++;
		attackcounter++;
		//up���v���C���[�Ɍ������ēˌ�����B
		if (attack >= 0)
		{
			position_up += moveSpeed_up;
		}
		//center���v���C���[�Ɍ������ēˌ�����B
		if (attack >=1)
		{
			position_center += moveSpeed_center;
		}
		//down���v���C���[�Ɍ������ēˌ�����B
		if (attack >=2)
		{
			position_down += moveSpeed_down;
		}
		//60�t���[�������Ƃɓˌ�������B
		if (attackcounter >=60)
		{
			attack++;
			attackcounter = 0;
			targetstate = 0;
			attackcomplete++;

			if (attackcomplete >= 4)
			{
				//�ˌ����鏈�����s��Ȃ��悤�ɂ���B
				attack = -1;
			}
		}
	}
}

void Boss02::Target_up()
{
	Vector3 diff_up = player->position - position_up;
	
	//up�̃x�N�g���𐳋K������B
	diff_up.Normalize();
	//�ړ����x��ݒ肷��B
	moveSpeed_up = diff_up * 17.0f;
	//attack++;
	targetstate = 1;
}

void Boss02::Target_center()
{
	Vector3 diff_center = player->position - position_center;

	//up�̃x�N�g���𐳋K������B
	diff_center.Normalize();
	//�ړ����x��ݒ肷��B
	moveSpeed_center = diff_center * 17.0f;
	//attack++;
	targetstate = 1;
}

void Boss02::Target_down()
{
	Vector3 diff_down = player->position - position_down;

	//up�̃x�N�g���𐳋K������B
	diff_down.Normalize();
	//�ړ����x��ݒ肷��B
	moveSpeed_down = diff_down * 17.0f;
	//attack++;
	targetstate = 1;
}

void Boss02::Dead()
{
	//���ꂽ�Ƃ��̉��̍Đ��B
	SoundSource* dead = NewGO<SoundSource>(18);
	dead->Init(18);
	dead->SetVolume(1.2f);
	dead->Play(false);
	//�����G�t�F�N�g�̍Đ��B
	{
		EffectEmitter* effectEmitter_u = NewGO<EffectEmitter>(9);
		effectEmitter_u->Init(9);
		effectEmitter_u->SetScale({ 2.0f,2.0f,0.0f });
		effectEmitter_u->SetPosition(position_up);
		effectEmitter_u->Play();
		EffectEmitter* effectEmitter_s = NewGO<EffectEmitter>(9);
		effectEmitter_s->Init(9);
		effectEmitter_s->SetScale({ 2.0f,2.0f,0.0f });
		effectEmitter_s->SetPosition(position_center);
		effectEmitter_s->Play();
		EffectEmitter* effectEmitter_d = NewGO<EffectEmitter>(9);
		effectEmitter_d->Init(9);
		effectEmitter_d->SetScale({ 2.0f,2.0f,0.0f });
		effectEmitter_d->SetPosition(position_down);
		effectEmitter_d->Play();
	}
	//�G��|�������𑝂₷�B
	player->downcount += 1;
	gameUI2->bossdeath = 1;
	//���g��j�󂷂�B
	DeleteGO(this);
}

void Boss02::Render(RenderContext& rc)
{
	modelRender_up.Draw(rc);
	modelRender_center.Draw(rc);
	modelRender_down.Draw(rc);
}