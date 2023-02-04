#include "stdafx.h"
#include "Boss01.h"
#include "Game.h"
#include "Player.h"
#include "Baria.h"
#include "Tama.h"
#include "Tama_tuibi.h"
#include "GameUI.h"
#include "graphics/effect/EffectEmitter.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"

Boss01::Boss01()
{

}

Boss01::~Boss01()
{
	DeleteGO(colli_up);
	DeleteGO(colli_down);

	QueryGOs<Tama>("tama", [&](Tama* tama_) {
		DeleteGO(tama_);
		return true;
		});

	QueryGOs<Tama_tuibi>("tama_tuibi", [&](Tama_tuibi* tama_tuibi_) {
		DeleteGO(tama_tuibi_);
		return true;
		});
}

bool Boss01::Start()
{
	// �����蔻��̉����B
	//�R�����g�A�E�g����B
	//PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();

	//��������Ƃ��̉���ǂݍ��ށB
	g_soundEngine->ResistWaveFileBank(18, "Assets/sound/boss_dead.wav");
	//�G�t�F�N�g��ǂݍ��ށB
	EffectEngine::GetInstance()->ResistEffect(8, u"Assets/effect/effectsprite/redright.efk");
	//�G�t�F�N�g��ǂݍ��ށB
	EffectEngine::GetInstance()->ResistEffect(9, u"Assets/effect/effectsprite/boss_dead.efk");

	//�v���C���[�̃C���X�^���X��T���B
	player = FindGO<Player>("player");
	//�Q�[���̃C���X�^���X��T���B
	game = FindGO<Game>("game");
	//�Q�[���̃C���X�^���X��T���B
	baria = FindGO<Baria>("baria");
	//�Q�[���̃C���X�^���X��T���B
	gameUI = FindGO<GameUI>("gameUI");

	
	modelRender_up.SetRaytracingWorld(false);
	modelRender_up.Init("Assets/modelData/enemy_boss01_up.tkm");
	modelRender_down.SetRaytracingWorld(false);
	modelRender_down.Init("Assets/modelData/enemy_boss01_down.tkm");



	//�R���W�����̍쐬�B
	colli_up = NewGO<CollisionObject>(0);
	colli_up->CreateCapsule(Vector3(0.0f, 0.0f, 0.0f),
		Quaternion(0.0f, 0.0f, 90.0f, 1.0f), 220.0f, 65.0f);
	colli_up->SetIsEnableAutoDelete(false);
	colli_up->SetName("boss01_up");
	rot_up2.SetRotationDegZ(90.0f);
	colli_up->SetRotation(rot_up2);
	colli_up->SetPosition(position_up);
	
	//�R���W�����̍쐬�B
	colli_down = NewGO<CollisionObject>(1);
	colli_down->CreateCapsule(Vector3(0.0f, 0.0f, 0.0f), 
		Quaternion(0.0f, 0.0f, 90.0f, 1.0f), 220.0f, 240.0f);
	colli_down->SetIsEnableAutoDelete(false);
	colli_down->SetName("boss01_down");
	rot_down2.SetRotationDegZ(90.0f);
	colli_down->SetRotation(rot_down2);
	colli_down->SetPosition(position_down);
                                              
	return true;
}

void Boss01::Update()
{
	muteki--;

	Move();

	Collision();

	count--;

		//count��0�̂Ƃ��B
		//count��0�ɂȂ�܂ł̓p�^�[����ێ�����B
		if (count == 0)
		{
			//�U���p�^�[�������߂�B
			pattern =  rand() % 3;
		}
		//count��-300�ȉ��ɂȂ�����B
		if (count <= -500/*-500*/)
		{
			//count��200�ɖ߂��B
			count = 290;
			//pattern2(Bite)�̒l�̏������B
			targetstate = 0;
			gostate = 1;
			backstate = 0;
			totugekitime = 70;
			totugekicount = 0;
			sarchtime = 80;
		}


		//�g�U����ʂ�łB
		if (pattern == 0)
		{
			Kakusan();
		}
		//�ǔ�����ʂ�łB
		if (pattern == 1)
		{
			Tuibi();
		}
		//���݂��B
		if (pattern == 2)
		{
			if (targetstate == 0)
			{
				Target();
				EffectEmitter*effectEmitter = NewGO<EffectEmitter>(8);
				effectEmitter->Init(8);
				effectEmitter->SetScale({ 60.0f,60.0f,0.0f });
				effectPos.x = 165.0f;
				effectPos.y = 90.0f;
				effectEmitter->SetPosition(effectPos);
				effectEmitter->Play();
				opentime = 50;
				closetime = 0;
			}
			Bite();
			if (totugekicount == 2)count = 1;
		}
	
		pos_colli = position_up;
		pos_colli.x -= 140.0f;
		pos_colli.y += 40.0f;

	colli_up->SetPosition(pos_colli);

	pos_colli = position_down;
	pos_colli.x -= 90.0f;

	colli_down->SetPosition(pos_colli);
	colli_up->SetRotation(rot_up);

	modelRender_up.SetPosition(position_up);
	modelRender_down.SetPosition(position_down);

	modelRender_up.SetRotation(rot_up);
	modelRender_down.SetRotation(rot_down);

	modelRender_up.Update();
	modelRender_down.Update();
}

