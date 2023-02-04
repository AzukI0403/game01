#include "stdafx.h"
#include "enemy01.h"
#include "Game.h"
#include "Dangan.h"
#include "Tama.h"
#include "Player.h"
#include "Baria.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
#include "Game2.h"
#include "Game3.h"
#include "graphics/effect/EffectEmitter.h"



Enemy01::Enemy01()
{

}

Enemy01::~Enemy01()
{
	DeleteGO(colli);
}

bool Enemy01::Start()
{
	//プレイヤーのインスタンスを探す。
	player = FindGO<Player>("player");
	//ゲーム1_1のインスタンスを探す。
	game = FindGO<Game>("game");
	//ゲーム1_2のインスタンスを探す。
	game2 = FindGO<Game2>("game2");
	//ゲームのインスタンスを探す。
	baria = FindGO<Baria>("baria");
	//ゲーム1_3のインスタンスを探す。
	game3 = FindGO<Game3>("game3");

	//生成するオブジェクトの処理を軽くする。
	modelRender.SetRaytracingWorld(false);
	modelRender.Init("Assets/modelData/enemy_eye.tkm");

	//爆発の音を読み込む。
	g_soundEngine->ResistWaveFileBank(2, "Assets/sound/enemy_death.wav");

	//エフェクトを読み込む。
	EffectEngine::GetInstance()->ResistEffect(0, u"Assets/effect/effectsprite/explosion.efk");

	//コリジョンの作成。
	colli = NewGO<CollisionObject>(0);
	colli->CreateSphere(Vector3(0.0f,0.0f, 0.0f), Quaternion::Identity,40.0f);
	colli->SetIsEnableAutoDelete(false);
	colli->SetName("enemy_eye");
	colli->SetPosition(position);


	characterController.Init(10.0f, 0.0f, position);

	//最初に上に移動するか下に移動するかランダムに決める。
	moveCount = rand() % 2;
	//とどまるか進むかランダムにきめる。
	go = rand() % 10;

	return true;
}



void Enemy01::Update()
{
	timeCount += 1;

	Move();
	
	Attack();

	//画面内に入ったら当たり判定を行う。
	if (position.x <= 900)
	{
		//弾丸との当たり判定。
		Collisiond();
		//プレイヤーとの当たり判定。
		Collisionp();
		//バリアとの当たり判定。
		Collisionb();
	}
	
	colli->SetPosition(position);
	modelRender.Update();
	
}

//移動処理。
void Enemy01::Move()
{
	position = characterController.Execute(moveSpeed, 2.0 / 60.0f);

	//goが9か10なら(突撃)。
	if (go > 8)
	{
		    //そのまま進む。
			moveSpeed.x -= 8.0f;
			if (position.x >= 1100)
			{
				timeCount = 0;

				//自身を破壊。
				DeleteGO(this);
			}
		
	}
	//goが8までなら(tamaを打つ)。
	else
	{
		//timeCountが340以下なら。
		if (timeCount <= 340)
		{
			if (position.x >= 700)
			{
				//x=700まで移動。
				moveSpeed.x -= 6.0f;
			}
			else
			{
				//x=700より前にいかないようにする。
				moveSpeed.x = 0.0f;
			}

		}
		//timeCountが340以上なら。
		else
		{
			moveSpeed.x -= 12.0f;
			if (position.x >= 1200)
			{
				timeCount = 0;
				//自身を破壊。
				DeleteGO(this);
			}
		}
	}
	
	//上下移動。
	if (timeCount <= 340)
	{
		if (moveCount == 0)
		{
			//上に移動する。
			moveSpeed.y += 7.5f;
		}
		if (moveCount == 1)
		{
			//下に移動する。
			moveSpeed.y -= 7.5f;
		}
		//y座標が初期座標y+50.0fを超えたら。
		if (position.y >= firstPosition.y + 50.0f)
		{
			//下に移動する。
			moveCount = 1;
		}
		//y座標が初期座標y-50.0fを超えたら。
		if (position.y <= firstPosition.y - 50.0f)
		{
			//上に移動する。
			moveCount = 0;
		}
	}
	//絵描きさんに座標を教える。
	modelRender.SetPosition(position);
}

//攻撃。
void Enemy01::Attack()
{
	if (position.x <= 800)
	{
		tamatime += 1;
			if (tamatime == 80)
			{
				if (tamaCount <= 4)
				{
					tamaCount += 1;
					Tama* tama = NewGO<Tama>(0,"tama");
					tama->position = position;
					tama->firstposition = tama->position;
					
					tamatime = 0;
				}

			}
	}
}

//弾丸との当たり判定。
void Enemy01::Collisiond()
{
	//danganのコリジョンを取得する。
	const auto& collisions=g_collisionObjectManager->FindCollisionObjects("dangan");
	                       
	//collisionの配列をfor文で回す。
	for (auto collision : collisions)
	{
		//設定したコリジョンが衝突したか判定する。
		if (collision->IsHit(colli))
		{
			//倒した敵のカウントを増やす。
			player->downcount += 1;
			//効果音とエフェクトを再生する。
			Dead();
			//自身を破壊する。
			DeleteGO(this);
		}
	}
	
	
}
//プレイヤーにぶつかった時の判定。
void Enemy01::Collisionp()
{
	//playerのコリジョンを取得する。
	const auto& collisions = g_collisionObjectManager->FindCollisionObjects("player");

	//collisionの配列をfor文で回す。
	for (auto collision : collisions)
	{
		//設定したコリジョンが衝突したか判定する。
		if (collision->IsHit(colli))
		{
			//ぶつかっただけならスコアには加えない。
			//player->downcount += 1;
			//無敵時間が70以上のとき。
			if (player->muteki >= 60)
			{
				//playerのHpを10減らす。
				player->playerHp -= player->damage;
				//ダメージを受けた。
				player->damagestate = 1;
				//無敵時間リセット。
				player->muteki = 0;
			}
			//効果音とエフェクトを再生する。
			Dead();
			//自身を破壊する。
			DeleteGO(this);
		}
	}
}
//bariaとの当たり判定。
void Enemy01::Collisionb()
{
	//bariaのコリジョンを取得する。
	const auto& collisions = g_collisionObjectManager->FindCollisionObjects("baria");

	//collisionの配列をfor文で回す。
	for (auto collision : collisions)
	{
		//設定したコリジョンが衝突したか判定する。
		if (collision->IsHit(colli))
		{
			player->downcount += 1;
			//効果音とエフェクトを再生する。
			Dead();
			//自身を破壊する。
			DeleteGO(this);
		}
	}


}

//エネミーがやられたときの処理。
void Enemy01::Dead()
{
	//やられたときの音を再生する。
	death = NewGO<SoundSource>(2);
	death->Init(2);
	death->SetVolume(1.2f);
	death->Play(false);
	//やられたときのエフェクトを再生する。
	EffectEmitter* effectEmitter = NewGO<EffectEmitter>(0);
	effectEmitter->Init(0);
	effectEmitter->SetScale({ 10.0f,10.0f,10.0f });
	effectEmitter->SetPosition(position);
	effectEmitter->Play();
}

void Enemy01::Render(RenderContext& rc)
{
	modelRender.Draw(rc);
}