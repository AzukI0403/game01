# UNIVESE PILOT

河原電子ビジネス専門学校  
ゲームクリエイター科1年　国宇雄飛

# 目次
- 紹介動画
- 作品概要  
- 操作説明  
- ボス紹介
- こだわったところ

# 1.紹介動画
[![UNIVESE PILOT](https://img.youtube.com/vi/5Qo3xKn76B4/0.jpg)](https://www.youtube.com/watch?v=5Qo3xKn76B4)  

# 2.作品概要
- UNIVRSE PILOT

1-1、1-2、1-3の3つのステージが存在し、それぞれのステージのボスを倒してスコアを獲得し、より高いランクを目指すシューティングゲームです。

- 制作人数  
1人  
- 制作期間  
2022年5月~2022年12月  
- ゲームジャンル  
シューティングゲーム  
- プレイ人数  
　1人  
- 使用言語  
　C++  
- 開発環境  
  + エンジン  
k2Engine(学校内製のエンジン)  
  + 使用したツール  
Visual Studio 2022  
3ds MAX  
Adobe Photoshop2023  
Effekseer  
  + 音源  
Audiostock

# 3.担当ソースコード
- BackGround.h、BackGround.cpp  
1-3のボスステージの背景の処理。  
- Bariaｈ、Baria.cpp  
バリア、スーパーバリアの処理。
- Boss01.h、Boss01.cpp  
1-1のボスの処理。  
- Boss02.h、Boss02.cpp  
1-2のボスの処理。  
- Boss03.h、Boss03.cpp  
1-3のボスの処理。  
- Box1_1.h、Box1_1.cpp  
ステージ選択画面の1-1のオブジェクトの処理。  
- Box1_2.h、Box1_2.cpp  
ステージ選択画面の1-2のオブジェクトの処理。  
- Box1_3.h、Box1_3.cpp  
ステージ選択画面の1-3のオブジェクトの処理。  
- Coin.h、Coin.cpp  
コインの処理。
- Dangan.h、Dangan.cpp  
プレイヤーの打つ弾の処理。  
- Enemy_bomb.h、Enemy_bomb.cpp  
1-3のボスが生成するボムの処理。  
- Enemy01.h、Enemy01.cpp  
一つ目のエネミーの処理。  
- Enemy02.h、Enemy02.cpp  
殻のついたエネミーの処理。  
- Explanation.h、Explanation.cpp  
操作説明画面、アイテム説明画面の処理。  
- Game.h、Game.cpp  
ステージ1-1の処理。
- Game_final.h、Game_final.cpp  
ステージ1-3のボスステージの処理。  
- Game2.h、Game2.cpp  
ステージ1-2の処理。  
- Game3.h、Game3.cpp  
ステージ1-3のボスステージ以外の処理。  
- GameCamera.h、GameCamera.cpp  
1-1、1-2、1-3のカメラの処理。  
- GameCamera_sc.h、GameCamera_sc.cpp  
ステージ選択画面のカメラの処理。  
- Gameover.h、Gameover.cpp  
ゲームオーバー画面の処理。  
- Gamestart.h、Gamestart.cpp  
タイトル画面の処理。  
- GameUI.h、GameUI.cpp  
1-1のUIの処理。  
- GameUI2.h、GameUI2.cpp
1-2のUIの処理。  
- GameUI3.h、GameUI3.cpp  
1-3のUIの処理。  
- Kyuen.h、Kyuen.cpp  
アイテムカプセルの処理。  
- Masingan.h、Masingan.cpp  
マシンガンの処理。  
- Numberhouse.h、Numberhouse.cpp  
挑戦しているステージのナンバーを取得するクラス。  
- Player.h、Player.cpp  
プレイヤーの処理。  
- Repair.h、Repair.cpp  
リペアキットの処理。  
- Result.h、Result.cpp  
リザルト画面の処理。  
- Sc_bg.h、Sc_bg.cpp  
ステージ選択画面の背景の処理。  
- SceneChangeDoor.h、SceneChangeDoor.cpp  
ステージを選択したしたときや、ステージ1-3のボスステージへの切り替　　わりの際に画像を生成する処理。  
- Scoreboard.h、Scoreboard.cpp  
ステージ選択画面のステージのランクを示したオブジェクトの処理。  
- Tama.h、Tama.cpp  
エネミーが打つ弾の処理。  
- Tama_big.h、Tama_big.cpp  
ステージ1-2のボスの打つ大きな弾の処理。  
- Tama_tuibi.h、Tama_tuibi.cpp
エネミーが打つプレイヤーを追尾する弾の処理。  
- Walls.h、Walls.cpp  
ボスステージ以外のステージの背景の処理。 

# 4.操作説明　
![sousasetumei](UNIVESEPILOT/sousasetumei.png)

# 5.ボス紹介
### 5.1　1-1のボス　　
１－１のボスの行動は３つあります。１つ目は、拡散弾で複数の弾をランダムな場所に発射します。  
![1-1kakusan](UNIVESEPILOT/1-1boss_kakusann.png)
２つ目は追尾弾で、弾を生成したときに一度だけボスからプレイヤーに向かうベクトルを計算して正規化し、10倍して移動させています。  
![1-1tuibi](UNIVESEPILOT/1-1boss_tuibi.png)
３つ目はかみつき攻撃です。ボスからプレイヤーに向かうベクトルを計算し、そのベクトルを正規化し16倍してボスを移動させています。
![1-1bite](UNIVESEPILOT/1-1boss_bite.png)
***
### 5.2　1-2のボス
１－２のボスの行動は３つあります。１つ目は、ボス３体のランダムで１体が大きな弾を前方に打つのを何度か繰り返します。  
![1-2tama](UNIVESEPILOT/1-2boss_tama.png)
２つ目は、追尾弾です。上から順番に追尾弾を打ちますが、下の１体は生成されてから何度かボスからプレイヤーに向かうベクトルを計算させて、しばらくの間プレイヤーを追いかけます。  
[![1-2boss_tuibi](https://img.youtube.com/vi/CMZXqRSW60U/0.jpg)](https://www.youtube.com/watch?v=CMZXqRSW60U)  
３つ目は突撃です。３体のボスが順番にプレイヤーに向かって突撃してきて、何度か繰り返します。  
![1-2totugeki](UNIVESEPILOT/1-2boss_totugeki.png)
***
### 5.3　1-3のボス
１－３のボスの行動は５つあります。１つ目は拡散弾です。　　
![1-3boss_kakusann](UNIVESEPILOT/1-3boss_kakusann.png)  
２つ目は追尾弾です。打ち出す全ての弾が生成されてからしばらくの間プレイヤーを追いかけます(黒い線で囲んだものが追尾弾)。  
![1-3boss_kakusann](UNIVESEPILOT/1-3boss_tuibi.png)  
３つ目はボム生成です。ボムのXY座標をランダムに決めて複数生成し、プレイヤーと同じZ軸に移動させます。ボスのHPによってボムの生成数が変わります。  
▼ボスのHPが31%以上のとき
![1-3boss_kakusann](UNIVESEPILOT/1-3boss_bomb1.png)  
▼ボスのHPが30%以下のとき
![1-3boss_kakusann](UNIVESEPILOT/1-3boss_bomb2.png)  
４つ目は回転攻撃です。ボスのZ座標をプレイヤーのZ座標と同じにして、自身を回転させながら画面を横切って攻撃します。画面上側か下側かランダムに決めて２回行動します。この行動を行う前は必ずボムを生成します。  

５つ目はビーム攻撃です。ボスのHPが30%を切った時に強制的に行う行動です。ビームを打つ行動をしている間はダメージを受けません。  
[![1-3boss_beam](https://img.youtube.com/vi/-vO1edqVciM/0.jpg)](https://www.youtube.com/watch?v=-vO1edqVciM)  


# 6.こだわったところ
###  6.1　ステージ選択画面のランク表示  
ステージ選択画面で、挑戦したステージのランクを表示するために、画面が切り替わるたびにそれぞれのステージのランクを示す値を次に生成する画面のクラスの値に代入しています。
![stagecelect](UNIVESEPILOT/stage_celect.png) 

### 6.2　プレイヤーを追尾するビーム  
１-３のボスがビームエフェクトを再生し始めたら、ボスの座標からプレイヤーまでのベクトルを計算します。次に、(0.0f,0.0f,0.0f)に設定したビームエフェクト用のベクトルNewdiffのX軸を4.0ずつ、Y軸を2.5ずつ、計算したベクトルより小さい間増やして正規化したものをmoveSpeedとします。そして、moveSpeedのX軸とZ軸をatan2関数でY軸の角度に変換してangleに代入し、angleを元にY軸回りの回転クォータニオンを作成しました。Y軸とZ軸で同様の処理を行いX軸回りの回転クォータニオンを作成し、２つのクォータニオンを乗算し、ビームを回転させプレイヤーに徐々に近づくようにしました。 
![beam](UNIVESEPILOT/setumei.png)
このステージでは、ボスがビームを打った時に1度きりのスーパーバリアを使用してビームを無効化できます。
ですが、ある程度ステージクリアが難しくなるようにしたかったため、ビームエフェクト用のベクトルNewdiffが計算したベクトルより大きくなったら、常に計算したベクトルを代入して、プレイヤーにビームが当たり続けるようにしました。

### 6.3　1-3のボスステージ  
ステージの１-３のボスは、視点を変えてエネミーが正面に見えるようにして迫力を出しクライマックス感を演出しました。ボスの見た目をコアのような見た目にして他のエネミー達を束ねるボスのようにしました。  
▼1-3のボスステージ以外のステージ  
![1-1](UNIVESEPILOT/1-1.png)  
▼1-3のボスステージ  
![1-1](UNIVESEPILOT/1-3_final.png)  

### 6.4　ステージ選択画面からステージ画面への移行  
ステージを選択した後に画面上下の扉が閉まって、開いた時にステージの画面が出るようにして、出撃しているように感じるようにしました。  
▼ステージ選択画面からステージ画面に移った画面  
[![screen](https://img.youtube.com/vi/rz5LT8hzspY/0.jpg)](https://www.youtube.com/watch?v=rz5LT8hzspY)