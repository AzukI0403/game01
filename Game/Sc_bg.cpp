#include "stdafx.h"
#include "Sc_bg.h"
#include "Stagecelect.h"

Sc_bg::Sc_bg()
{

}

Sc_bg::~Sc_bg()
{

}

bool Sc_bg::Start()
{
	//stagecelectÇÃîwåiÅB
	modelRender.SetRaytracingWorld(false);
	modelRender.Init("Assets/modelData/stagecelect_bg.tkm");

	return true;
}

void Sc_bg::Update()
{
	modelRender.SetPosition(position);
	modelRender.Update();
}

void Sc_bg::Render(RenderContext& rc)
{
	modelRender.Draw(rc);
}
