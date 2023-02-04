#include "stdafx.h"
#include "Coin.h"
#include "Game.h"
#include "Player.h"
#include "Game2.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"

Coin::Coin()
{

}

Coin::~Coin()
{
	DeleteGO(colli);
}

bool Coin::Start()
{
	//プレイヤーのインスタンスを探す。
	player = FindGO<Player>("player");
	//ゲーム1_1のインスタンスを探す。
	game = FindGO<Game>("game");
	//ゲーム1_2のインスタンスを探す。
	game2 = FindGO<Game2>("game2");
	//生成するオブジェクトの処理を軽くする。
	modelRender.SetRaytracingWorld(false);
	modelRender.Init("Assets/modelData/coin.tkm");

	//コインの音を読み込む。
	g_soundEngine->ResistWaveFileBank(5, "Assets/sound/coin_get.wav");

	//コリジョンの作成。
	colli = NewGO<CollisionObject>(0);
	colli->CreateSphere(Vector3(0.0f, 0.0f, 0.0f), Quaternion::Identity, 50.0f);
	colli->SetIsEnableAutoDelete(false);
	colli->SetName("coin");
	colli->SetPosition(position);

	return true;
}

void Coin::Update()
{
	//移動速度。
	position.x -= 10.0f;

	if (position.x <= -1500)
	{
		DeleteGO(this);
	}

	//プレイヤーがコインをとったとき。
	if (player->get==1)
	{
		player->get = 0;
		//プレイヤーがコインをゲットしたら。
			//コインの音を再生する。
			Coinget = NewGO<SoundSource>(5);
			Coinget->Init(5);
			Coinget->SetVolume(1.2f);
			Coinget->Play(false);
		DeleteGO(this);
	}

	colli->SetPosition(position);

	modelRender.SetPosition(position);

	modelRender.Update();
}

void Coin::Render(RenderContext& rc)
{
	modelRender.Draw(rc);
}

