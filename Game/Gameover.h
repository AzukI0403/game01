#pragma once

class Result;
class Numberhouse;
class SceneChangeDoor;

class Gameover:public IGameObject
{
public:
	Gameover();
	~Gameover();

	bool Start();
	void Update();
	void ResultGO();
	void RetryGO();
	void SwitchScreen();
	void Render(RenderContext& rc);

	Result* result;
	Numberhouse* numberhouse;
	SceneChangeDoor* SCD;

	SoundSource* gover;//ゲームオーバーの音

	SpriteRender spriteRender;
	SpriteRender spriteRender_A;
	SpriteRender spriteRender_B;

	int resultstate = 0;
	int retrystate = 0;
	//60
	int count = 60;

	bool resultNotDraw = false;
	bool retryNotDraw = false;

	int GOtime = 30;

	int Coin_rinzi = 0;
	int enemy_rinzi = 0;
	int Timeup_rinzi = 0;

	float color=0;
	float color_AB = 0;

	int rank_1 = 0;
	int rank_2 = 0;
	int rank_3 = 0;
	int stagenumber;

	int switchtime = 0;
	int switchok = 0;
	int doorOK = 0;

	int doorstate = 0;

	int state = 0;
};

