#include "stdafx.h"
#include "Result.h"
#include "Game.h"
#include "Gamestart.h"
#include "Timeup.h"
#include "Player.h"
#include "Gameover.h"
#include "GameUI.h"
#include "Game2.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"

Result::Result()
{

}

Result::~Result()
{

}

bool Result::Start()
{
	//スコアを表示するときの音を読み込む。
	g_soundEngine->ResistWaveFileBank(13, "Assets/sound/score.wav");
	//ランクを表示するときの音を読み込む。
	g_soundEngine->ResistWaveFileBank(14, "Assets/sound/rank.wav");
	
	spriteRender_c.Init("Assets/sprite/rank_C.DDS", 450.0f, 450.0f);
	spriteRender_b.Init("Assets/sprite/rank_B.DDS", 450.0f, 450.0f);
	spriteRender_a.Init("Assets/sprite/rank_A.DDS", 440.0f, 440.0f);
	spriteRender_s.Init("Assets/sprite/rank_S.DDS", 450.0f, 450.0f);
	spriteRender_u.Init("Assets/sprite/rank_U.DDS", 450.0f, 450.0f);

	spriteRender_c.SetPosition({ 700.0f,-285.0f,0.0f });
	spriteRender_b.SetPosition({ 700.0f,-285.0f,0.0f });
	spriteRender_a.SetPosition({ 700.0f,-265.0f,0.0f });
	spriteRender_s.SetPosition({ 700.0f,-285.0f,0.0f });
	spriteRender_u.SetPosition({ 700.0f,-285.0f,0.0f });

	//文字の座標を設定する。
	//経過時間のスコアの座標。
	fontRender_time.SetPosition({ -850.0f,150.0f,0.0f });
	fontRender_tscore.SetPosition({ 280.0f,150.0f,0.0f });
	//敵撃破のスコアの座標。
	fontRender_downenemy.SetPosition({ -850.0f,0.0f,0.0f });
	fontRender_descore.SetPosition({ 280.0f,0.0f,0.0f });
	//獲得したコインのスコアの座標。
	fontRender_getcoin.SetPosition({ -850.0f,-150.0f,0.0f });
	fontRender_gcscore.SetPosition({ 280.0f,-150.0f,0.0f });
	fontRender_coin.SetPosition({ -280.0f,-150.0f,0.0f });
	//トータルスコアの座標。
	fontRender_total.SetPosition({ -850.0f,-300.0f,0.0f });
	fontRender_totalscore.SetPosition({ 280.0f,-300.0f,0.0f });


	//表示する色を設定する。
	//経過時間のスコアの色。
	fontRender_time.SetColor(g_vec4White);
	fontRender_tscore.SetColor(g_vec4White);
	//敵撃破のスコアの色。
	fontRender_downenemy.SetColor(g_vec4White);
	fontRender_descore.SetColor(g_vec4White);
	//獲得したコインのスコアの色。
	fontRender_getcoin.SetColor(g_vec4White);
	fontRender_gcscore.SetColor(g_vec4White);
	fontRender_coin.SetColor(g_vec4White);
	//トータルスコアの色。
	fontRender_total.SetColor(g_vec4White);
	fontRender_totalscore.SetColor(g_vec4White);

	//文字の大きさを設定する。
	//経過時間のスコアの色。
	fontRender_time.SetScale(2.0f);
	fontRender_tscore.SetScale(2.0f);
	//敵撃破のスコアの色。
	fontRender_downenemy.SetScale(2.0f);
	fontRender_descore.SetScale(2.0f);
	//獲得したコインのスコアの色。
	fontRender_getcoin.SetScale(2.0f);
	fontRender_gcscore.SetScale(2.0f);
	fontRender_coin.SetScale(2.0f);
	//トータルスコアの色。
	fontRender_total.SetScale(2.0f);
	fontRender_totalscore.SetScale(2.0f);

	//読み込む。
	spriteRender.Init("Assets/sprite/result.DDS", 1920.0f, 1080.0f);

	//ゲーム1_1のインスタンスを探す。
	game = FindGO<Game>("game");
	//ゲーム1_2のインスタンスを探す。
	game2 = FindGO<Game2>("game2");
	//ゲームUIのインスタンスを探す。
	gameUI = FindGO<GameUI>("gameUI");

	spriteRender_c.Update();
	spriteRender_b.Update();
	spriteRender_a.Update();
	spriteRender_s.Update();
	spriteRender_u.Update();

	return true;
}

