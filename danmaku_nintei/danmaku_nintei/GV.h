#include "DxLib.h"
#include "define.h"
#include <math.h>

#ifdef GLOBAL_INSTANCE
#define GLOBAL
#else
#define GLOBAL extern
#endif

#include "function.h"

//�摜�p�ϐ��錾��
GLOBAL int img_ch[12];	//�L�����N�^�摜12����
GLOBAL int img_enemy[9];	//�G�摜9����
GLOBAL int img_board[5];	//�{�[�h�ɂ����摜
GLOBAL int img_bullet[12][10];//�e�p�摜
GLOBAL int img_etc[5];//���̑��̉摜
GLOBAL int img_num[10];//�����̉摜
GLOBAL int img_bom;	//�{���摜�n���h��

//���y�t�@�C���p�ϐ��錾��
GLOBAL int sound_se[SE_MAX];

//�t���O�E�X�e�[�^�X�ϐ�
GLOBAL int func_state,count,menu_state;//�֐�����p�ϐ�
GLOBAL int scount;	//�Q�[���I�[�o�[���̒B���x�v�Z�p
GLOBAL int stage,type;	//��Փx�A���@�^�C�v
GLOBAL int spcount;	//�X�y�����Ƃ̃J�E���g�p
GLOBAL int winflag;	//�E�C���h�E�E�t���X�N���[���ύX�p�̃t���O
GLOBAL int se_flag[SE_MAX];			//�T�E���h�t���O
GLOBAL int shut_flag;				//�����~�p�t���O
GLOBAL int spell_flag;				//�X�y���擾���Ă��邩�̃t���O
GLOBAL int sg_flag;					//�X�y���擾���̕\���p�t���O
GLOBAL int spell;					//�X�y���擾����

//���̑��̕ϐ�
GLOBAL int color[10],font[5];//�F �t�H���g

//�\���̕ϐ��錾��
GLOBAL ch_t ch;			//�L�����N�^�f�[�^�錾
GLOBAL enemy_t enemy;//�G���
GLOBAL configpad_t configpad;//�R���t�B�O�Őݒ肵���L�[���
GLOBAL bullet_t bullet[BULLET_MAX];//�e
GLOBAL bullet_info_t bullet_info[12];//�e���
