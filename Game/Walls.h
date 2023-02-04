#pragma once

class Game;
class Game2;
class Game3;
class Game_final;

class Walls:public IGameObject
{
public:
	Walls();
	~Walls();

	bool Start();
	void Update();
	void Move();
	void Render(RenderContext& rc);

	Game* game;
	Game2* game2;
	Game3* game3;
	Game_final* game_final;

	ModelRender modelRender;
	Vector3 position;
	Vector3 moveSpeed;
	Vector3 firstPosition;
};

