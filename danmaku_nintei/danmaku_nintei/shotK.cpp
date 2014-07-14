#include "GV.h"

//低速ばらまき弾
void K0(){
	int t=spcount;
	int k;

	for(int i=0;i<7;i++){
		if((k=shot_search())!=-1){//弾が登録可能なら
			bullet[k].knd	=8;
			bullet[k].angle	=PI2/10*t+PI2/70*i+rang(PI2/140);//角度
			bullet[k].spd	=0.5;//スピード
			bullet[k].vx	=0;
			bullet[k].vy	=0;
			bullet[k].flag	=1;//フラグ
			bullet[k].x		=enemy.x;//座標
			bullet[k].y		=enemy.y;
			bullet[k].col	=GetRand(4);//色
			bullet[k].cnt	=0;//カウンタ
			bullet[k].gflag	=0;
			bullet[k].state	=0;
		}
	}
}

//Spell１｢低速ばらまき弾｣
void shot_K0(){
	int t=spcount;

	if(t>=120){
		K0();

		if(t%8==0)
			se_flag[0]=1;
	}

	for(int i=0;i < BULLET_MAX;i++){
		if(bullet[i].flag==1){
			if(bullet[i].cnt<20){
				bullet[i].spd+=0.025;
			}
		}
	}
}

//低速落下弾
void K1_0(){
	int k;

	for(double i = FX;i<FX+FMX;i+=(30+rang(10))){
		if((k=shot_search())!=-1){//弾が登録可能なら
			bullet[k].knd	=7;
			bullet[k].state =0;
			bullet[k].angle	=0;//角度
			bullet[k].spd	=0;//スピード
			bullet[k].vx	=0;
			bullet[k].vy	=-1;//落下速度
			bullet[k].flag	=1;//フラグ
			bullet[k].x		=i;//座標
			bullet[k].y		=200+rang(90);
			bullet[k].col	=0;//色
			bullet[k].cnt	=0;//カウンタ
			bullet[k].gflag	=0;
		}
	}
}

//中速落下弾
void K1_1(){
	int k;

	for(double i = FX;i<FX+FMX;i+=(35+rang(10))){
		if((k=shot_search())!=-1){//弾が登録可能なら
			bullet[k].knd	=7;
			bullet[k].state =1;
			bullet[k].angle	=0;//角度
			bullet[k].spd	=0;//スピード
			bullet[k].vx	=0;
			bullet[k].vy	=-2;//落下速度
			bullet[k].flag	=1;//フラグ
			bullet[k].x		=i;//座標
			bullet[k].y		=150+rang(60);
			bullet[k].col	=1;//色
			bullet[k].cnt	=0;//カウンタ
			bullet[k].gflag	=0;
		}
	}
}

//高速落下弾
void K1_2(){
	int k;

	for(double i = FX;i<FX+FMX;i+=(40+rang(10))){
		if((k=shot_search())!=-1){//弾が登録可能なら
			bullet[k].knd	=7;
			bullet[k].state =2;
			bullet[k].angle	=0;//角度
			bullet[k].spd	=0;//スピード
			bullet[k].vx	=0;
			bullet[k].vy	=-3;//落下速度
			bullet[k].flag	=1;//フラグ
			bullet[k].x		=i;//座標
			bullet[k].y		=40+rang(30);
			bullet[k].col	=3;//色
			bullet[k].cnt	=0;//カウンタ
			bullet[k].gflag	=0;
		}
	}
}

//Spell２｢三段速落下弾｣
void shot_K1(){
	int t=spcount;

	if(t>=120){
		if((t-120)%45==0){
			K1_0();
		}

		if((t-120)%50==0){
			K1_1();
			se_flag[0]=1;
		}

		if((t-120)%60==0){
			K1_2();
		}
	}

	for(int i=0;i < BULLET_MAX;i++){
		if(bullet[i].flag==1){
			if(bullet[i].cnt<90){
				switch(bullet[i].state){
				case 0:
					bullet[i].vy+=0.03;
					break;
				case 1:
					bullet[i].vy+=0.065;
					break;
				case 2:
					bullet[i].vy+=0.1;
					break;
				}
			}
		}
	}
}

//交差前の全方位弾
void K2(){
	int k;
	double angle=rang(PI);

	for(int j=0;j<2;j++){//途中から２分裂する分
		for(int i=0;i<100;i++){
			if((k=shot_search())!=-1){
				bullet[k].knd    =8;//8番の弾
				bullet[k].angle  =angle+PI2/100*i;
				bullet[k].spd    =2.5;
				bullet[k].vx	=0;
				bullet[k].vy	=0;
				bullet[k].flag   =1;
				bullet[k].x      =enemy.x;
				bullet[k].y      =enemy.y;
				bullet[k].col    =1;
				bullet[k].cnt    =0;
				bullet[k].state  =j;//ステータス。0か1かで回転がかわる
				se_flag[0]=1;//発射音鳴らす
			}
		}
	}
}

