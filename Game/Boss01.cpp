#include "stdafx.h"
#include "Boss01.h"
#include "Game.h"
#include "Player.h"
#include "Baria.h"
#include "Tama.h"
#include "Tama_tuibi.h"
#include "GameUI.h"
#include "graphics/effect/EffectEmitter.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"

Boss01::Boss01()
{

}

Boss01::~Boss01()
{
	DeleteGO(colli_up);
	DeleteGO(colli_down);

	QueryGOs<Tama>("tama", [&](Tama* tama_) {
		DeleteGO(tama_);
		return true;
		});

	QueryGOs<Tama_tuibi>("tama_tuibi", [&](Tama_tuibi* tama_tuibi_) {
		DeleteGO(tama_tuibi_);
		return true;
		});
}

bool Boss01::Start()
{
	// 当たり判定の可視化。
	//コメントアウトする。
	//PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();

	//爆発するときの音を読み込む。
	g_soundEngine->ResistWaveFileBank(18, "Assets/sound/boss_dead.wav");
	//エフェクトを読み込む。
	EffectEngine::GetInstance()->ResistEffect(8, u"Assets/effect/effectsprite/redright.efk");
	//エフェクトを読み込む。
	EffectEngine::GetInstance()->ResistEffect(9, u"Assets/effect/effectsprite/boss_dead.efk");

	//プレイヤーのインスタンスを探す。
	player = FindGO<Player>("player");
	//ゲームのインスタンスを探す。
	game = FindGO<Game>("game");
	//ゲームのインスタンスを探す。
	baria = FindGO<Baria>("baria");
	//ゲームのインスタンスを探す。
	gameUI = FindGO<GameUI>("gameUI");

	
	modelRender_up.SetRaytracingWorld(false);
	modelRender_up.Init("Assets/modelData/enemy_boss01_up.tkm");
	modelRender_down.SetRaytracingWorld(false);
	modelRender_down.Init("Assets/modelData/enemy_boss01_down.tkm");



	//コリジョンの作成。
	colli_up = NewGO<CollisionObject>(0);
	colli_up->CreateCapsule(Vector3(0.0f, 0.0f, 0.0f),
		Quaternion(0.0f, 0.0f, 90.0f, 1.0f), 220.0f, 65.0f);
	colli_up->SetIsEnableAutoDelete(false);
	colli_up->SetName("boss01_up");
	rot_up2.SetRotationDegZ(90.0f);
	colli_up->SetRotation(rot_up2);
	colli_up->SetPosition(position_up);
	
	//コリジョンの作成。
	colli_down = NewGO<CollisionObject>(1);
	colli_down->CreateCapsule(Vector3(0.0f, 0.0f, 0.0f), 
		Quaternion(0.0f, 0.0f, 90.0f, 1.0f), 220.0f, 240.0f);
	colli_down->SetIsEnableAutoDelete(false);
	colli_down->SetName("boss01_down");
	rot_down2.SetRotationDegZ(90.0f);
	colli_down->SetRotation(rot_down2);
	colli_down->SetPosition(position_down);
                                              
	return true;
}

void Boss01::Update()
{
	muteki--;

	Move();

	Collision();

	count--;

		//countが0のとき。
		//countが0になるまではパターンを保持する。
		if (count == 0)
		{
			//攻撃パターンを決める。
			pattern =  rand() % 3;
		}
		//countが-300以下になったら。
		if (count <= -500/*-500*/)
		{
			//countを200に戻す。
			count = 290;
			//pattern2(Bite)の値の初期化。
			targetstate = 0;
			gostate = 1;
			backstate = 0;
			totugekitime = 70;
			totugekicount = 0;
			sarchtime = 80;
		}


		//拡散する玉を打つ。
		if (pattern == 0)
		{
			Kakusan();
		}
		//追尾する玉を打つ。
		if (pattern == 1)
		{
			Tuibi();
		}
		//かみつく。
		if (pattern == 2)
		{
			if (targetstate == 0)
			{
				Target();
				EffectEmitter*effectEmitter = NewGO<EffectEmitter>(8);
				effectEmitter->Init(8);
				effectEmitter->SetScale({ 60.0f,60.0f,0.0f });
				effectPos.x = 165.0f;
				effectPos.y = 90.0f;
				effectEmitter->SetPosition(effectPos);
				effectEmitter->Play();
				opentime = 50;
				closetime = 0;
			}
			Bite();
			if (totugekicount == 2)count = 1;
		}
	
		pos_colli = position_up;
		pos_colli.x -= 140.0f;
		pos_colli.y += 40.0f;

	colli_up->SetPosition(pos_colli);

	pos_colli = position_down;
	pos_colli.x -= 90.0f;

	colli_down->SetPosition(pos_colli);
	colli_up->SetRotation(rot_up);

	modelRender_up.SetPosition(position_up);
	modelRender_down.SetPosition(position_down);

	modelRender_up.SetRotation(rot_up);
	modelRender_down.SetRotation(rot_down);

	modelRender_up.Update();
	modelRender_down.Update();
}

