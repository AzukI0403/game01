#pragma once
#include "sound/SoundSource.h"

class Enemy01;
class Enemy02;
class Repair;
class Game;
class Coin;
class Kyuen;
class Masingan;
class Tama;
class Baria;
class Tama_tuibi;
class Boss01;
class Game2;
class Boss02;
class Numberhouse;
class Game3;
class Game_final;
class Tama_big;
class Boss03;

class Player:public IGameObject
{
public:
	Player();
	~Player();

	bool Start();
	//�X�V�����B
	void Update();
	//�`�揈���B
	void Render(RenderContext& rc);
	//�ړ������B
	void Move();
	void DamageUP();
	//�񕜃A�C�e���̊Ǘ��B
	void Repairp();
	//�R�C���̊Ǘ��B
	void CoinGet();
	//�~���̊Ǘ��B
	void KyuenGet();
	//masingan�̊Ǘ��B
	void MasinganG();
	//�o���A�̊Ǘ��B
	void BariaG();
	//�X�[�p�[�o���A�̊Ǘ��B
	void SuparBariaG();
	void SetResultDataToGame();
	void SetResultDataToGame2();
	void SetResultDataToGame3();
	void SetResultDataToGame4();
	
	//�����o�ϐ��B
	Enemy01* enemy01;
	Enemy02* enemy02;
	Repair* repair;
	Game* game;
	Coin* coin;
	Kyuen* kyuen;
	Masingan* masingan;
	Baria* baria;
	Tama_tuibi* tama_tuibi;
	Boss01* boss01;
	Game2* game2;
	Boss02* boss02;
	Numberhouse* numberhouse;
	Game3* game3;
	Game_final* game_final;
	Tama_big* tama_big;
	Boss03* boss03;

	SoundSource* syageki;//�e�ۂ�ł����Ƃ��̉�

	ModelRender modelRender;	//���f�������_�\�B
	Vector3 position;   //�v���C���[�̍��W�B
	Vector3 firstposition;
	Vector3 oldposition = { 0.0f,0.0f,0.0f };
	Vector3 moveSpeed;//�ړ����x�B
	Vector3 oldmoveSpeed;
	Quaternion rotation;  //�N�H�[�^�j�I���B
	CollisionObject* colli;

	EffectEmitter* effectEmitter;
	EffectEmitter* effectEmitter_dead;
	EffectEmitter* effectEmitter_attackUP;
	EffectEmitter* effectEmitter_blueright;

	int playerState = 0;	//�v���C���[�̃X�e�[�g(���)��\���ϐ��B
	//�����B
	float kasoku =8;
	//�����������̔���B
	bool kasokustate = false;
	//�����̃N�[���^�C���B
	int cooltime=100;
	//�_���[�W�����������̖��G���ԁB
    int muteki = 0;
	//HP
	int maxhp = 100;
	int playerHp = 100;
	//1�������y�A����������Ȃ��悤�ɂ���B
	int one;
	//ripair�̐������鐔�B
	int limit=0;
	//masingan���擾������̒e�ہB
	int kankaku=1;
	//�R�C���B
	int get = 0;
	//�R�C���̃J�E���g�B
	int getcount = 0;
	//���y�A�B
	int repairget=0;
	int repairtime = 0;
	//�~���B
	int kyuenget = 0;
	//masingan�B
	int Mcount = 0;
	int MM = 0;
	//�e�ۂ̃_���[�W���グ�邩�̔���B
	bool pawerUp = false;
	//�U���͂��オ���Ă��鎞�ԁB
	int paweruptime = 10;
	int Ptimer = 0;
	//�p���[�A�b�v�̃G�t�F�N�g���Đ����Ă��邩�̔���B
	int pawerUPeffectState = 0;
	//�G��|�������B
	int downcount = 0;
	//�o���A
	int maxbariapoint = 5;
	int bariapoint=5;
	int BB=0;
	//�X�[�p�[�o���A�̃|�C���g=1
	int SBPoint = 1;
	//�X�[�p�[�o���A���g�������̔���B
	bool SuparBariaState = false;
	int SBState = 0;
	//�󂯂�_���[�W=10�B
	int damage = 10;
	//�^����_���[�W=10�B
	int attackdamage = 10;
	//�_���[�W���󂯂����ǂ����̔���B
	int damagestate = 0;
	//���f��������=true�B
	bool notdraw = false;

	//���킵�Ă���X�e�[�W�̃i���o�[�B
	//�v���C���[���|���ꂽ�Ƃ��ɒl�𑗂�X�e�[�W�̔���B
	int stagenumber=0;
	//�v���C���[���|���ꂽ�Ƃ��ɃG�t�F�N�g���Đ��������̔���B
	bool DeadEffect = false;
	int find=0;

	int SavePositionTime = 0;
	//�X�^�[�g���Ƀv���C���[���Ƃ܂��Ă��鎞�ԁB
	//1_1,1_2,1_3=220
	int Stoptime = 220;
	//���Ԑ؂�ɂȂ�����true�ɂ���B
	bool timeover = false;
};

