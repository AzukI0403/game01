#include "stdafx.h"
#include "Player.h"
#include "Game.h"
#include "Dangan.h"
#include "Tama.h"
#include "Repair.h"
#include "Coin.h"
#include "Kyuen.h"
#include "Masingan.h"
#include "Baria.h"
#include "Tama_tuibi.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
#include "Game2.h"
#include "Boss02.h"
#include "Numberhouse.h"
#include "Game3.h"
#include "Game_final.h"
#include "Tama_big.h"
#include "Boss03.h"
#include "graphics/effect/EffectEmitter.h"


Player::Player()
{

}

Player::~Player()
{
	DeleteGO(effectEmitter_attackUP);
	DeleteGO(effectEmitter_blueright);
	DeleteGO(colli);
}

bool Player::Start()
{
	//戦闘機のモデルを読み込む。
	modelRender.SetRaytracingWorld(false);
	modelRender.Init("Assets/modelData/sentouki.tkm");
	
	//エフェクトを読み込む。
	EffectEngine::GetInstance()->ResistEffect(3, u"Assets/effect/effectsprite/player_dead.efk");
	EffectEngine::GetInstance()->ResistEffect(6, u"Assets/effect/effectsprite/attackUP.efk");
	EffectEngine::GetInstance()->ResistEffect(11, u"Assets/effect/effectsprite/blueright.efk");

	//プレイヤーのインスタンスを探す。
	boss02 = FindGO<Boss02>("boss02");
	boss03 = FindGO<Boss03>("boss03");
	//ゲーム1_1のインスタンスを探す。
	game = FindGO<Game>("game");
	//ゲーム1_2のインスタンスを探す。
	game2 = FindGO<Game2>("game2");
	coin = FindGO<Coin>("coin");

	//ゲーム1_3のインスタンスを探す。
	game3 = FindGO<Game3>("game3");

	//ゲーム1_3_finalのインスタンスを探す。
	game_final = FindGO<Game_final>("game_final");

	numberhouse = FindGO<Numberhouse>("numberhouse");

	//弾丸を打つときの音を読み込む。
	g_soundEngine->ResistWaveFileBank(1, "Assets/sound/syageki.wav");

	//プレイしているステージを示す値を受け取る。
	stagenumber = numberhouse->stagenumber;

	if (stagenumber == 4)
	{
		// //コリジョンの作成。
		colli = NewGO<CollisionObject>(0);
		colli->CreateCapsule(Vector3(0.0f, 0.0f, 0.0f), Quaternion(90.0f, 0.0f, 0.0f, 90.0f), 21.0f, 180.0f);
		colli->SetIsEnableAutoDelete(false);
		colli->SetName("player");
	}
	else
	{
		//キャラコンを初期化する。
	//当たり判定。
	//コリジョンの作成。
		colli = NewGO<CollisionObject>(0);
		colli->CreateCapsule(Vector3 (0.0f,0.0f,0.0f), Quaternion (0.0f,0.0f,90.0f,90.0f), 21.0f, 180.0f);
		colli->SetIsEnableAutoDelete(false);
		colli->SetName("player");
	}

	return true;
}

