#include "stdafx.h"
#include "Boss03.h"
#include "Game_final.h"
#include "Player.h"
#include "Baria.h"
#include "Tama.h"
#include "Tama_big.h"
#include "Tama_tuibi.h"
#include "GameUI3.h"
#include "Enemy_bomb.h"
#include "graphics/effect/EffectEmitter.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"


Boss03::Boss03()
{

}

Boss03::~Boss03()
{
	DeleteGO(colli_eye);
	DeleteGO(colli_eye_light);
	DeleteGO(colli_eye_left);

	QueryGOs<Tama>("tama", [&](Tama* tama_) {
		DeleteGO(tama_);
		return true;
		});

	QueryGOs<Tama_tuibi>("tama_tuibi", [&](Tama_tuibi* tama_tuibi_) {
		DeleteGO(tama_tuibi_);
		return true;
		});

	QueryGOs<Enemy_bomb>("enemy_bomb", [&](Enemy_bomb* enemy_bomb_) {
		DeleteGO(enemy_bomb_);
		return true;
		});
}

bool Boss03::Start()
{
	//�v���C���[�̃C���X�^���X��T���B
	player = FindGO<Player>("player");
	//�Q�[���̃C���X�^���X��T���B
	game_final = FindGO<Game_final>("game_final");
	//�Q�[���̃C���X�^���X��T���B
	baria = FindGO<Baria>("baria");
	//�Q�[���̃C���X�^���X��T���B
	gameUI3 = FindGO<GameUI3>("gameUI3");

	//��������Ƃ��̉���ǂݍ��ށB
	g_soundEngine->ResistWaveFileBank(18, "Assets/sound/boss_dead.wav");
	//�G�t�F�N�g��ǂݍ��ށB
	EffectEngine::GetInstance()->ResistEffect(1, u"Assets/effect/effectsprite/beam_2.efk");
	//�G�t�F�N�g��ǂݍ��ށB
	EffectEngine::GetInstance()->ResistEffect(9, u"Assets/effect/effectsprite/boss_dead.efk");

	//�e�ۂ�łƂ��̉���ǂݍ��ށB
	g_soundEngine->ResistWaveFileBank(15, "Assets/sound/beamchage.wav");
	//�e�ۂ�łƂ��̉���ǂݍ��ށB
	g_soundEngine->ResistWaveFileBank(16, "Assets/sound/beam.wav");

	modelRender.SetRaytracingWorld(false);
	modelRender.Init("Assets/modelData/enemy_boss03.tkm");
	modelRender_ring.SetRaytracingWorld(false);
	modelRender_ring.Init("Assets/modelData/enemy_boss03_ring.tkm");
	//�����O�̏�̖ځB
	modelRender_ring_Eup.SetRaytracingWorld(false);
	modelRender_ring_Eup.Init("Assets/modelData/ring_eye_up.tkm");
	//�����O�̉E�̖ځB
	modelRender_ring_Elight.SetRaytracingWorld(false);
	modelRender_ring_Elight.Init("Assets/modelData/ring_eye_light.tkm");
	//�����O�̍��̖ځB
	modelRender_ring_Eleft.SetRaytracingWorld(false);
	modelRender_ring_Eleft.Init("Assets/modelData/ring_eye_left.tkm");
	//�����O�̉��̖ځB
	modelRender_ring_Edown.SetRaytracingWorld(false);
	modelRender_ring_Edown.Init("Assets/modelData/ring_eye_down.tkm");

	//colli_eye�̃R���W�����̍쐬�B
	colli_eye = NewGO<CollisionObject>(0);
	colli_eye->CreateSphere(Vector3(0.0f, 0.0f, 0.0f), Quaternion::Identity, 270.0f);
	colli_eye->SetIsEnableAutoDelete(false);
	colli_eye->SetName("boss03_eye");
	colli_eye->SetPosition(position);

	position_light = { position.x + 420,position.y ,position.z };
	position_left = { position.x - 420,position.y ,position.z };
	//���E�̃R���W�����̍쐬�B
	colli_eye_light = NewGO<CollisionObject>(1);
	colli_eye_light->CreateBox(Vector3 (0.0f,0.0f,0.0f), Quaternion (0.0f,0.0f,110.0f,45.0f), 
		Vector3(400.0f, 400.0f, 100.0f));
	colli_eye_light->SetIsEnableAutoDelete(false);
	colli_eye_light->SetName("boss03_eye_light");
	colli_eye_light->SetPosition(position_light);

	colli_eye_left = NewGO<CollisionObject>(2);
	colli_eye_left->CreateBox(Vector3(0.0f, 0.0f, 0.0f), Quaternion(0.0f, 0.0f, 110.0f, 45.0f),
		Vector3(400.0f, 400.0f, 100.0f));
	colli_eye_left->SetIsEnableAutoDelete(false);
	colli_eye_left->SetName("boss03_eye_left");
	colli_eye_left->SetPosition(position_left);

	position_light = position;
	position_left = position;

	position_ring_up = { position_ring.x,position_ring.y + ringeyepos_y,position_ring.z };
	position_ring_light = { position_ring.x + ringeyepos_x,position_ring.y,position_ring.z };
	position_ring_left = { position_ring.x - ringeyepos_x,position_ring.y,position_ring.z };
	position_ring_down = { position_ring.x,position_ring.y - ringeyepos_y,position_ring.z };
	return true;
}

