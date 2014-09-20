// see: http://msdn.microsoft.com/ja-jp/library/4hwaceh6.aspx
#define _USE_MATH_DEFINES
#include <math.h>

//円周率
#define PI M_PI
#define PI2 (M_PI*2)
//フィールドの広さ
#define FMX 384
#define FMY 448
//フィールドの左上の座標
#define FX 32
#define FY 16

//効果音の種類の最大数
#define SE_MAX 12

//パッドキーの最大数
#define PAD_MAX 16

//自機の当たり判定・グレイズ判定範囲
#define CRANGE 4.5
#define CRANGE11 13.5
//弾の最大数
#define BULLET_MAX 3000

//本編総フレーム数
#define FLAME_MAX 19800

#include "struct.h"
