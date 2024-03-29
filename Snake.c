/*
  Name: Snake in C
  Copyright: ITI
  Author: David Geirola
  Date: 07/04/13 13:34
  Description: Snake in C
*/

#include <stdlib.h>
#include "lib\function_lib.c"

#define snake_def_size 5
#define snake_def_speed 100
#define food_def_chance 1

#define button_up 72
#define button_down 80
#define button_left 75
#define button_right 77


//{struct e enum
struct coordinate {
     short x;
     short y;
};
struct food
{
    short x;
    short y;
    int tipo;
};
enum diff{
    easy,
    medium,
    difficult,
    impossible,
    supermegaimpossible,
};
enum settype{
    nullsett,
    Saudio,
    Sdiff,
    Stime,
};
//}
//{ setting
int snake_speed; //veloci� snake
int snake_size; //dimensione snake
int game_difficult; //livello corrente
int game_audio;//togle audio
int game_duration;
char player_name[20]; //nome giocatore
int  player_score; //punteggio partita
int  player_total_score;//punteggio totale del giocatore
int a,c,k,r,j,i,s,foodC=0;//contatori
int isPlaying=FALSE; //varibile che mantiene il game in esecuzione
struct coordinate VetSn[1000]; //vettore posizioni snake
struct food FoodPoint[1000];//vettore posizioni food
int appendscore; //punti da agiungere
int food_chance; //probabilit� generazione cibo
int sel=1; //item selezionato nel menu

//setting
char DiffStr[30];
char DiffVet[5][30]={"Facile","Medio","Difficile","Impossibile","Supermegaimpossibile"};



//}
//{prototipi
void Game(); //inizia il gioco
void init_menu(); //printa il menu
//}



//{/////////////////////////TIMER/////////////////////////////////
int TTcurtime;
int TTold;
time_t t;
time_t TTstart;
char StrCurTime[60];

void SecToMin(int sec)
{
char newtimestr[60];
char buf[5];

int minutes = sec /60;
int second = 60*minutes;
second=sec-second;

strcpy(newtimestr,itoa(minutes,buf,10));
strcat(newtimestr," e ");
strcat(newtimestr,itoa(second,buf,10));

strcpy(StrCurTime,newtimestr);
}

int UpTimer(){
        time(&t);
        TTcurtime=(int)difftime(t,TTstart);
        if(TTold !=TTcurtime){
        gotoxy(50,22);
        setcolor(WHITE,0);
        SecToMin(TTcurtime);
        printf("Time: min%ssec    ",StrCurTime);
        TTold=TTcurtime;
    }
 }

//}//////////////////////////////////////////////////////////////




//{/////////////////////////INTRO///////////////////////////////////
void intro()
{
     cls();
     system("title Snake by 3I");
     gotoxy(0,0);
     printlogo();
     gotoxy(29,10);
     printf("inserire nome giocatore:\n");
     gotoxy(30,11);
     setcolor(WHITE,0);
     gets(player_name);

     if(strlen(player_name)<3){
        setcolor(RED,0);
        printf("\t\t\tLnghezza minima di 3 caratteri!");
        GetEnter();
        intro();
     }
     setcolor(RED,0);
     gotoxy(29+strlen(player_name)/2,19);
     printf("WELCOME %s",player_name);
     gotoxy(29,20);
     setcolor(RED,0);
     printf("PRESS ENTER TO CONTINUE");
     GetEnter();

}
//}******************************************************************************

//{/////////////////////////SETTING////////////////////////////////

void  changeDiff(char in)
{
    switch(in)
    {
    case button_left:
        if(game_difficult>0) game_difficult--;
        break;
    case button_right:
        if(game_difficult<4) game_difficult++;
        break;


    }
}

void timechange(char in1)
{
    switch(in1)
    {
    case button_left:
        if(game_duration>=1) game_duration--;
        break;
    case button_right:
        if(game_duration<6) game_duration++;
        break;


    }
    if(game_duration>=6) game_duration=0;
}

void printSettingMenu()
{
     //item1
     gotoxy(20,10);
     if(sel==1){setcolor(RED,BLACK);}else{setcolor(WHITE,BLACK);}
     if(game_audio==1)printf("    AUDIO     \t\t\tON");
     if(game_audio==0)printf("    AUDIO     \t\t\tOFF");

     //item2
     gotoxy(20,12);
     if(sel==2){setcolor(RED,BLACK);}else{setcolor(WHITE,BLACK);}
     printf("    DIFFICOLTA     \t\t\t%s",DiffVet[game_difficult]);

     //item3
     gotoxy(20,14);
     if(sel==3){setcolor(RED,BLACK);}else{setcolor(WHITE,BLACK);}
     if(game_duration<=0){
     printf("    DURATA     \t\t\t-");
     }else{
     printf("    DURATA     \t\t\t%dmin",game_duration);}

     //item3
     gotoxy(30,18);
     if(sel==4){setcolor(RED,BLACK);}else{setcolor(WHITE,BLACK);}
     printf("%c     TORNA AL MENU     %c",219,219);

}

