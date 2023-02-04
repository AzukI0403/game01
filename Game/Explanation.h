#pragma once
class Explanation:public IGameObject
{
public:
	Explanation();
	~Explanation();

	bool Start();
	void Update();
	void Render(RenderContext& rc);

	SpriteRender spriteRender;
	SpriteRender spriteRender_atem;

	int atemscreenON = 0;
};

