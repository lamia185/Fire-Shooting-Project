#include<iostream>
using namespace std;

#include "iGraphics.h"
#define screenwidth 1000
#define screenheight 500


char scoreCh[100];
int villanX = 0;
int villanY = 300;
int blastx,blasty;
bool bulletShoot = false;
int score =0;
int tm=0;
int bulletX ;
int bulletY ;
int shooterX = 0;
int shooterY = 20;
bool start=false;
int mposx,  mposy;

char bc[4][20]={"back.bmp"};
int bcIndex=0;

char villan[2][30] = {"badship.bmp"};
int villanIndex = 0;
int dx = 5;
int key=0;
bool menu=true,over=false,leader=false,blast=false;


struct point{
	int pt;
	char ptch[10];
}b[20];

int index=-1;

void save(){
	FILE *fp;
	fp=fopen("data.dat","wb");
	fwrite(&b,sizeof(b),1,fp);
	fwrite(&index,sizeof(index),1,fp);
	fclose(fp);
}
void read(){
	FILE *fp;
	fp=fopen("data.dat","rb");
	fread(&b,sizeof(b),1,fp);
	fread(&index,sizeof(index),1,fp);
	fclose(fp);
}


void iDraw()
{
	
	iClear();
	if(leader){
		iShowBMP(0,0,"leaderbg.bmp");
		for(int i=index,j=0;i>=0;i--,j++){
			iText(482,500-(166+(j*30)),b[i].ptch);
			if(j==6)break;
		}
	}

	if(start){
	iShowBMP(0,0,bc[bcIndex]); 
	_itoa_s(b[index].pt,b[index].ptch,10);
	tm++;
	if(tm==1000){
		start=false;
		over=true;
	}
	iText(810,450,"Score :",GLUT_BITMAP_TIMES_ROMAN_24);
	iText(870,449,b[index].ptch,GLUT_BITMAP_TIMES_ROMAN_24);
	iShowBMP2(villanX, villanY, villan[villanIndex], 0);
	iShowBMP2(shooterX, shooterY, "goodship.bmp", 0);
	if (bulletShoot){
		iShowBMP2(bulletX, bulletY, "fire.bmp", 0);
		bulletY += 10;
	}
	if(blast){
		iShowBMP2(blastx,blasty,"blast.bmp",0);
		key++;


		if(key==5){
			blast=false;
			key=0;
		}
	}
	}

	if(over){
		iShowBMP(0,0,"gameover.bmp");
		iText(400,150,"Your Score:",GLUT_BITMAP_TIMES_ROMAN_24);
	iText(520,149,b[index].ptch,GLUT_BITMAP_TIMES_ROMAN_24);
	}
	if(menu){
		iShowBMP(0,0,"menu.bmp");
		iShowBMP2(100,200,"play.bmp",0);
		iShowBMP2(100,100,"leader.bmp",0);
	}
} 

/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx, int my)
{
	//place your codes here
}

/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouse(int button, int state, int mx, int my)
{
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		//place your codes here
		if(mx>=100&&mx<=100+335&&my>=200&&my<=200+92){
			menu=false;
			start=true;
			index++;
		}
		if(mx>=100&&mx<=100+335&&my>=100&&my<=100+92){
			menu=false;
			leader=true;
		}

	}
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		//place your codes here
	}
}
/*iPassiveMouseMove is called to detect and use
the mouse point without pressing any button */

void iPassiveMouseMove(int mx,int my)
{
	//place your code here

 mposx = mx;
 mposy = my;
 if(mx== 2){}        /*Something to do with mx*/
 else if(my== 2){}   /*Something to do with my*/

}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
*/
void iKeyboard(unsigned char key)
{

	if(key == 8){
		if(over){
			over =false;
			menu=true;
		}
		if(start){
			start=false;
			menu=true;
		}
		if(leader){
			leader=false;
			menu=true;
		}
	}
	if (key ==AUX_SPACE){
		bulletX = shooterX + 30;
		bulletY = 100;
		bulletShoot = true;
	}
}

/*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
*/
void iSpecialKeyboard(unsigned char key)
{
	if (key == GLUT_KEY_LEFT){
		
		if(shooterX>1) {
           shooterX-=25;
     }
	}
	
	if (key == GLUT_KEY_RIGHT){
		
		if(shooterX<=999-(100)) {
           shooterX+=25;
     }
	}
}


void villanChange()
{
	save();
	villanX += dx;
	blastx+=dx;
	if (villanX >= 800){
		dx *= -1;
		villanIndex = 0;
	}
	if (villanX <= 0){
		dx *= -1;
		villanIndex = 0;
	}

}

void fireCol()
{
	if(bulletShoot){
		if((bulletX>=villanX && bulletX<=villanX+162) && bulletY>=villanY){
		b[index].pt+=5;
		blast=true;
		blastx=bulletX;
		blasty=bulletY;
		bulletShoot=false;
	}
	_itoa_s(b[index].pt,b[index].ptch,10);
	}

}

int main()
{
	read();
	FreeConsole();
	iSetTimer(20, villanChange);
	iSetTimer(50,fireCol);
	iInitialize(screenwidth,screenheight , "KILL THE ENEMY");
	return 0;
}