void Player::Update()
{
	if (stagenumber == 4&&find==0)
	{
		//ゲーム1_3_finalのインスタンスを探す。
		game_final = FindGO<Game_final>("game_final");
		find = 1;
	}
	//プレイしているステージの制限時間に達したらGameOverFlagをtrueにする。
	
	//mistionstartの表示が終わるまで動かない。
	if (Stoptime >= 0)
	{
		Stoptime--;
	}
	//mistionstartの表示が終わったら処理を始める。
	if (Stoptime <= 0)
	{
		//無敵時間。
		muteki += 1;

		//モデルが表示されない状態なら。
		if (notdraw == true)notdraw = false;
		
		//ダメージを受けた後、無敵時間が終わったら。
		if (muteki >= 60)damagestate = 0;
		
		//クールタイムが0より大きかったらクールタイムを0まで減らす。
		if (cooltime >= 0)cooltime--;
		
		if (kasokustate == true)
		{
			if (cooltime < 90)
			{
				kasokustate = false;
				//kasokuを元の値に戻す。
				kasoku = 8;
			}
		}

		//Hpが0以下になったら。
		if (playerHp <= 0)
		{
			playerHp = 0;
			//エフェクトを再生していなかったら。
			if (DeadEffect != true)
			{
				//やられたときのエフェクトを再生する。
				effectEmitter_dead = NewGO<EffectEmitter>(3);
				effectEmitter_dead->Init(3);
				//エフェクトのサイズ。
				//game_finalのとき
				if (stagenumber == 4)effectEmitter_dead->SetScale({ 30.0f,30.0f,10.0f });
				//それ以外の時。
				else effectEmitter_dead->SetScale({ 50.0f,50.0f,10.0f });
				effectEmitter_dead->SetPosition({ position.x,position.y,-30.0f });
				effectEmitter_dead->Play();
				DeadEffect = true;
			}
			//プレイしているステージのGameOverFlagをtrueにする。
			switch (stagenumber)
			{
			case 1:
				game->GameOverFlag = true;
				break;
			case 2:
				game2->GameOverFlag = true;
				break;
			case 3:
				game3->GameOverFlag = true;
				break;
			case 4:
				game_final->GameOverFlag = true;
				break;
			}
		}
		//Hpが0以下になったら。
		if (timeover==true)
		{
			muteki = 0;
			DeadEffect = true;
			//プレイしているステージのGameOverFlagをtrueにする。
			switch (stagenumber)
			{
			case 1:
				game->GameOverFlag = true;
				break;
			case 2:
				game2->GameOverFlag = true;
				break;
			case 3:
				game3->GameOverFlag = true;
				break;
			case 4:
				game_final->GameOverFlag = true;
				break;
			}
		}

		//ダッシュ。
		//Bボタンが押されたら。
		if (g_pad[0]->IsTrigger(enButtonB))
		{
			if (cooltime <= 0)
			{
				kasokustate = true;
				cooltime = 100;
			}

		}

		//DeadEffectがfalseなら移動処理(プレイヤーが生きている間)。
		if (DeadEffect == false)Move();

		//3回回復したら処理を行わない。
		if (limit <= 3)
		{
			//回復管理。
			Repairp();
		}

		CoinGet();
		KyuenGet();
		MasinganG();
		BariaG();
		//スーパーバリア
		if (SBPoint == 1)
		{
			if (stagenumber >= 3)SuparBariaG();
		}
		if (pawerUp == true)DamageUP();

		//マシンガンをとっているとき。
		if (MM == 1)
		{
			//LB1を押したら弾丸を生成する。
			if (g_pad[0]->IsPress(enButtonLB1))
			{
				kankaku -= 1;
				if (kankaku <= 0)
				{
					//弾丸を打つときの音を再生する。
					syageki = NewGO<SoundSource>(1);
					syageki->Init(1);
					syageki->SetVolume(1.2f);
					syageki->Play(false);
					kankaku = 10;
					//game_finalのとき。
					if (stagenumber == 4)
					{
						//Z方向に向かって打つ。
						Dangan* dangan = NewGO<Dangan>(0, "dangan");
						dangan->rotation.SetRotationDegY(-90.0f);
						dangan->position = position;
						//dangan->position.z += 20;
						dangan->position.y -= 23;
					}
					//game_final以外。
					else
					{
						//X方向に向かって打つ。
						Dangan* dangan = NewGO<Dangan>(0, "dangan");
						dangan->position = position;
						//dangan->position.x += 20;
						dangan->position.y -= 23;

					}

				}

			}
		}
		else
		{
			//LB1を押したら弾丸を生成する。
			if (g_pad[0]->IsTrigger(enButtonLB1))
			{
				//弾丸を打つときの音を再生する。
				syageki = NewGO<SoundSource>(1);
				syageki->Init(1);
				syageki->SetVolume(1.2f);
				syageki->Play(false);
				//game_finalのとき。
				if (stagenumber == 4)
				{
					//Z方向に向かって打つ。
					Dangan* dangan = NewGO<Dangan>(0, "dangan");
					dangan->rotation.SetRotationDegY(-90.0f);
					dangan->position = position;
					dangan->position.y -= 23;
				}
				//game_final以外。
				else
				{
					//X方向に向かって打つ。
					Dangan* dangan = NewGO<Dangan>(0, "dangan");
					dangan->position = position;
					dangan->position.y -= 23;
				}
			}
		}
	}

	//座標を設定。
	modelRender.SetPosition(position);
	modelRender.SetRotation(rotation);
	colli->SetPosition(position);
	//絵描きさんの更新処理。
	modelRender.Update();
}