void Boss01::Move()
{
	if (pattern != 2)
	{
		if (position_up.x >= 600)
		{
			//x=600�܂ňړ��B
			position_up.x -= 10.0f;
			position_down.x -= 10.0f;
		}
	}

	if (pattern != 2)
	{
		if (moveCount == 0)
		{
			//��Ɉړ�����B
			position_up.y += 3.0f;
			position_down.y += 3.0f;
		}
		if (moveCount == 1)
		{
			//���Ɉړ�����B
			position_up.y -= 3.0f;
			position_down.y -= 3.0f;
		}
		//y���W���������Wy+150.0f�𒴂�����B
		if (position_up.y >= firstPosition_up.y + 150.0f)
		{
			//���Ɉړ�����B
			moveCount = 1;
		}
		//y���W���������Wy-150.0f�𒴂�����B
		if (position_up.y <= firstPosition_up.y - 150.0f)
		{
			//��Ɉړ�����B
			moveCount = 0;
		}
	}
}

void Boss01::Collision()
{
	//dangan�̃R���W�������擾����B
	const auto& collisions_down = g_collisionObjectManager->FindCollisionObjects("dangan");
	//collision�̔z���for���ŉ񂷁B
	for (auto collision : collisions_down)
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

			if (bosshp <= 0)
			{
				Dead();
			}
		}
	}

	//player�̃R���W�������擾����B
	const auto& collisions_p_up = g_collisionObjectManager->FindCollisionObjects("player");

	//collision�̔z���for���ŉ񂷁B
	for (auto collision : collisions_p_up)
	{
		//�ݒ肵���R���W�������Փ˂��������肷��B
		if (collision->IsHit(colli_up))
		{
			//���G���Ԃ�60�ȏ�̂Ƃ��B
			if (player->muteki >= 60)
			{
				Damage();
			}
		}
	}

	//player�̃R���W�������擾����B
	const auto& collisions_p_down = g_collisionObjectManager->FindCollisionObjects("player");

	//collision�̔z���for���ŉ񂷁B
	for (auto collision : collisions_p_down)
	{
		//�ݒ肵���R���W�������Փ˂��������肷��B
		if (collision->IsHit(colli_down))
		{
			//���G���Ԃ�60�ȏ�̂Ƃ��B
			if (player->muteki >= 60)
			{
				Damage();
			}
		}
	}
}

void Boss01::Kakusan()
{
	countdown -- ;
	//rand() % 1401 - 700;
	//90�b���Ƃɐ�������B
	if (countdown <= 0)
	{
		Tama* tama = NewGO<Tama>(0, "tama");
		//tama�̔�΂�����ς���B
		tama->change = 1;
		tama->position = position_up;
		tama->firstposition = tama->position;
		tama->ramdom_y =0;
		tama->randomposition = { 0.0f,tama->ramdom_y,0.0f };

		Tama* tama01 = NewGO<Tama>(0, "tama");
		//tama�̔�΂�����ς���B
		tama01->change = 1;
		tama01->position = position_up;
		tama01->firstposition = tama01->position;
		tama01->ramdom_y = rand() % 1001 - 500;
		tama01->randomposition = { 0.0f,tama01->ramdom_y,0.0f };

		Tama* tama02 = NewGO<Tama>(0, "tama");
		//tama�̔�΂�����ς���B
		tama02->change = 1;
		tama02->position = position_up;
		tama02->firstposition = tama02->position;
		tama02->ramdom_y = rand() % 1001 - 500;
		tama02->randomposition = { 0.0f,tama02->ramdom_y,0.0f };

		Tama* tama03 = NewGO<Tama>(0, "tama");
		//tama�̔�΂�����ς���B
		tama03->change = 1;
		tama03->position = position_up;
		tama03->firstposition = tama03->position;
		tama03->ramdom_y = rand() % 1001 - 500;
		tama03->randomposition = { 0.0f,tama03->ramdom_y,0.0f };

		Tama* tama04 = NewGO<Tama>(0, "tama");
		//tama�̔�΂�����ς���B
		tama04->change = 1;
		tama04->position = position_up;
		tama04->firstposition = tama04->position;
		tama04->ramdom_y = rand() % 1001 - 500;
		tama04->randomposition = { 0.0f,tama04->ramdom_y,0.0f };

		Tama* tama05 = NewGO<Tama>(0, "tama");
		//tama�̔�΂�����ς���B
		tama05->change = 1;
		tama05->position = position_up;
		tama05->firstposition = tama05->position;
		tama05->ramdom_y = rand() % 1001 - 500;
		tama05->randomposition = { 0.0f,tama05->ramdom_y,0.0f };
		countdown = 90;
	}
}

