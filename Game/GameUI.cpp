#include "stdafx.h"
#include "GameUI.h"
#include "Game.h"
#include "Player.h"
#include "Gameover.h"
#include "Coin.h"
#include "Result.h"
#include "Baria.h"
#include "Boss01.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"


GameUI::GameUI()
{

}

GameUI::~GameUI()
{
	DeleteGO(warning);
	DeleteGO(complete);
}

bool GameUI::Start()
{
	player = FindGO<Player>("player");
	//�Q�[��1_1�̃C���X�^���X��T���B
	game = FindGO<Game>("game");
	coin = FindGO<Coin>("coin");
	result = FindGO<Result>("result");
	
	//warning�̉���ǂݍ��ށB
	g_soundEngine->ResistWaveFileBank(0, "Assets/sound/warning.wav");
	//gameclear�̉���ǂݍ��ށB
	g_soundEngine->ResistWaveFileBank(17, "Assets/sound/gameclear.wav");
	//�ǂݍ��ށB
	
	//�\��������W��ݒ肷��B
	fontRender_time.SetPosition({ -84.0f,540.0f,0.0f/*-42.0f,540.0f,0.0f*/ });
	//y=-400
	fontRender_coin.SetPosition({ -50.0f,-475.0f,0.0f });
	//y=-410
	fontRender_x.SetPosition({ -77.0f,-485.0f,0.0f });
	//�\������F��ݒ肷��B
	
	fontRender_coin.SetColor(g_vec4White);
	fontRender_x.SetColor(g_vec4White);
	//�����̑傫����ݒ肷��B
	fontRender_time.SetScale(2.0f);
	fontRender_coin.SetScale(1.5f);
	fontRender_x.SetScale(1.0f);

	//HP�o�[�̐ݒ�B
	spriteRender_bar.Init("Assets/sprite/hp.DDS",800.0f,20.0f);
	spriteRender_under.Init("Assets/sprite/hp_ura.DDS", 800.0f, 20.0f);
	spriteRender_bar2.Init("Assets/sprite/hpbar.DDS", 1920.0f, 100.0f);

	//HP�o�[(�{�X)�̐ݒ�B
	spriteRender_bar_boss.Init("Assets/sprite/hp_boss.DDS", 600.0f, 40.0f);
	spriteRender_under_boss.Init("Assets/sprite/hp_ura.DDS", 600.0f, 40.0f);
	spriteRender_bar2_boss.Init("Assets/sprite/hpbar_boss.DDS", 1920.0f, 100.0f);

	//�o���A�o�[�̐ݒ�B
	spriteRender_bariabar.Init("Assets/sprite/baria_bar.DDS", 800.0f, 20.0f);
	spriteRender_bariaunder.Init("Assets/sprite/baria_underbar.DDS", 800.0f, 20.0f);

	//timebar�̐ݒ�B
	spriteRender_timebar.Init("Assets/sprite/timebar.DDS", 1920.0f,190.0f);

	//�R�C���̉摜�̐ݒ�B
	spriteRender_coin.Init("Assets/sprite/coingazou.DDS", 60.0f, 60.0f);

	//missonstart�̉摜�̐ݒ�B
	spriteRender_missonstart.Init("Assets/sprite/missonstart.DDS", 1000.0f, 300.0f);
	//missonstart_bark�̉摜�̐ݒ�B
	spriteRender_missonstart_back.Init("Assets/sprite/missonstart_back.DDS", 1920.0f, 400.0f);

	//missioncomplete�̉摜�̐ݒ�B
	spriteRender_missoncomplete.Init("Assets/sprite/missoncomplete02.DDS", 1300.0f, 310.0f);

	//missioncomplete_back�̉摜�̐ݒ�B
	spriteRender_missoncomplete_back.Init("Assets/sprite/missoncomplete_back.DDS", 1920.0f, 1080.0f);

	//warning�o�[�̐ݒ�B
	spriteRender_warning.Init("Assets/sprite/warning.DDS", 1000.0f, 500.0f);
	spriteRender_warning_ura.Init("Assets/sprite/warning_ura.DDS", 1920.0f, 200.0f);
	spriteRender_warning_bar.Init("Assets/sprite/warning_bar.DDS", 3000.0f, 600.0f);

	//HP�o�[�̍��W�By=-420,y=-445
	spriteRender_bar.SetPosition({ -960.0f, -520.0f, 0.0f });
	spriteRender_under.SetPosition({-560.0f,-520.0f,0.0f});
	spriteRender_bar2.SetPosition({ 0.0f, -495.0f, 0.0f });

	//HP�o�[(�{�X)�̍��W�By=-420,y=-445
	spriteRender_bar_boss.SetPosition({ 250.0f, -500.0f, 0.0f });
	spriteRender_under_boss.SetPosition({ 550.0f,-500.0f,0.0f });
	spriteRender_bar2_boss.SetPosition({ 0.0f, -495.0f, 0.0f });

	//�o���A�o�[�̐ݒ�By=-420
	spriteRender_bariabar.SetPosition({ -960.0f, -495.0f, 0.0f });
	spriteRender_bariaunder.SetPosition({ -560.0f,-495.0f,0.0f });

	//timebar�̍��W�B
	spriteRender_timebar.SetPosition({ 0.0f,500.0f, 0.0f });

	//�R�C���̍��W�By=-430
	spriteRender_coin.SetPosition({ -100.0f,-505.0f, 0.0f });

	//missonstart�̍��W�B
	spriteRender_missonstart.SetPosition({ -1500.0f,0.0f, 0.0f });
	//-1400
	position_ms.x = -200;
	//missonstart_back�̍��W�B
	spriteRender_missonstart_back.SetPosition({ 0.0f,0.0f, 0.0f });

	//missoncomplete�̍��W�B
	spriteRender_missoncomplete.SetPosition({ 0.0f,0.0f, 0.0f });
	position_mc.x = -1400;

	//missoncomplete_back�̍��W�B
	spriteRender_missoncomplete_back.SetPosition({ 0.0f,0.0f, 0.0f });

	//warning�̍��W�B
	spriteRender_warning.SetPosition({ 0.0f,0.0f,0.0f });
	//warning_ura�̍��W�B
	spriteRender_warning_ura.SetPosition({ 0.0f,0.0f,0.0f });
	//warning_bar�̍��W�B
	spriteRender_warning_bar.SetPosition({ 0.0f,0.0f,0.0f });
	positon_war.x = -100;

	//HP�o�[�̃s�{�b�g
	spriteRender_bar.SetPivot({ 0.0f, 0.5f });
	spriteRender_bar.SetScale({ 1.0f,1.0f,1.0f });

	//HP�o�[(�{�X)�̃s�{�b�g
	spriteRender_bar_boss.SetPivot({ 0.0f, 0.5f });
	spriteRender_bar_boss.SetScale({ 1.0f,1.0f,1.0f });

	//�o���A�o�[�̃s�{�b�g
	spriteRender_bariabar.SetPivot({ 0.0f, 0.5f });
	spriteRender_bariabar.SetScale({ 1.0f,1.0f,1.0f });



	spriteRender_bar.Update();
	spriteRender_under.Update();
	spriteRender_bar2.Update();

	spriteRender_bar_boss.Update();
	spriteRender_under_boss.Update();
	spriteRender_bar2_boss.Update();

	spriteRender_bariaunder.Update();
	spriteRender_bariabar.Update();
	
	spriteRender_timebar.Update();

	spriteRender_coin.Update();

	spriteRender_missonstart.Update();
	spriteRender_missonstart_back.Update();
	spriteRender_missoncomplete.Update();
	spriteRender_missoncomplete_back.Update();

	spriteRender_warning.Update();
	spriteRender_warning_ura.Update();
	spriteRender_warning_bar.Update();

	return true;
}

