#include "stdafx.h"
#include "Boss03.h"
#include "Game_final.h"
#include "Player.h"
#include "Baria.h"
#include "Tama.h"
#include "Tama_big.h"
#include "Tama_tuibi.h"
#include "GameUI3.h"
#include "Enemy_bomb.h"
#include "graphics/effect/EffectEmitter.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"


Boss03::Boss03()
{

}

Boss03::~Boss03()
{
	DeleteGO(colli_eye);
	DeleteGO(colli_eye_light);
	DeleteGO(colli_eye_left);

	QueryGOs<Tama>("tama", [&](Tama* tama_) {
		DeleteGO(tama_);
		return true;
		});

	QueryGOs<Tama_tuibi>("tama_tuibi", [&](Tama_tuibi* tama_tuibi_) {
		DeleteGO(tama_tuibi_);
		return true;
		});

	QueryGOs<Enemy_bomb>("enemy_bomb", [&](Enemy_bomb* enemy_bomb_) {
		DeleteGO(enemy_bomb_);
		return true;
		});
}

bool Boss03::Start()
{
	//プレイヤーのインスタンスを探す。
	player = FindGO<Player>("player");
	//ゲームのインスタンスを探す。
	game_final = FindGO<Game_final>("game_final");
	//ゲームのインスタンスを探す。
	baria = FindGO<Baria>("baria");
	//ゲームのインスタンスを探す。
	gameUI3 = FindGO<GameUI3>("gameUI3");

	//爆発するときの音を読み込む。
	g_soundEngine->ResistWaveFileBank(18, "Assets/sound/boss_dead.wav");
	//エフェクトを読み込む。
	EffectEngine::GetInstance()->ResistEffect(1, u"Assets/effect/effectsprite/beam_2.efk");
	//エフェクトを読み込む。
	EffectEngine::GetInstance()->ResistEffect(9, u"Assets/effect/effectsprite/boss_dead.efk");

	//弾丸を打つときの音を読み込む。
	g_soundEngine->ResistWaveFileBank(15, "Assets/sound/beamchage.wav");
	//弾丸を打つときの音を読み込む。
	g_soundEngine->ResistWaveFileBank(16, "Assets/sound/beam.wav");

	modelRender.SetRaytracingWorld(false);
	modelRender.Init("Assets/modelData/enemy_boss03.tkm");
	modelRender_ring.SetRaytracingWorld(false);
	modelRender_ring.Init("Assets/modelData/enemy_boss03_ring.tkm");
	//リングの上の目。
	modelRender_ring_Eup.SetRaytracingWorld(false);
	modelRender_ring_Eup.Init("Assets/modelData/ring_eye_up.tkm");
	//リングの右の目。
	modelRender_ring_Elight.SetRaytracingWorld(false);
	modelRender_ring_Elight.Init("Assets/modelData/ring_eye_light.tkm");
	//リングの左の目。
	modelRender_ring_Eleft.SetRaytracingWorld(false);
	modelRender_ring_Eleft.Init("Assets/modelData/ring_eye_left.tkm");
	//リングの下の目。
	modelRender_ring_Edown.SetRaytracingWorld(false);
	modelRender_ring_Edown.Init("Assets/modelData/ring_eye_down.tkm");

	//colli_eyeのコリジョンの作成。
	colli_eye = NewGO<CollisionObject>(0);
	colli_eye->CreateSphere(Vector3(0.0f, 0.0f, 0.0f), Quaternion::Identity, 270.0f);
	colli_eye->SetIsEnableAutoDelete(false);
	colli_eye->SetName("boss03_eye");
	colli_eye->SetPosition(position);

	position_light = { position.x + 420,position.y ,position.z };
	position_left = { position.x - 420,position.y ,position.z };
	//左右のコリジョンの作成。
	colli_eye_light = NewGO<CollisionObject>(1);
	colli_eye_light->CreateBox(Vector3 (0.0f,0.0f,0.0f), Quaternion (0.0f,0.0f,110.0f,45.0f), 
		Vector3(400.0f, 400.0f, 100.0f));
	colli_eye_light->SetIsEnableAutoDelete(false);
	colli_eye_light->SetName("boss03_eye_light");
	colli_eye_light->SetPosition(position_light);

	colli_eye_left = NewGO<CollisionObject>(2);
	colli_eye_left->CreateBox(Vector3(0.0f, 0.0f, 0.0f), Quaternion(0.0f, 0.0f, 110.0f, 45.0f),
		Vector3(400.0f, 400.0f, 100.0f));
	colli_eye_left->SetIsEnableAutoDelete(false);
	colli_eye_left->SetName("boss03_eye_left");
	colli_eye_left->SetPosition(position_left);

	position_light = position;
	position_left = position;

	position_ring_up = { position_ring.x,position_ring.y + ringeyepos_y,position_ring.z };
	position_ring_light = { position_ring.x + ringeyepos_x,position_ring.y,position_ring.z };
	position_ring_left = { position_ring.x - ringeyepos_x,position_ring.y,position_ring.z };
	position_ring_down = { position_ring.x,position_ring.y - ringeyepos_y,position_ring.z };
	return true;
}

