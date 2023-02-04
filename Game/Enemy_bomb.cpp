#include "stdafx.h"
#include "Enemy_bomb.h"
#include "Baria.h"
#include "Player.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
#include "Game_final.h"
#include "Boss03.h"
#include "graphics/effect/EffectEmitter.h"


Enemy_bomb::Enemy_bomb()
{

}

Enemy_bomb::~Enemy_bomb()
{
	EffectEmitter* effectEmitter = NewGO<EffectEmitter>(0);
	effectEmitter->Init(0);
	effectEmitter->SetScale({ 10.0f,10.0f,10.0f });
	effectEmitter->SetPosition(position);
	effectEmitter->Play();

	DeleteGO(colli);
}

bool Enemy_bomb::Start()
{
	//プレイヤーのインスタンスを探す。
	player = FindGO<Player>("player");
	//ゲームのインスタンスを探す。
	baria = FindGO<Baria>("baria");

	//やられたときの音を読み込む。
	g_soundEngine->ResistWaveFileBank(2, "Assets/sound/enemy_death.wav");

	modelRender.SetRaytracingWorld(false);
	modelRender.Init("Assets/modelData/bomb.tkm");

	//エフェクトを読み込む。
	EffectEngine::GetInstance()->ResistEffect(0, u"Assets/effect/effectsprite/explosion.efk");

	//コリジョンの作成。
	colli = NewGO<CollisionObject>(0);
	colli->CreateSphere(Vector3(0.0f, 0.0f, 0.0f), Quaternion::Identity, 30.0f);
	colli->SetIsEnableAutoDelete(false);
	colli->SetName("bomb");
	colli->SetPosition(position);

	//tamaの速度。
	//tamaからプレイヤーに向かうベクトルを計算する。
	Vector3 diff = randomposition - position;

	//ベクトルを正規化する。
	diff.Normalize();
	//移動速度を設定する。
	moveSpeed = diff * 15.0f;

	return true;
}

void Enemy_bomb::Update()
{
	if (position.z >= 0)
	{
		position += moveSpeed;
	}

	if (position.z <= 0)
	{
		//explode=400
		explode--;
		//400フレームたったら爆発させる。
		if (explode <= 0)
		{
			//爆発の音を再生する。
			SoundSource* death = NewGO<SoundSource>(2);
			death->Init(2);
			death->SetVolume(0.7f);
			death->Play(false);
			//自身を破壊する。
			DeleteGO(this);
		}
	}

	if(position.z<=0)Collition();

	modelRender.SetPosition(position);
	colli->SetPosition(position);
	modelRender.Update();
}

void Enemy_bomb::Collition()
{
	//bariaのコリジョンを取得する。
	const auto& collisions = g_collisionObjectManager->FindCollisionObjects("baria");

	//collisionの配列をfor文で回す。
	for (auto collision : collisions)
	{
		//設定したコリジョンが衝突したか判定する。
		if (collision->IsHit(colli))
		{
			//爆発の音を再生する。
			SoundSource* death = NewGO<SoundSource>(2);
			death->Init(2);
			death->SetVolume(1.0f);
			death->Play(false);
			//自身を破壊する。
			DeleteGO(this);
		}
	}

	const auto& collisions_p = g_collisionObjectManager->FindCollisionObjects("player");

	//collisionの配列をfor文で回す。
	for (auto collision : collisions_p)
	{
		//設定したコリジョンが衝突したか判定する。
		if (collision->IsHit(colli))
		{
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
			//爆発の音を再生する。
			SoundSource*death = NewGO<SoundSource>(2);
			death->Init(2);
			death->SetVolume(1.0f);
			death->Play(false);
			//自身を破壊する。
			DeleteGO(this);
		}
	}
}

void Enemy_bomb::Render(RenderContext& rc)
{
	modelRender.Draw(rc);
}
