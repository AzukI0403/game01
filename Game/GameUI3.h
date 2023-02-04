#pragma once
class Player;
class Coin;
class Result;
class Baria;
class Boss03;
class Game3;
class Game_final;

class GameUI3 :public IGameObject
{
public:
	GameUI3();
	~GameUI3();

	bool Start();
	void Update();
	void Time();
	void Coincount();
	void MissonStart();
	void MissonComplete();
	void SetResultDataToGame();
	void Warning();
	void Render(RenderContext& rc);


	Player* player;
	Coin* coin;
	Result* result;
	Baria* baria;
	Boss03* boss03;
	Game3* game3;
	Game_final* game_final;

	Vector3 position;
	Vector3 position_ms;
	Vector3 position_mc;

	Vector3 positon_war;

	Vector3 pos_1 = { -42.0f,540.0f,0.0f };
	//-63.0f,540.0f,0.0f
	Vector3 pos_10 = { -63.0f,540.0f,0.0f };
	//-84.0f,540.0f,0.0f
	Vector3 pos_100 = { -84.0f,540.0f,0.0f };

	//player��hp�̕\����Ԃ�����B
	Vector4 color_red = { 0.7f,0.0f,0.0f,1.0f };
	//player��hp�̕\�������F������B
	Vector4 color_yellow = { 0.7f,0.7f,0.0f,1.0f };
	//player��hp�̕\����ΐF�ɂ���B
	Vector4 color_green = { 0.0f,0.7f,0.0f,1.0f };

	SpriteRender spriteRender_under;
	SpriteRender spriteRender_bar;
	SpriteRender spriteRender_bar2;

	SpriteRender spriteRender_under_boss;
	SpriteRender spriteRender_bar_boss;
	SpriteRender spriteRender_bar2_boss;

	SpriteRender spriteRender_bariaunder;
	SpriteRender spriteRender_bariabar;

	SpriteRender spriteRender_timebar;

	SpriteRender spriteRender_coin;

	SpriteRender spriteRender_missonstart;
	SpriteRender spriteRender_missonstart_back;

	SpriteRender spriteRender_missoncomplete;
	SpriteRender spriteRender_missoncomplete_back;

	SpriteRender spriteRender_warning;
	SpriteRender spriteRender_warning_ura;
	SpriteRender spriteRender_warning_bar;

	SpriteRender spriteRender_SB;

	FontRender fontRender_time;
	FontRender fontRender_coin;
	FontRender fontRender_x;

	SoundSource* warning;//warning��\������Ƃ��̉�
	SoundSource* complete;//�N���A�̉�

	int TIME;
	//��������300�b
	int time = 300;
	int count = 60;

	int COIN;

	//missonstart��\�����鎞�ԁB
	int ms_btime = 220;
	//missoncomplete��\�����鎞��300�A70�̓{�X�������G�t�F�N�g���Đ����鎞�ԁB
	int mc_btime = 370;

	int boss=0;
	int bosstimer = 200;
	int bossdiscover = 0;
	//boss03���|���ꂽ���̔���B
	int bossdeath = 0;

	int stagenumber;
	//game_final
	int findGame_final = 0;

	int completestate = 0;
	int warningstate = 0;
	bool musicON = false;
};