void Boss01::Move()
{
	if (pattern != 2)
	{
		if (position_up.x >= 600)
		{
			//x=600まで移動。
			position_up.x -= 10.0f;
			position_down.x -= 10.0f;
		}
	}

	if (pattern != 2)
	{
		if (moveCount == 0)
		{
			//上に移動する。
			position_up.y += 3.0f;
			position_down.y += 3.0f;
		}
		if (moveCount == 1)
		{
			//下に移動する。
			position_up.y -= 3.0f;
			position_down.y -= 3.0f;
		}
		//y座標が初期座標y+150.0fを超えたら。
		if (position_up.y >= firstPosition_up.y + 150.0f)
		{
			//下に移動する。
			moveCount = 1;
		}
		//y座標が初期座標y-150.0fを超えたら。
		if (position_up.y <= firstPosition_up.y - 150.0f)
		{
			//上に移動する。
			moveCount = 0;
		}
	}
}

void Boss01::Collision()
{
	//danganのコリジョンを取得する。
	const auto& collisions_down = g_collisionObjectManager->FindCollisionObjects("dangan");
	//collisionの配列をfor文で回す。
	for (auto collision : collisions_down)
	{
		//設定したコリジョンとキャラクターコントローラーが衝突したか判定する。
		if (collision->IsHit(colli_down))
		{
			//mutekiが0以下になったら。
			if (muteki <= 0)
			{
				//ボスのhpを2減らす。
				bosshp -= 2;
				muteki = 40;
			}

			if (bosshp <= 0)
			{
				Dead();
			}
		}
	}

	//playerのコリジョンを取得する。
	const auto& collisions_p_up = g_collisionObjectManager->FindCollisionObjects("player");

	//collisionの配列をfor文で回す。
	for (auto collision : collisions_p_up)
	{
		//設定したコリジョンが衝突したか判定する。
		if (collision->IsHit(colli_up))
		{
			//無敵時間が60以上のとき。
			if (player->muteki >= 60)
			{
				Damage();
			}
		}
	}

	//playerのコリジョンを取得する。
	const auto& collisions_p_down = g_collisionObjectManager->FindCollisionObjects("player");

	//collisionの配列をfor文で回す。
	for (auto collision : collisions_p_down)
	{
		//設定したコリジョンが衝突したか判定する。
		if (collision->IsHit(colli_down))
		{
			//無敵時間が60以上のとき。
			if (player->muteki >= 60)
			{
				Damage();
			}
		}
	}
}

void Boss01::Kakusan()
{
	countdown -- ;
	//rand() % 1401 - 700;
	//90秒ごとに生成する。
	if (countdown <= 0)
	{
		Tama* tama = NewGO<Tama>(0, "tama");
		//tamaの飛ばし方を変える。
		tama->change = 1;
		tama->position = position_up;
		tama->firstposition = tama->position;
		tama->ramdom_y =0;
		tama->randomposition = { 0.0f,tama->ramdom_y,0.0f };

		Tama* tama01 = NewGO<Tama>(0, "tama");
		//tamaの飛ばし方を変える。
		tama01->change = 1;
		tama01->position = position_up;
		tama01->firstposition = tama01->position;
		tama01->ramdom_y = rand() % 1001 - 500;
		tama01->randomposition = { 0.0f,tama01->ramdom_y,0.0f };

		Tama* tama02 = NewGO<Tama>(0, "tama");
		//tamaの飛ばし方を変える。
		tama02->change = 1;
		tama02->position = position_up;
		tama02->firstposition = tama02->position;
		tama02->ramdom_y = rand() % 1001 - 500;
		tama02->randomposition = { 0.0f,tama02->ramdom_y,0.0f };

		Tama* tama03 = NewGO<Tama>(0, "tama");
		//tamaの飛ばし方を変える。
		tama03->change = 1;
		tama03->position = position_up;
		tama03->firstposition = tama03->position;
		tama03->ramdom_y = rand() % 1001 - 500;
		tama03->randomposition = { 0.0f,tama03->ramdom_y,0.0f };

		Tama* tama04 = NewGO<Tama>(0, "tama");
		//tamaの飛ばし方を変える。
		tama04->change = 1;
		tama04->position = position_up;
		tama04->firstposition = tama04->position;
		tama04->ramdom_y = rand() % 1001 - 500;
		tama04->randomposition = { 0.0f,tama04->ramdom_y,0.0f };

		Tama* tama05 = NewGO<Tama>(0, "tama");
		//tamaの飛ばし方を変える。
		tama05->change = 1;
		tama05->position = position_up;
		tama05->firstposition = tama05->position;
		tama05->ramdom_y = rand() % 1001 - 500;
		tama05->randomposition = { 0.0f,tama05->ramdom_y,0.0f };
		countdown = 90;
	}
}

