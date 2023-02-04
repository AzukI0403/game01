#pragma once

class Player;
class Kyuen:public IGameObject
{
public:
	Kyuen();
	~Kyuen();

	bool Start();
	void Update();
	void Render(RenderContext& rc);

	Player* player;

	ModelRender modelRender;
	Vector3 position;
	Quaternion rotation;  //クォータニオン。
	CollisionObject* colli;  //コリジョン。
};

