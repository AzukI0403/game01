#include "stdafx.h"
#include "Dangan.h"
#include "Player.h"
#include "GameCamera.h"
#include "Game.h"
#include "Game2.h"
#include "Numberhouse.h"



Dangan::Dangan()
{

}

Dangan::~Dangan()
{
	DeleteGO(colli);
}

bool Dangan::Start()
{
	player = FindGO<Player>("player");
	//�Q�[��1_1�̃C���X�^���X��T���B
	game = FindGO<Game>("game");
	//�Q�[��1_2�̃C���X�^���X��T���B
	game2 = FindGO<Game2>("game2");
	
	numberhouse = FindGO<Numberhouse>("numberhouse");

	//�R���W�����̍쐬�B
	colli = NewGO<CollisionObject>(0);
	colli->CreateSphere(Vector3(0.0f,-20.0f, 0.0f), Quaternion ::Identity, 5.0f);
	colli->SetIsEnableAutoDelete(false);
	colli->SetName("dangan");
	colli->SetPosition(position);

	//��������I�u�W�F�N�g�̏������y������B
	modelRender.SetRaytracingWorld(false);
	modelRender.Init("Assets/modelData/dangan.tkm");

	stagenumber = numberhouse->stagenumber;
	

	if (stagenumber == 4) {
		modelRender.SetRotation(rotation);
		colli->SetRotation(rotation);
	}

	return true;

}


 void Dangan::Update()
 {
	 collision();
	 
	 if (stagenumber == 4)
	 {
		 //�e�ۂ̑��x�B
		 position.z += 50.0f;
	 }
	 else
	 {
		 //�e�ۂ̑��x�B
		 position.x += 50.0f;
	 }
	
	
	 colli->SetPosition(position);

	 //�v���C���[����e�ۂ̃x�N�g�����v�Z�B
	 Vector3 diff = player->position - position;
	 //�x�N�g���̒�����2000.0f���傫���Ȃ�����B
	if (diff.Length() >= 2000.0f)
	 {
		 //�e�ۂ������B
		 DeleteGO(this);
	 }

	//�G�`������ɍ��W��������B
	modelRender.SetPosition(position);
	 modelRender.Update();
 }

 //enemy01�Ƃ̓����蔻��B
 void Dangan::collision()
 {
	 //enemy01�̃R���W�������擾����B
	 const auto& collisions = g_collisionObjectManager->FindCollisionObjects("enemy_eye");
	                         
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
	
	 //boss01_down�̃R���W�������擾����B
	 const auto& collisions_b12 = g_collisionObjectManager->FindCollisionObjects("boss01_down");

	 //collision�̔z���for���ŉ񂷁B
	 for (auto collision : collisions_b12)
	 {
		 //�ݒ肵���R���W�������Փ˂��������肷��B
		 if (collision->IsHit(colli))
		 {
			 //���g��j�󂷂�B
			 DeleteGO(this);
		 }
	 }
	 //boss02�̃R���W�������擾����B
	 const auto& collisions_b2_up = g_collisionObjectManager->FindCollisionObjects("up");

	 //collision�̔z���for���ŉ񂷁B
	 for (auto collision : collisions_b2_up)
	 {
		 //�ݒ肵���R���W�������Փ˂��������肷��B
		 if (collision->IsHit(colli))
		 {
			 //���g��j�󂷂�B
			 DeleteGO(this);
		 }
	 }
	 //boss02�̃R���W�������擾����B
	 const auto& collisions_b2_center = g_collisionObjectManager->FindCollisionObjects("center");

	 //collision�̔z���for���ŉ񂷁B
	 for (auto collision : collisions_b2_center)
	 {
		 //�ݒ肵���R���W�������Փ˂��������肷��B
		 if (collision->IsHit(colli))
		 {
			 //���g��j�󂷂�B
			 DeleteGO(this);
		 }
	 }
	 //boss02�̃R���W�������擾����B
	 const auto& collisions_b2_down = g_collisionObjectManager->FindCollisionObjects("down");

	 //collision�̔z���for���ŉ񂷁B
	 for (auto collision : collisions_b2_down)
	 {
		 //�ݒ肵���R���W�������Փ˂��������肷��B
		 if (collision->IsHit(colli))
		 {
			 //���g��j�󂷂�B
			 DeleteGO(this);
		 }
	 }
	 //boss03�̃R���W�������擾����B
	 const auto& collisions_b3 = g_collisionObjectManager->FindCollisionObjects("boss03");

	 //collision�̔z���for���ŉ񂷁B
	 for (auto collision : collisions_b3)
	 {
		 //�ݒ肵���R���W�������Փ˂��������肷��B
		 if (collision->IsHit(colli))
		 {
			 //���g��j�󂷂�B
			 DeleteGO(this);
		 }
	 }
 }

 void Dangan::Render(RenderContext& rc)
 {
	 modelRender.Draw(rc);
 }