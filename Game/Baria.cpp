#include "stdafx.h"
#include "Baria.h"
#include "Game.h"
#include "Player.h"
#include "Game2.h"
#include "graphics/effect/EffectEmitter.h"

Baria::Baria()
{

}

Baria::~Baria()
{
	DeleteGO(effectEmitter);
	DeleteGO(colli);
}

bool Baria::Start()
{
	//プレイヤーのインスタンスを探す。
	player = FindGO<Player>("player");
	//ゲーム1_1のインスタンスを探す。
	game = FindGO<Game>("game");
	//ゲーム1_2のインスタンスを探す。
	game2 = FindGO<Game2>("game2");
	//生成するオブジェクトの処理を軽くする。
	modelRender.SetRaytracingWorld(false);
	modelRender.IniTranslucent("Assets/modelData/baria.tkm");

	EffectEngine::GetInstance()->ResistEffect(10, u"Assets/effect/effectsprite/suparbaria.efk");


	//コリジョンの作成。
	colli = NewGO<CollisionObject>(0);
	colli->CreateSphere(Vector3(0.0f, 0.0f, 0.0f), Quaternion::Identity, 150.0f);
	colli->SetIsEnableAutoDelete(false);
	colli->SetName("baria");
	colli->SetPosition(position);

	if (SuparBariaState == true)time = 300;

	return true;
}

void Baria::Update()
{
	//time=200
	time--;

	position = player->position;
	
	//コリジョンのポジション。
	Cposition = player->position;
	
	if (SuparBariaState == true)
	{
		effectEmitter = NewGO<EffectEmitter>(10);
		effectEmitter->Init(10);
		effectEmitter->SetScale({ 35.0f,35.0f,35.0f });
		effectEmitter->SetPosition(position);
		effectEmitter->Play();
		SuparBariaState = false;
		SBOK = 1;
	}
	if (SBOK == 1)
	{
		effectEmitter->SetPosition(position);
	}
	

	//バリアを出している時間が0以下になったら。
	if (time <= 0)
	{
		//バリアを出す時間を戻す。
		time = 100;
		//もう一度バリアを出せるようにする。
		player->BB = 0;
		player->SuparBariaState = false;
		DeleteGO(this);
	}

	//絵描きさんに座標を教える。
	modelRender.SetPosition(position);
	colli->SetPosition(Cposition);
	modelRender.Update();
}

void Baria::Render(RenderContext& rc)
{
	modelRender.Draw(rc);
}