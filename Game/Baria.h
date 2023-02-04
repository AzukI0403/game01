#pragma once

class Player;
class Game;
class Game2;

class Baria:public IGameObject
{
public:
	Baria();
	~Baria();

	bool Start();
	void Update();
	void Render(RenderContext& rc);

	Player* player;
	Game* game;
	Game2* game2;

	ModelRender modelRender;
	Vector3 position;
	Vector3 Cposition;
	CollisionObject* colli;  //コリジョン。
	EffectEmitter* effectEmitter;

	//バリアが継続する時間=200。
	int time = 200;

	int stagenumber;

	float SuparBariaState = false;
	int SBOK = 0;
};

