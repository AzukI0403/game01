#pragma once
class Sc_bg:public IGameObject
{
public:
	Sc_bg();
	~Sc_bg();

	bool Start();
	void Update();
	void Render(RenderContext& rc);

	ModelRender modelRender;
	Vector3 position;
};