void GameUI::Update()
{
	

	//game->GameOverFlag��true�Ȃ甲���o���B
	if (game->GameOverFlag == true) {
		return;
	}
	//game��boss01�𐶐�������B
	if (game->boss == 1)
	{
		//���̏�����1�x�����B
		if (bossdiscover == 0)
		{
			//boss01�̃C���X�^���X��T���B
			boss01 = FindGO<Boss01>("boss01");
			bossdiscover = 1;
		}
	}

	//missonstart��\�����鎞�Ԃ����炷�B
	if (ms_btime >= 0)
	{
		ms_btime--;
	}
	
	//�v���C���[��HP��51%�ȏ�Ȃ�\������F��ΐF�ɂ���B
	if (player->playerHp > 50)
	{
		//��̃o�[
		spriteRender_timebar.SetMulColor(color_green);
		//���̃o�[
		spriteRender_bar2.SetMulColor(color_green);
		//HP�o�[
		spriteRender_bar.SetMulColor(color_green);
	}

	//�v���C���[��HP��50%�ȉ��Ȃ�\������F�����F�ɂ���B
	if (player->playerHp <= 50)
	{
		//��̃o�[
		spriteRender_timebar.SetMulColor(color_yellow);
		//���̃o�[
		spriteRender_bar2.SetMulColor(color_yellow);
		//HP�o�[
		spriteRender_bar.SetMulColor(color_yellow);
	}

	//�v���C���[��HP��20�ȉ��Ȃ�\������F��ԐF�ɂ���B
	if (player->playerHp <= 20)
	{
		//��̃o�[
		spriteRender_timebar.SetMulColor(color_red);
		//���̃o�[
		spriteRender_bar2.SetMulColor(color_red);
		//HP�o�[
		spriteRender_bar.SetMulColor(color_red);
	}

	
	//missonstart�̕\���������ꂽ��B
	if (ms_btime <= 0)
	{
		//boss02���|����Ă��Ȃ��A�������͎��Ԃ�0�łȂ��ԁB
		if (bossdeath == 0)
		{
			if (time > 0) {

				//�o�ߎ��Ԃ̃J�E���g�B
				count -= 1;
				//count��0�ȉ��ɂȂ�����
				if (count <= 0)
				{
					//time��1���₷�B(��ʂɕ\������Ă���B)
					time -= 1;
					count = 60;
				}
			}
				
		}
	}
	//�������Ԃ��߂Â��Ă�����A���Ԃ̐F�̕\����ԐF�ɂ���B
	if(time<=50)fontRender_time.SetColor(color_red);

	//���Ԃ̌��������邲�Ƃɍ��W�����炷�B
	if (time == 99)fontRender_time.SetPosition(pos_10);
	if (time == 9)fontRender_time.SetPosition(pos_1);

	//HP�o�[�̌����Ă��������B
	float X_Size = (float)player->playerHp / (float)player->maxhp;
	spriteRender_bar.SetScale({ X_Size,1.0f,1.0f });
	
	//boss01�̃C���X�^���X������������boss01���|����Ă��Ȃ��Ȃ�B
	if (bossdiscover ==1&& bossdeath == 0)
	{
			//HP�o�[�̌����Ă��������B
			float X_BossSize = (float)boss01->bosshp / (float)boss01->maxbosshp;
			spriteRender_bar_boss.SetScale({ X_BossSize,1.0f,1.0f });
	}
	

	//�o���A�o�[�̌����Ă��������B
	float X_BariaSize = (float)player->bariapoint / (float)player->maxbariapoint;
	spriteRender_bariabar.SetScale({ X_BariaSize,1.0f,1.0f });
	
	
	Time();

	Coincount();
	//missonstart�̕\���Ə����B
	if (ms_btime <= 140 && ms_btime >= 20)
	{
		MissonStart();
	}
	//missoncomplete�̕\���Ə����B
	if (bossdeath >= 1&& mc_btime<=300)
	{
		MissonComplete();
	}
	//�{�X���|���ꂽ�Ƃ�
	if (bossdeath >= 1)
	{
		mc_btime--;
	}
	//warning�̕\���Ə����B
	//time >= 40 && time <= 45
	if (time <= 160 && time >= 155)
	{
		warningstate = 1;
		Warning();
	}
	
	spriteRender_bar.Update();
	spriteRender_bar_boss.Update();
	spriteRender_bariabar.Update();
	spriteRender_missonstart.Update();
	spriteRender_missoncomplete.Update();
	spriteRender_warning_bar.Update();
}

