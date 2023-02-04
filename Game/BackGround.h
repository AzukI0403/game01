#pragma once
//背景。

class Game_final;

class BackGround:public IGameObject
{
public:
	BackGround();
	~BackGround();

	//一度だけ読み込む。
	bool Start();
	void Update();
	
	//描画関数。
	void Render(RenderContext& rc);

	Game_final* game_final;

	//モデルレンダー。
	ModelRender modelRender;
	PhysicsStaticObject physicsStaticObject;

	Vector3 position;
	Vector3 firstposition;
	Quaternion rot;

};

