#pragma once

class Player;
class Game;
class kyuen;
class Game2;

class Masingan:public IGameObject
{
public:
	Masingan();
	~Masingan();

	bool Start();
	void Update();
	void Render(RenderContext& rc);

	Player* player;
	Game* game;
	Game2* game2;

	ModelRender modelRender;
	Quaternion rotation;  //クォータニオン。
	Vector3 position;
	Vector3 firstposition;
	
};

