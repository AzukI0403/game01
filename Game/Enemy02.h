#pragma once
#include "sound/SoundSource.h"

class Player;
class Dangan;
class Game;
class Result;
class Tama;
class Tama_tuibi;
class Game2;
class Game3;
class Numberhouse;
class Baria;

class Enemy02:public IGameObject
{
public:
	Enemy02();
	~Enemy02();

	bool Start();
	void Update();
	void Move();
	void Move2();
	void Rotation();
	void Attack();
	//�e�ۂƂ̓����蔻��B	
	void Collision();
	void Render(RenderContext& rc);
	void Dead();
	
	Player* player;
	Dangan* dangan;
	Game* game;
	Result* result;
	Tama* tama;
	Tama_tuibi* tama_tuibi;
	Game2* game2;
	Game3* game3;
	Numberhouse* numberhouse;
	Baria* baria;

	ModelRender modelRender;
	ModelRender modelRender_eye;
	ModelRender modelRender_up;
	ModelRender modelRender_down;


	Vector3 position;
	Vector3 position_up;
	Vector3 position_down;
	Vector3 firstPosition;
	Vector3 firstPosition_up;
	Vector3 firstPosition_down;

	Quaternion rotation;
	Vector3 moveSpeed;
	
	Vector3	forward = Vector3::AxisZ;//�G�l�~�[�̐��ʃx�N�g���B
	//CharacterController characterController;  //�L�����N�^�[�R���g���[���[�B
	CollisionObject* colli;  //�R���W�����B

	SoundSource* death;//���ꂽ�Ƃ��̉�

	int enemyState = 0;
	int moveCount;
	int timeCount = 0;
	int tamaCount = 0;
	int tamatime = 0;
	bool collision = false;
	//enemy02��game2��change=1�̂Ƃ���ʓ��ɂ��鎞�ԁB
	int timer = 500;

	int upstate=0;
	//��~����B
	int stopstate;
	//�U������B
	int attackstate;
	//�h�䔻��B
	int gardstate=0;
	int opentimer=100;

	int change=0;
	int tamachange = 0;
	int stagenumber;
};

