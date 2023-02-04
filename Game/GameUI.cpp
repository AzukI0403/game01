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
	//ゲーム1_1のインスタンスを探す。
	game = FindGO<Game>("game");
	coin = FindGO<Coin>("coin");
	result = FindGO<Result>("result");
	
	//warningの音を読み込む。
	g_soundEngine->ResistWaveFileBank(0, "Assets/sound/warning.wav");
	//gameclearの音を読み込む。
	g_soundEngine->ResistWaveFileBank(17, "Assets/sound/gameclear.wav");
	//読み込む。
	
	//表示する座標を設定する。
	fontRender_time.SetPosition({ -84.0f,540.0f,0.0f/*-42.0f,540.0f,0.0f*/ });
	//y=-400
	fontRender_coin.SetPosition({ -50.0f,-475.0f,0.0f });
	//y=-410
	fontRender_x.SetPosition({ -77.0f,-485.0f,0.0f });
	//表示する色を設定する。
	
	fontRender_coin.SetColor(g_vec4White);
	fontRender_x.SetColor(g_vec4White);
	//文字の大きさを設定する。
	fontRender_time.SetScale(2.0f);
	fontRender_coin.SetScale(1.5f);
	fontRender_x.SetScale(1.0f);

	//HPバーの設定。
	spriteRender_bar.Init("Assets/sprite/hp.DDS",800.0f,20.0f);
	spriteRender_under.Init("Assets/sprite/hp_ura.DDS", 800.0f, 20.0f);
	spriteRender_bar2.Init("Assets/sprite/hpbar.DDS", 1920.0f, 100.0f);

	//HPバー(ボス)の設定。
	spriteRender_bar_boss.Init("Assets/sprite/hp_boss.DDS", 600.0f, 40.0f);
	spriteRender_under_boss.Init("Assets/sprite/hp_ura.DDS", 600.0f, 40.0f);
	spriteRender_bar2_boss.Init("Assets/sprite/hpbar_boss.DDS", 1920.0f, 100.0f);

	//バリアバーの設定。
	spriteRender_bariabar.Init("Assets/sprite/baria_bar.DDS", 800.0f, 20.0f);
	spriteRender_bariaunder.Init("Assets/sprite/baria_underbar.DDS", 800.0f, 20.0f);

	//timebarの設定。
	spriteRender_timebar.Init("Assets/sprite/timebar.DDS", 1920.0f,190.0f);

	//コインの画像の設定。
	spriteRender_coin.Init("Assets/sprite/coingazou.DDS", 60.0f, 60.0f);

	//missonstartの画像の設定。
	spriteRender_missonstart.Init("Assets/sprite/missonstart.DDS", 1000.0f, 300.0f);
	//missonstart_barkの画像の設定。
	spriteRender_missonstart_back.Init("Assets/sprite/missonstart_back.DDS", 1920.0f, 400.0f);

	//missioncompleteの画像の設定。
	spriteRender_missoncomplete.Init("Assets/sprite/missoncomplete02.DDS", 1300.0f, 310.0f);

	//missioncomplete_backの画像の設定。
	spriteRender_missoncomplete_back.Init("Assets/sprite/missoncomplete_back.DDS", 1920.0f, 1080.0f);

	//warningバーの設定。
	spriteRender_warning.Init("Assets/sprite/warning.DDS", 1000.0f, 500.0f);
	spriteRender_warning_ura.Init("Assets/sprite/warning_ura.DDS", 1920.0f, 200.0f);
	spriteRender_warning_bar.Init("Assets/sprite/warning_bar.DDS", 3000.0f, 600.0f);

	//HPバーの座標。y=-420,y=-445
	spriteRender_bar.SetPosition({ -960.0f, -520.0f, 0.0f });
	spriteRender_under.SetPosition({-560.0f,-520.0f,0.0f});
	spriteRender_bar2.SetPosition({ 0.0f, -495.0f, 0.0f });

	//HPバー(ボス)の座標。y=-420,y=-445
	spriteRender_bar_boss.SetPosition({ 250.0f, -500.0f, 0.0f });
	spriteRender_under_boss.SetPosition({ 550.0f,-500.0f,0.0f });
	spriteRender_bar2_boss.SetPosition({ 0.0f, -495.0f, 0.0f });

	//バリアバーの設定。y=-420
	spriteRender_bariabar.SetPosition({ -960.0f, -495.0f, 0.0f });
	spriteRender_bariaunder.SetPosition({ -560.0f,-495.0f,0.0f });

	//timebarの座標。
	spriteRender_timebar.SetPosition({ 0.0f,500.0f, 0.0f });

	//コインの座標。y=-430
	spriteRender_coin.SetPosition({ -100.0f,-505.0f, 0.0f });

	//missonstartの座標。
	spriteRender_missonstart.SetPosition({ -1500.0f,0.0f, 0.0f });
	//-1400
	position_ms.x = -200;
	//missonstart_backの座標。
	spriteRender_missonstart_back.SetPosition({ 0.0f,0.0f, 0.0f });

	//missoncompleteの座標。
	spriteRender_missoncomplete.SetPosition({ 0.0f,0.0f, 0.0f });
	position_mc.x = -1400;

	//missoncomplete_backの座標。
	spriteRender_missoncomplete_back.SetPosition({ 0.0f,0.0f, 0.0f });

	//warningの座標。
	spriteRender_warning.SetPosition({ 0.0f,0.0f,0.0f });
	//warning_uraの座標。
	spriteRender_warning_ura.SetPosition({ 0.0f,0.0f,0.0f });
	//warning_barの座標。
	spriteRender_warning_bar.SetPosition({ 0.0f,0.0f,0.0f });
	positon_war.x = -100;

	//HPバーのピボット
	spriteRender_bar.SetPivot({ 0.0f, 0.5f });
	spriteRender_bar.SetScale({ 1.0f,1.0f,1.0f });

	//HPバー(ボス)のピボット
	spriteRender_bar_boss.SetPivot({ 0.0f, 0.5f });
	spriteRender_bar_boss.SetScale({ 1.0f,1.0f,1.0f });

	//バリアバーのピボット
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
	

	//game->GameOverFlagがtrueなら抜け出す。
	if (game->GameOverFlag == true) {
		return;
	}
	//gameがboss01を生成したら。
	if (game->boss == 1)
	{
		//この処理は1度だけ。
		if (bossdiscover == 0)
		{
			//boss01のインスタンスを探す。
			boss01 = FindGO<Boss01>("boss01");
			bossdiscover = 1;
		}
	}

	//missonstartを表示する時間を減らす。
	if (ms_btime >= 0)
	{
		ms_btime--;
	}
	
	//プレイヤーのHPが51%以上なら表示する色を緑色にする。
	if (player->playerHp > 50)
	{
		//上のバー
		spriteRender_timebar.SetMulColor(color_green);
		//下のバー
		spriteRender_bar2.SetMulColor(color_green);
		//HPバー
		spriteRender_bar.SetMulColor(color_green);
	}

	//プレイヤーのHPが50%以下なら表示する色を黄色にする。
	if (player->playerHp <= 50)
	{
		//上のバー
		spriteRender_timebar.SetMulColor(color_yellow);
		//下のバー
		spriteRender_bar2.SetMulColor(color_yellow);
		//HPバー
		spriteRender_bar.SetMulColor(color_yellow);
	}

	//プレイヤーのHPが20以下なら表示する色を赤色にする。
	if (player->playerHp <= 20)
	{
		//上のバー
		spriteRender_timebar.SetMulColor(color_red);
		//下のバー
		spriteRender_bar2.SetMulColor(color_red);
		//HPバー
		spriteRender_bar.SetMulColor(color_red);
	}

	
	//missonstartの表示が消されたら。
	if (ms_btime <= 0)
	{
		//boss02が倒されていない、もしくは時間が0でない間。
		if (bossdeath == 0)
		{
			if (time > 0) {

				//経過時間のカウント。
				count -= 1;
				//countが0以下になったら
				if (count <= 0)
				{
					//timeを1増やす。(画面に表示されている。)
					time -= 1;
					count = 60;
				}
			}
				
		}
	}
	//制限時間が近づいてきたら、時間の色の表示を赤色にする。
	if(time<=50)fontRender_time.SetColor(color_red);

	//時間の桁が下がるごとに座標をずらす。
	if (time == 99)fontRender_time.SetPosition(pos_10);
	if (time == 9)fontRender_time.SetPosition(pos_1);

	//HPバーの減っていく割合。
	float X_Size = (float)player->playerHp / (float)player->maxhp;
	spriteRender_bar.SetScale({ X_Size,1.0f,1.0f });
	
	//boss01のインスタンスを見つけたかつboss01が倒されていないなら。
	if (bossdiscover ==1&& bossdeath == 0)
	{
			//HPバーの減っていく割合。
			float X_BossSize = (float)boss01->bosshp / (float)boss01->maxbosshp;
			spriteRender_bar_boss.SetScale({ X_BossSize,1.0f,1.0f });
	}
	

	//バリアバーの減っていく割合。
	float X_BariaSize = (float)player->bariapoint / (float)player->maxbariapoint;
	spriteRender_bariabar.SetScale({ X_BariaSize,1.0f,1.0f });
	
	
	Time();

	Coincount();
	//missonstartの表示と処理。
	if (ms_btime <= 140 && ms_btime >= 20)
	{
		MissonStart();
	}
	//missoncompleteの表示と処理。
	if (bossdeath >= 1&& mc_btime<=300)
	{
		MissonComplete();
	}
	//ボスが倒されたとき
	if (bossdeath >= 1)
	{
		mc_btime--;
	}
	//warningの表示と処理。
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

