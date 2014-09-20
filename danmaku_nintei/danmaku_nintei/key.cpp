#include "GV.h"

unsigned int stateKey[256];

int GetHitKeyStateAll_2(){
    char GetHitKeyStateAll_Key[256];
    GetHitKeyStateAll( GetHitKeyStateAll_Key );
    for(int i=0;i<256;i++){
        if(GetHitKeyStateAll_Key[i]==1) stateKey[i]++;
        else                            stateKey[i]=0;
    }
    return 0;
}

int CheckStateKey(unsigned char Handle){
	return stateKey[Handle];
}

//�p�b�h�̓��͏�Ԃ��i�[����ϐ�
pad_t pad;

//�����P�ƈ����Q�̂����傫�����������P�ɑ������
void input_pad_or_key(int *p, int k){
	*p = *p>k ? *p : k;
}

//�p�b�h�ƃL�[�{�[�h�̗����̓��͂��`�F�b�N����֐�
void GetHitPadStateAll(){
	int i,PadInput,mul=1;
	PadInput = GetJoypadInputState( DX_INPUT_PAD1 );//�p�b�h�̓��͏�Ԃ��擾
	for(i=0;i<16;i++){
		if(PadInput & mul)	pad.key[i]++;
		else				pad.key[i]=0;
		mul*=2;
	}
	input_pad_or_key(&pad.key[configpad.left]	,CheckStateKey(KEY_INPUT_LEFT	 ));
	input_pad_or_key(&pad.key[configpad.up]	    ,CheckStateKey(KEY_INPUT_UP	     ));
	input_pad_or_key(&pad.key[configpad.right]  ,CheckStateKey(KEY_INPUT_RIGHT	 ));
	input_pad_or_key(&pad.key[configpad.down]	,CheckStateKey(KEY_INPUT_DOWN	 ));
	input_pad_or_key(&pad.key[configpad.shot]	,CheckStateKey(KEY_INPUT_Z	     ));
	input_pad_or_key(&pad.key[configpad.bom]	,CheckStateKey(KEY_INPUT_X		 ));
	input_pad_or_key(&pad.key[configpad.slow]	,CheckStateKey(KEY_INPUT_LSHIFT	 ));
	input_pad_or_key(&pad.key[configpad.start]  ,CheckStateKey(KEY_INPUT_ESCAPE	 ));
}

//�n���ꂽ�p�b�h�L�[�ԍ��̓��͏�Ԃ�Ԃ��B�Ԃ�l��-1�Ȃ�s��
int CheckStatePad(int Handle){
	if(0<=Handle && Handle<PAD_MAX){
		return pad.key[Handle];
	}
	else{
		printfDx("CheckStatePad�ɓn�����l���s���ł�\n");
		return -1;
	}
}
