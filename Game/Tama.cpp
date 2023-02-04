#include "stdafx.h"
#include "Tama.h"
#include "Enemy01.h"
#include "Player.h"
#include "Game.h"
#include "Baria.h"
#include "Boss01.h"
#include "Game2.h"
#include "Numberhouse.h"

Tama::Tama()
{

}

Tama::~Tama()
{
	DeleteGO(colli);
}

bool Tama::Start()
{
	//Numberhouseのインスタンスを探す。
	numberhouse = FindGO<Numberhouse>("numberhouse");

	baria = FindGO<Baria>("baria");

	modelRender.SetRaytracingWorld(false);
	modelRender.Init("Assets/modelData/tama.tkm");

	//ゲーム1_1のインスタンスを探す。
	game = FindGO<Game>("game");
	//ゲーム1_2のインスタンスを探す。
	game2 = FindGO<Game2>("game2");
	//プレイヤーのインスタンスを探す。
	player = FindGO<Player>("player");

	//コリジョンの作成。
	colli = NewGO<CollisionObject>(0);
	colli->CreateSphere(Vector3(0.0f, 0.0f, 0.0f), Quaternion::Identity, 20.0f);
	colli->SetIsEnableAutoDelete(false);
	colli->SetName("tama");
	colli->SetPosition(position);
	//ステージのナンバーを代入する。
	stagenumber = numberhouse->stagenumber;

	//tamaの速度。
	//tamaからランダムに向かうベクトルを計算する。
	Vector3 diff = randomposition - position;

	//ベクトルを正規化する。
	diff.Normalize();
	//移動速度を設定する。
	moveSpeed = diff * 10.0f;

	return true;
}

void Tama::Update()
{
	//changeが１ならboss01の打つ玉に変える。
	if (change == 1)
	{
		//tamaの速度。
		position += moveSpeed;
	}
	else
	{
		if (stagenumber == 4)
		{
			//tamaの速度。
			position.z -= 13;
		}
		else
		{
			//tamaの速度。
			position.x -= 20;
		}
		
	}
		
	//画面外に出たら。
	if (position.x <= -1050)
	{
		//自身を消す。
		DeleteGO(this);
	}
	if (position.z <= -500)
	{
		//自身を消す。
		DeleteGO(this);
	}

	Collitionb();

	colli->SetPosition(position);

	modelRender.SetPosition(position);

	modelRender.Update();
}

void Tama::Collitionb()
{
	//bariaのコリジョンを取得する。
	const auto& collisions = g_collisionObjectManager->FindCollisionObjects("baria");

	//collisionの配列をfor文で回す。
	for (auto collision : collisions)
	{
		//設定したコリジョンが衝突したか判定する。
		if (collision->IsHit(colli))
		{
			//自身を破壊する。
			DeleteGO(this);
		}
	}

	//playerのコリジョンを取得する。
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
			//自身を破壊する。
			DeleteGO(this);
		}
	}
}

void Tama::Render(RenderContext& rc)
{
	modelRender.Draw(rc);
}