//Spell３｢交差弾｣
void shot_K2(){
	int t=spcount;

	if(t>=120){
		if(t<600){
			if(t%60==0){
				K2();
				se_flag[0]=1;
			}
		}

		else if(t<1200){
			if(t%50==0){
				K2();
				se_flag[0]=1;
			}
		}

		else if(t%40==0){
			K2();
			se_flag[0]=1;
		}
	}

	for(int i=0;i<BULLET_MAX;i++){//全弾分
		if(bullet[i].flag>0){//登録されている弾があれば
			if(30<bullet[i].cnt && bullet[i].cnt<120){//30～120カウントなら
				bullet[i].spd-=1.5/90.0;//90カウントかけて1.5減らす
				bullet[i].angle+=(PI/2)/90.0*(bullet[i].state?-1:1);//90カウントかけて90°傾ける
			}
			if(bullet[i].cnt==120)
				bullet[i].state=3;	//ダメージ減少補正
		}
	}
}

//高速ばらまき弾
void K3(){
	int t=spcount;
	int k;

	for(int i=0;i<4;i++){
		if((k=shot_search())!=-1){//弾が登録可能なら
			bullet[k].knd	=7;
			bullet[k].angle	=PI2/10*t+PI2/40*i+rang(PI2/80);//角度
			bullet[k].spd	=3+rang(1);//スピード
			bullet[k].vx	=0;
			bullet[k].vy	=0;
			bullet[k].flag	=1;//フラグ
			bullet[k].x		=enemy.x;//座標
			bullet[k].y		=enemy.y;
			bullet[k].col	=GetRand(4);//色
			bullet[k].cnt	=0;//カウンタ
			bullet[k].gflag	=0;
			bullet[k].state	=0;
		}
	}
}

//Spell４｢高速ばらまき弾｣
void shot_K3(){
	int t=spcount;

	if(t>=120){
		K3();

		if(t%8==0)
			se_flag[0]=1;
	}

	for(int i=0;i < BULLET_MAX;i++){
		if(bullet[i].flag==1){
			if(bullet[i].cnt<80){
				bullet[i].spd*=1.008;
			}
		}
	}
}

//回転ワインダー
void K4_0(double ang){
	int k;

	for(int i=0;i<7;i++){
		if((k=shot_search())!=-1){//弾が登録可能なら
			bullet[k].knd	=8;
			bullet[k].angle	=ang+((PI2/7)*i);//角度
			bullet[k].spd	=5;//スピード
			bullet[k].vx	=0;
			bullet[k].vy	=0;
			bullet[k].flag	=1;//フラグ
			bullet[k].x		=enemy.x;//座標
			bullet[k].y		=enemy.y;
			bullet[k].col	=5;//色
			bullet[k].cnt	=0;//カウンタ
			bullet[k].gflag	=0;
			bullet[k].state	=3;//ダメージ減衰補正
		}
	}
}

//停滞ばらまき弾
void K4_1(){
	int k;

	if((k=shot_search())!=-1){//弾が登録可能なら
		bullet[k].knd	=10;
		bullet[k].angle	=rang(PI2);//角度
		bullet[k].spd	=0.5;//スピード
		bullet[k].vx	=0;
		bullet[k].vy	=0;
		bullet[k].flag	=1;//フラグ
		bullet[k].x		=enemy.x;//座標
		bullet[k].y		=enemy.y;
		bullet[k].col	=0;//色
		bullet[k].cnt	=0;//カウンタ
		bullet[k].gflag	=0;
		bullet[k].state	=3;//ダメージ減衰補正
	}
}

//逆方向ワインダー
void K4_2(double ang2){
	int k;

	for(int i=0;i<10;i++){
		if((k=shot_search())!=-1){//弾が登録可能なら
			bullet[k].knd	=4;
			bullet[k].angle	=ang2+((PI2/10)*i);//角度
			bullet[k].spd	=1.5;//スピード
			bullet[k].vx	=0;
			bullet[k].vy	=0;
			bullet[k].flag	=1;//フラグ
			bullet[k].x		=enemy.x;//座標
			bullet[k].y		=enemy.y;
			bullet[k].col	=1;//色
			bullet[k].cnt	=0;//カウンタ
			bullet[k].gflag	=0;
			bullet[k].state	=0;
		}
	}
}

