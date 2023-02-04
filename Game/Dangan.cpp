#include "stdafx.h"
#include "Dangan.h"
#include "Player.h"
#include "GameCamera.h"
#include "Game.h"
#include "Game2.h"
#include "Numberhouse.h"



Dangan::Dangan()
{

}

Dangan::~Dangan()
{
	DeleteGO(colli);
}

bool Dangan::Start()
{
	player = FindGO<Player>("player");
	//ゲーム1_1のインスタンスを探す。
	game = FindGO<Game>("game");
	//ゲーム1_2のインスタンスを探す。
	game2 = FindGO<Game2>("game2");
	
	numberhouse = FindGO<Numberhouse>("numberhouse");

	//コリジョンの作成。
	colli = NewGO<CollisionObject>(0);
	colli->CreateSphere(Vector3(0.0f,-20.0f, 0.0f), Quaternion ::Identity, 5.0f);
	colli->SetIsEnableAutoDelete(false);
	colli->SetName("dangan");
	colli->SetPosition(position);

	//生成するオブジェクトの処理を軽くする。
	modelRender.SetRaytracingWorld(false);
	modelRender.Init("Assets/modelData/dangan.tkm");

	stagenumber = numberhouse->stagenumber;
	

	if (stagenumber == 4) {
		modelRender.SetRotation(rotation);
		colli->SetRotation(rotation);
	}

	return true;

}


 void Dangan::Update()
 {
	 collision();
	 
	 if (stagenumber == 4)
	 {
		 //弾丸の速度。
		 position.z += 50.0f;
	 }
	 else
	 {
		 //弾丸の速度。
		 position.x += 50.0f;
	 }
	
	
	 colli->SetPosition(position);

	 //プレイヤーから弾丸のベクトルを計算。
	 Vector3 diff = player->position - position;
	 //ベクトルの長さが2000.0fより大きくなったら。
	if (diff.Length() >= 2000.0f)
	 {
		 //弾丸を消す。
		 DeleteGO(this);
	 }

	//絵描きさんに座標を教える。
	modelRender.SetPosition(position);
	 modelRender.Update();
 }

 //enemy01との当たり判定。
 void Dangan::collision()
 {
	 //enemy01のコリジョンを取得する。
	 const auto& collisions = g_collisionObjectManager->FindCollisionObjects("enemy_eye");
	                         
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
	
	 //boss01_downのコリジョンを取得する。
	 const auto& collisions_b12 = g_collisionObjectManager->FindCollisionObjects("boss01_down");

	 //collisionの配列をfor文で回す。
	 for (auto collision : collisions_b12)
	 {
		 //設定したコリジョンが衝突したか判定する。
		 if (collision->IsHit(colli))
		 {
			 //自身を破壊する。
			 DeleteGO(this);
		 }
	 }
	 //boss02のコリジョンを取得する。
	 const auto& collisions_b2_up = g_collisionObjectManager->FindCollisionObjects("up");

	 //collisionの配列をfor文で回す。
	 for (auto collision : collisions_b2_up)
	 {
		 //設定したコリジョンが衝突したか判定する。
		 if (collision->IsHit(colli))
		 {
			 //自身を破壊する。
			 DeleteGO(this);
		 }
	 }
	 //boss02のコリジョンを取得する。
	 const auto& collisions_b2_center = g_collisionObjectManager->FindCollisionObjects("center");

	 //collisionの配列をfor文で回す。
	 for (auto collision : collisions_b2_center)
	 {
		 //設定したコリジョンが衝突したか判定する。
		 if (collision->IsHit(colli))
		 {
			 //自身を破壊する。
			 DeleteGO(this);
		 }
	 }
	 //boss02のコリジョンを取得する。
	 const auto& collisions_b2_down = g_collisionObjectManager->FindCollisionObjects("down");

	 //collisionの配列をfor文で回す。
	 for (auto collision : collisions_b2_down)
	 {
		 //設定したコリジョンが衝突したか判定する。
		 if (collision->IsHit(colli))
		 {
			 //自身を破壊する。
			 DeleteGO(this);
		 }
	 }
	 //boss03のコリジョンを取得する。
	 const auto& collisions_b3 = g_collisionObjectManager->FindCollisionObjects("boss03");

	 //collisionの配列をfor文で回す。
	 for (auto collision : collisions_b3)
	 {
		 //設定したコリジョンが衝突したか判定する。
		 if (collision->IsHit(colli))
		 {
			 //自身を破壊する。
			 DeleteGO(this);
		 }
	 }
 }

 void Dangan::Render(RenderContext& rc)
 {
	 modelRender.Draw(rc);
 }