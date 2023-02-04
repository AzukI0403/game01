#pragma once
#include "sound/SoundSource.h"

class Player;
class Dangan;
class Game;
class Baria;
class Game2;
class Game3;

class Enemy01 :public IGameObject
{
public:
	Enemy01();
	~Enemy01();

	bool Start();
	void Update();
	void Attack();
	void Move();
	//�e�ۂƂ̓����蔻��B	
	void Collisiond();
	//�v���C���[�Ƃ̓����蔻��B
	void Collisionp();
	//�o���A�Ƃ̓����蔻��B
	void Collisionb();
	//���g�����ꂽ�Ƃ��̏����B
	void Dead();
	void Render(RenderContext& rc);


	Player* player;
	Dangan* dangan;
	Game* game;
	Baria* baria;
	Game2* game2;
	Game3* game3;

	SoundSource* kougeki;//tama��ł����Ƃ��̉�
	SoundSource* death;//���ꂽ�Ƃ��̉�

	ModelRender modelRender;
	Vector3 position;
	Quaternion rotation;
	Vector3 moveSpeed;
	Vector3 firstPosition;
	Vector3	forward = Vector3::AxisZ;//�G�l�~�[�̐��ʃx�N�g���B
	CharacterController characterController;  //�L�����N�^�[�R���g���[���[�B
	CollisionObject* colli;  //�R���W�����B
	int tamaCount=0;
	int moveCount;
	int timeCount = 0;
	int tamatime = 0;
	int go;
	

};