double K4_ang=0,K4_ang2=0;	//回転ワインダー用角度

//Spell５｢回転ワインダー｣
void shot_K4(){
	int t=spcount;

	if(t>=120){
		if(t%2==0)
			K4_0(K4_ang);

		if(t%10==0)
			K4_1();

		if(t%45==0)
			K4_2(K4_ang2);

		if(t%8==0)
			se_flag[0]=1;

		K4_ang-=PI2/360;
		K4_ang2+=PI2/540;
	}
	else
		K4_ang=0,K4_ang2=0;
}

//自機狙い
void K5_0(){
	int k;

	if((k=shot_search())!=-1){//弾が登録可能なら
		bullet[k].knd	=6;
		bullet[k].angle	=shotatan2();//角度
		bullet[k].spd	=5;//スピード
		bullet[k].vx	=0;
		bullet[k].vy	=0;
		bullet[k].flag	=1;//フラグ
		bullet[k].x		=enemy.x;//座標
		bullet[k].y		=enemy.y;
		bullet[k].col	=0;//色
		bullet[k].cnt	=0;//カウンタ
		bullet[k].gflag	=0;
		bullet[k].state	=3;//ダメージ減衰補正
	}
}

//停滞ばらまき弾
void K5_1(){
	int k;

	if((k=shot_search())!=-1){//弾が登録可能なら
		bullet[k].knd	=11;
		bullet[k].angle	=rang(PI2);//角度
		bullet[k].spd	=1.5+rang(1);//スピード
		bullet[k].vx	=0;
		bullet[k].vy	=0;
		bullet[k].flag	=1;//フラグ
		bullet[k].x		=enemy.x;//座標
		bullet[k].y		=enemy.y;
		bullet[k].col	=GetRand(5);//色
		bullet[k].cnt	=0;//カウンタ
		bullet[k].gflag	=0;
		bullet[k].state	=0;
	}
}

//Spell６｢自機狙い複合弾｣
void shot_K5(){
	int t=spcount;

	if(t>=120){
		if(t%8==0)
			K5_0();

		K5_1();

		if(t%8==0)
			se_flag[0]=1;
	}
}

//大弾全方位弾
void K6(){
	int k;
	double angle=rang(PI);

	for(int i=0;i<15;i++){
		if((k=shot_search())!=-1){//弾が登録可能なら
			bullet[k].knd	=0;
			bullet[k].angle	=angle+PI2/15*i;//角度
			bullet[k].spd	=5;//スピード
			bullet[k].vx	=0;
			bullet[k].vy	=0;
			bullet[k].flag	=1;//フラグ
			bullet[k].x		=enemy.x;//座標
			bullet[k].y		=enemy.y;
			bullet[k].col	=1;//色
			bullet[k].cnt	=0;//カウンタ
			bullet[k].gflag	=0;
			bullet[k].state	=4;//ダメージ増加補正
		}
	}
}

//Spell７｢大弾物量殺し｣
void shot_K6(){
	int t=spcount;

	if(t>=120){
		if(t%26==0){
			K6();
			se_flag[0]=1;
		}
	}

	for(int i=0;i < BULLET_MAX;i++){
		if(bullet[i].flag==1){
			if(bullet[i].cnt<60){
				bullet[i].spd-=0.08;
			}

			if(bullet[i].cnt==60){
				bullet[i].spd	=0.8;
				bullet[i].state	=5;	//詐欺判定化
			}
		}
	}
}

//左右ワインダー
void K7_0(double ang){
	int k;

	for(int i=0;i<12;i++){
		if((k=shot_search())!=-1){//弾が登録可能なら
			bullet[k].knd	=6;
			bullet[k].angle	=ang+((PI2/12)*i);//角度
			bullet[k].spd	=4;//スピード
			bullet[k].vx	=0;
			bullet[k].vy	=0;
			bullet[k].flag	=1;//フラグ
			bullet[k].x		=enemy.x;//座標
			bullet[k].y		=enemy.y;
			bullet[k].col	=0;//色
			bullet[k].cnt	=0;//カウンタ
			bullet[k].gflag	=0;
			bullet[k].state	=3;//ダメージ減衰補正
		}
	}
}