void Boss03::Update()
{
	muteki--;
	Move();

	//1度しかこの処理を行わない。
	if (bosshp <= 500&&beamstate==0&&beamOK==0)
	{
		beamstate = 1;
		beamOK = 1;
	}

	//定位置に着いたら。
	if (position.y>=-200&&beamstate==0)
	{
		count--;
		//countが0のとき。
			//countが0になるまではパターンを保持する。
		if (count == 0)
		{
			//攻撃パターンを決める。
			pattern = rand() % 3;
			//ボムを設置していたら。
			if (setbomb == 1)
			{
				//パターンを変えるかランダムで決める。
				int changepattern = rand() % 4;
				switch (changepattern)
				{
				case 0:
					pattern = 0;
					break;
				case 1:
					pattern = 1;
					break;
				case 2:
					pattern = 3;
					break;
				case 3:
					pattern = 3;
					break;
				default:
					break;
				}
				//changepattern=0なら。		
				//if (changepattern == 0)pattern = 3;
			}
			tamacount = 0;
			countdown = 10;
			setbomb = 0;
			step = 0;
		}
		//countが-500以下になったら。
		if (count <= -500)
		{
			//パターンが3(totugeki)の場合。
			if (pattern == 3)count = 700;
			else  count = 250;   //パターンが3以外の場合。
		}

		//拡散する玉を打つ。
		if (pattern == 0)Kakusan();
		//追尾する玉を打つ。
		if (pattern == 1)Tuibi();

		//爆弾を配置する。
		if (pattern == 2)
		{
			if (setbomb == 0)Bomb();
			//ボムの配置が終わったら。
			if (setbomb == 1)count = 1;
		}
	}
	if (beamstate == 0)
	{
		//プレイヤーに突撃する。
		if (pattern == 3)
		{
			totugekistate = 1;
			Totugeki();
		}
	}
		//hpが50％を切ったとき。
		if (beamstate == 1)Beam();

	//行動パターンがビームではないかつ突撃ではないとき当たり判定の処理を行う。	
		if (beamstate == 0) {
			AttackColli();
			if (totugekistate == 0) {
				Collition();
			}
		}

	//本体
	modelRender.SetPosition(position);
	modelRender.SetRotation(rotation);
	//リング
	modelRender_ring.SetPosition(position_ring);
	modelRender_ring.SetRotation(rot_ring);
	//リングの目
	modelRender_ring_Eup.SetPosition(position_ring);
	modelRender_ring_Elight.SetPosition(position_ring);
	modelRender_ring_Eleft.SetPosition(position_ring);
	modelRender_ring_Edown.SetPosition(position_ring);

	modelRender_ring_Eup.SetRotation(rot_ring);
	modelRender_ring_Elight.SetRotation(rot_ring);
	modelRender_ring_Eleft.SetRotation(rot_ring);
	modelRender_ring_Edown.SetRotation(rot_ring);

	//本体
	colli_eye->SetPosition(position);
	//回りのとげ
	colli_eye_light->SetPosition(position_light);
	colli_eye_left->SetPosition(position_left);
	
	modelRender.Update();
	modelRender_ring.Update();
	modelRender_ring_Eup.Update();
	modelRender_ring_Elight.Update();
	modelRender_ring_Eleft.Update();
	modelRender_ring_Edown.Update();
}

