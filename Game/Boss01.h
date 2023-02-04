#pragma once

class Player;
class Game;
class Baria;
class Tama;
class Tama_tuibi;
class GameUI;

class Boss01:public IGameObject
{
public:
	Boss01();
	~Boss01();

	bool Start();
	void Update();
	void Move();
	void Collision();
	void Tuibi();
	void Kakusan();
	void Bite();
	void Target();
	void Damage();
	void BiteRot();
	void Dead();
	void Render(RenderContext& rc);


	Player* player;
	Game* game;
	Baria* baria;
	Tama* tama;
	Tama_tuibi* tama_tuibi;
	GameUI* gameUI;

	Vector3 moveSpeed;
	Vector3 moveSpeed_b;
	
	Vector3 position_up;
	Vector3 firstPosition_up;
	Vector3 position_down;
	Vector3 firstPosition_down;

	Vector3 effectPos;

	Vector3 pos_colli;

	Vector3 diff;

	ModelRender modelRender_up;
	ModelRender modelRender_down;

	CollisionObject* colli_up;  //コリジョン。
	CollisionObject* colli_down;  //コリジョン。

	Quaternion rot_up;  //上顎クォータニオン。
	Quaternion rot_down;  //下顎クォータニオン。

	Quaternion rot_up2={0.0f,0.0f,0.0f,1.0f};  //上顎クォータニオン。
	Quaternion rot_down2{ 0.0f,0.0f,0.0f,1.0f };  //下顎クォータニオン。

	int moveCount=0;

	int pattern=4;

	int count=100;

	int countdown=10;

	int change = 0;

	int maxbosshp = 100;
	int bosshp = 100;

	int muteki = 100;

	int targetstate=0;

	int totugekitime = 70;
	//突撃する回数のカウント=2。
	int totugekicount = 0;
	int gostate = 1;
	int backstate = 0;
	int sarchtime = 90;

	//かみつく攻撃のダメージ=20。
	int bitedamage = 20;

	int opentime = 50;
	int closetime = 0;
};

