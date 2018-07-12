#include<stdlib.h>
#include<stdio.h>
#include<conio.h>
#include<dos.h>
#define bwfb (7*16+1)
#define bwfr (7*16+4)
#define bwfw (7*16+7)
#define bbwfr (16*15+4)
void stage_generator();


char far *origin=(char*)0xB8000000;
char *message;
int h=-51,v=-70;
int s,stage=0;
int x[30],y[30];
void menu();

void stage_generator()
{int n=70,m=21;
int limit1,limit2;
int r1,r2;
char far *ptr;
 stage++;

limit1 =RAND_MAX-(RAND_MAX % n);
limit2 =RAND_MAX-(RAND_MAX % m);
for(s=0;s<(4+stage*2);s++)
{while((r1=rand())>=limit1);
while((r2=rand())>=limit2);
r1=(r1%n)+2;
r2=(r2%m)+2;
if((r1==20&&r2<6)||r2==6&&(r1>60&&r1<78)||(r1>2&&r1<30)&&r2==18||r1==60&&r2>18)
 s--;
 else
{ x[s]= r1;
  y[s]=r2;

}
}
ptr=origin;
for( s=0;s<4*80*25;s++)
{*ptr=32;
ptr++;
*ptr=7*16;
ptr++;}
ptr=origin+2*12*80+2*30;
message="stage :" ;
for( s=0;message[s]!='\0';s++)
{ if(message[s]=='\n')
{ptr=origin+(2*13*80)+28*2;
continue;}
*ptr=message[s];
ptr++;
*ptr=bwfb;
ptr++; }
*ptr=48+stage;
ptr++;
*ptr=bwfb;
ptr++;
delay(2000);

}