void Boss03::Move()
{
	//本体の移動。
	if (pattern != 3)
	{
		rotation.SetRotationDegY(360.0f);
		//position.yが0より小さいなら。
		if (position.y <= 0.0f)position.y += 10.0f;
	}

	//本体の横移動。
	if (pattern != 3&&beamstate==0)
	{
		if (position.y >= 0.0f)
		{
			//右に移動する。
			if (RandLstate == 0)position.x += 3.0f;
			//左に移動する。
			if (RandLstate == 1)position.x -= 3.0f;

			if (position.x >= 300)RandLstate = 1;
			if (position.x <= -300)RandLstate = 0;
		}
	}

	//リングの移動。
	if (position_ring.y != 0.0f)position_ring.y += 10.0f;

	position_light = { position.x+420,position.y ,position.z };
	position_left = { position.x-420,position.y ,position.z };

	position_ring_up = { position_ring.x,position_ring.y+ ringeyepos_y,position_ring.z };
	position_ring_light = { position_ring.x+ ringeyepos_x,position_ring.y,position_ring.z };
	position_ring_left = { position_ring.x- ringeyepos_x,position_ring.y,position_ring.z };
	position_ring_down = { position_ring.x,position_ring.y - ringeyepos_y,position_ring.z };
}

void Boss03::Collition()
{
	//danganのコリジョンを取得する。
	const auto& collisions = g_collisionObjectManager->FindCollisionObjects("dangan");
	//collisionの配列をfor文で回す。
	for (auto collision : collisions)
	{
		//設定したコリジョンとキャラクターコントローラーが衝突したか判定する。
		if (collision->IsHit(colli_eye))
		{
			//mutekiが0以下になったら。
			if (muteki <= 0)
			{
				//ボスのhpを10減らす。
				bosshp -= player->attackdamage;
				muteki = 30;
			}
			//ボスのHPが0になったら。
			if (bosshp <= 0)
			{
				//やられたときの音の再生。
				SoundSource* dead = NewGO<SoundSource>(18);
				dead->Init(18);
				dead->SetVolume(1.2f);
				dead->Play(false);
				//爆発エフェクトの再生。
				EffectEmitter* effectEmitter_d = NewGO<EffectEmitter>(9);
				effectEmitter_d->Init(9);
				effectEmitter_d->SetScale({ 7.0f,7.0f,0.0f });
				effectEmitter_d->SetPosition(position);
				effectEmitter_d->Play();
				//敵を倒した数を増やす。
				player->downcount += 1;
				gameUI3->bossdeath = 1;
				//自身を破壊する。
				DeleteGO(this);
			}
		}
	}
}
//攻撃するときの当たり判定の処理。
void Boss03::AttackColli()
{
	//プレイヤーに対する当たり判定の処理。
	//プレイヤーがスーパーバリアを使っていなかったら。
	if (player->SuparBariaState == false) {
		//playerのコリジョンを取得する。
		const auto& collisions_eye = g_collisionObjectManager->FindCollisionObjects("player");
		//collisionの配列をfor文で回す。
		for (auto collision : collisions_eye)
		{
			//設定したコリジョンが衝突したか判定する。
			if (collision->IsHit(colli_eye))Damage();
		}
		//playerのコリジョンを取得する。
		const auto& collisions_light = g_collisionObjectManager->FindCollisionObjects("player");
		//collisionの配列をfor文で回す。
		for (auto collision : collisions_light)
		{
			//設定したコリジョンが衝突したか判定する。
			if (collision->IsHit(colli_eye_light))Damage();
		}
		//playerのコリジョンを取得する。
		const auto& collisions_left = g_collisionObjectManager->FindCollisionObjects("player");
		//collisionの配列をfor文で回す。
		for (auto collision : collisions_left)
		{
			//設定したコリジョンが衝突したか判定する。
			if (collision->IsHit(colli_eye_left))Damage();
		}
	}
}
//ビームの当たり判定の処理。
void Boss03::BeamColli()
{
	//playerのコリジョンを取得する。
	const auto& collisions_beam = g_collisionObjectManager->FindCollisionObjects("player");
	//collisionの配列をfor文で回す。
	for (auto collision : collisions_beam)
	{
		//設定したコリジョンが衝突したか判定する。
		if (collision->IsHit(colli_beam))Damage();
	}
}

