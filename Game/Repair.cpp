#include "stdafx.h"
#include "Repair.h"
#include "Game.h"
#include "Player.h"
#include "Game2.h"
#include "Game3.h"
#include "graphics/effect/EffectEmitter.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
#include "Numberhouse.h"


Repair::Repair()
{
	
}

Repair::~Repair()
{
	DeleteGO(colli);
}

bool Repair::Start()
{
	//プレイヤーのインスタンスを探す。
	player = FindGO<Player>("player");
	//ゲーム1_1のインスタンスを探す。
	game = FindGO<Game>("game");
	//ゲーム1_2のインスタンスを探す。
	game2 = FindGO<Game2>("game2");
	//ゲーム1_2のインスタンスを探す。
	game3 = FindGO<Game3>("game3");
	numberhouse = FindGO<Numberhouse>("numberhouse");

	//生成するオブジェクトの処理を軽くする。
	modelRender.SetRaytracingWorld(false);
	modelRender.Init("Assets/modelData/repair.tkm");

	//選択したときの音を読み込む。
	g_soundEngine->ResistWaveFileBank(10, "Assets/sound/repair.wav");

	//エフェクトを読み込む。
	EffectEngine::GetInstance()->ResistEffect(4, u"Assets/effect/effectsprite/Recovery.efk");

	//コリジョンの作成。
	colli = NewGO<CollisionObject>(0);
	colli->CreateCapsule(Vector3(0.0f, 10.0f, 0.0f), Quaternion(90.0f,-35.0f,0.0f,0.0f), 23.0f,120.0f);
	colli->SetIsEnableAutoDelete(false);
	colli->SetName("repair");
	colli->SetPosition(position);
	
	return true;
}

void Repair::Update()
{
	if (player->repairget >= 1)
	{
		player->playerHp += 50;
		//エフェクトの再生。
		Kaihuku();
		//プレイヤーのHPが100を超えるなら、超えないようにする。
		if (player->playerHp >= 100)
		{
			player->playerHp = 100;
		}
		player->repairget = 0;
		player->one = 0;

		//自身を消す。
		DeleteGO(this);
	}
	
	//移動速度。
	position.x -= 8.0f;

	//消去する条件。
	//画面外に出たら。
	if (position.x <= -1100)
	{
		player->one = 0;

		int stagenumber=numberhouse->stagenumber;
		//画面外に出たということはHPを回復していないので、limitを１つ減らす(元に戻す)。
		switch (stagenumber)
		{
		case 1:
			game->repairtime = 0;
			game->limit--;
			break;
		case 2:
			game2->repairtime = 0;
			game2->limit--;
			break;
		case 3:
			game3->repairtime = 0;
			game3->limit--;
			break;

		default:
			break;
		}

		DeleteGO(this);
	}

	colli->SetPosition(position);
	//絵描きさんに座標を教える。
	modelRender.SetPosition(position);
	modelRender.Update();
}



void Repair::Kaihuku()
{
	kaifuku = NewGO<SoundSource>(10);
	kaifuku->Init(10);
	kaifuku->SetVolume(1.2f);
	kaifuku->Play(false);

	EffectEmitter* effectEmitter;
	effectEmitter = NewGO<EffectEmitter>(4);
	effectEmitter->Init(4);
	effectEmitter->SetScale({ 50.0f,40.0f,50.0f });
	effectEmitter->SetPosition(player->position);
	effectEmitter->Play();
}

void Repair::Render(RenderContext& rc)
{
	modelRender.Draw(rc);
}
