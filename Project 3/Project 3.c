/*
 * Project_3.c
 *
 * Created: 5/3/2015 7:45:51 PM
 *  Author: John
 */ 

/*
 * keyPad.c
 *
 * Created: 4/26/2015 7:28:57 PM
 *  Author: John
 */ 

#include <avr/io.h>
#include "avr.h"
#include "lcd.h"

#define C 19
#define CS 18
#define D 17
#define DS 16
#define E 15
#define F 14
#define FS 13
#define G 12
#define GS 11
#define A 10
#define AS 9
#define B 8

#define WHOLE 8
#define HALF 4
#define QUARTER 2
#define EIGHTH 1

unsigned char convert(unsigned int c){
	unsigned char r = 0;
	switch(c){
		case 1:
		r = 1 + '0';
		break;
		case 2:
		r = 2 + '0';
		break;
		case 3:
		r = 3 + '0';
		break;
		case 4:
		r = 'A';
		break;
		case 5:
		r = 4 +'0';
		break;
		case 6:
		r = 5 + '0';
		break;
		case 7:
		r = 6 + '0';
		break;
		case 8:
		r = 'B';
		break;
		case 9:
		r = 7 + '0';
		break;
		case 10:
		r = 8 + '0';
		break;
		case 11:
		r = 9 + '0';
		break;
		case 12:
		r = 'C';
		break;
		case 13:
		r = '*'; // Key to restart
		break;
		case 14:
		r = 0 + '0';
		break;
		case 15:
		r = '#';
		break;
		case 16:
		r = 'D';
		break;
	}
	return r;
}

int key_pressed(int r, int c){
	int pressed;
	DDRC = 0;
	PORTC = 0;
	
	SET_BIT(PORTC, r);
	SET_BIT(DDRC, c+4);
	CLR_BIT(PORTC, c+4);
	if (!GET_BIT(PINC,r)){
		pressed=1;
	}
	else
	{
		pressed = 0;
	}
	return pressed;
}

unsigned char get_key(){
	unsigned int r,c;
	for (r = 0; r<4; r++){
		for (c = 0; c < 4; c++){
			if (key_pressed(r,c)){
				return convert((r*4) + c + 1);
			}
		}
	}
	return 0;
}


typedef struct note note;

struct note {
	unsigned char freq;
	unsigned char duration;
};

void play_song(note* song, int N){
	for (int i = 0 ; i < N; i++){
		play_note(song[i].freq, song[i].duration);
	}
}

void play_note (unsigned char freq, unsigned char duration){
	int n = duration - '0';
	int t = freq - '0';
	for (int i = 0;i < n; ++i){
		PORTA = 1;
		wait_avr(t);
		PORTA = 0;
		wait_avr(t);
	}
}

int main(void)
{
	DDRA = 1;
	ini_lcd();
	clr_lcd();
	pos_lcd(0,0);
	
	note aw = {A + '0', WHOLE + '0'};
	note ah = {A + '0', HALF + '0'};
	note aq = {A + '0', QUARTER + '0'};
	note ae = {A + '0', EIGHTH + '0'};
	note SONG[4] = {aw};

	char key = 0;
	/*
	while(1){
		key = get_key();
		if (key == 'A'){
			break;
		}
		play_song(SONG, 1);
	}
	*/

}