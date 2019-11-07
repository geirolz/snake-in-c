/*
  Name: function_lib
  Copyright: David Geirola
  Author: David geirola
  Date: 07/04/13 13:40
*/
#include <stdio.h>
#include <windows.h>
#include <unistd.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

#define dir_setting "set"

int fdebug=1;

//colors
typedef enum
{
    BLACK,
    BLUE,
    GREEN,
    CYAN,
    RED,
    MAGENTA,
    BROWN,
    LIGHTGRAY,
    DARKGRAY,
    LIGHTBLUE,
    LIGHTGREEN,
    LIGHTCYAN,
    LIGHTRED,
    LIGHTMAGENTA,
    YELLOW,
    WHITE
} COLORS;

typedef enum
{
  name,
  surname,
  age,
  score,
}PlayerLines;

//--file
FILE *file_setting;

void SettingWrite(int a,int d, int dur){
 file_setting=fopen(dir_setting,"w");
 fprintf(file_setting,"%d %d %d",a,d,dur);
 fclose(file_setting);
}

int SettingGet(int SettType){
 int st[5];
 int Value;
 file_setting=fopen(dir_setting,"r");
if(!file_setting) SettingWrite(1,0,0);
 int i;
 for(i=0;i<3;i++) fscanf(file_setting,"%d",&st[i]);
 fclose(file_setting);

 switch(SettType){
    case 1://audio
        Value=st[0];
        break;
    case 2://diff
        Value=st[1];
        break;
    case 3://time
        Value=st[2];
        break;

 }


return Value;
}






void gotoxy(int x, int y)
{
    COORD Cur= {(SHORT)x, (SHORT) y};

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}


void setcolor(int color, int bgcolor) {
    color &= 0xf;
    bgcolor &= 0xf;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (bgcolor << 4) | color);
}

int getcolor() {
    CONSOLE_SCREEN_BUFFER_INFO info;
    int color;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
    color = info.wAttributes & 0xf;
    return color;
}



void printlogo()
{
//Arkanoid
setcolor(YELLOW,0);
printf("\n\n\t     |||||||    ||||   ||       |||        ||  ||   ||||||   ");
printf("\n\t     ||         || ||  ||      || ||       || ||    ||       ");
printf("\n\t     |||||||    ||  || ||     ||   ||      |||      |||||   ");
printf("\n\t          ||    ||   ||||    ||/////||     || ||    ||       ");
printf("\n\t     |||||||    ||    |||   ||       ||    ||  ||   ||||||   \n");


}

void GetEnter()
{
    while(getch()!=13){getch();};
}

void cls(){system("cls");fflush(stdin);gotoxy(28,0);printlogo();}