//大弾自機狙い
void K7_1(){
	int k;

	for(int i=0;i<3;i++){
		if((k=shot_search())!=-1){//弾が登録可能なら
			bullet[k].knd	=0;
			bullet[k].angle	=(shotatan2()-PI/4)+(PI/4*i);//角度
			bullet[k].spd	=3;//スピード
			bullet[k].vx	=0;
			bullet[k].vy	=0;
			bullet[k].flag	=1;//フラグ
			bullet[k].x		=enemy.x;//座標
			bullet[k].y		=enemy.y;
			bullet[k].col	=1;//色
			bullet[k].cnt	=0;//カウンタ
			bullet[k].gflag	=0;
			bullet[k].state	=4;//ダメージ増加補正
		}
	}
}

//ランダム落下
void K7_2(){
	int k;

	if((k=shot_search())!=-1){//弾が登録可能なら
		bullet[k].knd	=1;
		bullet[k].angle	=0;//角度
		bullet[k].spd	=0;//スピード
		bullet[k].vx	=rang(1);
		bullet[k].vy	=3+rang(1.5);
		bullet[k].flag	=1;//フラグ
		bullet[k].x		=FX+(FMX/2)+rang(130);//座標
		bullet[k].y		=FY+10;
		bullet[k].col	=5;//色
		bullet[k].cnt	=0;//カウンタ
		bullet[k].gflag	=0;
		bullet[k].state	=0;
	}
}

double K7_ang=-PI/12,K7_vang=-PI/4/75;	//左右ワインダー用角度・角速度

//Spell８｢左右ワインダー｣
void shot_K7(){
	int t=spcount;

	if(t>=120){
		if(t%2==0)
			K7_0(K7_ang);

		if(t%60==0)
			K7_1();

		if(t%4==0)
			K7_2();

		if(t%8==0)
			se_flag[0]=1;

		K7_ang+=K7_vang;
		if(K7_ang>=((PI/4)-(PI/12)) || K7_ang<=(-(PI/4)-(PI/12)))
			K7_vang=-K7_vang;
	}
	else
		K7_ang=-PI/12,K7_vang=-PI/4/90;
}

//横方向の固定弾
void K8_0(int length,double speed,int joge){
	int k;

	for(int i = FX;i<=FX+FMX+10;i+=length){
		if((k=shot_search())!=-1){//弾が登録可能なら
			bullet[k].knd	=7;
			bullet[k].state =0;
			bullet[k].angle	=0;//角度
			bullet[k].spd	=0;//スピード
			bullet[k].vx	=0;
			bullet[k].vy	=(joge)? speed:-speed;//落下速度
			bullet[k].flag	=1;//フラグ
			bullet[k].x		=i;//座標
			bullet[k].y		=(joge)? 0:480;
			bullet[k].col	=1;//色
			bullet[k].cnt	=0;//カウンタ
			bullet[k].gflag	=0;
		}
	}
}

//縦方向の固定弾
void K8_1(int length,double speed,int sayu){
	int k;

	for(int i = FY;i<=FY+FMY+10;i+=length){
		if((k=shot_search())!=-1){//弾が登録可能なら
			bullet[k].knd	=7;
			bullet[k].state =0;
			bullet[k].angle	=0;//角度
			bullet[k].spd	=0;//スピード
			bullet[k].vx	=(sayu)? speed:-speed;
			bullet[k].vy	=0;//落下速度
			bullet[k].flag	=1;//フラグ
			bullet[k].x		=(sayu)? 0:FX+FMX+10;//座標
			bullet[k].y		=i;
			bullet[k].col	=1;//色
			bullet[k].cnt	=0;//カウンタ
			bullet[k].gflag	=0;
		}
	}
}

//spell９｢低速移動禁止＆拘束弾｣
void shot_K8(){
	int t = spcount;

	if(t>=120){
		if(t<1200){
			if((t-300)%60==0){
				K8_0(33,1.8,0);
				K8_1(33,1.5,0);
				se_flag[0]=1;
			}

			if((t-300)%180==0){
				se_flag[11]=1;
			}

			if((t-300)%180==60){
				for(int i=0;i < BULLET_MAX;i++){
					if(bullet[i].flag==1){
						bullet[i].knd=0;	//大弾化
						bullet[i].state=4;	//ダメージ増加補正
					}
				}
				se_flag[8]=1;
			}

			if((t-300)%180==120){
				for(int i=0;i < BULLET_MAX;i++){
					if(bullet[i].flag==1){
						bullet[i].knd=7;
						bullet[i].state=0;	//補正解除
					}
				}
			}
		}
		else{
			if(t==1200){
				bdelete();
				se_flag[8]=1;
			}

			if((t-1200)%50==0){
				K8_0(40,2.5,1);
				K8_1(40,2,1);
				se_flag[0]=1;
			}

			if((t-1260)%120==0){
				se_flag[11]=1;
			}

			if((t-1260)%120==60){
				for(int i=0;i < BULLET_MAX;i++){
					if(bullet[i].flag==1){
						bullet[i].knd=0;	//大弾化
						bullet[i].state=4;	//ダメージ増加補正
					}
				}
				se_flag[8]=1;
			}

			if((t-1260)%120==119){
				for(int i=0;i < BULLET_MAX;i++){
					if(bullet[i].flag==1){
						bullet[i].knd=7;
						bullet[i].state=0;	//補正解除
					}
				}
			}
		}
	}
}