void togleAudio()
{
    if(game_audio==0) game_audio=1; else if(game_audio==1) game_audio=0;
}

void init_Setting_menu(){

     cls();
     printSettingMenu();

     char inputSel=getch();
     switch(inputSel)
     {
     case button_up://su
          if(sel>1)sel--;
          init_Setting_menu();
          break;
     case button_down://giu
          if(sel<4)sel++;
          init_Setting_menu();
          break;
     case button_right:
     case button_left:

          switch(sel)
            {
            case 1://AUDIO
                 togleAudio();

                break;
            case 2:
                changeDiff(inputSel);

                break;
            case 3:
                timechange(inputSel);
                break;
            }
          break;

     case 13://enter
          if(sel==4)
            {

                    SettingWrite(game_audio,game_difficult,game_duration);//default
                    init_menu();}
}
init_Setting_menu();
}






//}******************************************************************************

//{////////////////////////FUNCTION///////////////////////////////
void printRecords()
{
cls();
setcolor(WHITE,BLUE);
gotoxy(20,8);
printf("RECORDS");
gotoxy(20,9);
printf("        NAME               SCORE        ");
gotoxy(20,10);
printf("|-------------------|------------------|");
for(i=0;i<10;i++){
    gotoxy(20,11+3*i);
    printf("|                   |                  |");
    gotoxy(20,12+3*i);
    printf("|  %s                 |  %d               |\n",player_name,player_score);
    gotoxy(20,13+3*i);
    printf("|-------------------|------------------|");
    //printf("|------------------|------------------|");
}
gotoxy(20,10);
setcolor(WHITE,BLACK);
GetEnter();
}

void lose(){
//sconfitta
//quando si perde vengono visualizzati i punti del giocatore

cls();
//scherzetto :)
if(game_difficult==supermegaimpossible){
     gotoxy(0,10);
     setcolor(RED,BLACK);
     printf("\t\tLa difficolta' di gioco si chiama supermegaimpossibile\n\t\t\t e' inutile che ci provi!",player_name);
     player_score=666;
}

gotoxy(0,14);
setcolor(RED,BLACK);
printf("\t\t\t\tRISULTATO PARTITA\n");
setcolor(WHITE,BLACK);
printf("\t\t\t--------------------------------\n");
printf("\t\t\tHai perso %s!\n",player_name);
printf("\t\t\tPunti:\t%d",player_score);
Beep( 200,400);
Sleep(10);
Beep( 150,1000);
getchar();
}

void InitSetting(){
    //inizializzazione delle varibili di gioco in base alla difficolt�

    switch(game_difficult)
        {
        case easy:
                snake_speed=150;
                snake_size=2;
            break;
        case medium:
                snake_speed=100;
                snake_size=4;
            break;
        case difficult:
                snake_speed=60;
                snake_size=6;
            break;
        case impossible:
                snake_speed=45;
                snake_size=8;
            break;
        }
   appendscore=0;
   player_score=0;

   //load
   game_difficult=impossible;///debug

   game_audio=SettingGet(Saudio);
   game_difficult=SettingGet(Sdiff);
   game_duration=SettingGet(Stime);
}

void HeadCollision(char obj[],int type)
{
if(strcmp(obj,"border")==0) //se il collider � un bordo
    {

    switch(game_difficult)//in base alla difficolt� viene deciso cosa fare
        {
        case difficult:
            isPlaying=FALSE;
            break;
        case impossible:
            isPlaying=FALSE;
            break;
        default:
             switch(type)
                {
                case button_up:
                    VetSn[0].y=19;
                    break;
                case button_down:
                    VetSn[0].y=2;
                    break;
                case button_left:
                    VetSn[0].x=74;
                    break;
                case button_right:
                    VetSn[0].x=4;
                    break;
                }
            break;
        }
    }
 else if(strcmp(obj,"food")==0) //Se il collider � cibo
 {
   snake_size++;

   switch(type)//SWITCH DEL TIPO CI CIBO MANGIATO
   {
   case RED:
        appendscore=10;
        break;
   case BLUE:
        appendscore=15;
        break;
   case YELLOW:
        appendscore=150;
        break;
   case  WHITE:
        appendscore=200;
        break;
   case  CYAN:
        appendscore=1000;
        break;
   }

 }
}

