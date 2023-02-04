#pragma once
#include "sound/SoundSource.h"

class Enemy01;
class Enemy02;
class Repair;
class Game;
class Coin;
class Kyuen;
class Masingan;
class Tama;
class Baria;
class Tama_tuibi;
class Boss01;
class Game2;
class Boss02;
class Numberhouse;
class Game3;
class Game_final;
class Tama_big;
class Boss03;

class Player:public IGameObject
{
public:
	Player();
	~Player();

	bool Start();
	//更新処理。
	void Update();
	//描画処理。
	void Render(RenderContext& rc);
	//移動処理。
	void Move();
	void DamageUP();
	//回復アイテムの管理。
	void Repairp();
	//コインの管理。
	void CoinGet();
	//救援の管理。
	void KyuenGet();
	//masinganの管理。
	void MasinganG();
	//バリアの管理。
	void BariaG();
	//スーパーバリアの管理。
	void SuparBariaG();
	void SetResultDataToGame();
	void SetResultDataToGame2();
	void SetResultDataToGame3();
	void SetResultDataToGame4();
	
	//メンバ変数。
	Enemy01* enemy01;
	Enemy02* enemy02;
	Repair* repair;
	Game* game;
	Coin* coin;
	Kyuen* kyuen;
	Masingan* masingan;
	Baria* baria;
	Tama_tuibi* tama_tuibi;
	Boss01* boss01;
	Game2* game2;
	Boss02* boss02;
	Numberhouse* numberhouse;
	Game3* game3;
	Game_final* game_final;
	Tama_big* tama_big;
	Boss03* boss03;

	SoundSource* syageki;//弾丸を打ったときの音

	ModelRender modelRender;	//モデルレンダ―。
	Vector3 position;   //プレイヤーの座標。
	Vector3 firstposition;
	Vector3 oldposition = { 0.0f,0.0f,0.0f };
	Vector3 moveSpeed;//移動速度。
	Vector3 oldmoveSpeed;
	Quaternion rotation;  //クォータニオン。
	CollisionObject* colli;

	EffectEmitter* effectEmitter;
	EffectEmitter* effectEmitter_dead;
	EffectEmitter* effectEmitter_attackUP;
	EffectEmitter* effectEmitter_blueright;

	int playerState = 0;	//プレイヤーのステート(状態)を表す変数。
	//加速。
	float kasoku =8;
	//加速したかの判定。
	bool kasokustate = false;
	//加速のクールタイム。
	int cooltime=100;
	//ダメージをくらった後の無敵時間。
    int muteki = 0;
	//HP
	int maxhp = 100;
	int playerHp = 100;
	//1個しかリペアが生成されないようにする。
	int one;
	//ripairの生成する数。
	int limit=0;
	//masinganを取得した後の弾丸。
	int kankaku=1;
	//コイン。
	int get = 0;
	//コインのカウント。
	int getcount = 0;
	//リペア。
	int repairget=0;
	int repairtime = 0;
	//救援。
	int kyuenget = 0;
	//masingan。
	int Mcount = 0;
	int MM = 0;
	//弾丸のダメージを上げるかの判定。
	bool pawerUp = false;
	//攻撃力が上がっている時間。
	int paweruptime = 10;
	int Ptimer = 0;
	//パワーアップのエフェクトを再生しているかの判定。
	int pawerUPeffectState = 0;
	//敵を倒した数。
	int downcount = 0;
	//バリア
	int maxbariapoint = 5;
	int bariapoint=5;
	int BB=0;
	//スーパーバリアのポイント=1
	int SBPoint = 1;
	//スーパーバリアを使ったかの判定。
	bool SuparBariaState = false;
	int SBState = 0;
	//受けるダメージ=10。
	int damage = 10;
	//与えるダメージ=10。
	int attackdamage = 10;
	//ダメージを受けたかどうかの判定。
	int damagestate = 0;
	//モデルを消す=true。
	bool notdraw = false;

	//挑戦しているステージのナンバー。
	//プレイヤーが倒されたときに値を送るステージの判定。
	int stagenumber=0;
	//プレイヤーが倒されたときにエフェクトを再生したかの判定。
	bool DeadEffect = false;
	int find=0;

	int SavePositionTime = 0;
	//スタート時にプレイヤーがとまっている時間。
	//1_1,1_2,1_3=220
	int Stoptime = 220;
	//時間切れになったらtrueにする。
	bool timeover = false;
};