//波紋の全方位弾
void K9(double x,double y){
	int k;
	double angle=rang(PI);

	for(int i=0;i<30;i++){
		if((k=shot_search())!=-1){//弾が登録可能なら
			bullet[k].knd	=8;
			bullet[k].angle	=angle+PI2/30*i;//角度
			bullet[k].spd	=2;//スピード
			bullet[k].vx	=0;
			bullet[k].vy	=0;
			bullet[k].flag	=1;//フラグ
			bullet[k].x		=x+15*cos(bullet[k].angle);//座標
			bullet[k].y		=y+15*sin(bullet[k].angle);
			bullet[k].col	=0;//色
			bullet[k].cnt	=0;//カウンタ
			bullet[k].gflag	=0;
			bullet[k].state	=1;
		}
	}
}

int K9_state=0;	//波紋発射位置変更テーブル

//発射位置設定を含めた波紋の全方位弾
void K9_1(){
	switch(K9_state){
	case 0:
		K9(enemy.x-(FMX/4)+rang(20),enemy.y-50+(rang(25)));
		K9_state=1;
		break;
	case 1:
		K9(enemy.x+(FMX/4)+rang(20),enemy.y+50+(rang(25)));
		K9_state=2;
		break;
	case 2:
		K9(enemy.x-(FMX/4)+rang(20),enemy.y+50+(rang(25)));
		K9_state=3;
		break;
	case 3:
		K9(enemy.x+(FMX/4)+rang(20),enemy.y-50+(rang(25)));
		K9_state=0;
		break;
	}
}

//Spell１０｢波紋疾走｣
void shot_K9(){
	int t=spcount;

	if(t>=120){
		if(t<600){
			if(t%40==0){
				K9_1();
				se_flag[0]=1;
			}

			for(int i=0;i < BULLET_MAX;i++){
				if(bullet[i].flag==1){
					bullet[i].spd+=0.006;
					if(bullet[i].y<FY && bullet[i].state==1){
						bullet[i].angle=-bullet[i].angle;
						bullet[i].state=0;
					}
					if(bullet[i].x<FX && bullet[i].state==1){
						bullet[i].angle=PI/2-(bullet[i].angle-PI/2);
						bullet[i].state=0;
					}
					if(bullet[i].x>FX+FMX && bullet[i].state==1){
						bullet[i].angle=PI/2+(PI/2-bullet[i].angle);
						bullet[i].state=0;
					}
				}
			}
		}

		else if(t<1200){
			if(t%30==0){
				K9_1();
				se_flag[0]=1;
			}

			for(int i=0;i < BULLET_MAX;i++){
				if(bullet[i].flag==1){
					bullet[i].spd+=0.008;
					if(bullet[i].y<FY && bullet[i].state==1){
						bullet[i].angle=-bullet[i].angle;
						bullet[i].state=0;
					}
					if(bullet[i].x<FX && bullet[i].state==1){
						bullet[i].angle=PI/2-(bullet[i].angle-PI/2);
						bullet[i].state=0;
					}
					if(bullet[i].x>FX+FMX && bullet[i].state==1){
						bullet[i].angle=PI/2+(PI/2-bullet[i].angle);
						bullet[i].state=0;
					}
				}
			}
		}

		else{
			if(t%20==0){
				K9_1();
				se_flag[0]=1;
			}

			for(int i=0;i < BULLET_MAX;i++){
				if(bullet[i].flag==1){
					bullet[i].spd+=0.012;
					if(bullet[i].y<FY && bullet[i].state==1){
						bullet[i].angle=-bullet[i].angle;
						bullet[i].state=0;
					}
					if(bullet[i].x<FX && bullet[i].state==1){
						bullet[i].angle=PI/2-(bullet[i].angle-PI/2);
						bullet[i].state=0;
					}
					if(bullet[i].x>FX+FMX && bullet[i].state==1){
						bullet[i].angle=PI/2+(PI/2-bullet[i].angle);
						bullet[i].state=0;
					}
				}
			}
		}
	}
	else
		K9_state=0;
}