#pragma once

class Player;
class Game;
class Baria;
class Tama;
class Tama_tuibi;
class GameUI;

class Boss01:public IGameObject
{
public:
	Boss01();
	~Boss01();

	bool Start();
	void Update();
	void Move();
	void Collision();
	void Tuibi();
	void Kakusan();
	void Bite();
	void Target();
	void Damage();
	void BiteRot();
	void Dead();
	void Render(RenderContext& rc);


	Player* player;
	Game* game;
	Baria* baria;
	Tama* tama;
	Tama_tuibi* tama_tuibi;
	GameUI* gameUI;

	Vector3 moveSpeed;
	Vector3 moveSpeed_b;
	
	Vector3 position_up;
	Vector3 firstPosition_up;
	Vector3 position_down;
	Vector3 firstPosition_down;

	Vector3 effectPos;

	Vector3 pos_colli;

	Vector3 diff;

	ModelRender modelRender_up;
	ModelRender modelRender_down;

	CollisionObject* colli_up;  //�R���W�����B
	CollisionObject* colli_down;  //�R���W�����B

	Quaternion rot_up;  //��{�N�H�[�^�j�I���B
	Quaternion rot_down;  //���{�N�H�[�^�j�I���B

	Quaternion rot_up2={0.0f,0.0f,0.0f,1.0f};  //��{�N�H�[�^�j�I���B
	Quaternion rot_down2{ 0.0f,0.0f,0.0f,1.0f };  //���{�N�H�[�^�j�I���B

	int moveCount=0;

	int pattern=4;

	int count=100;

	int countdown=10;

	int change = 0;

	int maxbosshp = 100;
	int bosshp = 100;

	int muteki = 100;

	int targetstate=0;

	int totugekitime = 70;
	//�ˌ�����񐔂̃J�E���g=2�B
	int totugekicount = 0;
	int gostate = 1;
	int backstate = 0;
	int sarchtime = 90;

	//���݂��U���̃_���[�W=20�B
	int bitedamage = 20;

	int opentime = 50;
	int closetime = 0;
};