void Boss03::Update()
{
	muteki--;
	Move();

	//1�x�������̏������s��Ȃ��B
	if (bosshp <= 500&&beamstate==0&&beamOK==0)
	{
		beamstate = 1;
		beamOK = 1;
	}

	//��ʒu�ɒ�������B
	if (position.y>=-200&&beamstate==0)
	{
		count--;
		//count��0�̂Ƃ��B
			//count��0�ɂȂ�܂ł̓p�^�[����ێ�����B
		if (count == 0)
		{
			//�U���p�^�[�������߂�B
			pattern = rand() % 3;
			//�{����ݒu���Ă�����B
			if (setbomb == 1)
			{
				//�p�^�[����ς��邩�����_���Ō��߂�B
				int changepattern = rand() % 4;
				switch (changepattern)
				{
				case 0:
					pattern = 0;
					break;
				case 1:
					pattern = 1;
					break;
				case 2:
					pattern = 3;
					break;
				case 3:
					pattern = 3;
					break;
				default:
					break;
				}
				//changepattern=0�Ȃ�B		
				//if (changepattern == 0)pattern = 3;
			}
			tamacount = 0;
			countdown = 10;
			setbomb = 0;
			step = 0;
		}
		//count��-500�ȉ��ɂȂ�����B
		if (count <= -500)
		{
			//�p�^�[����3(totugeki)�̏ꍇ�B
			if (pattern == 3)count = 700;
			else  count = 250;   //�p�^�[����3�ȊO�̏ꍇ�B
		}

		//�g�U����ʂ�łB
		if (pattern == 0)Kakusan();
		//�ǔ�����ʂ�łB
		if (pattern == 1)Tuibi();

		//���e��z�u����B
		if (pattern == 2)
		{
			if (setbomb == 0)Bomb();
			//�{���̔z�u���I�������B
			if (setbomb == 1)count = 1;
		}
	}
	if (beamstate == 0)
	{
		//�v���C���[�ɓˌ�����B
		if (pattern == 3)
		{
			totugekistate = 1;
			Totugeki();
		}
	}
		//hp��50����؂����Ƃ��B
		if (beamstate == 1)Beam();

	//�s���p�^�[�����r�[���ł͂Ȃ����ˌ��ł͂Ȃ��Ƃ������蔻��̏������s���B	
		if (beamstate == 0) {
			AttackColli();
			if (totugekistate == 0) {
				Collition();
			}
		}

	//�{��
	modelRender.SetPosition(position);
	modelRender.SetRotation(rotation);
	//�����O
	modelRender_ring.SetPosition(position_ring);
	modelRender_ring.SetRotation(rot_ring);
	//�����O�̖�
	modelRender_ring_Eup.SetPosition(position_ring);
	modelRender_ring_Elight.SetPosition(position_ring);
	modelRender_ring_Eleft.SetPosition(position_ring);
	modelRender_ring_Edown.SetPosition(position_ring);

	modelRender_ring_Eup.SetRotation(rot_ring);
	modelRender_ring_Elight.SetRotation(rot_ring);
	modelRender_ring_Eleft.SetRotation(rot_ring);
	modelRender_ring_Edown.SetRotation(rot_ring);

	//�{��
	colli_eye->SetPosition(position);
	//���̂Ƃ�
	colli_eye_light->SetPosition(position_light);
	colli_eye_left->SetPosition(position_left);
	
	modelRender.Update();
	modelRender_ring.Update();
	modelRender_ring_Eup.Update();
	modelRender_ring_Elight.Update();
	modelRender_ring_Eleft.Update();
	modelRender_ring_Edown.Update();
}

