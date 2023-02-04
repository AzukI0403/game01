#include "stdafx.h"
#include "Boss02.h"
#include "Game2.h"
#include "Player.h"
#include "Baria.h"
#include "Tama_big.h"
#include "Tama_tuibi.h"
#include "GameUI2.h"
#include "graphics/effect/EffectEmitter.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"

Boss02::Boss02()
{

}

Boss02::~Boss02()
{
	DeleteGO(colli_center);
	DeleteGO(colli_up);
	DeleteGO(colli_down);

	QueryGOs<Tama_tuibi>("tama_tuibi", [&](Tama_tuibi* tama_tuibi_) {
		DeleteGO(tama_tuibi_);
		return true;
		});

	QueryGOs<Tama_big>("tama_big", [&](Tama_big* tama_big_) {
		DeleteGO(tama_big_);
		return true;
		});
}

bool Boss02::Start()
{
	//プレイヤーのインスタンスを探す。
	player = FindGO<Player>("player");
	//ゲームのインスタンスを探す。
	game2 = FindGO<Game2>("game2");
	//ゲームのインスタンスを探す。
	baria = FindGO<Baria>("baria");
	//ゲームのインスタンスを探す。
	gameUI2 = FindGO<GameUI2>("gameUI2");

	//爆発するときの音を読み込む。
	g_soundEngine->ResistWaveFileBank(18, "Assets/sound/boss_dead.wav");
	//エフェクトを読み込む。
	EffectEngine::GetInstance()->ResistEffect(9, u"Assets/effect/effectsprite/boss_dead.efk");

	modelRender_up.SetRaytracingWorld(false);
	modelRender_up.Init("Assets/modelData/enemy_boss02_up.tkm");
	modelRender_center.SetRaytracingWorld(false);
	modelRender_center.Init("Assets/modelData/enemy_boss02_center.tkm");
	modelRender_down.SetRaytracingWorld(false);
	modelRender_down.Init("Assets/modelData/enemy_boss02_down.tkm");

	//upのコリジョンの作成。
	colli_up = NewGO<CollisionObject>(0);
	colli_up->CreateSphere(Vector3(0.0f, 0.0f, 0.0f), Quaternion::Identity, 160.0f);
	colli_up->SetIsEnableAutoDelete(false);
	colli_up->SetName("up");

	//centerのコリジョンの作成。
	colli_center = NewGO<CollisionObject>(0);
	colli_center->CreateSphere(Vector3(0.0f, 0.0f, 0.0f), Quaternion::Identity, 160.0f);
	colli_center->SetIsEnableAutoDelete(false);
	colli_center->SetName("center");

	//downのコリジョンの作成。
	colli_down = NewGO<CollisionObject>(0);
	colli_down->CreateSphere(Vector3(0.0f, 0.0f, 0.0f), Quaternion::Identity, 160.0f);
	colli_down->SetIsEnableAutoDelete(false);
	colli_down->SetName("down");

	return true;
}

void Boss02::Update()
{
	muteki--;

	Move();

	//定位置に着いたら。
	if (position_up.x <= 700)
	{
		count--;
		//countが0のとき。
			//countが0になるまではパターンを保持する。
		if (count == 0)
		{
			//攻撃パターンを決める。
			pattern = rand() % 3;
			attack = 0;
			targetstate = 0;
			attackcounter = 0;
			attackcomplete = 0;
			sarchtime = 100;
		}
		//countが-500以下になったら。
		if (count <= -500)
		{
				if (pattern == 2)
				{
					count = 150;
				}
				else
				{
					//countを200に戻す。
					count = 250;
				}
		}
		//大きな玉を打つ。
		if (pattern == 0)
		{
			Tama();
		}
		//追尾する玉を打つ。
		if (pattern == 1)
		{
			Tuibi();
		}
		//順番にプレイヤーに突撃する。
		if (pattern == 2)
		{
			if (targetstate == 0)
			{
				//プレイヤーの位置を特定する。
				switch (attack)
				{
					//up
				case 0:
					Target_up();
					break;
					//center
				case 1:
					Target_center();
					break;
					//down
				case 2:
					Target_down();
					break;

				default:
					break;
				}
				
			}
			Totugeki();
		}
	}

	Collision_center();
	Collision_up();
	Collision_down();

	modelRender_center.SetPosition(position_center);
	modelRender_up.SetPosition(position_up);
	modelRender_down.SetPosition(position_down);

	colli_center->SetPosition(position_center);
	colli_up->SetPosition(position_up);
	colli_down->SetPosition(position_down);

	modelRender_center.Update();
	modelRender_up.Update();
	modelRender_down.Update();

}

void Boss02::Move()
{
	if (attack<=0)
	{
		if (position_up.x >= 600)
		{
			position_up.x -= 10.0f;
		}
		if (position_center.x >= 600)
		{
			position_center.x -= 10.0f;
		}
		if (position_down.x >= 600)
		{
			position_down.x -= 10.0f;
		}
	}

	//画面外に出たら位置を戻す。
	if (attack==-1)
	{
			position_up.x = 2000;
			position_up.y = 410;
	
			position_center.x = 2000;
			position_center.y = 60;
		
			position_down.x = 2000;
			position_down.y = -290;
	
			attack = 0;
			attackcomplete = 0;
			sarchtime = 70;
	}
}

