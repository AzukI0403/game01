#pragma once
#include "sound/SoundSource.h"


class Player;
class Game;
class Game2;

class Coin:public IGameObject
{
public:
	Coin();
	~Coin();

	bool Start();
	void Update();

	void Render(RenderContext&rc);

	Player* player;
	Game* game;
	Game2* game2;

	SoundSource* Coinget;//�e�ۂ�ł����Ƃ��̉�

	ModelRender modelRender;
	Vector3 position;
	Quaternion rotation;  //�N�H�[�^�j�I���B
	CollisionObject* colli;  //�R���W�����B
	
	int get=0;
	bool GetFlag = false;
	int score=0;

	//int NoBGM = 0;
};

