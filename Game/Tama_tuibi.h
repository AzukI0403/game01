#pragma once

class Player;
class Enemy01;
class Game;
class Baria;
class Game2;
class Game3;
class Game_final;
class Numberhouse;

class Tama_tuibi :public IGameObject
{
public:
	Tama_tuibi();
	~Tama_tuibi();

	bool Start();
	void Update();
	void Collitionb();
	void Render(RenderContext& rc);

	Player* player;
	Enemy01* enemy01;
	Game* game;
	Baria* baria;
	Game2* game2;
	Game3* game3;
	Game_final* game_final;
	Numberhouse* Numberhouse;

	ModelRender modelRender;
	Vector3 position;
	Vector3 moveSpeed;
	Vector3 firstposition;
	CollisionObject* colli;  //ƒRƒŠƒWƒ‡ƒ“B

	int change;
	int countdown=30;
	int count=0;
};

