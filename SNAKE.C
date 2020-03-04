#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<dos.h>
#include<graphics.h>
#include<time.h>
#include<math.h>
#define maxlength 2000

typedef struct snake{
   int x1,y1,width,height;
}Snake;
int page=0;
int borderx1=40,bordery1=80,borderx2=600,bordery2=400;
int snakelength=3;
int speed=10, velocityx=0,velocityy=0; // velocity = width = height
int foodx,foody,foodflag;
Snake snake[maxlength];
int gameover=0; // 0 false  1 true
int score=0;
char scorestring[10]="score:";
void Border()
{
   setcolor(4);
   rectangle(borderx1,bordery1,borderx2,bordery2);
   setcolor(2);
   rectangle(borderx1+2,bordery1+2,borderx2-2,bordery2-2);
   setcolor(1);
   rectangle(borderx1+4,bordery1+4,borderx2-4,bordery2-4);
   setcolor(6);
   outtextxy(200,420,"PRESS ESC TO EXIT");
}

void gameOver()
{
    sound(1000);
    delay(500);
    nosound();
    setcolor(RED);
    ellipse(320,240,0,360,150,75);
    setcolor(GREEN);
    ellipse(320,240,0,360,148,73);
    setcolor(BLUE);
    ellipse(320,240,0,360,146,71);
    setfillstyle(10,3);
    floodfill(320,240,BLUE);
    setcolor(YELLOW);
    settextstyle(8,0,3);
    outtextxy(195,220,"G A M E   O V E R");
}
void food()
{
  setcolor(15);
  setfillstyle(1,15);
  fillellipse(foodx,foody,5,4);
}
void generaterandomfood()
{
   foodx = rand()%585;
   if(foodx<=borderx1+15)
       foodx = foodx+55;
   foody = rand()%385;
   if(foody<=bordery1+15)
       foody = foody+95;
}
void drawsnake()
{
  int i=0;
  sprintf(scorestring,"score: %d",score);
  if(foodflag==1){
    generaterandomfood();
    score++;
    foodflag = 0;
  }
  cleardevice();
  setcolor(13);
  settextstyle(3,HORIZ_DIR,1);
  outtextxy(40,50,scorestring);
  Border();
  food();
  setfillstyle(1,6);
  setcolor(6);
  for(i=0;i<snakelength;i++)
  {
	 rectangle(snake[i].x1,snake[i].y1,snake[i].x1+10,snake[i].y1+10); // 10 =width
	 floodfill(snake[i].x1+2,snake[i].y1+2,6);
    }
}

void check(char key,char prevkey)
{
   int i=0;
   if(snake[0].x1<=49 || snake[0].x1>=584)
      gameover=1;
   if(snake[0].y1<=85 || snake[0].y1>=384)
      gameover=1;
   // handle eating in x-axis
   if((foody>=snake[0].y1 && foody<=snake[0].y1+10) && abs(snake[0].x1+10-foodx)<=5)
   {
     foodflag=1;
     snakelength++;
     sound(500);
     delay(30);
     nosound();
   }
   // handle eating in y-axis
   else if((foodx>=snake[0].x1 && foodx<=snake[0].x1+10) && abs(snake[0].y1+10-foody)<=4)
   {
     foodflag=1;
     snakelength++;
     sound(500);
     delay(30);
     nosound();
   }
   if((prevkey=='a' && key=='d') || (prevkey=='d' && key=='a'))
      gameover=1;
   if((prevkey=='w' && key=='s') || (prevkey=='s' && key=='w'))
      gameover=1;
   for(i=2;i<snakelength;i++){
      if((snake[0].x1>=snake[i].x1 && snake[0].x1<=snake[i].x1+10) &&
	  (snake[0].y1>=snake[i].y1 && snake[0].y1<=snake[i].y1))
	  {
	     gameover=1;
	  }
   }
}

void main()
{
  char key,prevkey;
  int i,length=snakelength;
  int gd=DETECT,gm;
  initgraph(&gd,&gm,"c:\\tc\\bgi");
  snake[0].x1=70; snake[0].y1=120;snake[0].width=10;snake[0].height=10;
  snake[1].x1=60; snake[1].y1=120;snake[1].width=10;snake[1].height=10;
  snake[2].x1=50; snake[2].y1=120;snake[2].width=10;snake[2].height=10;
  Border();
  srand(time(NULL));
  generaterandomfood();
  food();
  foodflag=0;
  drawsnake();
  key = getch();
  while(!gameover && key!=27)
  {
	       velocityx=0; velocityy=0;
		if(kbhit())
		    key = getch();
		if (key == 'a'){
		      velocityx=-10;
		      velocityy=0;
	       }else if(key == 'd'){
		      velocityx=10;
		      velocityy=0;
	       }else if(key == 'w'){
		      velocityx=0;
		      velocityy=-10;
	      }else if(key == 's'){
		      velocityx=0;
		      velocityy=10;
	      }else if(key ==27)
			exit(1);
	      else
		key = prevkey;
      length++;
      for(i=length-1;i>0;i--)
      {
	   snake[i].x1 = snake[i-1].x1;
	   snake[i].y1 = snake[i-1].y1;
	   snake[i].width = snake[i].height = 10;
      }
      snake[0].x1 = snake[1].x1+velocityx;
      snake[0].y1 = snake[1].y1+velocityy;
      if(length >snakelength){
	  length = snakelength;
      }
      if(snakelength>=maxlength)
      snakelength = maxlength;
      check(key,prevkey);
      drawsnake();
      delay(120);
      prevkey = key;
  }
  delay(10);
  if(gameover)
     gameOver();
  delay(1000);
  getch();
  closegraph();
}