void Boss03::Move()
{
	//�{�̂̈ړ��B
	if (pattern != 3)
	{
		rotation.SetRotationDegY(360.0f);
		//position.y��0��菬�����Ȃ�B
		if (position.y <= 0.0f)position.y += 10.0f;
	}

	//�{�̂̉��ړ��B
	if (pattern != 3&&beamstate==0)
	{
		if (position.y >= 0.0f)
		{
			//�E�Ɉړ�����B
			if (RandLstate == 0)position.x += 3.0f;
			//���Ɉړ�����B
			if (RandLstate == 1)position.x -= 3.0f;

			if (position.x >= 300)RandLstate = 1;
			if (position.x <= -300)RandLstate = 0;
		}
	}

	//�����O�̈ړ��B
	if (position_ring.y != 0.0f)position_ring.y += 10.0f;

	position_light = { position.x+420,position.y ,position.z };
	position_left = { position.x-420,position.y ,position.z };

	position_ring_up = { position_ring.x,position_ring.y+ ringeyepos_y,position_ring.z };
	position_ring_light = { position_ring.x+ ringeyepos_x,position_ring.y,position_ring.z };
	position_ring_left = { position_ring.x- ringeyepos_x,position_ring.y,position_ring.z };
	position_ring_down = { position_ring.x,position_ring.y - ringeyepos_y,position_ring.z };
}

void Boss03::Collition()
{
	//dangan�̃R���W�������擾����B
	const auto& collisions = g_collisionObjectManager->FindCollisionObjects("dangan");
	//collision�̔z���for���ŉ񂷁B
	for (auto collision : collisions)
	{
		//�ݒ肵���R���W�����ƃL�����N�^�[�R���g���[���[���Փ˂��������肷��B
		if (collision->IsHit(colli_eye))
		{
			//muteki��0�ȉ��ɂȂ�����B
			if (muteki <= 0)
			{
				//�{�X��hp��10���炷�B
				bosshp -= player->attackdamage;
				muteki = 30;
			}
			//�{�X��HP��0�ɂȂ�����B
			if (bosshp <= 0)
			{
				//���ꂽ�Ƃ��̉��̍Đ��B
				SoundSource* dead = NewGO<SoundSource>(18);
				dead->Init(18);
				dead->SetVolume(1.2f);
				dead->Play(false);
				//�����G�t�F�N�g�̍Đ��B
				EffectEmitter* effectEmitter_d = NewGO<EffectEmitter>(9);
				effectEmitter_d->Init(9);
				effectEmitter_d->SetScale({ 7.0f,7.0f,0.0f });
				effectEmitter_d->SetPosition(position);
				effectEmitter_d->Play();
				//�G��|�������𑝂₷�B
				player->downcount += 1;
				gameUI3->bossdeath = 1;
				//���g��j�󂷂�B
				DeleteGO(this);
			}
		}
	}
}
//�U������Ƃ��̓����蔻��̏����B
void Boss03::AttackColli()
{
	//�v���C���[�ɑ΂��铖���蔻��̏����B
	//�v���C���[���X�[�p�[�o���A���g���Ă��Ȃ�������B
	if (player->SuparBariaState == false) {
		//player�̃R���W�������擾����B
		const auto& collisions_eye = g_collisionObjectManager->FindCollisionObjects("player");
		//collision�̔z���for���ŉ񂷁B
		for (auto collision : collisions_eye)
		{
			//�ݒ肵���R���W�������Փ˂��������肷��B
			if (collision->IsHit(colli_eye))Damage();
		}
		//player�̃R���W�������擾����B
		const auto& collisions_light = g_collisionObjectManager->FindCollisionObjects("player");
		//collision�̔z���for���ŉ񂷁B
		for (auto collision : collisions_light)
		{
			//�ݒ肵���R���W�������Փ˂��������肷��B
			if (collision->IsHit(colli_eye_light))Damage();
		}
		//player�̃R���W�������擾����B
		const auto& collisions_left = g_collisionObjectManager->FindCollisionObjects("player");
		//collision�̔z���for���ŉ񂷁B
		for (auto collision : collisions_left)
		{
			//�ݒ肵���R���W�������Փ˂��������肷��B
			if (collision->IsHit(colli_eye_left))Damage();
		}
	}
}
//�r�[���̓����蔻��̏����B
void Boss03::BeamColli()
{
	//player�̃R���W�������擾����B
	const auto& collisions_beam = g_collisionObjectManager->FindCollisionObjects("player");
	//collision�̔z���for���ŉ񂷁B
	for (auto collision : collisions_beam)
	{
		//�ݒ肵���R���W�������Փ˂��������肷��B
		if (collision->IsHit(colli_beam))Damage();
	}
}