void text (char *message,int a)
{ char far *ptr;
 ptr=origin;
 ptr=ptr+(2*12*80)+30*2;
 for( s=0;message[s]!='\0';s++)
{ if(message[s]=='\n')
{ptr=origin+(2*13*80)+28*2;
continue;}
*ptr=message[s];
ptr++;
if(a==0)
*ptr=bwfb;
else
*ptr=bbwfr;
ptr++; }
getch();}
void gameover()
{text("GAME OVER !!!          ",1);
exit(0);
}
void main()
{char a=-37,b=32,blocks=-80,z,points=1,heart=3;
int k1=2,l1=2,k2=1,l2=1,k3=0,l3=0,k4=-1,l4=-1;
int life=0,point=0,counter=0;
int i,n,j,p,g,m;
int k=0;
char far *ptr;
stage=0;
menu();

for (n=0;n<1000;n++ )
{clrscr();
ptr=origin;
for( j=0;j<25;j++)
{
for(i=0;i<80;i++)
{if(j==0)
{if(i==5)
{message="points=";
for( s=0;message[s]!='\0';s++)
{
*ptr=message[s];
ptr++;
*ptr=bwfb;
ptr++; }
for( p=0;p<point;p++)
{*ptr=points;
ptr++;
*ptr=bwfr;
ptr++;}
i=11+point;}
else
if(i==40)
{ message="life=";
  for( s=0;message[s]!='\0';s++)
{
*ptr=message[s];
ptr++;
*ptr=bwfb;
ptr++; }


for(g=0;g<life;g++)
{
*ptr=heart;
ptr++;
*ptr=bwfr;
ptr++;
}
i=44+life;}
else if(i==60)
{ message="steps=";
  for( s=0;message[s]!='\0';s++)
{
*ptr=message[s];
ptr++;
*ptr=bwfb;
ptr++;
i++; }
*ptr=(48)+((99-k)/10);
ptr++;
i++;
*ptr=bwfb;
ptr++;
*ptr=(48)+((99-k)%10);
ptr++;
*ptr=bwfb;
ptr++;
i++;
k++;
if(k>=999)
exit(0);
   }


else
{*ptr=32;
ptr++;
*ptr=bwfw;
ptr++;
}}

else
if(j==1&&i==2)
{*ptr=-43;
ptr++;
*ptr=bwfb;
ptr++; }
else
if(j==24&&i==2)
{*ptr=-44;
ptr++;
*ptr=bwfb;
ptr++; }
else
if(j==1&&i==77)
{*ptr=-73;
ptr++;
*ptr=bwfb;
ptr++; }
else
if(j==24&&i==77)
{*ptr=-39;
ptr++;
*ptr=bwfb;
ptr++; }
else

if((j==1&&i>2&&i<77)||(j==24&&i>2&&i<=77))
{
*ptr=h;
ptr++;
*ptr=bwfb;
ptr++;
}
else if((i==2&&j>=1&&j<=24)||(i==77&&j>=1&&j<=24))
{
*ptr=v;
ptr++;
*ptr=bwfb;
ptr++;
}
else
if(i==20&&j<6||j==6&&(i>60&&i<78)||(i>2&&i<30)&&j==18||i==60&&j>18)
{*ptr=blocks;
ptr++;
*ptr=6;
ptr++;}
else if((i==k1)&&(j==l1)||(i==k2)&&(j==l2)||(i==k3)&&(j==l3)||(i==k4)&&(j==l4))
{*ptr=a;
ptr++;
*ptr=bbwfr;
ptr++;}
else
 {m=0;
 for(s=0;s<(stage*2+4);s++)
{
if(i==x[s]&&j==y[s])
{
*ptr=points;
ptr++;
*ptr=bbwfr;
ptr++;
m++;}}
if(m==0)
{*ptr=a;
 ptr++;
 *ptr=bwfw;
 ptr++;}}


 } }
 if(kbhit())
 {delay(125);
z=getch();
if(z=='s')
{
k4=k3;l4=l3;
k3=k2;l3=l2;
k2=k1;l2=l1;
if((l1+1)%24==0)
{l1=3;}
else{l1++;}
}else
if(z=='p')
{menu();}
else
if(z=='d')
{
k4=k3;l4=l3;
k3=k2;l3=l2;
k2=k1;l2=l1;
if((k1+1)%78==0)
{k1=1;}
else{
k1++;}}
else if(z=='a')
{
k4=k3;l4=l3;
k3=k2;l3=l2;
k2=k1;l2=l1;
if((k1-1)==2)
{k1=77;}
else{
k1--;}

}
else if(z=='w')
{
k4=k3;l4=l3;
k3=k2;l3=l2;
k2=k1;l2=l1;
if((l1-1)==1)
{l1=24;}
else{ l1--;}}
}else
{ delay(250);
if(z=='s')
{
k4=k3;l4=l3;
k3=k2;l3=l2;
k2=k1;l2=l1;
if((l1+1)%24==0)
{l1=3;}
else{l1++;}
}
else
if(z=='d')
{
k4=k3;l4=l3;
k3=k2;l3=l2;
k2=k1;l2=l1;
if((k1+1)%78==0)
{k1=1;}
else{
k1++;}}
else if(z=='a')
{
k4=k3;l4=l3;
k3=k2;l3=l2;
k2=k1;l2=l1;
if((k1-1)==2)
{k1=77;}
else{
k1--;}

}
else if(z=='w')
{
k4=k3;l4=l3;
k3=k2;l3=l2;
k2=k1;l2=l1;
if((l1-1)==1)
{l1=24;}
else{ l1--;}}

}
for(s=0;s<(stage*2+4);s++)
{
if(k1==x[s]&&l1==y[s])
 {point++;
  x[s]=-1;
 y[s]=-1;
 counter++;}}
 if (counter==(stage*2+4))
 {text("congratulation!! \n you won the stage",1);
 stage_generator();
 point=0;
 counter=0;
 life=0;
  k1=2;l1=2;k2=1;l2=1;k3=0;l3=0;k4=-1;l4=-1;}
 if((point%3==0&&point!=0)&&(life<3))
 {life++;
 point=point-3;}
 if((k1==20&&l1<6)||(l1==6&&k1>60)||(k1<30&&l1==18)||(k1==60&&l1>18))
 {text("sorry, you died !!",0);
 if(life==0)
 {
 gameover();}
 else{--life;
      text("you still have life.\n press key to restart",0);

       k1=2;l1=2;k2=1;l2=1;k3=0;l3=0;k4=-1;l4=-1;}

  }
}getch();}
void menu()
{int u=1,i,j;
char ch;
char far *ptr;


while(1)
{ptr=origin;
for(j=0;j<25;j++)
{
 for( i=0;i<80;i++)
{
if(j==1&&i==2)
{*ptr=-43;
ptr++;
*ptr=bwfb;
ptr++; }
else
if(j==24&&i==2)
{*ptr=-44;
ptr++;
*ptr=bwfb;
ptr++; }
else
if(j==1&&i==77)
{*ptr=-73;
ptr++;
*ptr=bwfb;
ptr++; }
else
if(j==24&&i==77)
{*ptr=-39;
ptr++;
*ptr=bwfb;
ptr++; }
else

if((j==1&&i>2&&i<77)||(j==24&&i>2&&i<=77))
{
*ptr=h;
ptr++;
*ptr=bwfb;
ptr++;
}
else if((i==2&&j>=1&&j<=24)||(i==77&&j>=1&&j<=24))
{
*ptr=v;
ptr++;
*ptr=bwfb;
ptr++;
}
else
{*ptr=32;
ptr++;
*ptr=7*16;
ptr++;}
}}
ptr=origin+2*12*80+2*30;
message="=>restart" ;
for( s=0;message[s]!='\0';s++)
{
*ptr=message[s];
ptr++;
if(u==2)
{
*ptr=bbwfr;
ptr++;}
else
{*ptr=bwfb;
ptr++;}
 }
ptr=origin+2*13*80+2*30;
message="=>exit";
for( s=0;message[s]!='\0';s++)
{
*ptr=message[s];
ptr++;
if(u==3)
{
*ptr=bbwfr;
ptr++;}
else
{*ptr=bwfb;
ptr++;}}
if (stage!=0)
{ptr=origin+2*11*80+2*30;
message="=>resume";
for( s=0;message[s]!='\0';s++)
{
*ptr=message[s];
ptr++;
if(u==1)
{
*ptr=bbwfr;
ptr++;}
else
{*ptr=bwfb;
ptr++;} }
 }
 else
 {ptr=origin+2*11*80+2*35;
message="MENU";
for( s=0;message[s]!='\0';s++)
{
*ptr=message[s];
ptr++;
if(u==1)
{
*ptr=bbwfr;
ptr++;}
else
{*ptr=bwfb;
ptr++;} } }
ch=getch();
if(ch=='\r')
{if(u==1)
{ if(stage!=0)
break;}
else if(u==2)
{stage=0;
stage_generator();
break;}
if(u==3)
{exit(0);}

}

else if(ch=='w')
{if(u==1)
u=3;
else
u--;}
else if(ch=='s')
{if(u==3)
u=1;
else
u++;}


}

}

