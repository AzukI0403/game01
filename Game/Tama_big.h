#pragma once

class Player;
class Baria;
class Boss02;
class Game2;

class Tama_big:public IGameObject
{
public:
	Tama_big();
	~Tama_big();

	bool Start();
	void Update();
	void Collition();
	void Render(RenderContext& rc);

	Player* player;
	Baria* baria;
	Boss02* boss02;
	Game2* game2;

	Vector3 position;
	ModelRender modelRender;
	CollisionObject* colli;  //ƒRƒŠƒWƒ‡ƒ“B
};

