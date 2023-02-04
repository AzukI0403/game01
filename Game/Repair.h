#pragma once

class Player;
class Game;
class Game2;
class Game3;
class Numberhouse;

class Repair:public IGameObject
{
public:
	Repair();
	~Repair();

	bool Start();
	void Update();
	
	void Kaihuku();
	void Render(RenderContext&rc);

	Player* player;
	Game* game;
	Game2* game2;
	Game3* game3;
	Numberhouse* numberhouse;

	ModelRender modelRender;
	Vector3 position;
	Vector3 moveSpeed;
	Quaternion rotation;  //クォータニオン。
	CollisionObject* colli;  //コリジョン。

	SoundSource* kaifuku;//回復したときの音

	int get=0;
	int repairget = 0;
	//int effecttime = 40;
};