void CollisionControl()
{

//COLLISIONI CON BORDI
if(VetSn[0].x==3) HeadCollision("border",button_left); //bordo sinistro
if(VetSn[0].x==75) HeadCollision("border",button_right); //bordo destro
if(VetSn[0].y==1) HeadCollision("border",button_up); //bordo alto
if(VetSn[0].y==20) HeadCollision("border",button_down); //bordo basso

//COLLISIONI CON CODA
for(s=1;s<snake_size;s++)
{
    if( (VetSn[0].x==VetSn[s].x) && (VetSn[0].y==VetSn[s].y))isPlaying=FALSE;
}

//COLLISIONI CON CIBO

int kk;
for(kk=0;kk<foodC;kk++)
    {

            if( (VetSn[0].x==FoodPoint[kk].x)&&(VetSn[0].y==FoodPoint[kk].y)){
                HeadCollision("food",FoodPoint[kk].tipo);
                //slittamento
                int sl;
                for(sl=0;sl<foodC;sl++)
                {
                    FoodPoint[kk]=FoodPoint[kk+1];
                }
                foodC--;

            }
    }

}

void spawnFood(int TypeOfFood)
{
    short rX,rY;
int nonspawna=0,fsnake=0;
do{
fsnake=0;
rX=(rand()%68+4);
rY=(rand()%15+4);
nonspawna++;
for(s=0;s<snake_size;s++){
        if(((rX==VetSn[s].x)&&(rY==VetSn[s].y)) || (rX==VetSn[s].x-1)&&(rY==VetSn[s].y) || (rX==VetSn[s].x+1)&&(rY==VetSn[s].y) || (rX==VetSn[s].x)&&(rY==VetSn[s].y-1) || (rX==VetSn[s].x)&&(rY==VetSn[s].y+1) || (rX==VetSn[s].x+1)&&(rY==VetSn[s].y-1) || (rX==VetSn[s].x-1)&&(rY==VetSn[s].y-1) || (rX==VetSn[s].x+1)&&(rY==VetSn[s].y+1) || (rX==VetSn[s].x-1)&&(rY==VetSn[s].y+1))
           {
               fsnake=1;
           }
 }

for(s=0;s<foodC;s++){
        if((rX==FoodPoint[s].x) && (rY==FoodPoint[s].y))
        {
            fsnake=1;
        }
}

}while(nonspawna<100&&fsnake==1);

for(s=0;s<foodC;s++)
{
    gotoxy(FoodPoint[s].x,FoodPoint[s].y);
    printf(" ");
}

FoodPoint[foodC].tipo=TypeOfFood;
FoodPoint[foodC].x=rX;
FoodPoint[foodC].y=rY;
foodC++;

for(s=0;s<foodC;s++)
{
    gotoxy(FoodPoint[s].x,FoodPoint[s].y);
    setcolor(FoodPoint[s].tipo,0);
    printf("%c",2);
}



setcolor(WHITE,BLACK);
}



void FoodGenerator()
{
food_chance=32000;
int raa = rand()%(food_chance);

if(foodC<4){
if((raa>=200)&&(raa<300)) spawnFood(RED);
if((raa>=120)&&(raa<200)) spawnFood(BLUE);
if((raa>=60)&&(raa<120)) spawnFood(YELLOW);
if((raa>=20)&&(raa<60)) spawnFood(WHITE);
if(raa<20) spawnFood(CYAN);
}


}

void printScore()
{
Beep(650,100);
Beep(600,100);
gotoxy(0,22);
printf("\tplayer name: %s\n",player_name);
printf("\tscore: %d",player_score);
}

void printMap()
{



void printStats()
{
cls();
setcolor(WHITE,BLUE);
gotoxy(20,8);
printf("RECORDS");
gotoxy(20,9);
printf("        NAME               SCORE        ");
gotoxy(20,10);
printf("|-------------------|------------------|");
for(i=0;i<10;i++){
    gotoxy(20,11+3*i);
    printf("|                   |                  |");
    gotoxy(20,12+3*i);
    printf("|  %s                 |  %d               |\n",player_name,player_score);
    gotoxy(20,13+3*i);
    printf("|-------------------|------------------|");
    //printf("|------------------|------------------|");
}
gotoxy(20,10);
setcolor(WHITE,BLACK);
GetEnter();
}
//PRINT MAPPA
system("cls");
for(i=0;i<19;i++)
{
gotoxy(3,2+i);
printf("%c",178);
gotoxy(75,2+i);
printf("%c",178);
}

for(i=0;i<73;i++)
{
gotoxy(i+3,1);
printf("%c",178);
gotoxy(i+3,20);
printf("%c",178);
}
}
//}******************************************************************************

//{//////////////////////////MENU/////////////////////////////////

