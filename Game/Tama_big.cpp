#include "stdafx.h"
#include "Tama_big.h"
#include "Boss02.h"
#include "Game2.h"
#include "Player.h"
#include "Baria.h"

Tama_big::Tama_big()
{

}

Tama_big::~Tama_big()
{
	DeleteGO(colli);
}

bool Tama_big::Start()
{
	modelRender.SetRaytracingWorld(false);
	modelRender.Init("Assets/modelData/tama_big.tkm");

	//ゲーム1_2のインスタンスを探す。
	game2 = FindGO<Game2>("game2");
	//プレイヤーのインスタンスを探す。
	player = FindGO<Player>("player");
	//バリアのインスタンスを探す。
	baria = FindGO<Baria>("baria");

	//コリジョンの作成。
	colli = NewGO<CollisionObject>(0);
	colli->CreateSphere(Vector3(0.0f, 0.0f, 0.0f), Quaternion::Identity, 138.0f);
	colli->SetIsEnableAutoDelete(false);
	colli->SetName("tama_big");
	colli->SetPosition(position);

	return true;
}

void Tama_big::Update()
{
	position.x -= 8.0f;

	if (position.x <= -1200)
	{
		//自身を消す。
		DeleteGO(this);
	}

	Collition();

	colli->SetPosition(position);

	modelRender.SetPosition(position);

	modelRender.Update();
}

void Tama_big::Collition()
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
		}
	}
}

void Tama_big::Render(RenderContext& rc)
{
	modelRender.Draw(rc);
}