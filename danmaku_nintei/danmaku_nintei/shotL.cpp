#include "GV.h"

//低速ばらまき弾
void L0(){
	int t=spcount;
	int k;

	for(int i=0;i<5;i++){
		if((k=shot_search())!=-1){//弾が登録可能なら
			bullet[k].knd	=8;
			bullet[k].angle	=PI2/10*t+PI2/50*i+rang(PI2/100);//角度
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
void shot_L0(){
	int t=spcount;

	if(t>=120){
		L0();

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
void L1_0(){
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
void L1_1(){
	int k;

	for(double i = FX;i<FX+FMX;i+=(30+rang(10))){
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
void L1_2(){
	int k;

	for(double i = FX;i<FX+FMX;i+=(40+rang(15))){
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
void shot_L1(){
	int t=spcount;

	if(t>=120){
		if((t-120)%40==0){
			L1_0();
		}

		if((t-120)%60==0){
			L1_1();
			se_flag[0]=1;
		}

		if((t-120)%80==0){
			L1_2();
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
void L2(){
	int k;
	double angle=rang(PI);

	for(int j=0;j<2;j++){//途中から２分裂する分
		for(int i=0;i<90;i++){
			if((k=shot_search())!=-1){
				bullet[k].knd    =8;//8番の弾
				bullet[k].angle  =angle+PI2/90*i;
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
void shot_L2(){
	int t=spcount;

	if(t>=120){
		if(t<600){
			if(t%60==0){
				L2();
				se_flag[0]=1;
			}
		}

		else if(t<1200){
			if(t%50==0){
				L2();
				se_flag[0]=1;
			}
		}

		else if(t%40==0){
			L2();
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
void L3(){
	int t=spcount;
	int k;

	for(int i=0;i<3;i++){
		if((k=shot_search())!=-1){//弾が登録可能なら
			bullet[k].knd	=7;
			bullet[k].angle	=PI2/10*t+PI2/30*i+rang(PI2/60);//角度
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
void shot_L3(){
	int t=spcount;

	if(t>=120){
		L3();

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
void L4_0(double ang){
	int k;

	for(int i=0;i<6;i++){
		if((k=shot_search())!=-1){//弾が登録可能なら
			bullet[k].knd	=8;
			bullet[k].angle	=ang+((PI2/6)*i);//角度
			bullet[k].spd	=4;//スピード
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
void L4_1(){
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
void L4_2(double ang2){
	int k;

	for(int i=0;i<10;i++){
		if((k=shot_search())!=-1){//弾が登録可能なら
			bullet[k].knd	=4;
			bullet[k].angle	=ang2+((PI2/10)*i);//角度
			bullet[k].spd	=1.2;//スピード
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

double L4_ang=0,L4_ang2=0;	//回転ワインダー用角度

//Spell５｢回転ワインダー｣
void shot_L4(){
	int t=spcount;

	if(t>=120){
		if(t%2==0)
			L4_0(L4_ang);

		if(t%10==0)
			L4_1();

		if(t%60==0)
			L4_2(L4_ang2);

		if(t%8==0)
			se_flag[0]=1;

		L4_ang-=PI2/360;
		L4_ang2+=PI2/540;
	}
	else
		L4_ang=0,L4_ang2=0;
}

//自機狙い
void L5_0(){
	int k;

	if((k=shot_search())!=-1){//弾が登録可能なら
		bullet[k].knd	=6;
		bullet[k].angle	=shotatan2();//角度
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

//停滞ばらまき弾
void L5_1(){
	int k;

	if((k=shot_search())!=-1){//弾が登録可能なら
		bullet[k].knd	=11;
		bullet[k].angle	=rang(PI2);//角度
		bullet[k].spd	=0.8+rang(0.7);//スピード
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
void shot_L5(){
	int t=spcount;

	if(t>=120){
		if(t%8==0)
			L5_0();

		L5_1();

		if(t%8==0)
			se_flag[0]=1;
	}
}

//大弾全方位弾
void L6(){
	int k;
	double angle=rang(PI);

	for(int i=0;i<14;i++){
		if((k=shot_search())!=-1){//弾が登録可能なら
			bullet[k].knd	=0;
			bullet[k].angle	=angle+PI2/14*i;//角度
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

//Spell７｢詐欺判定弾｣
void shot_L6(){
	int t=spcount;

	if(t>=120){
		if(t%22==0){
			L6();
			se_flag[0]=1;
		}
	}

	for(int i=0;i < BULLET_MAX;i++){
		if(bullet[i].flag==1){
			if(bullet[i].cnt<60){
				bullet[i].spd-=0.08;
			}

			if(bullet[i].cnt==60){
				bullet[i].knd	=1;
				bullet[i].spd	=1;
				bullet[i].col	=0;
				bullet[i].state	=5;	//詐欺判定化
			}
		}
	}
}

//左右ワインダー
void L7_0(double ang){
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
void L7_1(){
	int k;

	for(int i=0;i<3;i++){
		if((k=shot_search())!=-1){//弾が登録可能なら
			bullet[k].knd	=0;
			bullet[k].angle	=(shotatan2()-PI/4)+(PI/4*i);//角度
			bullet[k].spd	=2.5;//スピード
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
void L7_2(){
	int k;

	if((k=shot_search())!=-1){//弾が登録可能なら
		bullet[k].knd	=1;
		bullet[k].angle	=0;//角度
		bullet[k].spd	=0;//スピード
		bullet[k].vx	=rang(0.6);
		bullet[k].vy	=3+rang(1);
		bullet[k].flag	=1;//フラグ
		bullet[k].x		=FX+(FMX/2)+rang(130);//座標
		bullet[k].y		=FY+10;
		bullet[k].col	=5;//色
		bullet[k].cnt	=0;//カウンタ
		bullet[k].gflag	=0;
		bullet[k].state	=0;
	}
}

double L7_ang=-PI/12,L7_vang=-PI/4/90;	//左右ワインダー用角度・角速度

//Spell８｢左右ワインダー｣
void shot_L7(){
	int t=spcount;

	if(t>=120){
		if(t%3==0)
			L7_0(L7_ang);

		if(t%60==0)
			L7_1();

		if(t%5==0)
			L7_2();

		if(t%8==0)
			se_flag[0]=1;

		L7_ang+=L7_vang;
		if(L7_ang>=((PI/4)-(PI/12)) || L7_ang<=(-(PI/4)-(PI/12)))
			L7_vang=-L7_vang;
	}
	else
		L7_ang=-PI/12,L7_vang=-PI/4/90;
}

//横方向の固定弾
void L8_0(int length,double speed,int joge){
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
void L8_1(int length,double speed,int sayu){
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
void shot_L8(){
	int t = spcount;

	if(t>=120){
		if(t<1200){
			if((t-120)%60==0){
				L8_0(35,1.8,0);
				L8_1(35,1.5,0);
				se_flag[0]=1;
			}

			if((t-300)%240==0){
				se_flag[11]=1;
			}

			if((t-300)%240==60){
				for(int i=0;i < BULLET_MAX;i++){
					if(bullet[i].flag==1){
						bullet[i].knd=0;	//大弾化
						bullet[i].state=4;	//ダメージ増加補正
					}
				}
				se_flag[8]=1;
			}

			if((t-300)%240==120){
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

			if((t-1200)%45==0){
				L8_0(45,2.5,1);
				L8_1(45,2,1);
				se_flag[0]=1;
			}

			if((t-1260)%180==0){
				se_flag[11]=1;
			}

			if((t-1260)%180==60){
				for(int i=0;i < BULLET_MAX;i++){
					if(bullet[i].flag==1){
						bullet[i].knd=0;	//大弾化
						bullet[i].state=4;	//ダメージ増加補正
					}
				}
				se_flag[8]=1;
			}

			if((t-1260)%180==120){
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
void L9(double x,double y){
	int k;
	double angle=rang(PI);

	for(int i=0;i<22;i++){
		if((k=shot_search())!=-1){//弾が登録可能なら
			bullet[k].knd	=8;
			bullet[k].angle	=angle+PI2/22*i;//角度
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

int L9_state=0;	//波紋発射位置変更テーブル

//発射位置設定を含めた波紋の全方位弾
void L9_1(){
	switch(L9_state){
	case 0:
		L9(enemy.x-(FMX/4)+rang(20),enemy.y-50+(rang(25)));
		L9_state=1;
		break;
	case 1:
		L9(enemy.x+(FMX/4)+rang(20),enemy.y+50+(rang(25)));
		L9_state=2;
		break;
	case 2:
		L9(enemy.x-(FMX/4)+rang(20),enemy.y+50+(rang(25)));
		L9_state=3;
		break;
	case 3:
		L9(enemy.x+(FMX/4)+rang(20),enemy.y-50+(rang(25)));
		L9_state=0;
		break;
	}
}

//Spell１０｢波紋疾走｣
void shot_L9(){
	int t=spcount;

	if(t>=120){
		if(t<600){
			if(t%40==0){
				L9_1();
				se_flag[0]=1;
			}

			for(int i=0;i < BULLET_MAX;i++){
				if(bullet[i].flag==1){
					bullet[i].spd+=0.005;
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
				L9_1();
				se_flag[0]=1;
			}

			for(int i=0;i < BULLET_MAX;i++){
				if(bullet[i].flag==1){
					bullet[i].spd+=0.007;
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
				L9_1();
				se_flag[0]=1;
			}

			for(int i=0;i < BULLET_MAX;i++){
				if(bullet[i].flag==1){
					bullet[i].spd+=0.01;
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
		L9_state=0;
}