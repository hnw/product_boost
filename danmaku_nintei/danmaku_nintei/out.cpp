#include "GV.h"

//敵の当たり判定範囲
int enemy_range = 16;

//当たり判定
//ショットの座標:1  当たりを判定する物体:2
int out_judge(double x1, double y1, double x2, double y2,
              double range1, double range2, double spd1,double angle1){
    int j;
    double x=x1-x2;//敵と自機ショットとの距離
    double y=y1-y2;
    //敵の当たり判定と自機ショットの当たり判定の合計範囲
    double r=range1+range2;
    //中間を計算する必要があれば
    if(spd1>r){
        //１フレーム前にいた位置を格納する
        double pre_x=x1+cos(angle1+PI)*spd1;
        double pre_y=y1+sin(angle1+PI)*spd1;
        double px,py;
        for(j=0;j<spd1/r;j++){//進んだ分÷当たり判定分ループ
            px=pre_x-x2;
            py=pre_y-y2;
            if(px*px+py*py<r*r)
                return 1;
            pre_x+=cos(angle1)*r;
            pre_y+=sin(angle1)*r;
        }
    }
    if(x*x+y*y<r*r)//当たり判定内なら
        return 1;//当たり
    return 0;
}

//自機と敵ショットが当たったかどうかを判定する
int out_judge_enemyshot(int n){
	if(bullet[n].cnt>0){//ショットの軌道が１度でも計算されていたら
		int knd = (bullet[n].state==5) ? 0 : bullet[n].knd;	//詐欺判定

		if(type == 0){
			if(out_judge(
				bullet[n].x,bullet[n].y,ch.x,ch.y,
				bullet_info[knd].range,CRANGE-1.0,
				bullet[n].spd,bullet[n].angle
				)){
					return 1;
			}
		}
		else{
			if(out_judge(
				bullet[n].x,bullet[n].y,ch.x,ch.y,
				bullet_info[knd].range,CRANGE,
				bullet[n].spd,bullet[n].angle
				)){
					return 1;
			}
		}
	}
	return 0;
}

//自機と敵ショットがグレイズしているかどうかを判定する
int out_graze_enemyshot(int n){
    if(bullet[n].cnt>0){//ショットの軌道が１度でも計算されていたら
		int knd = (bullet[n].state==5) ? 0 : bullet[n].knd;	//詐欺判定

        if(out_judge(
            bullet[n].x,bullet[n].y,ch.x,ch.y,
            bullet_info[knd].range,CRANGE11,
            bullet[n].spd,bullet[n].angle
            )){
                return 1;
        }
    }
    return 0;
}

//自機と敵が当たったかどうかを判断する
int out_judge_enemy(){
	if(type == 0){
		if(out_judge(
			enemy.x,enemy.y,ch.x,ch.y,
			enemy_range,CRANGE-1.5,
			0,0
			)){
				return 1;
		}
	}
	else{
		if(out_judge(
			enemy.x,enemy.y,ch.x,ch.y,
			enemy_range,CRANGE,
			0,0
			)){
				return 1;
		}
	}
	return 0;
}

//敵ショットと自機との処理
void enemyshot_and_ch(){
	int n;
	double dif[5]={1.5,1.0,0.75,0.5,0.3};//ゲージ回復量の難易度補正
	double typ[3]={1.0,1.5,1.0};	//ゲージ回復量の自機タイプ補正
	double dtyp[3]={1.0,0.8,1.0};	//低空ゲージ減少量の自機タイプ補正

	if(ch.flag==1){
		for(n=0;n<BULLET_MAX;n++){//弾総数
			if(bullet[n].flag==1){//弾が登録されていたら
				double state = (bullet[n].state==3) ? 0.7 : 1.0;	//ワインダー・自機狙いなどのダメージ減衰補正
				state = (bullet[n].state==4)		? 1.3 : state;	//大弾などのダメージ増加補正

				if(out_judge_enemyshot(n)==1){//自機にその弾が接触していたら
					bullet[n].flag=0;//弾を消す
					spell_flag=1;	//スペル取得失敗判定
					if(ch.percent <= 30.0){
						ch.percent-=(4.0*state*dtyp[type]);	//低空補正
						se_flag[10]=1;
					}
					else{
						ch.percent-=7.0*state;
						se_flag[1]=1;
					}
				}
				if(out_graze_enemyshot(n)==1){//自機にその弾がグレイズしていたら
					if(bullet[n].gflag==0){
						ch.graze++;
							ch.percent+=(0.5*dif[stage]*typ[type]);
						se_flag[2]=1;
						bullet[n].gflag=1;
					}
				}
			}
		}
	}
}

//敵と自機との処理
void enemy_and_ch(){
	if(ch.flag==1){
		if(enemy.flag!=0){
			if(out_judge_enemy()==1){
				ch.percent-=1.0;
				spell_flag=1;	//スペル取得失敗判定
				if(ch.percent <= 30.0)
					se_flag[10]=1;
				else
					se_flag[1]=1;
			}
		}
	}
}



//当たり判定メイン
void out_main(){
    enemyshot_and_ch();//敵ショットと自機との処理
	enemy_and_ch();//敵と自機との処理
}