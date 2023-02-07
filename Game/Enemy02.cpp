#include "stdafx.h"
#include "Enemy02.h"
#include "Game.h"
#include "Dangan.h"
#include "Player.h"
#include "Tama.h"
#include "Tama_tuibi.h"
#include "Game2.h"
#include "Game3.h"
#include "Numberhouse.h"
#include "Baria.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
#include "graphics/effect/EffectEmitter.h"

bool Enemy02::Start()
{

	//生成するオブジェクトの処理を軽くする。
	modelRender_eye.SetRaytracingWorld(false);
	modelRender_eye.Init("Assets/modelData/shell_eye.tkm");
	modelRender_up.SetRaytracingWorld(false);
	modelRender_up.Init("Assets/modelData/shell_up.tkm");
	modelRender_down.SetRaytracingWorld(false);
	modelRender_down.Init("Assets/modelData/shell_down.tkm");

	//やられたときの音を読み込む。
	g_soundEngine->ResistWaveFileBank(2, "Assets/sound/enemy_death.wav");

	//エフェクトを読み込む。
	EffectEngine::GetInstance()->ResistEffect(0, u"Assets/effect/explosion.efk");

	//コリジョンの作成。
	colli = NewGO<CollisionObject>(0);
	colli->CreateSphere(Vector3(0.0f, 0.0f, 0.0f), Quaternion::Identity, 30.0f);
	colli->SetIsEnableAutoDelete(false);
	colli->SetName("enemy02");
	colli->SetPosition(position);

	//ゲーム1_1のインスタンスを探す。
	game = FindGO<Game>("game");
	//ゲーム1_2のインスタンスを探す。
	game2 = FindGO<Game2>("game2");
	player = FindGO<Player>("player");
	//ゲーム1_3のインスタンスを探す。
	game3 = FindGO<Game3>("game3");
	//バリアのインスタンスを探す。
	baria = FindGO<Baria>("baria");
	//Numberhouseのインスタンスを探す。
	numberhouse = FindGO<Numberhouse>("numberhouse");
	stagenumber = numberhouse->stagenumber;

	if (numberhouse->stagenumber == 3)
	{
		tamachange = 1;
	}

	position_up = position;
	position_down = position;

	return true;
}

Enemy02::Enemy02()
{

}

Enemy02::~Enemy02()
{
	DeleteGO(colli);
}

void Enemy02::Update()
{
	//画面左に移動するとき
	if (change == 1)
	{
		Move2();
	}
	//画面右に移動するとき
	else
	{
		Move();
	}

	Rotation();

	if (attackstate == 1)
	{
		Attack();
	}
	
	if(position.x<=900)Collision();

	colli->SetPosition(position);
	modelRender_eye.SetPosition(position);
	modelRender_up.SetPosition(position_up);
	modelRender_down.SetPosition(position_down);
	modelRender_eye.Update();
	modelRender_up.Update();
	modelRender_down.Update();
}

void Enemy02::Move()
{
	timer--;
	
	if (timer <= -100)
	{
		position.x += 10.0f;
		position_up.x += 10.0f;
		position_down.x += 10.0f;
		if (position.x >= 1300)
		{
			Dead();
			DeleteGO(this);
		}
	}

	//position.xが800より大きいなら。
	else if (position.x >= 800)
		{
			//移動速度。
			position.x -= 10.0f;
			position_up.x -= 10.0f;
			position_down.x -= 10.0f;
		}
		
		//stopstateが1のとき、shellが開いている、閉じている状態を維持する。
		if (stopstate == 1)
		{
			opentimer--;
			
			if (opentimer > 0)
			{
				return;
			}
			else if (opentimer <= 0)
			{
				opentimer = 100;
				stopstate = 0;
			}
		}

		//shell_upの上下移動。
		//shellを開く。
		if (upstate == 0)
		{
			gardstate = 0;
			//上に移動する。
			position_up.y += 2.0f;
			//下に移動する。
			position_down.y -= 2.0f;
			
		}
		//shellを閉じる。
		if (upstate == 1)
		{
			//下に移動する。
			position_up.y -= 2.0f;
			//上に移動する。
			position_down.y += 2.0f;
			
		}

		//shell_upがfirstPosition_up.xより大きくなったら(shellが開いたら)。
		if (position_up.y >= firstPosition_up.y + 60)
		{
			upstate = 1;
			stopstate = 1;
			attackstate = 1;
			gardstate = 0;
		}
		//shell_upがfirstPosition_up.xより小さくなったら(shellが閉じたら)。
		if (position_up.y <= firstPosition_up.y)
		{
			upstate = 0;
			stopstate = 1;
			attackstate = 0;
			gardstate = 1;
		}

	modelRender_eye.SetPosition(position);
	modelRender_up.SetPosition(position_up);
	modelRender_down.SetPosition(position_down);
}

