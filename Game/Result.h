#pragma once

class Game;
class Gamestart;
class Player;
class GameUI;
class Game2;

class Result:public IGameObject
{
public:
	Result();
	~Result();

	bool Start();
	void Update();

	void Timeresult();
	void TimeScore1_1();
	void TimeScore1_2();
	void TimeScore1_3();


	void Downenemyresult();
	void Getcoinresult();
	void Total();
	void Rank();

	void Gotitle();
	void Render(RenderContext& rc);

	Game* game;
	Gamestart* gamestart;
	Player* player;
	GameUI* gameUI;
	Game2* game2;

	SpriteRender spriteRender;


	Vector3 position_t;
	Vector3 position_de;
	Vector3 position_gc;
	Vector3 position_rank;

	//�^�C���X�R�A�̕\���B
	FontRender fontRender_time;
	FontRender fontRender_tscore;
	//�|�����G�̃X�R�A�̕\���B
	FontRender fontRender_downenemy;
	FontRender fontRender_descore;
	//��ɓ��ꂽ�R�C���̃X�R�A�̕\���B
	FontRender fontRender_getcoin;
	FontRender fontRender_gcscore;
	FontRender fontRender_coin;
	//�g�[�^���X�R�A�̕\���B
	FontRender fontRender_total;
	FontRender fontRender_totalscore;
	//�����N�̕\���B
	FontRender fontRender_rank;

	SpriteRender spriteRender_c;
	SpriteRender spriteRender_b;
	SpriteRender spriteRender_a;
	SpriteRender spriteRender_s;
	SpriteRender spriteRender_u;

	SoundSource* SCORE;//�̉�
	SoundSource* ScoreRank;//�̉�

	int GetCoin;
	int CoinScore;
	int DownEnemy;
	int DownEnemyScore=0;
	int count=0;
	int ttt;
	int Maxtime = 120;
	int keikatime;
	int keikatimeScore = 0;
	int Time;
	int total=0;

	int rank;
	int rank_1 = 0;
	int rank_2 = 0;
	int rank_3 = 0;

	int hyouzitime = 320;
	//0�ɂȂ�����X�^�[�g��ʂɖ߂��B
	int rock=1;

	int rank2;
	int stagenumber=0;

};

