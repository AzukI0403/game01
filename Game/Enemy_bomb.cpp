#include "stdafx.h"
#include "Enemy_bomb.h"
#include "Baria.h"
#include "Player.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
#include "Game_final.h"
#include "Boss03.h"
#include "graphics/effect/EffectEmitter.h"


Enemy_bomb::Enemy_bomb()
{

}

Enemy_bomb::~Enemy_bomb()
{
	EffectEmitter* effectEmitter = NewGO<EffectEmitter>(0);
	effectEmitter->Init(0);
	effectEmitter->SetScale({ 10.0f,10.0f,10.0f });
	effectEmitter->SetPosition(position);
	effectEmitter->Play();

	DeleteGO(colli);
}

bool Enemy_bomb::Start()
{
	//�v���C���[�̃C���X�^���X��T���B
	player = FindGO<Player>("player");
	//�Q�[���̃C���X�^���X��T���B
	baria = FindGO<Baria>("baria");

	//���ꂽ�Ƃ��̉���ǂݍ��ށB
	g_soundEngine->ResistWaveFileBank(2, "Assets/sound/enemy_death.wav");

	modelRender.SetRaytracingWorld(false);
	modelRender.Init("Assets/modelData/bomb.tkm");

	//�G�t�F�N�g��ǂݍ��ށB
	EffectEngine::GetInstance()->ResistEffect(0, u"Assets/effect/effectsprite/explosion.efk");

	//�R���W�����̍쐬�B
	colli = NewGO<CollisionObject>(0);
	colli->CreateSphere(Vector3(0.0f, 0.0f, 0.0f), Quaternion::Identity, 30.0f);
	colli->SetIsEnableAutoDelete(false);
	colli->SetName("bomb");
	colli->SetPosition(position);

	//tama�̑��x�B
	//tama����v���C���[�Ɍ������x�N�g�����v�Z����B
	Vector3 diff = randomposition - position;

	//�x�N�g���𐳋K������B
	diff.Normalize();
	//�ړ����x��ݒ肷��B
	moveSpeed = diff * 15.0f;

	return true;
}

void Enemy_bomb::Update()
{
	if (position.z >= 0)
	{
		position += moveSpeed;
	}

	if (position.z <= 0)
	{
		//explode=400
		explode--;
		//400�t���[���������甚��������B
		if (explode <= 0)
		{
			//�����̉����Đ�����B
			SoundSource* death = NewGO<SoundSource>(2);
			death->Init(2);
			death->SetVolume(0.7f);
			death->Play(false);
			//���g��j�󂷂�B
			DeleteGO(this);
		}
	}

	if(position.z<=0)Collition();

	modelRender.SetPosition(position);
	colli->SetPosition(position);
	modelRender.Update();
}

void Enemy_bomb::Collition()
{
	//baria�̃R���W�������擾����B
	const auto& collisions = g_collisionObjectManager->FindCollisionObjects("baria");

	//collision�̔z���for���ŉ񂷁B
	for (auto collision : collisions)
	{
		//�ݒ肵���R���W�������Փ˂��������肷��B
		if (collision->IsHit(colli))
		{
			//�����̉����Đ�����B
			SoundSource* death = NewGO<SoundSource>(2);
			death->Init(2);
			death->SetVolume(1.0f);
			death->Play(false);
			//���g��j�󂷂�B
			DeleteGO(this);
		}
	}

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
			//�����̉����Đ�����B
			SoundSource*death = NewGO<SoundSource>(2);
			death->Init(2);
			death->SetVolume(1.0f);
			death->Play(false);
			//���g��j�󂷂�B
			DeleteGO(this);
		}
	}
}

void Enemy_bomb::Render(RenderContext& rc)
{
	modelRender.Draw(rc);
}
