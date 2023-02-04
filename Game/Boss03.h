#pragma once

class Player;
class Game_final;
class Baria;
class Tama_tuibi;
class GameUI3;
class Numberhouse;
class Tama;
class Enemy_bomb;

class Boss03 :public IGameObject
{
public:
	Boss03();
	~Boss03();

	bool Start();
	void Update();
	void Move();
	void Collition();
	void AttackColli();
	void Kakusan();
	void Tuibi();
	void Totugeki();
	void Bomb();
	void Beam();
	void BeamColli();
	void RookON();
	void RookON_eff();
	void Damage();
	void Render(RenderContext& rc);

	Player* player;
	Game_final* game_final;
	Baria* baria;
	Tama_tuibi* tama_tuibi;
	GameUI3* gameUI3;
	Numberhouse* numberhouse;
	Tama* tama;
	Enemy_bomb* enemy_bomb;

	Vector3 position;
	Vector3 moveSpeed;
	Vector3 forward;
	Vector3 _AxiZ={0.0f,0.0f,-1.0f};
	Vector3 firstposition;
	Vector3 position_ring;
	Vector3 firstposition_ring;

	Vector3 position_light;
	Vector3 position_left;

	Vector3 position_ring_up;
	Vector3 position_ring_light;
	Vector3 position_ring_left;
	Vector3 position_ring_down;
	Vector3 beamchargePos = { 0.0f,0.0f,800.0f };
	Vector3 diff;
	Vector3 olddiff = { 0.0f,0.0f,0.0f };
	Vector3 Newdiff = { 0.0f,0.0f,0.0f };

	Quaternion rot_effect_x;
	Quaternion rot_effect_y;

	Quaternion rotation;  //�N�H�[�^�j�I���B
	Quaternion rotation_x;

	Quaternion rot_eff = { 90.0f,180.0f,180.0f,1.0f };

	Quaternion rot_ring;  //�N�H�[�^�j�I���B



	ModelRender modelRender;
	ModelRender modelRender_ring;
	ModelRender modelRender_ring_Eup;
	ModelRender modelRender_ring_Elight;
	ModelRender modelRender_ring_Eleft;
	ModelRender modelRender_ring_Edown;

	EffectEmitter* effectEmitter;

	SoundSource* charge;//�e�ۂ�ł����Ƃ��̉�
	SoundSource* beamburst;//�e�ۂ�ł����Ƃ��̉�
	CollisionObject* colli_eye;  //up�̃R���W�����B

	CollisionObject* colli_eye_light;  //up�̃R���W�����B
	CollisionObject* colli_eye_left;  //up�̃R���W�����B

	CollisionObject* colli_ring_up;
	CollisionObject* colli_ring_light;
	CollisionObject* colli_ring_left;
	CollisionObject* colli_ring_down;

	CollisionObject* colli_beam;

	int moveCount = 0;
	//�U���p�^�[���B
	int pattern;
	//�O��̍U���p�^�[���B
	int oldpattern=0;
	//�U���p�^�[�������߂�܂ł̎��ԁB
	int count = 600;
	//tama_big��ł܂ł̎��ԁB
	int countdown = 10;

	int tamacount = 0;

	int tuibitimer=40;

	int change = 0;
	//boss03�̍ő�HP�B
	int maxbosshp = 1500;
	//boss03��HP�B
	int bosshp = 1500;
	//�_���[�W���󂯂Ă���̖��G���ԁB
	int muteki = 100;

	int sarchtime = 200;

	int totugekicount = 0;
	int totugekistate = 0;
	//���E�ړ��̃X�e�[�g�B
	int RandLstate = 0;
	
	int setbomb = 0;

	int step = 0;

	float randampos_y;

	float ringeyepos_x = 420;
	float ringeyepos_y = 420;

	int posOK = 0;

	bool colliState = false;
	int beamstate=0;
	int beamOK = 0;
	int beamchargetime = 200;
	int beambursttime = 200;

	float kyori=0.0f;
	float kasokudo_y = 0.0f;
	float kasokudo_x = 0.0f;
};

