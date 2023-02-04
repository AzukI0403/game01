#include "stdafx.h"
#include "Tama_tuibi.h"
#include "Enemy01.h"
#include "Player.h"
#include "Game.h"
#include "Baria.h"
#include "Game2.h"
#include "Numberhouse.h"

Tama_tuibi::Tama_tuibi()
{

}

Tama_tuibi::~Tama_tuibi()
{
	DeleteGO(colli);
}

bool Tama_tuibi::Start()
{
	baria = FindGO<Baria>("baria");

	modelRender.SetRaytracingWorld(false);
	modelRender.Init("Assets/modelData/tama02.tkm");

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
	colli->SetName("tama_tuibi");
	colli->SetPosition(position);
	//tamaの速度。
	//tamaからプレイヤーに向かうベクトルを計算する。
	Vector3 diff = player->position - position;

	//ベクトルを正規化する。
	diff.Normalize();
	//移動速度を設定する。
	moveSpeed = diff * 10.0f;

	return true;
}

void Tama_tuibi::Update()
{
	countdown--;
	//tamaの追尾を仕方をかえるとき。
	//change == 1かつcountdown<=0&かつcount<=20のとき。
	//20回繰り返す。
	if (change == 1&&countdown<=0&&count<=20)
	{
		//tamaの速度。
	//tamaからプレイヤーに向かうベクトルを計算する。
		Vector3 diff = player->position - position;

		//ベクトルを正規化する。
		diff.Normalize();
		//移動速度を設定する。
		moveSpeed = diff * 8.0f;

		countdown = 5;
		count++;
	}

	//移動速度を座標に足していく。
	position += moveSpeed;

	//画面外に出たら。
	if (position.x <= -1050||position.x>=1050||position.y>=1000||position.y<=-1000)
	{
		//自身を消す。
		DeleteGO(this);
	}

	Collitionb();

	colli->SetPosition(position);

	modelRender.SetPosition(position);

	modelRender.Update();
}

void Tama_tuibi::Collitionb()
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

void Tama_tuibi::Render(RenderContext& rc)
{
	modelRender.Draw(rc);
}