void Boss03::Kakusan()
{
	countdown--;
	//rand() % 1401 - 700;
	//90秒ごとに生成する。
	if (countdown <= 0)
	{
		if (tamacount <= 10)
		{
			Tama* tama01 = NewGO<Tama>(0, "tama");
			//tamaの飛ばし方を変える。
			tama01->change = 1;
			tama01->position = position;
			tama01->firstposition = tama01->position;
			tama01->ramdom_x = rand() % 501 - 250;
			tama01->ramdom_y = rand() % 501 - 250;
			tama01->randomposition = { tama01->ramdom_x,tama01->ramdom_y,0.0f };

			tamacount++;
			countdown = 5;
		}
	}
	if (tamacount > 10)
	{
		tamacount = 0;
		countdown = 150;
	}
	
}

void Boss03::Tuibi()
{
	countdown--;
	//90秒ごとに生成する。
	if (countdown <= 0)
	{
		tuibitimer--;
		if (tuibitimer <= 0&&tamacount<=5)
		{
			//centerから追尾する玉を打つ。
			Tama_tuibi* tama_tuibi = NewGO<Tama_tuibi>(0, "tama_tuibi");
			tama_tuibi->position = position;
			tama_tuibi->change = 1;
			tamacount++;
			tuibitimer = 60;
		}

		if (tamacount > 5)
		{
			countdown = 70;
			tamacount = 0;
		}
	}
}

void Boss03::Totugeki()
{
	switch (step)
	{
		//画面外に移動させる。
	case 0:
		position.x += 15.0f;
		if (position.x >= 2500.0f)step = 1;
		break;
		//回転させてZ座標をプレイヤーのZ座標と合わせる。
	case 1:
		rotation.SetRotationDegX(90);
		//横切る座標をランダムに2つから選ぶ。
		randampos_y = rand() % 2;
		if (randampos_y == 0)randampos_y = 300;
		else randampos_y = -200;

		position = {2500.0f,randampos_y,0.0f};
		step = 2;
		break;
		//画面を横切る。
	case 2:
		position.x -= 13.0f;
		rotation.AddRotationDegZ(6.0f);
		if (position.x <= -2500.0f)
		{
			step = 3;
		}
		break;
		//
	case 3:
		//もう一度横切る座標をランダムに2つから選ぶ。
		randampos_y = rand() % 2;

		if (randampos_y == 0)randampos_y = 300;
		else randampos_y = -200;

		position = { -2500.0f,randampos_y,0.0f };
		step = 4;
		break;
		//画面を横切る。
	case 4:
		position.x += 13.0f;
		rotation.AddRotationDegZ(-6.0f);
		if (position.x >= 2500.0f)step = 5;
		break;
		//回転して元のZ座標に戻る。
	case 5:
		rotation.SetRotationDegX(180.0f);
		rotation.SetRotationDegY(360.0f);
		position = { 1500.0f,0.0f,1200.0f };
		step = 6;
		break;
		//元の位置に戻る。
	case 6:
		position.x -= 10.0f;
		if (position.x <= 0)step = 7;
		break;
	case 7:
		count = 1;
		totugekistate = 0;
		break;
	default:
		break;
	}
}

void Boss03::Bomb()
{
	countdown--;
	//rand() % 1401 - 700;
	//90秒ごとに生成する。
	if (countdown <= 0)
	{
			Enemy_bomb* enemy_bomb01 = NewGO<Enemy_bomb>(0, "enemy_bomb");
			enemy_bomb01->position = position;
			//enemy_bomb01->firstposition = tama01->position;
			enemy_bomb01->ramdom_x = rand() % 1201 - 600;
			enemy_bomb01->ramdom_y = rand() % 801 - 400;
			enemy_bomb01->randomposition = { enemy_bomb01->ramdom_x,enemy_bomb01->ramdom_y,0.0f };
			tamacount++;
			countdown = 15;
	}
	//ボスのHPが30％以上なら。
	if (bosshp > 500)
	{
		//ボム7個配置。
		if (tamacount >= 10)
		{
			countdown = 150;
			setbomb = 1;
		}
	}
	//50％以下なら。
	else
	{
		//ボム10個配置。
		if (tamacount >= 22)
		{
			countdown = 150;
			setbomb = 1;
		}
	}
}

