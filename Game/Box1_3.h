#pragma once

class Scoreboard;

class Box1_3 :public IGameObject
{
public:
	Box1_3();
	~Box1_3();

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
	int rank_3=0;

	int oldrank = 0;
};

