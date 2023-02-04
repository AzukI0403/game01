#pragma once

class Scoreboard;

class Box1_2 :public IGameObject
{
public:
	Box1_2();
	~Box1_2();

	bool Start();
	void Update();
	void Render(RenderContext& rc);

	Scoreboard* scoreboard;

	Vector3 firstposition;
	Vector3 position;
	ModelRender modelRender;
	CollisionObject* colli;
	Quaternion rot;

	int rank = 0;
	int rank_2=0;

	int oldrank = 0;
};