void Result::Update()
{
	hyouzitime -= 1;

	Timeresult();

	Downenemyresult();

	Getcoinresult();

	Total();

	Rank();

	Gotitle();
}

//経過時間のスコアの処理。
void Result::Timeresult()
{
	//経過時間短いほうがいい
	keikatime = ttt;
	//時間を10で割る。
	keikatime = keikatime / 10;

	switch (stagenumber)
	{
	case 1:
		TimeScore1_1();
		break;
	case 2:
		TimeScore1_2();
		break;
	case 3:
		TimeScore1_3();
		break;
	default:
		break;
	}

	if (hyouzitime == 240)
	{
		SCORE = NewGO<SoundSource>(13);
		SCORE->Init(13);
		SCORE->SetVolume(1.2f);
		SCORE->Play(false);

		fontRender_time.SetText(L"経過時間スコア");
		//Time = keikatime;
		wchar_t Timescore[255];
		swprintf_s(Timescore, 255, L"%d", keikatimeScore);
		fontRender_tscore.SetText(Timescore);
	}
}
//ステージ1_1の経過時間スコアの計算。
void Result::TimeScore1_1()
{
	if (keikatime <= 10) {
		keikatime = 20 - keikatime;
		//割った数に100をかける。
		keikatimeScore = keikatime * 100;
		//スコア1000から100ずつ減らす。
		keikatimeScore = 1900 - keikatimeScore;
		if (keikatimeScore <= 0)keikatimeScore = 0;
	}
	else {
		keikatime = 20 - keikatime;
		//割った数に100をかける。
		keikatimeScore = keikatime * 100;
		//keikatimeが7のときスコアを800にする。
		if (keikatime == 8)keikatimeScore = 800;
		//keikatimeが8以上のとき、スコアを1000(max)にする。
		if (keikatime >= 9)keikatimeScore = 1000;
	}
}
//ステージ1_2の経過時間スコアの計算。
void Result::TimeScore1_2()
{
	if (keikatime <= 9) {
		keikatime = 20 - keikatime;
		//割った数に100をかける。
		keikatimeScore = keikatime * 100;
		//スコア1000から100ずつ減らす。
		keikatimeScore = 2000 - keikatimeScore;
		if (keikatimeScore <= 0)keikatimeScore = 0;
	}
	else {
		keikatime = 20 - keikatime;
		//割った数に100をかける。
		keikatimeScore = keikatime * 100;
		//keikatimeが7のときスコアを800にする。
		if (keikatime == 7)keikatimeScore = 900;
		//keikatimeが8以上のとき、スコアを1000(max)にする。
		if (keikatime >= 8)keikatimeScore = 1000;
	}
}
//ステージ1_3の経過時間スコアの計算。
void Result::TimeScore1_3()
{
	if (keikatime <= 10) {
		keikatime = 20 - keikatime;
		//割った数に100をかける。
		keikatimeScore = keikatime * 100;
		//スコア1000から100ずつ減らす。
		keikatimeScore = 1900 - keikatimeScore;
		if (keikatimeScore <= 0)keikatimeScore = 0;
	}
	else {
		//15~11
		keikatime = 30 - keikatime;
		switch (keikatime)
		{
		case 1:
			keikatimeScore = 0;
			break;
		case 2:
			keikatimeScore = 100;
			break;
		case 3:
			keikatimeScore = 100;
			break;
		case 4:
			keikatimeScore = 200;
			break;
		case 5:
			keikatimeScore = 200;
			break;
		case 6:
			keikatimeScore = 300;
			break;
		case 7:
			keikatimeScore = 300;
			break;
		case 8:
			keikatimeScore = 400;
			break;
		case 9:
			keikatimeScore = 400;
			break;
		case 10:
			keikatimeScore = 500;
			break;
		case 11:
			keikatimeScore = 600;
			break;
		case 12:
			keikatimeScore = 700;
			break;
		case 13:
			keikatimeScore = 800;
			break;
		case 14:
			keikatimeScore = 900;
			break;
		default:
			break;
		}

		//残り時間が150秒以上200秒以下のとき、スコアを1000(max)にする。
		if (keikatime >= 15&&keikatime <= 19)keikatimeScore = 1000;
	}
}

