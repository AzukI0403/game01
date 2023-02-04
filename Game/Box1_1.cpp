#include "stdafx.h"
#include "Box1_1.h"
#include "Stagecelect.h"
#include "Scoreboard.h"

Box1_1::Box1_1()
{

}

Box1_1::~Box1_1()
{
	DeleteGO(colli);
}

bool Box1_1::Start()
{
	modelRender.SetRaytracingWorld(false);
	modelRender.Init("Assets/modelData/1_1.tkm");



	//1-1ƒRƒŠƒWƒ‡ƒ“‚Ìì¬B
	colli = NewGO<CollisionObject>(0);
	
	colli->CreateBox(Vector3(0.0f, 0.0f, 0.0f), Quaternion::Identity,
		Vector3(370.0f, 200.0f, 20.0f));

	colli->SetIsEnableAutoDelete(false);

	colli->SetName("1_1");

	scoreboard = NewGO<Scoreboard>(0, "scoreboard");
	scoreboard->position = { -370.0f,-40.0f,0.0f };
	scoreboard->position_rank= { -370.0f,-40.0f,0.0f };
	scoreboard->rank = rank;

	
	return true;
}

void Box1_1::Update()
{
	colli->SetPosition(position);
	modelRender.SetPosition(position);
	modelRender.Update();
}

void Box1_1::Render(RenderContext& rc)
{
	modelRender.Draw(rc);
}