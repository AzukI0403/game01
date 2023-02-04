#pragma once

class Player;
class Enemy01;
class Game;
class Result;
class Game2;
class Numberhouse;
class Boss01;
class Boss02;
class Boss03;

class Dangan :public IGameObject
{
public:
	Dangan();
		~Dangan();

	bool Start();
	void Update();
	void collision();
	void Render(RenderContext& rc);
	


	Player* player;
	Enemy01* enemy01;
	Game* game;
	Result* result;
	Game2* game2;
	Numberhouse* numberhouse;
	Boss01* boss01;
	Boss02* boss02;
	Boss03* boss03;

	ModelRender modelRender;
	Vector3 position;
	Vector3 moveSpeed;
	Quaternion rot={0.0f,90.0f,0.0f,1.0f};
	Quaternion rotation;  //クォータニオン。
	CollisionObject* colli;  //コリジョン。

	int stagenumber;
	
};