#include "stdafx.h"
#include "Baria.h"
#include "Game.h"
#include "Player.h"
#include "Game2.h"
#include "graphics/effect/EffectEmitter.h"

Baria::Baria()
{

}

Baria::~Baria()
{
	DeleteGO(effectEmitter);
	DeleteGO(colli);
}

bool Baria::Start()
{
	//�v���C���[�̃C���X�^���X��T���B
	player = FindGO<Player>("player");
	//�Q�[��1_1�̃C���X�^���X��T���B
	game = FindGO<Game>("game");
	//�Q�[��1_2�̃C���X�^���X��T���B
	game2 = FindGO<Game2>("game2");
	//��������I�u�W�F�N�g�̏������y������B
	modelRender.SetRaytracingWorld(false);
	modelRender.IniTranslucent("Assets/modelData/baria.tkm");

	EffectEngine::GetInstance()->ResistEffect(10, u"Assets/effect/effectsprite/suparbaria.efk");


	//�R���W�����̍쐬�B
	colli = NewGO<CollisionObject>(0);
	colli->CreateSphere(Vector3(0.0f, 0.0f, 0.0f), Quaternion::Identity, 150.0f);
	colli->SetIsEnableAutoDelete(false);
	colli->SetName("baria");
	colli->SetPosition(position);

	if (SuparBariaState == true)time = 300;

	return true;
}

void Baria::Update()
{
	//time=200
	time--;

	position = player->position;
	
	//�R���W�����̃|�W�V�����B
	Cposition = player->position;
	
	if (SuparBariaState == true)
	{
		effectEmitter = NewGO<EffectEmitter>(10);
		effectEmitter->Init(10);
		effectEmitter->SetScale({ 35.0f,35.0f,35.0f });
		effectEmitter->SetPosition(position);
		effectEmitter->Play();
		SuparBariaState = false;
		SBOK = 1;
	}
	if (SBOK == 1)
	{
		effectEmitter->SetPosition(position);
	}
	

	//�o���A���o���Ă��鎞�Ԃ�0�ȉ��ɂȂ�����B
	if (time <= 0)
	{
		//�o���A���o�����Ԃ�߂��B
		time = 100;
		//������x�o���A���o����悤�ɂ���B
		player->BB = 0;
		player->SuparBariaState = false;
		DeleteGO(this);
	}

	//�G�`������ɍ��W��������B
	modelRender.SetPosition(position);
	colli->SetPosition(Cposition);
	modelRender.Update();
}

void Baria::Render(RenderContext& rc)
{
	modelRender.Draw(rc);
}