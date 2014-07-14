#include "GV.h"

//行動パターンのextern宣言
extern void act0();	extern void act1();	extern void act2();

//敵の行動制御
void enemy_act(){
	if(enemy.flag!=0){//その敵のフラグがオンになってたら
		enemy.x+=cos(enemy.ang)*enemy.sp;
		enemy.y+=sin(enemy.ang)*enemy.sp;//三角関数による移動
		enemy.x+=enemy.vx;
		enemy.y+=enemy.vy;//絶対量による移動
		enemy.cnt++;
        enemy.img=3+(enemy.cnt%18)/6;//6フレームごと3パターンでアニメーション
	}
}

//敵処理メイン
void enemy_main(){
    enemy_act();

	//合計フレーム依存で移動パターンの変更
	if(count>=7960 && count<=8060)
		act1();

	else if(count>=9940 && count<=10040)
		act2();

	else if(count>=11920 && count<=12020)
		act1();

	else if(count>=13900 && count<=14000)
		act2();

	else
		act0();
}