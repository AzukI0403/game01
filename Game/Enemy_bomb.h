#pragma once
//#include "sound/SoundSource.h"

class Baria;
class Game_final;
class Boss03;
class Player;

class Enemy_bomb:public IGameObject
{
public:
	Enemy_bomb();
	~Enemy_bomb();

	bool Start();
	void Update();
	void Collition();
	void Render(RenderContext& rc);

	Baria* baria;
	Game_final* game_final;
	Boss03* boss03;
	Player* player;

	Vector3 position;
	Vector3 moveSpeed;
	Vector3 randomposition;
	ModelRender modelRender;
	CollisionObject* colli;  //ÉRÉäÉWÉáÉìÅB

	int explode=800;

	float ramdom_y;
	float ramdom_x;
};

