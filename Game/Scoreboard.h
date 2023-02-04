#pragma once

class Box1_1;
class Box1_2;
class Box1_3;


class Scoreboard:public IGameObject
{
public:
	Scoreboard();
	~Scoreboard();

	bool Start();
	void Update();
	void Render(RenderContext& rc);

	Box1_1* box1_1;
	Box1_2* box1_2;
	Box1_3* box1_3;

	ModelRender modelRender;
	ModelRender modelRender_rank;
	ModelRender modelRender_rank_c;
	ModelRender modelRender_rank_b;
	ModelRender modelRender_rank_a;
	ModelRender modelRender_rank_s;
	ModelRender modelRender_rank_u;

	Vector3 position;
	Vector3 position_rank;

	int rank;
	int rank_1 = 0;
	int rank_2 = 0;
	int rank_3 = 0;
	int oldrank=0;
};