void Boss02::Collision_center()
{
	//danganのコリジョンを取得する。
	const auto& collisions = g_collisionObjectManager->FindCollisionObjects("dangan");
	//collisionの配列をfor文で回す。
	for (auto collision : collisions)
	{
		//設定したコリジョンとキャラクターコントローラーが衝突したか判定する。
		if (collision->IsHit(colli_center))
		{
			//mutekiが0以下になったら。
			if (muteki <= 0)
			{
				//ボスのhpを2減らす。
				bosshp -= 2;
				muteki = 40;
			}
			//ボスのhpが0以下になったら。
			if (bosshp <= 0)
			{
				Dead();
			}
		}
	}
	//playerのコリジョンを取得する。
	const auto& collisions_p = g_collisionObjectManager->FindCollisionObjects("player");
	//collisionの配列をfor文で回す。
	for (auto collision : collisions_p)
	{
		//設定したコリジョンが衝突したか判定する。
		if (collision->IsHit(colli_center))
		{
			//無敵時間が60以上のとき。
			if (player->muteki >= 60)
			{
				//playerのHpを10減らす。
				player->playerHp -= player->damage;
				//ダメージを受けた。
				player->damagestate = 1;
				//無敵時間リセット。
				player->muteki = 0;
			}
		}
	}
}

void Boss02::Collision_up()
{
	//danganのコリジョンを取得する。
	const auto& collisions = g_collisionObjectManager->FindCollisionObjects("dangan");
	//collisionの配列をfor文で回す。
	for (auto collision : collisions)
	{
		//設定したコリジョンとキャラクターコントローラーが衝突したか判定する。
		if (collision->IsHit(colli_up))
		{
			//mutekiが0以下になったら。
			if (muteki <= 0)
			{
				//ボスのhpを2減らす。
				bosshp -= 2;
				muteki = 40;
			}
			//ボスのhpが0以下になったら。
			if (bosshp <= 0)
			{
				Dead();
			}
		}
	}

	//playerのコリジョンを取得する。
	const auto& collisions_p = g_collisionObjectManager->FindCollisionObjects("player");
	//collisionの配列をfor文で回す。
	for (auto collision : collisions_p)
	{
		//設定したコリジョンが衝突したか判定する。
		if (collision->IsHit(colli_up))
		{
			//無敵時間が60以上のとき。
			if (player->muteki >= 60)
			{
				//playerのHpを10減らす。
				player->playerHp -= player->damage;
				//ダメージを受けた。
				player->damagestate = 1;
				//無敵時間リセット。
				player->muteki = 0;
			}
		}
	}
}

void Boss02::Collision_down()
{
	//danganのコリジョンを取得する。
	const auto& collisions = g_collisionObjectManager->FindCollisionObjects("dangan");
	//collisionの配列をfor文で回す。
	for (auto collision : collisions)
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
			//ボスのhpが0以下になったら。
			if (bosshp <= 0)
			{
				Dead();
			}
		}
	}
	//playerのコリジョンを取得する。
	const auto& collisions_p = g_collisionObjectManager->FindCollisionObjects("player");
	//collisionの配列をfor文で回す。
	for (auto collision : collisions_p)
	{
		//設定したコリジョンが衝突したか判定する。
		if (collision->IsHit(colli_down))
		{
			//無敵時間が60以上のとき。
			if (player->muteki >= 60)
			{
				//playerのHpを10減らす。
				player->playerHp -= player->damage;
				//ダメージを受けた。
				player->damagestate = 1;
				//無敵時間リセット。
				player->muteki = 0;
			}
		}
	}
}

void Boss02::Tama()
{
	countdown--;
	attack = rand() % 3;
	
	//もし前回打ったtamaと今回打つtamaが同じ場所なら。
	if (attack == oldattack)
	{
		attack = rand() % 3;
		//もう一度ランダムに決めても前回打ったtamaと今回打つtamaが同じ場所なら。
		if (attack == oldattack)
		{
			switch (attack)
			{
			case 0:
				//centerに決める。
				attack = 1;
				break;

			case 1:
				//upに決める。
				attack = 0;
				break;

			case 2:
				//upかcenterからランダムに決める。
				attack = rand() % 2;
				break;
			}
		}
	}

	//70秒ごとに生成する。
	if (countdown <= 0)
	{
		if (attack == 0)
		{
			//centerから玉を打つ。
			Tama_big* tama_big_u = NewGO<Tama_big>(0, "tama_big");
			tama_big_u->position = position_up;
			tama_big_u->position.x = position_up.x - 130.0f;
		}
		if (attack == 1)
		{
			//centerから玉を打つ。
			Tama_big* tama_big_c = NewGO<Tama_big>(0, "tama_big");
			tama_big_c->position = position_center;
			tama_big_c->position.x = position_center.x - 130.0f;
		}

		if (attack == 2)
		{
			//centerから玉を打つ。
			Tama_big * tama_big_d = NewGO<Tama_big>(0, "tama_big");
			tama_big_d->position = position_down;
			tama_big_d->position.x = position_down.x - 130.0f;
		}
		oldattack = attack;
		countdown = 70;
	}
}

