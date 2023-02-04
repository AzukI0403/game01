#pragma once

class Stagecelect;

class Gamestart :public IGameObject
{
public:
	Gamestart();
	~Gamestart();

	bool Start();
	void Update();
	void StagecelectSelect();
	void ExplanationSelect();
	void Render(RenderContext& rc);

	//Stagecelect* stagecelect;

	SpriteRender spriteRender;

	SpriteRender spriteRender_A;
	SpriteRender spriteRender_B;

	SoundSource* celect;//‘I‘ð‚µ‚½‚Æ‚«‚Ì‰¹
	SoundSource* BGM;//BGM‚Ì‰¹

	/*Vector3 bottunApos;
	Vector3 bottunBpos;*/

	float brack = 1;

	int count = 60;

	int explanationstate = 0;
	int stageselectstate = 0;

	bool exNotDraw = false;
	bool scNotDraw = false;

	int rank=0;
	int rank_1=0;
	int rank_2=0;
	int rank_3=0;
	int stagenumber=0;
};

