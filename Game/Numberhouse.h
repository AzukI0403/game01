#pragma once

class Player;
class Game;
class Game2;

class Numberhouse:public IGameObject
{
public:
	Numberhouse();
	~Numberhouse();

	bool Start();
	void Update();


	Player* player;
	Game* game;
	Game2* game2;

	//�X�e�[�W�������l�B
	int stagenumber;
};

