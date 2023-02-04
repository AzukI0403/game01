#pragma once

class Player;
class Enemy01;
class Game;
class Baria;
class Boss01;
class Game2;
class Numberhouse;

class Tama:public IGameObject
{
public:
	Tama();
	~Tama();

	bool Start();
	void Update();
	void Collitionb();
	void Render(RenderContext& rc);
	
	Player* player;
	Enemy01* enemy01;
	Game* game;
	Baria* baria;
	Boss01* boss01;
	Game2* game2;
	Numberhouse* numberhouse;

	ModelRender modelRender;
	Vector3 position;
	Vector3 moveSpeed;
	Vector3 firstposition;
	Vector3 randomposition;
	CollisionObject* colli;  //ƒRƒŠƒWƒ‡ƒ“B

	int change=0;
	float ramdom_y;
	float ramdom_x;

	int stagenumber;
};