void Player::Move()
{
	//game_finalのとき。
	if (stagenumber == 4)
	{
		//移動できる範囲。
	//xが1400、-400まで。
		if (position.x >= firstposition.x + 700 || position.x <= firstposition.x - 700)
		{
			moveSpeed.x = 0.0f;
			
		}
		//yが500，-570まで。
		if (position.y >= firstposition.y + 470 || position.y <= firstposition.y - 400)
		{
			moveSpeed.y = 0.0f;
			
		}
	}
	//game,game2,game3のとき。
	else
	{
		//移動できる範囲。
	//xが1400、-400まで。
		if (position.x >= firstposition.x +1400 || position.x <= firstposition.x -400)
		{
			moveSpeed.x = 0.0f;
			
		}
		//yが510，-500まで。
		if (position.y >= firstposition.y + 580 || position.y <= firstposition.y - 500)
		{
			moveSpeed.y = 0.0f;
			
		}
	}

	//kasoku =8
	//moveSpeed.x = 0.0f;
	//moveSpeed.y = 0.0f;
	
	oldmoveSpeed = moveSpeed;

	//反対方向に移動した時にkasokuを0にする。
	if (moveSpeed.x > 0 && oldmoveSpeed.x < 0)
	{
		kasoku = 0.0f;
	}
	if (moveSpeed.x < 0 && oldmoveSpeed.x > 0)
	{
		kasoku = 0.0f;
	}
	if (moveSpeed.y > 0 && oldmoveSpeed.y < 0)
	{
		kasoku = 0.0f;
	}
	if (moveSpeed.y < 0 && oldmoveSpeed.y > 0)
	{
		kasoku = 0.0f;
	}

	//ダッシュしたなら。
	if (kasokustate==true)kasoku = 16;

	//移動速度。
	moveSpeed.x += g_pad[0]->GetLStickXF() * kasoku * 2.5f / 60.0f;
	moveSpeed.y += g_pad[0]->GetLStickYF() * kasoku * 2.5f / 60.0f;

	//GetLStickXFは、ゲームパッドの横方向の倒れ具合で-1.0～1.0を返してきます。
	//GetLStickYFは、ゲームパッドの縦方向の倒れ具合で-1.0～1.0を返してきます。
	//キャラクターコントローラーを使って座標を移動させる。
	//position = characterController.Execute(moveSpeed, 3.0f / 60.0f);
	//moveSpeed *= 3.0 / 60.0f;
	position +=moveSpeed;
}

//リペアの当たり判定と生成の管理。
void Player::Repairp()
{
	const auto& collisions = g_collisionObjectManager->FindCollisionObjects("repair");
	//collisionの配列をfor文で回す。
	for (auto collision : collisions)
	{
		//設定したコリジョンとキャラクターコントローラーが衝突したか判定する。
		if (collision->IsHit(colli))
		{
			repairget += 1;
		}
	}

}

//コインの処理。
void Player::CoinGet()
{
	const auto& collisions = g_collisionObjectManager->FindCollisionObjects("coin");
	//collisionの配列をfor文で回す。
	for (auto collision : collisions)
	{
		//設定したコリジョンとキャラクターコントローラーが衝突したか判定する。
		if (collision->IsHit(colli))
		{
			get++;
			//コインを手に入れたら。
			getcount+=1;
		}
	}

}

