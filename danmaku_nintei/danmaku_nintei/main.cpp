#define GLOBAL_INSTANCE 
#include "GV.h"


namespace
{

//初回のみ入る処理
void initialize(void)
{
	load(); //データロード
	first_ini(); //初回の初期化
	func_state = 1;
}

//タイトル＆モードセレクト
void mode_select(void)
{
	graph_title();
	calc_title();
}

//ポーズ画面
void pause(void)
{
	calc_pause();
	graph_pause();
}

//リザルト画面
void result(void)
{
	calc_result();
	graph_result();
	++count;
}

//ゲームオーバー画面
void game_over(void)
{
	calc_result();
	graph_result();
	++count;
}

//キーコンフィグ
void key_config(void)
{
	calc_key();
	graph_key();
}

//マニュアル
void manual(void)
{
	calc_manual();
	graph_manual();
}

//難易度の選択
void difficult_select(void)
{
	graph_difficult();
	calc_difficult();
}

//自機タイプの選択
void self_type_select(void)
{
	graph_type();
	calc_type();
}

//各種データの初期化
void data_clear(void)
{
	ini();
	func_state=10;
}

//通常処理
void main_sequence(void)
{
	calc_main();
	ch_main();
	enemy_main();
	shot_main();
	out_main();
	graph_main();
	++count;
}

typedef void (*sequence)(void);
sequence sequences[] = {
  initialize,
  mode_select,
  pause,
  result,
  game_over,
  key_config,
  manual,
  difficult_select,
  self_type_select,
  data_clear,
  main_sequence
};

} // namespace

//ループで必ず行う３大処理
int ProcessLoop(){
	if(ProcessMessage()!=0)return -1;//プロセス処理がエラーなら-1を返す
	if(ClearDrawScreen()!=0)return -1;//画面クリア処理がエラーなら-1を返す
	GetHitKeyStateAll_2();//現在のキー入力処理を行う
	GetHitPadStateAll();  //現在のパッド入力処理を行う
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow){
	ChangeWindowMode(TRUE);//ウィンドウモード
	SetMainWindowText("弾幕段位認定ver1.10");//ウインドウ表示名
	if(DxLib_Init() == -1 || SetDrawScreen( DX_SCREEN_BACK )!=0) return -1;//初期化と裏画面化

	while(ProcessLoop()==0){//メインループ
		music_ini();
		if ((func_state >= 0) && (func_state < sizeof(sequences)/sizeof(sequences[0]))) {
			sequences[func_state]();
		} else {
			printfDx("不明なfunc_state[%d]\n",
               func_state);
		}
		music_play();
		fps_wait();
		if(shut_flag == 1)break;//終了動作があったらブレイク
		ScreenFlip();//裏画面反映
	}
	DxLib_End();//ＤＸライブラリ終了処理
	return 0;
}
