#include "stdafx.h"
#include "Box1_3.h"
#include "Stagecelect.h"
#include "Scoreboard.h"

Box1_3::Box1_3()
{

}

Box1_3::~Box1_3()
{
	DeleteGO(colli);
}

bool Box1_3::Start()
{


	modelRender.SetRaytracingWorld(false);
	modelRender.Init("Assets/modelData/1_3.tkm");

	//1-1ƒRƒŠƒWƒ‡ƒ“‚Ìì¬B
	colli = NewGO<CollisionObject>(0);

	colli->CreateBox(Vector3(0.0f, 0.0f, 0.0f), Quaternion::Identity,
		Vector3(370.0f, 200.0f, 20.0f));

	colli->SetIsEnableAutoDelete(false);

	colli->SetName("1_3");

	scoreboard = NewGO<Scoreboard>(0, "scoreboard");
	scoreboard->position = { 880.0f,60.0f,0.0f };
	scoreboard->position_rank = { 880.0f,60.0f,0.0f };
	scoreboard->rank = rank;
	return true;
}

void Box1_3::Update()
{
	colli->SetPosition(position);
	modelRender.SetPosition(position);
	modelRender.Update();
}

void Box1_3::Render(RenderContext& rc)
{
	modelRender.Draw(rc);
}