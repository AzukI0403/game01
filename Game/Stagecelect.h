#pragma once
#include "sound/SoundSource.h"


//class Game;
class GameCamera_sc;
//class Pointer;
class Box1_1;
class Box1_2;
class Box1_3;
class Sc_bg;
class Scoreboard;
class Game;
class Game2;
class Game3;
class SceneChangeDoor;

class Stagecelect:public IGameObject
{
public:
	Stagecelect();
	~Stagecelect();

	bool Start();
	void Update();
	void PMove();
	void Collition();
	void SwitchScreen();
	void Render(RenderContext& rc);

	GameCamera_sc* gamecamera_sc;
	
	Box1_1*box1_1;
    Box1_2*box1_2;
	Box1_3* box1_3;
	Sc_bg* sc_bg;
	Scoreboard* scoreboard;
	SceneChangeDoor* SCD;

	Vector3 position;
	Vector3 position_sc_ue /*= { 0.0f,1190.0f,0.0f }*/;
	Vector3 position_sc_sita/* = { 0.0f,-1235.0f,0.0f }*/;
	Vector3 pointerPos;

	
	CollisionObject* colli1;  //コリジョン。
	CollisionObject* colli2;  //コリジョン。
	CollisionObject* colli3;  //コリジョン。

	CollisionObject* colli_pointer;  //コリジョン。

	ModelRender modelRender;

	SpriteRender spriteRender;
	SpriteRender spriteRender_ura;

	SpriteRender spriteRender_switch_ue;
	SpriteRender spriteRender_switch_sita;

	SpriteRender spriteRender_pointer;

	SoundSource* doorclose;//扉を閉めるときの音
	SoundSource* decision;//選択したときの音

	int rank=0;

	int rank_1 = 0;
	int rank_2 = 0;
	int rank_3 = 0;

	int Rank_1 = 0;
	int Rank_2 = 0;
	int Rank_3 = 0;

	int stagenumber=0;
	//rankを代入する時に使う変数。
	int StageNumber = 0;

	int switchtime = 0;
	int switchok = 0;
	int doorOK = 0;

	int doorstate = 0;

	int state = 0;

};