//game2がenemy02を生成し、change=1だったとき。
void Enemy02::Move2()
{
	timer--;
	if (timer <= 0)
	{
		position.x -= 10.0f;
		position_up.x -= 10.0f;
		position_down.x -= 10.0f;
		if (position.x <= -1200)
		{
			Dead();
			DeleteGO(this);
		}
	}

	//定位置への移動。
	//position.xが800より大きいなら。
	if (position.x >= -800)
	{
		//移動速度。
		position.x -= 10.0f;
		position_up.x -= 10.0f;
		position_down.x -= 10.0f;
	}

	//stopstateが1のとき、shellが開いている、閉じている状態を維持する。
	if (position.x <= -750)
	{
		if (stopstate == 1)
		{
			opentimer--;

			if (opentimer > 0)
			{
				return;
			}
			else if (opentimer <= 0)
			{
				opentimer = 100;
				stopstate = 0;
			}
		}

		//shell_upの上下移動。
		//shellを開く。
		if (upstate == 0)
		{
			gardstate = 0;
			//上に移動する。
			position_up.y += 2.0f;
			//下に移動する。
			position_down.y -= 2.0f;

		}
		//shellを閉じる。
		if (upstate == 1)
		{
			//下に移動する。
			position_up.y -= 2.0f;
			//上に移動する。
			position_down.y += 2.0f;
		}

		//shell_upがfirstPosition_up.xより大きくなったら(shellが開いたら)。
		if (position_up.y >= firstPosition_up.y + 60)
		{
			upstate = 1;
			stopstate = 1;
			attackstate = 1;
			gardstate = 0;
		}
		//shell_upがfirstPosition_up.xより小さくなったら(shellが閉じたら)。
		if (position_up.y <= firstPosition_up.y)
		{
			upstate = 0;
			stopstate = 1;
			attackstate = 0;
			gardstate = 1;
		}
	}

	modelRender_eye.SetPosition(position);
	modelRender_up.SetPosition(position_up);
	modelRender_down.SetPosition(position_down);
}


void Enemy02::Rotation()
{
	if (fabsf(position.x) < 0.001f
		&& fabsf(position.z) < 0.001f) {
		//m_moveSpeed.xとm_moveSpeed.zの絶対値がともに0.001以下ということは
		//このフレームではキャラは移動していないので旋回する必要はない。
		return;
	}
	//atan2はtanθの値を角度(ラジアン単位)に変換してくれる関数。
	//m_moveSpeed.x / m_moveSpeed.zの結果はtanθになる。
	//atan2を使用して、角度を求めている。
	//これが回転角度になる。
	float angle = atan2(-position.x, position.z);
	//atanが返してくる角度はラジアン単位なので
	//SetRotationDegではなくSetRotationを使用する。
	rotation.SetRotationY(-angle);

	//回転を設定する。
	modelRender_eye.SetRotation(rotation);

	//プレイヤーの前ベクトルを計算する。
	forward = Vector3::AxisZ;
	rotation.Apply(forward);
}

//玉を打つ処理。
void Enemy02::Attack()
{
	if (position.x <= 800)
	{
		tamatime += 1;
		if (tamatime == 70)
		{
				Tama_tuibi* tama_tuibi = NewGO<Tama_tuibi>(0, "tama_tuibi");
				tama_tuibi->position = position;
				tama_tuibi->firstposition = tama_tuibi->position;
				if (tamachange == 1)
				{
					//玉のパターンを変える。
					tama_tuibi->change = 1;
				}
				tamatime = 0;
		}
	}

}

//弾丸との当たり判定の処理。
 void Enemy02::Collision()
{
	//danganのコリジョンを取得する。
	const auto& collisions = g_collisionObjectManager->FindCollisionObjects("dangan");
	//collisionの配列をfor文で回す。
	for (auto collision : collisions)
	{
		//設定したコリジョンと衝突したか判定する。
		if (collision->IsHit(colli))
		{
			if (gardstate == 0)
			{
				//敵を倒した数を増やす。
				player->downcount += 1;
				Dead();
				//やられたときの音を再生する。
				death = NewGO<SoundSource>(2);
				death->Init(2);
				death->SetVolume(1.2f);
				death->Play(false);

				EffectEmitter* effectEmitter = NewGO<EffectEmitter>(0);
				effectEmitter->Init(0);
				effectEmitter->SetScale({ 10.0f,10.0f,10.0f });
				effectEmitter->SetPosition(position);
				effectEmitter->Play();
				//自身を破壊する。
				DeleteGO(this);
			}
			
		}
	}

	//danganのコリジョンを取得する。
	const auto& collisions_p = g_collisionObjectManager->FindCollisionObjects("player");
	//collisionの配列をfor文で回す。
	for (auto collision : collisions_p)
	{
		//設定したコリジョンと衝突したか判定する。
		if (collision->IsHit(colli))
		{
			if (gardstate == 0)
			{
				//ぶつかっただけならスコアには加えない。
				//player->downcount += 1;
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

	//bariaのコリジョンを取得する。
	const auto& collisions_b = g_collisionObjectManager->FindCollisionObjects("baria");
	//collisionの配列をfor文で回す。
	for (auto collision : collisions_b)
	{
		//設定したコリジョンと衝突したか判定する。
		if (collision->IsHit(colli))
		{
			if (gardstate == 0)
			{
				//敵を倒した数を増やす。
				//player->downcount += 1;
				Dead();
				//やられたときの音を再生する。
				death = NewGO<SoundSource>(2);
				death->Init(2);
				death->SetVolume(1.2f);
				death->Play(false);

				EffectEmitter* effectEmitter = NewGO<EffectEmitter>(0);
				effectEmitter->Init(0);
				effectEmitter->SetScale({ 10.0f,10.0f,10.0f });
				effectEmitter->SetPosition(position);
				effectEmitter->Play();
				//自身を破壊する。
				DeleteGO(this);
			}

		}
	}
}

//倒されたときの処理。
void Enemy02::Dead()
{
	switch (stagenumber)
	{
	case 1:
			game->dead++;
		break;
	case 2:
			game2->dead++;
		break;
	case 3:
			game3->dead++;
		break;

	default:
		break;
	}
}

void Enemy02::Render(RenderContext& rc)
{
	modelRender_up.Draw(rc);
	modelRender_eye.Draw(rc);
	modelRender_down.Draw(rc);
}