void Boss03::Beam()
{
	//行動に移すまでの時間
	if (sarchtime >= 0)	sarchtime--;
	
	if (sarchtime <= 0)
	{
		switch (step)
		{
		case 0:
			//リングを180°回転させる。
			rot_ring.SetRotationDegY(180);
			//本体より前に出現させる。
			position_ring = { 0.0f, 0.0f,800.0f };
			//リングの目のコリジョンをリングに合わせる。
			ringeyepos_x = 470;
			ringeyepos_y = 470;
			//本体のX座標が0.0ではなければ。
			if (position.x != 0.0f)step = 10;
			//X座標が0.0なら。
			else step = 1;
			break;
		case 1:
			//Z軸回りに2.0fで回転させ続ける。
			rot_ring.AddRotationDegZ(2.0f);
			//ビームをチャージする値を減らす。
			beamchargetime--;
			//チャージタイムが0以下になったら。
			if (beamchargetime <= 50)
			{
				beambursttime--;
				if (beamchargetime == 0)
				{
					charge = NewGO<SoundSource>(15);
					charge->Init(15);
					charge->SetVolume(1.2f);
					charge->Play(false);

					effectEmitter = NewGO<EffectEmitter>(1);
					effectEmitter->Init(1);
					effectEmitter->SetScale({ 30.0f,30.0f,60.0f });
					effectEmitter->SetPosition(beamchargePos);
					effectEmitter->Play();
				}
				//ビームを打っている間の処理。		
				if (beambursttime <= 0&& beambursttime > -340)
				{
					if (colliState == false)
					{
						colli_beam = NewGO<CollisionObject>(0);
						colli_beam->CreateBox(Vector3(0.0f, 0.0f, 0.0f), Quaternion(90.0f, 90.0f, 90.0f, 1.0f), { 300.0f,300.0f,3000.0f });
						colli_beam->SetIsEnableAutoDelete(false);
						colli_beam->SetName("beam");
						colliState = true;
					}
					//ビームの効果音の再生。
					if (beambursttime == 0)
					{
						beamburst = NewGO<SoundSource>(16);
						beamburst->Init(16);
						beamburst->SetVolume(1.2f);
						beamburst->Play(false);
					}
					if (beambursttime <= 180)
					{
						//自身からプレイヤーのベクトルを計算する。
						diff = player->position - position;
						//X
						if (diff.x > Newdiff.x) {
							Newdiff.x += kasokudo_x;
							if (diff.x < Newdiff.x)Newdiff.x = diff.x;
						}
						else if (diff.x < Newdiff.x) {
							Newdiff.x -= kasokudo_x;
							if (diff.x > Newdiff.x)Newdiff.x = diff.x;
						}
					    //Y
						if (diff.y > Newdiff.y) {
							Newdiff.y += kasokudo_y;
							if (diff.y < Newdiff.y)Newdiff.y=diff.y;
						}
						else if (diff.y < Newdiff.y) {
							Newdiff.y -= kasokudo_y;
							if (diff.y > Newdiff.y)Newdiff.y = diff.y;
						}
					    //Z
						Newdiff.z = diff.z;
						//ビームの速度を上げる。
						kasokudo_x += 2.5f;
						kasokudo_y += 2.5f;
						//ベクトルを正規化する。
						Newdiff.Normalize();
						//移動速度を設定する。
						moveSpeed = Newdiff * 0.1f;
						//本体とエフェクトの回転の処理。
						RookON();
						RookON_eff();
						//プレイヤーがスーパーバリアを使っていないとき当たり判定の処理を行う。
						if(player->SuparBariaState==false)BeamColli();
						colli_beam->SetPosition(position);
						colli_beam->SetRotation(rotation);
					}
				}
				if (beambursttime <= -345)
				{
					//ビームの当たり判定を消す。
					DeleteGO(colli_beam);
					effectEmitter->Stop();
					//無敵時間リセット。
					player->muteki = 0;
					step = 2;
				}
			}
			break;
		case 2:
			//リングを180°回転させる(最初に戻す)。
			rot_ring.SetRotationDegY(180);
			position_ring = {0.0f,0.0f,1600.0f};
			//リングの目のコリジョンをリングに合わせる。
			ringeyepos_x = 400;
			ringeyepos_y = 400;
			//beambursttime = 0;
			beamstate = 0;
			break;
		case 10:
			//本体の座標が0より大きかったら。
			if (position.x > 0)position.x -= 3.0f;
			//本体の座標が0より小さかったら。
			if (position.x < 0)position.x += 3.0f;
			if (position.x == 0.0f)step = 1;
			break;
		default:
			break;
		}
	}
}

