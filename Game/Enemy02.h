#pragma once
#include "sound/SoundSource.h"

class Player;
class Dangan;
class Game;
class Result;
class Tama;
class Tama_tuibi;
class Game2;
class Game3;
class Numberhouse;
class Baria;

class Enemy02:public IGameObject
{
public:
	Enemy02();
	~Enemy02();

	bool Start();
	void Update();
	void Move();
	void Move2();
	void Rotation();
	void Attack();
	//弾丸との当たり判定。	
	void Collision();
	void Render(RenderContext& rc);
	void Dead();
	
	Player* player;
	Dangan* dangan;
	Game* game;
	Result* result;
	Tama* tama;
	Tama_tuibi* tama_tuibi;
	Game2* game2;
	Game3* game3;
	Numberhouse* numberhouse;
	Baria* baria;

	ModelRender modelRender;
	ModelRender modelRender_eye;
	ModelRender modelRender_up;
	ModelRender modelRender_down;


	Vector3 position;
	Vector3 position_up;
	Vector3 position_down;
	Vector3 firstPosition;
	Vector3 firstPosition_up;
	Vector3 firstPosition_down;

	Quaternion rotation;
	Vector3 moveSpeed;
	
	Vector3	forward = Vector3::AxisZ;//エネミーの正面ベクトル。
	//CharacterController characterController;  //キャラクターコントローラー。
	CollisionObject* colli;  //コリジョン。

	SoundSource* death;//やられたときの音

	int enemyState = 0;
	int moveCount;
	int timeCount = 0;
	int tamaCount = 0;
	int tamatime = 0;
	bool collision = false;
	//enemy02がgame2でchange=1のとき画面内にいる時間。
	int timer = 500;

	int upstate=0;
	//停止判定。
	int stopstate;
	//攻撃判定。
	int attackstate;
	//防御判定。
	int gardstate=0;
	int opentimer=100;

	int change=0;
	int tamachange = 0;
	int stagenumber;
};