void Boss03::Kakusan()
{
	countdown--;
	//rand() % 1401 - 700;
	//90�b���Ƃɐ�������B
	if (countdown <= 0)
	{
		if (tamacount <= 10)
		{
			Tama* tama01 = NewGO<Tama>(0, "tama");
			//tama�̔�΂�����ς���B
			tama01->change = 1;
			tama01->position = position;
			tama01->firstposition = tama01->position;
			tama01->ramdom_x = rand() % 501 - 250;
			tama01->ramdom_y = rand() % 501 - 250;
			tama01->randomposition = { tama01->ramdom_x,tama01->ramdom_y,0.0f };

			tamacount++;
			countdown = 5;
		}
	}
	if (tamacount > 10)
	{
		tamacount = 0;
		countdown = 150;
	}
	
}

void Boss03::Tuibi()
{
	countdown--;
	//90�b���Ƃɐ�������B
	if (countdown <= 0)
	{
		tuibitimer--;
		if (tuibitimer <= 0&&tamacount<=5)
		{
			//center����ǔ�����ʂ�łB
			Tama_tuibi* tama_tuibi = NewGO<Tama_tuibi>(0, "tama_tuibi");
			tama_tuibi->position = position;
			tama_tuibi->change = 1;
			tamacount++;
			tuibitimer = 60;
		}

		if (tamacount > 5)
		{
			countdown = 70;
			tamacount = 0;
		}
	}
}

void Boss03::Totugeki()
{
	switch (step)
	{
		//��ʊO�Ɉړ�������B
	case 0:
		position.x += 15.0f;
		if (position.x >= 2500.0f)step = 1;
		break;
		//��]������Z���W���v���C���[��Z���W�ƍ��킹��B
	case 1:
		rotation.SetRotationDegX(90);
		//���؂���W�������_����2����I�ԁB
		randampos_y = rand() % 2;
		if (randampos_y == 0)randampos_y = 300;
		else randampos_y = -200;

		position = {2500.0f,randampos_y,0.0f};
		step = 2;
		break;
		//��ʂ����؂�B
	case 2:
		position.x -= 13.0f;
		rotation.AddRotationDegZ(6.0f);
		if (position.x <= -2500.0f)
		{
			step = 3;
		}
		break;
		//
	case 3:
		//������x���؂���W�������_����2����I�ԁB
		randampos_y = rand() % 2;

		if (randampos_y == 0)randampos_y = 300;
		else randampos_y = -200;

		position = { -2500.0f,randampos_y,0.0f };
		step = 4;
		break;
		//��ʂ����؂�B
	case 4:
		position.x += 13.0f;
		rotation.AddRotationDegZ(-6.0f);
		if (position.x >= 2500.0f)step = 5;
		break;
		//��]���Č���Z���W�ɖ߂�B
	case 5:
		rotation.SetRotationDegX(180.0f);
		rotation.SetRotationDegY(360.0f);
		position = { 1500.0f,0.0f,1200.0f };
		step = 6;
		break;
		//���̈ʒu�ɖ߂�B
	case 6:
		position.x -= 10.0f;
		if (position.x <= 0)step = 7;
		break;
	case 7:
		count = 1;
		totugekistate = 0;
		break;
	default:
		break;
	}
}

void Boss03::Bomb()
{
	countdown--;
	//rand() % 1401 - 700;
	//90�b���Ƃɐ�������B
	if (countdown <= 0)
	{
			Enemy_bomb* enemy_bomb01 = NewGO<Enemy_bomb>(0, "enemy_bomb");
			enemy_bomb01->position = position;
			//enemy_bomb01->firstposition = tama01->position;
			enemy_bomb01->ramdom_x = rand() % 1201 - 600;
			enemy_bomb01->ramdom_y = rand() % 801 - 400;
			enemy_bomb01->randomposition = { enemy_bomb01->ramdom_x,enemy_bomb01->ramdom_y,0.0f };
			tamacount++;
			countdown = 15;
	}
	//�{�X��HP��30���ȏ�Ȃ�B
	if (bosshp > 500)
	{
		//�{��7�z�u�B
		if (tamacount >= 10)
		{
			countdown = 150;
			setbomb = 1;
		}
	}
	//50���ȉ��Ȃ�B
	else
	{
		//�{��10�z�u�B
		if (tamacount >= 22)
		{
			countdown = 150;
			setbomb = 1;
		}
	}
}