//敵撃破のスコアの処理。
void Result::Downenemyresult()
{
	//倒した敵の数×100
	DownEnemyScore = DownEnemy * 100;
	
	if (hyouzitime == 160)
	{
		SCORE = NewGO<SoundSource>(13);
		SCORE->Init(13);
		SCORE->SetVolume(1.2f);
		SCORE->Play(false);

		fontRender_downenemy.SetText(L"敵撃破スコア");
		wchar_t downcount[255];
		swprintf_s(downcount, 255, L"%d", DownEnemyScore);
		fontRender_descore.SetText(downcount);	
	}
}

//コインのスコアの処理。
void Result::Getcoinresult()
{
	switch (GetCoin)
	{
	case 1:
		CoinScore = 100;
		break;
	case 2:
		CoinScore = 200;
		break;
	case 3:
		CoinScore = 300;
		break;
	case 4:
		CoinScore = 400;
		break;
	case 5:
		CoinScore = 500;
		break;
	default:
		break;
	}
	
	if (hyouzitime == 80)
	{
		SCORE = NewGO<SoundSource>(13);
		SCORE->Init(13);
		SCORE->SetVolume(1.2f);
		SCORE->Play(false);

		fontRender_getcoin.SetText(L"コインスコア    / 5");
		wchar_t get[255];
		swprintf_s(get, 255, L"%d", GetCoin);
		fontRender_coin.SetText(get);

		wchar_t getcount[255];
		swprintf_s(getcount, 255, L"%d", CoinScore);
		fontRender_gcscore.SetText(getcount);
	}
}

void Result::Total()
{
	//経過時間と倒した敵の数とコインのスコアの合計。
	total = keikatimeScore + DownEnemyScore + CoinScore;

	if (hyouzitime == 0)
	{
		SCORE = NewGO<SoundSource>(13);
		SCORE->Init(13);
		SCORE->SetVolume(1.2f);
		SCORE->Play(false);

		fontRender_total.SetText(L"トータルスコア");
		wchar_t totals[255];
		swprintf_s(totals, 255, L"%d", total);
		fontRender_totalscore.SetText(totals);
	}
}

//プレイの評価の処理。
void Result::Rank()
{
	if (hyouzitime == -80)
	{
		ScoreRank = NewGO<SoundSource>(14);
		ScoreRank->Init(14);
		ScoreRank->SetVolume(1.2f);
		ScoreRank->Play(false);
		
		if (total <= 1500)
		{
			//グレー。
			//C
			rank = 1;
			rank2 = 1;
		}
		else if (total <= 2500)
		{
			//青。
			//B
			rank = 2;
			rank2 = 2;
		}
		else if (total <= 3000)
		{
			//赤。
			//A
			rank = 3;
			rank2 = 3;
		}
		else if (total <= 3700)
		{
			//金。
			//S
			rank = 4;
			rank2 = 4;
		}
		else if (total > 3700)
		{
			//虹。
			//U
			rank = 5;
			rank2 = 5;
		}
		rock = 0;
	}
	
}

//ゲームスタート画面に移る。
void Result::Gotitle()
{
	if (rock == 0)
	{
		if (g_pad[0]->IsTrigger(enButtonA))
		{
			//挑戦したステージのrankに代入する。
			switch (stagenumber)
			{
			case 1:
				rank_1 = rank;
				break;
			case 2:
				rank_2 = rank;
				break;
			case 3:
				rank_3 = rank;
				break;
			default:
				break;
			}
			Gamestart* gamestart=NewGO<Gamestart>(0, "gamestart");
			
			//今回のステージのスコアのランクを代入する。
			gamestart->rank_1 = rank_1;
			gamestart->rank_2 = rank_2;
			gamestart->rank_3 = rank_3;

			gamestart->stagenumber = stagenumber;
			DeleteGO(this);
		}
	}
}

void Result::Render(RenderContext& rc)
{
	spriteRender.Draw(rc);

	
	 fontRender_time.Draw(rc);
	 fontRender_tscore.Draw(rc);

	 fontRender_downenemy.Draw(rc);
	 fontRender_descore.Draw(rc);

	 fontRender_getcoin.Draw(rc);
	 fontRender_gcscore.Draw(rc);
	 fontRender_coin.Draw(rc);

	 fontRender_total.Draw(rc);
	 fontRender_totalscore.Draw(rc);

	 switch (rank2)
	 {
	 case 1:
		 spriteRender_c.Draw(rc);
		 break;
	 case 2:
		 spriteRender_b.Draw(rc);
		 break;
	 case 3:
		 spriteRender_a.Draw(rc);
		 break;
	 case 4:
		 spriteRender_s.Draw(rc);
		 break;
	 case 5:
		 spriteRender_u.Draw(rc);
		 break;
	 }
}