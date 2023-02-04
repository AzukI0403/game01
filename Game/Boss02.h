#pragma once

class Player;
class Game2;
class Baria;
class Tama_tuibi;
class GameUI2;
class Numberhouse;
class Tama_big;


class Boss02:public IGameObject
{
public:
	Boss02();
	~Boss02();

	bool Start();
	void Update();
	void Move();
	void Collision_up();
	void Collision_center();
	void Collision_down();
	//�U���p�^�[��0
	void Tama();
	//�U���p�^�[��1
	void Tuibi();
	//�U���p�^�[��2
	void Totugeki();
	void Target_up();
	void Target_center();
	void Target_down();
	void Dead();
	void Render(RenderContext& rc);


	Player* player;
	Game2* game2;
	Baria* baria;
	Tama_tuibi* tama_tuibi;
	GameUI2* gameUI2;
	Numberhouse* numberhouse;
	//Tama_big* tama_big;

	Vector3 position_up;
	Vector3 position_center;
	Vector3 position_down;

	Vector3 moveSpeed_up;
	Vector3 moveSpeed_center;
	Vector3 moveSpeed_down;

	Vector3 firstPosition_up;
	Vector3 firstPosition_center;
	Vector3 firstPosition_down;

	ModelRender modelRender_up;
	ModelRender modelRender_center;
	ModelRender modelRender_down;

	CollisionObject* colli_up;  //up�̃R���W�����B
	CollisionObject* colli_center;  //center�̃R���W�����B
	CollisionObject* colli_down;  //down�̃R���W�����B

	int moveCount = 0;
	//�U���p�^�[���B
	int pattern;

	int count = 600;
	//tama_big��ł܂ł̎��ԁB
	int countdown = 10;

	int change = 0;
	//boss02��HP�B3�̋��L�B
	int maxbosshp = 100;
	int bosshp = 100;

	int muteki = 100;

	int targetstate = 0;

	int gostate = 1;
	int backstate = 0;
	int sarchtime = 100;
	int attackcounter=0;
	int stopstate_up=0;
	int stopstate_center=0;
	int stopstate_down=0;

	int totugekicount=0;

	int attackcomplete = 0;

	int attack=0;
	int oldattack=10;
};

