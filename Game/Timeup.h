#pragma once

class Result;

class Timeup:public IGameObject
{
public:
	Timeup();
	~Timeup();

	bool Start();
	void Update();
	void Render(RenderContext& rc);

	Result* result;
	SpriteRender spriteRender;

	int Coin_rinzi = 0;
	int enemy_rinzi = 0;
	int Timeup_rinzi = 0;

	int stagenumber;
};