void Boss03::Beam()
{
	//�s���Ɉڂ��܂ł̎���
	if (sarchtime >= 0)	sarchtime--;
	
	if (sarchtime <= 0)
	{
		switch (step)
		{
		case 0:
			//�����O��180����]������B
			rot_ring.SetRotationDegY(180);
			//�{�̂��O�ɏo��������B
			position_ring = { 0.0f, 0.0f,800.0f };
			//�����O�̖ڂ̃R���W�����������O�ɍ��킹��B
			ringeyepos_x = 470;
			ringeyepos_y = 470;
			//�{�̂�X���W��0.0�ł͂Ȃ���΁B
			if (position.x != 0.0f)step = 10;
			//X���W��0.0�Ȃ�B
			else step = 1;
			break;
		case 1:
			//Z������2.0f�ŉ�]����������B
			rot_ring.AddRotationDegZ(2.0f);
			//�r�[�����`���[�W����l�����炷�B
			beamchargetime--;
			//�`���[�W�^�C����0�ȉ��ɂȂ�����B
			if (beamchargetime <= 50)
			{
				beambursttime--;
				if (beamchargetime == 0)
				{
					charge = NewGO<SoundSource>(15);
					charge->Init(15);
					charge->SetVolume(1.2f);
					charge->Play(false);

					effectEmitter = NewGO<EffectEmitter>(1);
					effectEmitter->Init(1);
					effectEmitter->SetScale({ 30.0f,30.0f,60.0f });
					effectEmitter->SetPosition(beamchargePos);
					effectEmitter->Play();
				}
				//�r�[����ł��Ă���Ԃ̏����B		
				if (beambursttime <= 0&& beambursttime > -340)
				{
					if (colliState == false)
					{
						colli_beam = NewGO<CollisionObject>(0);
						colli_beam->CreateBox(Vector3(0.0f, 0.0f, 0.0f), Quaternion(90.0f, 90.0f, 90.0f, 1.0f), { 300.0f,300.0f,3000.0f });
						colli_beam->SetIsEnableAutoDelete(false);
						colli_beam->SetName("beam");
						colliState = true;
					}
					//�r�[���̌��ʉ��̍Đ��B
					if (beambursttime == 0)
					{
						beamburst = NewGO<SoundSource>(16);
						beamburst->Init(16);
						beamburst->SetVolume(1.2f);
						beamburst->Play(false);
					}
					if (beambursttime <= 180)
					{
						//���g����v���C���[�̃x�N�g�����v�Z����B
						diff = player->position - position;
						//X
						if (diff.x > Newdiff.x) {
							Newdiff.x += kasokudo_x;
							if (diff.x < Newdiff.x)Newdiff.x = diff.x;
						}
						else if (diff.x < Newdiff.x) {
							Newdiff.x -= kasokudo_x;
							if (diff.x > Newdiff.x)Newdiff.x = diff.x;
						}
					    //Y
						if (diff.y > Newdiff.y) {
							Newdiff.y += kasokudo_y;
							if (diff.y < Newdiff.y)Newdiff.y=diff.y;
						}
						else if (diff.y < Newdiff.y) {
							Newdiff.y -= kasokudo_y;
							if (diff.y > Newdiff.y)Newdiff.y = diff.y;
						}
					    //Z
						Newdiff.z = diff.z;
						//�r�[���̑��x���グ��B
						kasokudo_x += 2.5f;
						kasokudo_y += 2.5f;
						//�x�N�g���𐳋K������B
						Newdiff.Normalize();
						//�ړ����x��ݒ肷��B
						moveSpeed = Newdiff * 0.1f;
						//�{�̂ƃG�t�F�N�g�̉�]�̏����B
						RookON();
						RookON_eff();
						//�v���C���[���X�[�p�[�o���A���g���Ă��Ȃ��Ƃ������蔻��̏������s���B
						if(player->SuparBariaState==false)BeamColli();
						colli_beam->SetPosition(position);
						colli_beam->SetRotation(rotation);
					}
				}
				if (beambursttime <= -345)
				{
					//�r�[���̓����蔻��������B
					DeleteGO(colli_beam);
					effectEmitter->Stop();
					//���G���ԃ��Z�b�g�B
					player->muteki = 0;
					step = 2;
				}
			}
			break;
		case 2:
			//�����O��180����]������(�ŏ��ɖ߂�)�B
			rot_ring.SetRotationDegY(180);
			position_ring = {0.0f,0.0f,1600.0f};
			//�����O�̖ڂ̃R���W�����������O�ɍ��킹��B
			ringeyepos_x = 400;
			ringeyepos_y = 400;
			//beambursttime = 0;
			beamstate = 0;
			break;
		case 10:
			//�{�̂̍��W��0���傫��������B
			if (position.x > 0)position.x -= 3.0f;
			//�{�̂̍��W��0��菬����������B
			if (position.x < 0)position.x += 3.0f;
			if (position.x == 0.0f)step = 1;
			break;
		default:
			break;
		}
	}
}

