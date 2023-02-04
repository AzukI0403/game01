#include "stdafx.h"
#include "Kyuen.h"
#include "Player.h"


Kyuen::Kyuen()
{

}

Kyuen::~Kyuen()
{
	DeleteGO(colli);
}

bool Kyuen::Start()
{


	//�v���C���[�̃C���X�^���X��T���B
	player = FindGO<Player>("player");
	//��������I�u�W�F�N�g�̏������y������B
	modelRender.SetRaytracingWorld(false);
	modelRender.Init("Assets/modelData/kyuen.tkm");

	//�R���W�����̍쐬�B
	colli = NewGO<CollisionObject>(0);
	colli->CreateCapsule(Vector3(-20.0f, 0.0f, 0.0f), Quaternion(90.0f,90.0f,0.0f,0.0f), 30.0f,100.0f);
	colli->SetIsEnableAutoDelete(false);
	colli->SetName("kyuen");
	colli->SetPosition(position);

	return true;
}

void Kyuen::Update()
{
	if (player->kyuenget >= 1)
	{
		DeleteGO(this);
	}

	if (position.x <= -1100)
	{
		DeleteGO(this);
	}

	position.x -= 6.0f;

	colli->SetPosition(position);
	//�G�`������ɍ��W��������B
	modelRender.SetPosition(position);

	modelRender.Update();
}

void Kyuen::Render(RenderContext& rc)
{
	modelRender.Draw(rc);
}
