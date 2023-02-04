#include "stdafx.h"
#include "Box1_2.h"
#include "Stagecelect.h"
#include "Scoreboard.h"

Box1_2::Box1_2()
{

}

Box1_2::~Box1_2()
{
	DeleteGO(colli);
}

bool Box1_2::Start()
{
	

	modelRender.SetRaytracingWorld(false);
	modelRender.Init("Assets/modelData/1_2.tkm");

	//1-1ƒRƒŠƒWƒ‡ƒ“‚Ìì¬B
	colli = NewGO<CollisionObject>(0);

	colli->CreateBox(Vector3(0.0f, 0.0f, 0.0f), Quaternion/*(0.0f,0.0f,0.0f,0.0f)*/::Identity,
		Vector3(370.0f, 200.0f, 20.0f));

	colli->SetIsEnableAutoDelete(false);

	colli->SetName("1_2");

	scoreboard = NewGO<Scoreboard>(0, "scoreboard");
	scoreboard->position = { 260.0f,190.0f,0.0f };
	scoreboard->position_rank = { 260.0f,190.0f,0.0f };

	scoreboard->rank = rank;

	return true;
}

void Box1_2::Update()
{
	colli->SetPosition(position);
	modelRender.SetPosition(position);
	modelRender.Update();
}

void Box1_2::Render(RenderContext& rc)
{
	modelRender.Draw(rc);
}
