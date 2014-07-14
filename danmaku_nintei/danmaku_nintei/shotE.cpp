#include "GV.h"

//低速ばらまき弾
void E0(){
	int t=spcount;
	int k;

		if((k=shot_search())!=-1){//弾が登録可能なら
			bullet[k].knd	=8;
			bullet[k].angle	=PI2/10*t+rang(PI2/20);//角度
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

//Spell１｢低速ばらまき弾｣
void shot_E0(){
	int t=spcount;

	if(t>=120){
		E0();

		if(t%20==0)
			se_flag[0]=1;
	}

	for(int i=0;i < BULLET_MAX;i++){
		if(bullet[i].flag==1){
			if(bullet[i].cnt<20){
				bullet[i].spd+=0.02;
			}
		}
	}
}

//低速落下弾
void E1_0(){
	int k;

	for(double i = FX;i<FX+FMX;i+=(50+rang(5))){
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

//高速落下弾
void E1_1(){
	int k;

	for(double i = FX;i<FX+FMX;i+=(60+rang(10))){
		if((k=shot_search())!=-1){//弾が登録可能なら
			bullet[k].knd	=7;
			bullet[k].state =1;
			bullet[k].angle	=0;//角度
			bullet[k].spd	=0;//スピード
			bullet[k].vx	=0;
			bullet[k].vy	=-2;//落下速度
			bullet[k].flag	=1;//フラグ
			bullet[k].x		=i;//座標
			bullet[k].y		=40+rang(30);
			bullet[k].col	=1;//色
			bullet[k].cnt	=0;//カウンタ
			bullet[k].gflag	=0;
		}
	}
}

//Spell２｢二段速落下弾｣
void shot_E1(){
	int t=spcount;

	if(t>=120){
		if((t-120)%60==0){
			E1_0();
			se_flag[0]=1;
		}

		if((t-120)%120==0){
			E1_1();
		}
	}

	for(int i=0;i < BULLET_MAX;i++){
		if(bullet[i].flag==1){
			if(bullet[i].cnt<90){
				switch(bullet[i].state){//stateに合わせて落下速度の変更
				case 0:
					bullet[i].vy+=0.03;
					break;
				case 1:
					bullet[i].vy+=0.06;
					break;
				}
			}
		}
	}
}

//交差前の全方位弾
void E2(){
	int k;
	double angle=rang(PI);

	for(int j=0;j<2;j++){//途中から２分裂する分
		for(int i=0;i<30;i++){
			if((k=shot_search())!=-1){
				bullet[k].knd    =8;//8番の弾
				bullet[k].angle  =angle+PI2/30*i;
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
void shot_E2(){
	int t=spcount;

	if(t>=120){
		if(t%70==0){
			E2();
			se_flag[0]=1;
		}
	}

	for(int i=0;i<BULLET_MAX;i++){//全弾分
		if(bullet[i].flag>0){//登録されている弾があれば
			if(30<bullet[i].cnt && bullet[i].cnt<120){//30～120カウントなら
				bullet[i].spd-=1.7/90.0;//90カウントかけて1.7減らす
				bullet[i].angle+=(PI/4)/90.0*(bullet[i].state?-1:1);//90カウントかけて45°傾ける(stateで分離)
			}
			if(bullet[i].cnt==120)
				bullet[i].state=3;	//ダメージ減少補正
		}
	}
}

//高速ばらまき弾
void E3(){
	int t=spcount;
	int k;

	if((k=shot_search())!=-1){//弾が登録可能なら
		bullet[k].knd	=7;
		bullet[k].angle	=PI2/10*t+rang(PI2/20);//角度
		bullet[k].spd	=2+rang(0.3);//スピード
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

//Spell４｢高速ばらまき弾｣
void shot_E3(){
	int t=spcount;

	if(t>=120){
		E3();

		if(t%20==0)
			se_flag[0]=1;
	}

	for(int i=0;i < BULLET_MAX;i++){
		if(bullet[i].flag==1){
			if(bullet[i].cnt<20){//20フレーム間加速
				bullet[i].spd*=1.01;
			}
		}
	}
}

//回転ワインダー
void E4_0(double ang){
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
void E4_1(){
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

double E4_ang=0;	//回転ワインダー用角度

//Spell５｢回転ワインダー｣
void shot_E4(){
	int t=spcount;

	if(t>=120){
		if(t%4==0)
			E4_0(E4_ang);

		if(t%20==0)
			E4_1();

		if(t%20==0)
			se_flag[0]=1;

		E4_ang-=PI2/600;
	}
	else
		E4_ang=0;
}

//自機狙い
void E5_0(){
	int k;

	if((k=shot_search())!=-1){//弾が登録可能なら
		bullet[k].knd	=9;
		bullet[k].angle	=shotatan2();//角度
		bullet[k].spd	=2;//スピード
		bullet[k].vx	=0;
		bullet[k].vy	=0;
		bullet[k].flag	=1;//フラグ
		bullet[k].x		=enemy.x;//座標
		bullet[k].y		=enemy.y;
		bullet[k].col	=2;//色
		bullet[k].cnt	=0;//カウンタ
		bullet[k].gflag	=0;
		bullet[k].state	=3;//ダメージ減衰補正
	}
}

//停滞ばらまき弾
void E5_1(){
	int k;

	if((k=shot_search())!=-1){//弾が登録可能なら
		bullet[k].knd	=11;
		bullet[k].angle	=rang(PI2);//角度
		bullet[k].spd	=0.6+rang(0.2);//スピード
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
void shot_E5(){
	int t=spcount;

	if(t>=120){
		if(t%30==0)
			E5_0();

		if(t%6==0)
			E5_1();
			
		if(t%20==0)
			se_flag[0]=1;
	}
}

//大弾全方位弾
void E6(){
	int k;
	double angle=rang(PI);

	for(int i=0;i<8;i++){
		if((k=shot_search())!=-1){//弾が登録可能なら
			bullet[k].knd	=0;
			bullet[k].angle	=angle+PI2/8*i;//角度
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
void shot_E6(){
	int t=spcount;

	if(t>=120){
		if(t%30==0){
			E6();
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
				bullet[i].spd	=0.8;
				bullet[i].col	=0;
				bullet[i].state	=5;	//詐欺判定化
			}
		}
	}
}

//左右ワインダー
void E7_0(double ang){
	int k;

	for(int i=0;i<8;i++){
		if((k=shot_search())!=-1){//弾が登録可能なら
			bullet[k].knd	=8;
			bullet[k].angle	=ang+((PI2/8)*i);//角度
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

//ランダム落下
void E7_1(){
	int k;

	if((k=shot_search())!=-1){//弾が登録可能なら
		bullet[k].knd	=1;
		bullet[k].angle	=0;//角度
		bullet[k].spd	=0;//スピード
		bullet[k].vx	=rang(0.1);
		bullet[k].vy	=1.5+rang(0.5);
		bullet[k].flag	=1;//フラグ
		bullet[k].x		=FX+(FMX/2)+rang(130);//座標
		bullet[k].y		=FY+10;
		bullet[k].col	=5;//色
		bullet[k].cnt	=0;//カウンタ
		bullet[k].gflag	=0;
		bullet[k].state	=0;
	}
}

double E7_ang=-PI/8,E7_vang=-PI/4/180;	//左右ワインダー用角度・角速度

//Spell８｢左右ワインダー｣
void shot_E7(){
	int t=spcount;

	if(t>=120){
		if(t%4==0)
			E7_0(E7_ang);

		if(t%20==0)
			E7_1();

		if(t%20==0)
			se_flag[0]=1;

		E7_ang+=E7_vang;
		if(E7_ang>=((PI/6)-(PI/8)) || E7_ang<=(-(PI/6)-(PI/8)))
			E7_vang=-E7_vang;
	}
	else
		E7_ang=-PI/8,E7_vang=-PI/4/180;
}

//横方向の固定弾
void E8_0(int length,double speed,int joge){
	int k;

	for(double i = FX+rang(17.5);i<=FX+FMX+10;i+=length){
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
void E8_1(double length,double speed,int sayu){
	int k;

	for(double i = FY+rang(20);i<=FY+FMY+10;i+=length){
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

//spell９｢左右＆上下拘束弾｣
void shot_E8(){
	int t = spcount;

	if(t>=120){
		if(t<1200){
			if((t-120)%80==0){
				E8_1(38,1.5,0);
				E8_1(38,1.5,1);
				se_flag[0]=1;
			}
		}
		else{
			if(t==1200){
				bdelete();
				se_flag[8]=1;
			}

			if((t-1200)%60==0){
				E8_0(43,2,0);
				E8_0(43,2,1);
				se_flag[0]=1;
			}
		}
	}
}

//波紋の全方位弾
void E9(double x,double y){
	int k;
	double angle=rang(PI);

	for(int i=0;i<14;i++){
		if((k=shot_search())!=-1){//弾が登録可能なら
			bullet[k].knd	=8;
			bullet[k].angle	=angle+PI2/14*i;//角度
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

int E9_state=0;	//波紋発射位置変更テーブル

//発射位置設定を含めた波紋の全方位弾
void E9_1(){
	switch(E9_state){
	case 0:
		E9(enemy.x-(FMX/4)+rang(20),enemy.y-50+(rang(25)));
		E9_state=1;
		break;
	case 1:
		E9(enemy.x+(FMX/4)+rang(20),enemy.y+50+(rang(25)));
		E9_state=2;
		break;
	case 2:
		E9(enemy.x-(FMX/4)+rang(20),enemy.y+50+(rang(25)));
		E9_state=3;
		break;
	case 3:
		E9(enemy.x+(FMX/4)+rang(20),enemy.y-50+(rang(25)));
		E9_state=0;
		break;
	}
}

//Spell１０｢波紋疾走｣
void shot_E9(){
	int t=spcount;

	if(t>=120){
		if(t<600){
			if(t%90==0){
				E9_1();
				se_flag[0]=1;
			}

			for(int i=0;i < BULLET_MAX;i++){
				if(bullet[i].flag==1){
					bullet[i].spd+=0.002;
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
			if(t%75==0){
				E9_1();
				se_flag[0]=1;
			}

			for(int i=0;i < BULLET_MAX;i++){
				if(bullet[i].flag==1){
					bullet[i].spd+=0.003;
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
			if(t%60==0){
				E9_1();
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
	}
	else
		E9_state=0;
}