void Boss01::Tuibi()
{
	countdown--;
	//rand() % 1401 - 700;
	//70秒ごとに生成する。
	if (countdown <= 0)
	{
		Tama_tuibi* tama_tuibi = NewGO<Tama_tuibi>(0, "tama_tuibi");

		tama_tuibi->position = position_up;
		tama_tuibi->firstposition = tama_tuibi->position;
		countdown = 70;
	}
}

void Boss01:: Bite()
{
	if (sarchtime >= 0)
	{
		sarchtime--;
	}
	
	if (sarchtime <= 0)
	{
		totugekitime--;
		//口を開く処理。
		BiteRot();
		//プレイヤーに突撃する。
		if (gostate == 1)
		{
			position_up += moveSpeed;
			position_down += moveSpeed;
		}
		//元の位置に帰る。
		if (backstate == 1)
		{
			position_up -= moveSpeed_b;
			position_down -= moveSpeed_b;
		}

		//突撃が終わったら。
		if (totugekitime==0)
		{
			gostate = 0;
			backstate = 1;

		}
		//元の位置に戻ったら。
		if (totugekitime == -70)
		{
			backstate = 0;
			totugekicount++;
		}
	}
	modelRender_up.SetPosition(position_up);
	modelRender_down.SetPosition(position_down);
}

void Boss01::BiteRot()
{
	//口を開く。
	if (opentime>0)
	{
		rot_up.AddRotationDegZ(-1.6f);
		rot_down.AddRotationDegZ(0.5f);
	}
	//口を閉じる。
	if (opentime == 0&&closetime<20)
	{
		rot_up.AddRotationDegZ(4.0f);
		rot_down.AddRotationDegZ(-1.225f);
	}
	
	if (opentime != 0)
	{
		opentime--;
	}
	else 
		closetime++;
}

//プレイヤーの位置を見つける。
void Boss01::Target()
{
	diff = player->position - position_up;

	//ベクトルを正規化する。
	diff.Normalize();
	//移動速度を設定する。
	moveSpeed = diff * 16.0f;
	moveSpeed_b= diff * 16.0f;

	targetstate = 1;
}

//プレイヤーに与えるダメージの処理。
void Boss01::Damage()
{
	if (pattern == 2)
	{
		//playerのHpを20減らす。
		player->playerHp -= bitedamage;
		//ダメージを受けた。
		player->damagestate = 1;
		//無敵時間リセット。
		player->muteki = 0;
	}
	else
	{
		//playerのHpを10減らす。
		player->playerHp -= player->damage;
		//ダメージを受けた。
		player->damagestate = 1;
		//無敵時間リセット。
		player->muteki = 0;
	}
}

void Boss01::Dead()
{
	//やられたときの音の再生。
	SoundSource* dead = NewGO<SoundSource>(18);
	dead->Init(18);
	dead->SetVolume(1.2f);
	dead->Play(false);
	//爆発エフェクトの再生。
	EffectEmitter* effectEmitter_d = NewGO<EffectEmitter>(9);
	effectEmitter_d->Init(9);
	effectEmitter_d->SetScale({ 4.0f,4.0f,0.0f });
	effectEmitter_d->SetPosition(position_up);
	effectEmitter_d->Play();

	//敵を倒した数を増やす。
	player->downcount += 1;
	gameUI->bossdeath = 1;
	//自身を破壊する。
	DeleteGO(this);
}

void Boss01::Render(RenderContext& rc)
{
	modelRender_up.Draw(rc);
	modelRender_down.Draw(rc);
}