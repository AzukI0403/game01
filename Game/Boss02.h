#pragma once

class Player;
class Game2;
class Baria;
class Tama_tuibi;
class GameUI2;
class Numberhouse;
class Tama_big;


class Boss02:public IGameObject
{
public:
	Boss02();
	~Boss02();

	bool Start();
	void Update();
	void Move();
	void Collision_up();
	void Collision_center();
	void Collision_down();
	//攻撃パターン0
	void Tama();
	//攻撃パターン1
	void Tuibi();
	//攻撃パターン2
	void Totugeki();
	void Target_up();
	void Target_center();
	void Target_down();
	void Dead();
	void Render(RenderContext& rc);


	Player* player;
	Game2* game2;
	Baria* baria;
	Tama_tuibi* tama_tuibi;
	GameUI2* gameUI2;
	Numberhouse* numberhouse;
	//Tama_big* tama_big;

	Vector3 position_up;
	Vector3 position_center;
	Vector3 position_down;

	Vector3 moveSpeed_up;
	Vector3 moveSpeed_center;
	Vector3 moveSpeed_down;

	Vector3 firstPosition_up;
	Vector3 firstPosition_center;
	Vector3 firstPosition_down;

	ModelRender modelRender_up;
	ModelRender modelRender_center;
	ModelRender modelRender_down;

	CollisionObject* colli_up;  //upのコリジョン。
	CollisionObject* colli_center;  //centerのコリジョン。
	CollisionObject* colli_down;  //downのコリジョン。

	int moveCount = 0;
	//攻撃パターン。
	int pattern;

	int count = 600;
	//tama_bigを打つまでの時間。
	int countdown = 10;

	int change = 0;
	//boss02のHP。3体共有。
	int maxbosshp = 100;
	int bosshp = 100;

	int muteki = 100;

	int targetstate = 0;

	int gostate = 1;
	int backstate = 0;
	int sarchtime = 100;
	int attackcounter=0;
	int stopstate_up=0;
	int stopstate_center=0;
	int stopstate_down=0;

	int totugekicount=0;

	int attackcomplete = 0;

	int attack=0;
	int oldattack=10;
};

