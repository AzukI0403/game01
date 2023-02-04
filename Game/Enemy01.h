#pragma once
#include "sound/SoundSource.h"

class Player;
class Dangan;
class Game;
class Baria;
class Game2;
class Game3;

class Enemy01 :public IGameObject
{
public:
	Enemy01();
	~Enemy01();

	bool Start();
	void Update();
	void Attack();
	void Move();
	//弾丸との当たり判定。	
	void Collisiond();
	//プレイヤーとの当たり判定。
	void Collisionp();
	//バリアとの当たり判定。
	void Collisionb();
	//自身がやられたときの処理。
	void Dead();
	void Render(RenderContext& rc);


	Player* player;
	Dangan* dangan;
	Game* game;
	Baria* baria;
	Game2* game2;
	Game3* game3;

	SoundSource* kougeki;//tamaを打ったときの音
	SoundSource* death;//やられたときの音

	ModelRender modelRender;
	Vector3 position;
	Quaternion rotation;
	Vector3 moveSpeed;
	Vector3 firstPosition;
	Vector3	forward = Vector3::AxisZ;//エネミーの正面ベクトル。
	CharacterController characterController;  //キャラクターコントローラー。
	CollisionObject* colli;  //コリジョン。
	int tamaCount=0;
	int moveCount;
	int timeCount = 0;
	int tamatime = 0;
	int go;
	

};