void Records(){printRecords();}
void Credits(){
     cls();
     setcolor(RED,BLUE);
       gotoxy(20,9); printf("***************************************");
       gotoxy(20,10);printf("*                                     *");
       gotoxy(20,11);printf("*      Snake v1.0 creared by          *");
       gotoxy(20,12);printf("*             Bill Gates              *");
       gotoxy(20,13);printf("*             Steve Jobs              *");
       gotoxy(20,14);printf("*          Michele Minchioni          *");
       gotoxy(20,15);printf("*          Francesco I (Tuveri)       *");
       gotoxy(20,16);printf("*         David Sullivan Geirola      *");
       gotoxy(20,17);printf("*                                     *");
       gotoxy(20,18);printf("***************************************");
    setcolor(WHITE,BLACK);
     GetEnter();

}

void printfMainMenu()
{
     //item1

     gotoxy(30,10);
     if(sel==1){setcolor(RED,BLACK);}else{setcolor(WHITE,BLACK);}
     printf("%c    START GAME   %c",219,219);

     //item2
     gotoxy(30,12);
     if(sel==2){setcolor(RED,BLACK);}else{setcolor(WHITE,BLACK);}
     printf("%c     SETTINGS    %c",219,219);

     //item3
     gotoxy(30,14);
     if(sel==3){setcolor(RED,BLACK);}else{setcolor(WHITE,BLACK);}
     printf("%c     RECORDS     %c",219,219);

     //item3
     gotoxy(30,16);
     if(sel==4){setcolor(RED,BLACK);}else{setcolor(WHITE,BLACK);}
     printf("%c     CREDITS     %c",219,219);

     //item4
     gotoxy(30,18);
     if(sel==5){setcolor(RED,BLACK);}else{setcolor(WHITE,BLACK);}
     printf("%c     END GAME    %c",219,219);
}

void init_menu(){

     cls();
     printfMainMenu();

     char inputSel=getch();
     switch(inputSel)
     {
     case button_up://su
          if(sel>1)sel--;
          init_menu();
          break;
     case button_down://giu
          if(sel<5)sel++;
          init_menu();
          break;
     case 13://enter
          switch(sel)
           {
           case 1:
                Game();
                break;
           case 2:
                sel=1;
                init_Setting_menu();
                sel=2;
                break;
           case 3:
                Records();
                break;
           case 4:
                Credits();
                break;
           case 5:
                exit(0);
                break;
           }
           init_menu();
           break;
     case 27:
            exit(0);
            break;
     default:
            init_menu();
     }
}
//}******************************************************************************


//{/////////////////////////GAME/////////////////////////////////
void Game(){
//inizializzazione
InitSetting();
time(&TTstart);


//variabili
isPlaying=TRUE;
snake_size=snake_def_size;
int dir=button_right;
int direction=button_right;
printMap();

//Inizializzazione serpente

 for(s=0;s<snake_size;s++)
 {
  VetSn[s].x=40-s;
  VetSn[s].y=10;
 }


printScore();
//ciclo gioco
while(isPlaying==TRUE){

if(game_difficult==supermegaimpossible)isPlaying=FALSE;//scherzo :)
//modifica direzione
 if(kbhit()==1)
 {
  direction=getch();
  if(direction==27)isPlaying=FALSE;
  if((direction==button_left&&dir!=button_right)||(direction==button_right&&dir!=button_left)||(direction==button_up&&dir!=button_down)||(direction==button_down&&dir!=button_up))dir=direction;
  fflush(stdin);
 }

 Sleep(snake_speed);

//del snake
gotoxy(VetSn[snake_size].x,VetSn[snake_size].y);
printf(" ");

//shift snake
 for(s=snake_size-1;s>=0;s--){
     VetSn[s+1]=VetSn[s];
 }


//TIMER
UpTimer();

//increment snake position
  switch(dir)
  {
    case button_left:
                   VetSn[0].x -=1;
                   break;
    case button_right:
                   VetSn[0].x +=1;
                   break;
    case button_up:
                   VetSn[0].y -=1;
                   break;
    case button_down:
                   VetSn[0].y +=1;
                   break;
  }

//controllo collisioni
CollisionControl();

//creazione cibo
FoodGenerator();

//print snake
for(s=0;s<snake_size ;s++)
{
    gotoxy(VetSn[s].x,VetSn[s].y);
    printf("%c",254);
}

//print score
if(appendscore!=0){player_score+=appendscore;appendscore=0;printScore();}

}//end while

if(direction!=27)
lose();

}
//}******************************************************************************


//{//////////////////////////MAIN//////////////////////////////////
int main()
{
 intro();
InitSetting();
init_menu();
 return 0;
}
//}******************************************************************************


