void Boss03::RookON()
{
	if (fabsf(moveSpeed.x) < 0.001f
		&& fabsf(moveSpeed.z) < 0.001f) {
		//m_moveSpeed.x��m_moveSpeed.z�̐�Βl���Ƃ���0.001�ȉ��Ƃ������Ƃ�
		//���̃t���[���ł̓L�����͈ړ����Ă��Ȃ��̂Ő��񂷂�K�v�͂Ȃ��B
		return;
	}
	//atan2��tan�Ƃ̒l���p�x(���W�A���P��)�ɕϊ����Ă����֐��B
	//m_moveSpeed.x / m_moveSpeed.z�̌��ʂ�tan�ƂɂȂ�B
	//atan2���g�p���āA�p�x�����߂Ă���B
	//���ꂪ��]�p�x�ɂȂ�B
	float angle = atan2(moveSpeed.x, moveSpeed.z);
	//atan���Ԃ��Ă���p�x�̓��W�A���P�ʂȂ̂�
	//SetRotationDeg�ł͂Ȃ�SetRotation���g�p����B
	rotation.SetRotationY(angle);
	
	float angle_x = atan2(moveSpeed.y, moveSpeed.z);
	rotation_x.SetRotationX(angle_x);
	rotation *= rotation_x;
	//��]��ݒ肷��B
	modelRender.SetRotation(rotation);

	//�v���C���[�̐��ʃx�N�g�����v�Z����B
	forward = Vector3::AxisZ;
	rotation.Apply(forward);
}

void Boss03::RookON_eff()
{
	if (fabsf(moveSpeed.x) < 0.001f
		&& fabsf(moveSpeed.z) < 0.001f) {
		//m_moveSpeed.x��m_moveSpeed.z�̐�Βl���Ƃ���0.001�ȉ��Ƃ������Ƃ�
		//���̃t���[���ł̓L�����͈ړ����Ă��Ȃ��̂Ő��񂷂�K�v�͂Ȃ��B
		return;
	}
	float angle_eff = atan2(moveSpeed.x, moveSpeed.z);
	//Y�����̉�]�B
	rot_effect_y.SetRotationY(angle_eff);

	float angle_eff_x = atan2(moveSpeed.y, moveSpeed.z);
	//X�����̉�]�B
	rot_effect_x.SetRotationX(angle_eff_x);
	//X�����̉�]��Y�����̉�]�𑫂��B
	rot_effect_y *= rot_effect_x;

	effectEmitter->SetRotation(rot_effect_y);
	//�v���C���[�̐��ʃx�N�g�����v�Z����B
	forward = Vector3::AxisZ;
	rot_effect_y.Apply(forward);
}
//�v���C���[�Ƀ_���[�W��^�����Ƃ��̏����B
void Boss03::Damage()
{
	if (beamstate == 0) {
		if (player->muteki >= 60) {
			//player��Hp��10���炷�B
			player->playerHp -= player->damage;
			//�_���[�W���󂯂��B
			player->damagestate = 1;
			//���G���ԃ��Z�b�g�B
			player->muteki = 0;
		}
	}
	else if (beamstate == 1) {
		//���G���Ԃ��U�O�ȏ�Ȃ�B
		if (player->muteki >= 60) {
			//player��Hp��5���炷�B
			player->playerHp -= 6;
			//�_���[�W���󂯂��B
			player->damagestate = 1;
			//�p�����ă_���[�W��^���邽�߂ɖ��G���Ԃ�Z������B
			player->muteki = 40;
		}
	}
	
}

void Boss03::Render(RenderContext& rc)
{
	modelRender.Draw(rc);
	modelRender_ring.Draw(rc);

	modelRender_ring_Eup.Draw(rc);
	modelRender_ring_Elight.Draw(rc);
	modelRender_ring_Eleft.Draw(rc);
	modelRender_ring_Edown.Draw(rc);
}