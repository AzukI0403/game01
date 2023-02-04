#include "stdafx.h"
#include "BackGround.h"
#include "Game_final.h"

BackGround::BackGround()
{

}

BackGround::~BackGround()
{

}

bool BackGround::Start()
{
	//�Q�[��1_2�̃C���X�^���X��T���B
	game_final = FindGO<Game_final>("game_final");

	// �����蔻��̉����B
	//�R�����g�A�E�g����B
	//PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();
	modelRender.SetRaytracingWorld(false);
	modelRender.Init("Assets/modelData/utyu_shere.tkm");
	
	//physicsStaticObject.CreateFromModel(modelRender.GetModel(), modelRender.GetModel().GetWorldMatrix());
	
	modelRender.SetPosition(position);
	return true;
};

void BackGround::Update()
{
	rot.AddRotationY(0.001f);

	modelRender.SetRotation(rot);
	modelRender.SetPosition(position);
	modelRender.Update();
}



void BackGround::Render(RenderContext& rc)
{
	modelRender.Draw(rc);
}
