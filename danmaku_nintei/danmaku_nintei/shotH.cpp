#include "GV.h"

//低速ばらまき弾
void H0(){
	int t=spcount;
	int k;

	for(int i=0;i<3;i++){
		if((k=shot_search())!=-1){//弾が登録可能なら
			bullet[k].knd	=8;
			bullet[k].angle	=PI2/10*t+PI2/30*i+rang(PI2/60);//角度
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
void shot_H0(){
	int t=spcount;

	if(t>=120){
		H0();

		if(t%10==0)
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
void H1_0(){
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
void H1_1(){
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
void H1_2(){
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
void shot_H1(){
	int t=spcount;

	if(t>=120){
		if((t-120)%60==0){
			H1_0();
		}

		if((t-120)%60==0){
			H1_1();
			se_flag[0]=1;
		}

		if((t-120)%90==0){
			H1_2();
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
void H2(){
	int k;
	double angle=rang(PI);

	for(int j=0;j<2;j++){//途中から２分裂する分
		for(int i=0;i<75;i++){
			if((k=shot_search())!=-1){
				bullet[k].knd    =8;//8番の弾
				bullet[k].angle  =angle+PI2/75*i;
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
void shot_H2(){
	int t=spcount;

	if(t>=120){
		if(t<600){
			if(t%60==0){
				H2();
				se_flag[0]=1;
			}
		}

		else if(t<1200){
			if(t%50==0){
				H2();
				se_flag[0]=1;
			}
		}

		else if(t%40==0){
			H2();
			se_flag[0]=1;
		}
	}

	for(int i=0;i<BULLET_MAX;i++){//全弾分
		if(bullet[i].flag>0){//登録されている弾があれば
			if(30<bullet[i].cnt && bullet[i].cnt<120){//30～120カウントなら
				bullet[i].spd-=1.7/90.0;//90カウントかけて1.7減らす
				bullet[i].angle+=(PI/2)/90.0*(bullet[i].state?-1:1);//90カウントかけて90°傾ける
			}
			if(bullet[i].cnt==120)
				bullet[i].state=3;	//ダメージ減少補正
		}
	}
}

//高速ばらまき弾
void H3(){
	int t=spcount;
	int k;

	for(int i=0;i<3;i++){
		if((k=shot_search())!=-1){//弾が登録可能なら
			bullet[k].knd	=7;
			bullet[k].angle	=PI2/10*t+PI2/30*i+rang(PI2/60);//角度
			bullet[k].spd	=2.5+rang(0.5);//スピード
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
void shot_H3(){
	int t=spcount;

	if(t>=120){
		H3();

		if(t%10==0)
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
void H4_0(double ang){
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
void H4_1(){
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
void H4_2(double ang2){
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

double H4_ang=0,H4_ang2=0;	//回転ワインダー用角度

//Spell５｢回転ワインダー｣
void shot_H4(){
	int t=spcount;

	if(t>=120){
		if(t%2==0)
			H4_0(H4_ang);

		if(t%10==0)
			H4_1();

		if(t%90==0)
			H4_2(H4_ang2);

		if(t%10==0)
			se_flag[0]=1;

		H4_ang-=PI2/360;
		H4_ang2+=PI2/600;
	}
	else
		H4_ang=0,H4_ang2=0;
}

//自機狙い
void H5_0(){
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
void H5_1(){
	int k;

	for(int i=0;i<2;i++){
		if((k=shot_search())!=-1){//弾が登録可能なら
			bullet[k].knd	=11;
			bullet[k].angle	=rang(PI2);//角度
			bullet[k].spd	=0.8+rang(0.5);//スピード
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
}

//Spell６｢自機狙い複合弾｣
void shot_H5(){
	int t=spcount;

	if(t>=120){
		if(t%10==0)
			H5_0();

		if(t%2==0)
		H5_1();

		if(t%10==0)
			se_flag[0]=1;
	}
}

//大弾全方位弾
void H6(){
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
void shot_H6(){
	int t=spcount;

	if(t>=120){
		if(t%26==0){
			H6();
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
void H7_0(double ang){
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
void H7_1(){
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
void H7_2(){
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

double H7_ang=-PI/12,H7_vang=-PI/4/90;	//左右ワインダー用角度・角速度

//Spell８｢左右ワインダー｣
void shot_H7(){
	int t=spcount;

	if(t>=120){
		if(t%3==0)
			H7_0(H7_ang);

		if(t%90==0)
			H7_1();

		if(t%6==0)
			H7_2();

		if(t%10==0)
			se_flag[0]=1;

		H7_ang+=H7_vang;
		if(H7_ang>=((PI/4)-(PI/12)) || H7_ang<=(-(PI/4)-(PI/12)))
			H7_vang=-H7_vang;
	}
	else
		H7_ang=-PI/12,H7_vang=-PI/4/90;
}

//横方向の固定弾
void H8_0(int length,double speed,int joge){
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
void H8_1(int length,double speed,int sayu){
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
void shot_H8(){
	int t = spcount;

	if(t>=120){
		if(t<1200){
			if((t-120)%80==0){
				H8_0(35,2,0);
				H8_1(35,1.5,0);
				se_flag[0]=1;
			}

			if((t-300)%270==0){
				se_flag[11]=1;
			}

			if((t-300)%270==60){
				for(int i=0;i < BULLET_MAX;i++){
					if(bullet[i].flag==1){
						bullet[i].knd=0;	//大弾化
						bullet[i].state=4;	//ダメージ増加補正
					}
				}
				se_flag[8]=1;
			}

			if((t-300)%270==120){
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

			if((t-1200)%60==0){
				H8_0(40,2.5,1);
				H8_1(40,2,1);
				se_flag[0]=1;
			}

			if((t-1260)%210==0){
				se_flag[11]=1;
			}

			if((t-1260)%210==60){
				for(int i=0;i < BULLET_MAX;i++){
					if(bullet[i].flag==1){
						bullet[i].knd=0;	//大弾化
						bullet[i].state=4;	//ダメージ増加補正
					}
				}
				se_flag[8]=1;
			}

			if((t-1260)%210==120){
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
void H9(double x,double y){
	int k;
	double angle=rang(PI);

	for(int i=0;i<18;i++){
		if((k=shot_search())!=-1){//弾が登録可能なら
			bullet[k].knd	=8;
			bullet[k].angle	=angle+PI2/18*i;//角度
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

int H9_state=0;	//波紋発射位置変更テーブル

//発射位置設定を含めた波紋の全方位弾
void H9_1(){
	switch(H9_state){
	case 0:
		H9(enemy.x-(FMX/4)+rang(20),enemy.y-50+(rang(25)));
		H9_state=1;
		break;
	case 1:
		H9(enemy.x+(FMX/4)+rang(20),enemy.y+50+(rang(25)));
		H9_state=2;
		break;
	case 2:
		H9(enemy.x-(FMX/4)+rang(20),enemy.y+50+(rang(25)));
		H9_state=3;
		break;
	case 3:
		H9(enemy.x+(FMX/4)+rang(20),enemy.y-50+(rang(25)));
		H9_state=0;
		break;
	}
}

//Spell１０｢波紋疾走｣
void shot_H9(){
	int t=spcount;

	if(t>=120){
		if(t<620){
			if(t%40==0){
				H9_1();
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

		else if(t<1190){
			if(t%30==0){
				H9_1();
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

		else{
			if(t%20==0){
				H9_1();
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
	}
	else
		H9_state=0;
}