//救援の処理。
void Player::KyuenGet()
{
	const auto& collisions = g_collisionObjectManager->FindCollisionObjects("kyuen");
	//collisionの配列をfor文で回す。
	for (auto collision : collisions)
	{
		//設定したコリジョンとキャラクターコントローラーが衝突したか判定する。
		if (collision->IsHit(colli))
		{
			if (stagenumber == 4)pawerUp = true;
			else Mcount += 1;
			kyuenget += 1;
		}
	}

}
//マシンガンの生成。
void Player::MasinganG()
{
	//kyuenを取得したら。
	if (Mcount == 1)
	{
		//一度しか生成しない。
		if (MM == 0)
		{
			Masingan* masingan = NewGO<Masingan>(0, "masingan");
			masingan->position = position;
			MM++;
		}
		
	}
}
//バリアの生成。
void Player::BariaG()
{
	//バリア
	//もしYボタンが押されたら
	if (g_pad[0]->IsTrigger(enButtonY))
	{
		//maxbariapoint = 5
		if (bariapoint > 0&& BB == 0)
		{
			//１つしか生成しない。
			//バリアがなくなったらBaria.cppがBBを0にする。
				bariapoint--;
				Baria* baria = NewGO<Baria>(0, "baria");
				baria->position = position;
				baria->BariaState = true;
				BB++;
		}
	}
}
//スーパーバリアの生成。
void Player::SuparBariaG()
{
	//スーパーバリアが使われていない間エフェクトを点滅させる。
	if (SBState == 0) {
		effectEmitter_blueright = NewGO<EffectEmitter>(11);
		effectEmitter_blueright->Init(11);
		effectEmitter_blueright->SetScale({ 40.0f,40.0f,40.0f });
		effectEmitter_blueright->SetPosition(position);
		effectEmitter_blueright->Play();
		SBState = 1;
	}
	//エフェクトの再生が終わったら。
	if (effectEmitter_blueright->IsPlay() == false)
	{
		SBState = 0;
	}
	//エフェクトとプレイヤーの座標を合わせる。
	if (SBPoint == 1)effectEmitter_blueright->SetPosition(position);
		//もしXボタンが押されたら
		if (g_pad[0]->IsTrigger(enButtonX))
		{
			SuparBariaState = true;
			//maxbariapoint = 5
			if (bariapoint > 0 && BB == 0)
			{
				//１つしか生成しない。
				//バリアがなくなったらBaria.cppがBBを0にする。
				bariapoint--;
				Baria* baria = NewGO<Baria>(0, "baria");
				baria->position = position;
				baria->SuparBariaState = true;
				BB++;
				
				//ポイントを0にしてもうバリアを発動できないようにする。
				SBPoint = 0;
			}
			effectEmitter_blueright->Stop();
		}
}
//パワーアップの処理。
void Player::DamageUP()
{
	Ptimer++;
	if (Ptimer == 60)
	{
		paweruptime--;
		Ptimer = 0;
	}
	
	if (pawerUPeffectState == 0)
	{
		//パワーアップのエフェクトを再生。
		effectEmitter_attackUP = NewGO<EffectEmitter>(6);
		effectEmitter_attackUP->Init(6);
		effectEmitter_attackUP->SetScale({ 50.0f,40.0f,50.0f });
		effectEmitter_attackUP->SetPosition(position);
		effectEmitter_attackUP->Play();
		pawerUPeffectState = 1;
	}
	if (effectEmitter_attackUP->IsPlay() == false)
	{
		pawerUPeffectState = 0;
	}
	//paweruptimeが0より大きかったら。
	if (paweruptime > 0)
	{
		effectEmitter_attackUP->SetPosition(position);
		//与えるダメージを2倍にする。
		attackdamage = 20;
	}
	//paweruptimeが0より小さくなったら。
	else 
	{
		//もしエフェクトが再生中なら停止させる。
		if (effectEmitter_attackUP->IsPlay() == true)
		{
			effectEmitter_attackUP->Stop();
		}
		//この関数の処理を行わないようにする。
		pawerUp = false;
		//与えるダメージを元に戻す。
		attackdamage = 10;
	}
}

//プレイヤーが倒されたらコインの獲得数と倒した敵の数をgameのcoin_rinzi,enemy_rinziに代入する。
void Player::SetResultDataToGame() {
	game->coin_rinzi = getcount;
	game->enemy_rinzi = downcount;
	//game->GameOverFlag = true;
}
//プレイヤーが倒されたらコインの獲得数と倒した敵の数をgame2のcoin_rinzi,enemy_rinziに代入する。
void Player::SetResultDataToGame2() {
	game2->coin_rinzi = getcount;
	game2->enemy_rinzi = downcount;
	//game2->GameOverFlag = true;
}
//プレイヤーが倒されたらコインの獲得数と倒した敵の数をgame3のcoin_rinzi,enemy_rinziに代入する。
void Player::SetResultDataToGame3() {
	game3->coin_rinzi = getcount;
	game3->enemy_rinzi = downcount;
	game3->masinganGet = Mcount;
	game3->SBPoint = SBPoint;
	//game2->GameOverFlag = true;
}
//プレイヤーが倒されたらコインの獲得数と倒した敵の数をgame_finalのcoin_rinzi,enemy_rinziに代入する。
void Player::SetResultDataToGame4() {
	game_final->coin_rinzi = getcount;
	game_final->enemy_rinzi = downcount;
	//game2->GameOverFlag = true;
}

void Player::Render(RenderContext& rc)
{
	//ダメージを受けたら。
	if (damagestate == 1)
	{
		//無敵時間が60未満かつ無敵時間を10で割ってあまりが0なら。
		if (muteki < 60 && muteki % 10 == 0)
		{
			//モデルを表示しないようにする。
			notdraw = true;
		}
	}
	//notdrawがfalseのとき。
	if (notdraw == false)
	{
		//モデルを表示する。
		modelRender.Draw(rc);
	}
}