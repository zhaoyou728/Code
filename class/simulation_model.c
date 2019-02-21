#include"stdio.h"
#include"stdlib.h"
#include"time.h"
#define t 6
#define l 10
#define v 4

void RESET();
void CAR_PLANNING();
void NEXT_POSITION();
void PRINT();
int a[t][l];
float pro;

int main(void){
 printf("put in the pro:/n");
 scanf("%f",&pro);
 RESET();
 CAR_PLANNING();
 NEXT_POSITION();
 PRINT();
 
}
void RESET(){
    for( int b=0;b<t;++b) //初期化
    {
    for(int c=0;c<l;++c)
      {
      a[b][c]=0;
    }
  }
}

void CAR_PLANNING(){
  int cellnum;
   srand(time(0));
  for(int c=0;c<v;++c)//車の初期配置
    { 
    cellnum=rand()%l;
    if(a[0][cellnum]==1){
      c=c-1;
      continue;
    }
    a[0][cellnum]=1;
  }
}

void NEXT_POSITION(){
  srand((unsigned)time(NULL));
  float p;
  for(int b=1;b<t;++b)//車の位置の更新
    {
    for(int c=0;c<l;++c){
      if(a[b-1][c]==1){
	if(a[b-1][(c+1)%l]==0){
	  p=rand()/(float)(RAND_MAX+1);
      	  if(p<=pro){
	  a[b][(c+1)%l]=1;
        }
	}
	else{
 	  a[b][c]=1;
	    }
      }
    }
    }
  // printf("%.1f\n",p);
}
void PRINT(){
  for(int b=0;b<t;++b) //print結果
    {
    for(int c=0;c<l;++c)
      {
	printf("%d ",a[b][c]);
    }
    printf("\n");
  }
}