//�c�莞�Ԃ̕\���B
void GameUI::Time()
{
	TIME = time;
	wchar_t time[255];
	swprintf_s(time, 255, L"%d", TIME);
	fontRender_time.SetText(time);
	

}
//�R�C���̃J�E���g�̕\���B
void GameUI::Coincount()
{
	COIN = player->getcount;
	wchar_t getcount[255];
	swprintf_s(getcount, 255, L"%d", COIN);
	fontRender_coin.SetText(getcount);
	fontRender_x.SetText(L"X");

}
//missonstart�̃X�v���C�g�𓮂��������B
void GameUI::MissonStart()
{
	position_ms.x += 15.0f;

	spriteRender_missonstart.SetPosition(position_ms);
}

//missoncomplete�̃X�v���C�g�𓮂��������B
void GameUI::MissonComplete()
{
	if (completestate == 0)
	{
		//�N���A�����Ƃ��̉����Đ�����B
		complete = NewGO<SoundSource>(17);
		complete->Init(17);
		complete->SetVolume(1.2f);
		complete->Play(false);
		completestate = 1;
	}
	position_mc.x += 10.0f;

	spriteRender_missoncomplete.SetPosition(position_mc);
}

//warning_bar�̃X�v���C�g�𓮂��������B
void GameUI::Warning()
{
	if (musicON == false)
	{
		//boss���o������Ƃ��̉����Đ�����B
		warning = NewGO<SoundSource>(0);
		warning->Init(0);
		warning->SetVolume(0.5f);
		warning->Play(false);
		musicON = true;
	}
	

	positon_war.x += 2.0f;

	if (time <= 155)
	{
		warningstate = 0;
	}

	spriteRender_warning_bar.SetPosition(positon_war);
}