void Boss03::RookON()
{
	if (fabsf(moveSpeed.x) < 0.001f
		&& fabsf(moveSpeed.z) < 0.001f) {
		//m_moveSpeed.xとm_moveSpeed.zの絶対値がともに0.001以下ということは
		//このフレームではキャラは移動していないので旋回する必要はない。
		return;
	}
	//atan2はtanθの値を角度(ラジアン単位)に変換してくれる関数。
	//m_moveSpeed.x / m_moveSpeed.zの結果はtanθになる。
	//atan2を使用して、角度を求めている。
	//これが回転角度になる。
	float angle = atan2(moveSpeed.x, moveSpeed.z);
	//atanが返してくる角度はラジアン単位なので
	//SetRotationDegではなくSetRotationを使用する。
	rotation.SetRotationY(angle);
	
	float angle_x = atan2(moveSpeed.y, moveSpeed.z);
	rotation_x.SetRotationX(angle_x);
	rotation *= rotation_x;
	//回転を設定する。
	modelRender.SetRotation(rotation);

	//プレイヤーの正面ベクトルを計算する。
	forward = Vector3::AxisZ;
	rotation.Apply(forward);
}

void Boss03::RookON_eff()
{
	if (fabsf(moveSpeed.x) < 0.001f
		&& fabsf(moveSpeed.z) < 0.001f) {
		//m_moveSpeed.xとm_moveSpeed.zの絶対値がともに0.001以下ということは
		//このフレームではキャラは移動していないので旋回する必要はない。
		return;
	}
	float angle_eff = atan2(moveSpeed.x, moveSpeed.z);
	//Y軸回りの回転。
	rot_effect_y.SetRotationY(angle_eff);

	float angle_eff_x = atan2(moveSpeed.y, moveSpeed.z);
	//X軸回りの回転。
	rot_effect_x.SetRotationX(angle_eff_x);
	//X軸回りの回転とY軸回りの回転を足す。
	rot_effect_y *= rot_effect_x;

	effectEmitter->SetRotation(rot_effect_y);
	//プレイヤーの正面ベクトルを計算する。
	forward = Vector3::AxisZ;
	rot_effect_y.Apply(forward);
}
//プレイヤーにダメージを与えたときの処理。
void Boss03::Damage()
{
	if (beamstate == 0) {
		if (player->muteki >= 60) {
			//playerのHpを10減らす。
			player->playerHp -= player->damage;
			//ダメージを受けた。
			player->damagestate = 1;
			//無敵時間リセット。
			player->muteki = 0;
		}
	}
	else if (beamstate == 1) {
		//無敵時間が６０以上なら。
		if (player->muteki >= 60) {
			//playerのHpを5減らす。
			player->playerHp -= 6;
			//ダメージを受けた。
			player->damagestate = 1;
			//継続してダメージを与えるために無敵時間を短くする。
			player->muteki = 40;
		}
	}
	
}

void Boss03::Render(RenderContext& rc)
{
	modelRender.Draw(rc);
	modelRender_ring.Draw(rc);

	modelRender_ring_Eup.Draw(rc);
	modelRender_ring_Elight.Draw(rc);
	modelRender_ring_Eleft.Draw(rc);
	modelRender_ring_Edown.Draw(rc);
}