//残り時間の表示。
void GameUI::Time()
{
	TIME = time;
	wchar_t time[255];
	swprintf_s(time, 255, L"%d", TIME);
	fontRender_time.SetText(time);
	

}
//コインのカウントの表示。
void GameUI::Coincount()
{
	COIN = player->getcount;
	wchar_t getcount[255];
	swprintf_s(getcount, 255, L"%d", COIN);
	fontRender_coin.SetText(getcount);
	fontRender_x.SetText(L"X");

}
//missonstartのスプライトを動かす処理。
void GameUI::MissonStart()
{
	position_ms.x += 15.0f;

	spriteRender_missonstart.SetPosition(position_ms);
}

//missoncompleteのスプライトを動かす処理。
void GameUI::MissonComplete()
{
	if (completestate == 0)
	{
		//クリアしたときの音を再生する。
		complete = NewGO<SoundSource>(17);
		complete->Init(17);
		complete->SetVolume(1.2f);
		complete->Play(false);
		completestate = 1;
	}
	position_mc.x += 10.0f;

	spriteRender_missoncomplete.SetPosition(position_mc);
}

//warning_barのスプライトを動かす処理。
void GameUI::Warning()
{
	if (musicON == false)
	{
		//bossが出現するときの音を再生する。
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

//gameにtimeの値を返す。
void GameUI::SetResultDataToGame() {
	game->time_rinzi = time;
	
}

void GameUI::Render(RenderContext& rc)
{
	if (ms_btime <= 100)
	{
		//下のバー
		spriteRender_bar2.Draw(rc);
		//HPバーの裏
		spriteRender_under.Draw(rc);
		//HPバー
		spriteRender_bar.Draw(rc);
	}
	

	//boss01のインスタンスを見つけたかつboss01が倒されていないなら。
	if (bossdeath==0&&bossdiscover == 1)
	{
		spriteRender_bar2_boss.Draw(rc);
		spriteRender_under_boss.Draw(rc);
		spriteRender_bar_boss.Draw(rc);
	}
	
	if (ms_btime <= 100)
	{
		//バリア
		spriteRender_bariabar.Draw(rc);
		spriteRender_bariaunder.Draw(rc);
		//上のバー
		spriteRender_timebar.Draw(rc);
		//コイン
		spriteRender_coin.Draw(rc);
	}
	

	//missonstartを表示する時間が20以上の間表示する。
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
