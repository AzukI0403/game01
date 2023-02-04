#pragma once

class Scoreboard;

class Box1_1:public IGameObject
{
public:
	Box1_1();
	~Box1_1();

	bool Start();
	void Update();
	void Render(RenderContext& rc);

	Scoreboard* scoreboard;

	Vector3 firstposition;
	Vector3 position;
	Vector3 position_rank;
	
	ModelRender modelRender;
	ModelRender modelRender_rank;
	CollisionObject* colli;
	Quaternion rot;

	int rank=0;
	int rank_1=0;
	
	int oldrank=0;
};