void Boss01::Tuibi()
{
	countdown--;
	//rand() % 1401 - 700;
	//70�b���Ƃɐ�������B
	if (countdown <= 0)
	{
		Tama_tuibi* tama_tuibi = NewGO<Tama_tuibi>(0, "tama_tuibi");

		tama_tuibi->position = position_up;
		tama_tuibi->firstposition = tama_tuibi->position;
		countdown = 70;
	}
}

void Boss01:: Bite()
{
	if (sarchtime >= 0)
	{
		sarchtime--;
	}
	
	if (sarchtime <= 0)
	{
		totugekitime--;
		//�����J�������B
		BiteRot();
		//�v���C���[�ɓˌ�����B
		if (gostate == 1)
		{
			position_up += moveSpeed;
			position_down += moveSpeed;
		}
		//���̈ʒu�ɋA��B
		if (backstate == 1)
		{
			position_up -= moveSpeed_b;
			position_down -= moveSpeed_b;
		}

		//�ˌ����I�������B
		if (totugekitime==0)
		{
			gostate = 0;
			backstate = 1;

		}
		//���̈ʒu�ɖ߂�����B
		if (totugekitime == -70)
		{
			backstate = 0;
			totugekicount++;
		}
	}
	modelRender_up.SetPosition(position_up);
	modelRender_down.SetPosition(position_down);
}

void Boss01::BiteRot()
{
	//�����J���B
	if (opentime>0)
	{
		rot_up.AddRotationDegZ(-1.6f);
		rot_down.AddRotationDegZ(0.5f);
	}
	//�������B
	if (opentime == 0&&closetime<20)
	{
		rot_up.AddRotationDegZ(4.0f);
		rot_down.AddRotationDegZ(-1.225f);
	}
	
	if (opentime != 0)
	{
		opentime--;
	}
	else 
		closetime++;
}

//�v���C���[�̈ʒu��������B
void Boss01::Target()
{
	diff = player->position - position_up;

	//�x�N�g���𐳋K������B
	diff.Normalize();
	//�ړ����x��ݒ肷��B
	moveSpeed = diff * 16.0f;
	moveSpeed_b= diff * 16.0f;

	targetstate = 1;
}

//�v���C���[�ɗ^����_���[�W�̏����B
void Boss01::Damage()
{
	if (pattern == 2)
	{
		//player��Hp��20���炷�B
		player->playerHp -= bitedamage;
		//�_���[�W���󂯂��B
		player->damagestate = 1;
		//���G���ԃ��Z�b�g�B
		player->muteki = 0;
	}
	else
	{
		//player��Hp��10���炷�B
		player->playerHp -= player->damage;
		//�_���[�W���󂯂��B
		player->damagestate = 1;
		//���G���ԃ��Z�b�g�B
		player->muteki = 0;
	}
}

void Boss01::Dead()
{
	//���ꂽ�Ƃ��̉��̍Đ��B
	SoundSource* dead = NewGO<SoundSource>(18);
	dead->Init(18);
	dead->SetVolume(1.2f);
	dead->Play(false);
	//�����G�t�F�N�g�̍Đ��B
	EffectEmitter* effectEmitter_d = NewGO<EffectEmitter>(9);
	effectEmitter_d->Init(9);
	effectEmitter_d->SetScale({ 4.0f,4.0f,0.0f });
	effectEmitter_d->SetPosition(position_up);
	effectEmitter_d->Play();

	//�G��|�������𑝂₷�B
	player->downcount += 1;
	gameUI->bossdeath = 1;
	//���g��j�󂷂�B
	DeleteGO(this);
}

void Boss01::Render(RenderContext& rc)
{
	modelRender_up.Draw(rc);
	modelRender_down.Draw(rc);
}