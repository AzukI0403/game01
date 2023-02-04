#pragma once
#include "sound/SoundSource.h"

class SceneChangeDoor:public IGameObject
{
public:
	SceneChangeDoor();
	~SceneChangeDoor();

	bool Start();
	void Update();

	void Door();
	void Brackout();

	void Render(RenderContext& rc);

	SpriteRender spriteRender_brack;
	SpriteRender spriteRender_switch_ue;
	SpriteRender spriteRender_switch_sita;

	SoundSource* doorclose;//”à‚ğ•Â‚ß‚é‚Æ‚«‚Ì‰¹

	Vector3 position_sc_ue /*= { 0.0f,1190.0f,0.0f }*/;
	Vector3 position_sc_sita/* = { 0.0f,-1235.0f,0.0f }*/;

	//”à‚ª•Â‚¶‚Ä‚¢‚éŠÔ‚ÌŠÔB
	int count = 60;

	int patten = 0;

	float color = 0;

	int blacktime = 100;

	bool clear = false;

	bool openstate = false;
	bool closestate = true;

	int switchok = 0;
};