//game��time�̒l��Ԃ��B
void GameUI::SetResultDataToGame() {
	game->time_rinzi = time;
	
}

void GameUI::Render(RenderContext& rc)
{
	if (ms_btime <= 100)
	{
		//���̃o�[
		spriteRender_bar2.Draw(rc);
		//HP�o�[�̗�
		spriteRender_under.Draw(rc);
		//HP�o�[
		spriteRender_bar.Draw(rc);
	}
	

	//boss01�̃C���X�^���X������������boss01���|����Ă��Ȃ��Ȃ�B
	if (bossdeath==0&&bossdiscover == 1)
	{
		spriteRender_bar2_boss.Draw(rc);
		spriteRender_under_boss.Draw(rc);
		spriteRender_bar_boss.Draw(rc);
	}
	
	if (ms_btime <= 100)
	{
		//�o���A
		spriteRender_bariabar.Draw(rc);
		spriteRender_bariaunder.Draw(rc);
		//��̃o�[
		spriteRender_timebar.Draw(rc);
		//�R�C��
		spriteRender_coin.Draw(rc);
	}
	

	//missonstart��\�����鎞�Ԃ�20�ȏ�̊ԕ\������B
	if (ms_btime <= 140 && ms_btime >= 20)
	{
		spriteRender_missonstart_back.Draw(rc);
		spriteRender_missonstart.Draw(rc);
	}

	//missoncomplete
	if (bossdeath>=1 && mc_btime <= 300)
	{
		spriteRender_missoncomplete_back.Draw(rc);
		spriteRender_missonstart_back.Draw(rc);
		spriteRender_missoncomplete.Draw(rc);
	}

	if (ms_btime <= 100)
	{
		fontRender_time.Draw(rc);
		fontRender_coin.Draw(rc);
		fontRender_x.Draw(rc);
	}
	

	if (warningstate==1)
	{
		spriteRender_warning.Draw(rc);
		spriteRender_warning_ura.Draw(rc);
		spriteRender_warning_bar.Draw(rc);
	}
}