void Boss02::Tuibi()
{
	countdown--;
	//90秒ごとに生成する。
	if (countdown <= 0)
	{
		if (attack == 0)
		{
			//centerから追尾する玉を打つ。
			Tama_tuibi* tama_tuibi_u = NewGO<Tama_tuibi>(0, "tama_tuibi");
			tama_tuibi_u->position = position_up;
			tama_tuibi_u->position.x = position_up.x - 130.0f;
		}
		if (attack == 1)
		{
			//centerから追尾する玉を打つ。
			Tama_tuibi* tama_tuibi_c = NewGO<Tama_tuibi>(0, "tama_tuibi");
			tama_tuibi_c->position = position_center;
			tama_tuibi_c->position.x = position_center.x - 130.0f;
		}

		if (attack == 2)
		{
			//centerから追尾する玉を打つ。
			Tama_tuibi* tama_tuibi_d = NewGO<Tama_tuibi>(0, "tama_tuibi");
			tama_tuibi_d->position = position_down;
			tama_tuibi_d->position.x = position_down.x - 130.0f;
			tama_tuibi_d->change = 1;

		}
		countdown = 70;

		attack++;

		//upからdownまで玉を打ったら。
		if (attack >= 4)
		{
			//リセット。
			attack = 0;
		}
	}
}

void Boss02::Totugeki()
{
	//sarchtime=50
	if (sarchtime >= 0)
	{
		sarchtime--;
	}

	if (sarchtime <= 0)
	{
		//totugekicount++;
		attackcounter++;
		//upがプレイヤーに向かって突撃する。
		if (attack >= 0)
		{
			position_up += moveSpeed_up;
		}
		//centerがプレイヤーに向かって突撃する。
		if (attack >=1)
		{
			position_center += moveSpeed_center;
		}
		//downがプレイヤーに向かって突撃する。
		if (attack >=2)
		{
			position_down += moveSpeed_down;
		}
		//60フレームたつごとに突撃させる。
		if (attackcounter >=60)
		{
			attack++;
			attackcounter = 0;
			targetstate = 0;
			attackcomplete++;

			if (attackcomplete >= 4)
			{
				//突撃する処理を行わないようにする。
				attack = -1;
			}
		}
	}
}

void Boss02::Target_up()
{
	Vector3 diff_up = player->position - position_up;
	
	//upのベクトルを正規化する。
	diff_up.Normalize();
	//移動速度を設定する。
	moveSpeed_up = diff_up * 17.0f;
	//attack++;
	targetstate = 1;
}

void Boss02::Target_center()
{
	Vector3 diff_center = player->position - position_center;

	//upのベクトルを正規化する。
	diff_center.Normalize();
	//移動速度を設定する。
	moveSpeed_center = diff_center * 17.0f;
	//attack++;
	targetstate = 1;
}

void Boss02::Target_down()
{
	Vector3 diff_down = player->position - position_down;

	//upのベクトルを正規化する。
	diff_down.Normalize();
	//移動速度を設定する。
	moveSpeed_down = diff_down * 17.0f;
	//attack++;
	targetstate = 1;
}

void Boss02::Dead()
{
	//やられたときの音の再生。
	SoundSource* dead = NewGO<SoundSource>(18);
	dead->Init(18);
	dead->SetVolume(1.2f);
	dead->Play(false);
	//爆発エフェクトの再生。
	{
		EffectEmitter* effectEmitter_u = NewGO<EffectEmitter>(9);
		effectEmitter_u->Init(9);
		effectEmitter_u->SetScale({ 2.0f,2.0f,0.0f });
		effectEmitter_u->SetPosition(position_up);
		effectEmitter_u->Play();
		EffectEmitter* effectEmitter_s = NewGO<EffectEmitter>(9);
		effectEmitter_s->Init(9);
		effectEmitter_s->SetScale({ 2.0f,2.0f,0.0f });
		effectEmitter_s->SetPosition(position_center);
		effectEmitter_s->Play();
		EffectEmitter* effectEmitter_d = NewGO<EffectEmitter>(9);
		effectEmitter_d->Init(9);
		effectEmitter_d->SetScale({ 2.0f,2.0f,0.0f });
		effectEmitter_d->SetPosition(position_down);
		effectEmitter_d->Play();
	}
	//敵を倒した数を増やす。
	player->downcount += 1;
	gameUI2->bossdeath = 1;
	//自身を破壊する。
	DeleteGO(this);
}

void Boss02::Render(RenderContext& rc)
{
	modelRender_up.Draw(rc);
	modelRender_center.Draw(rc);
	modelRender_down.Draw(rc);
}