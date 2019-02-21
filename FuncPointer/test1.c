/*
#include"stdio.h"


int myfunc(int a,int b){
  if(a>b)}
    return 1;
} else{
    return -1;
}
}
void sortarray(int array,int n,int (*p)(int a,int b)){
  for(int i=1;i<=n;n++){
    for(int j=0;j<n-i;j++){
      if(p(array[j],array[j+1])>0){
	int temp;
	temp=array[j];
        array[j]=array[j+1];                   	
	array[j+1]=temp;
      }
    }
  }
  return ;
}


void PRI(int *arr,int a){
  for(int i=0;i<a;i++){
    printf("%d",*(arr+i));
  }
  return ;
}

int main(void){
  int array[5]={1,3,5,2,9};
  sortarray(array,5,myfunc);
  PRI(array,5);
}

*/
/*
#include"stdio.h"
#include"stdlib.h"
#include"time.h"
#define t 20
#define l 60
#define v 26

void SET();
void CARPLANNING();
void NEXT();
void PRINT();
int a[t][l];

int main(void){
 SET();
 CARPLANNING();
 NEXT();
 PRINT();
  
}
void SET(){
    for( int b=0;b<t;++b) //������
    {
    for(int c=0;c<l;++c)
      {
      a[b][c]=0;
    }
  }
}

void CARPLANNING(){
  int cellnum;
  srand(time(0));
  for(int c=0;c<v;++c)//�Ԃ̏����z�u
    { 
    cellnum=rand()%l;
    if(a[0][cellnum]==1){
      c=c-1;
      continue;
    }
    a[0][cellnum]=1;
  }
}

void NEXT(){
  for(int b=1;b<t;++b)//�Ԃ̈ʒu�̍X�V
    {
    for(int c=0;c<l;++c){
      if(a[b-1][c]==1){
	if(a[b-1][(c+1)%l]==0){
	  a[b][(c+1)%l]=1;
	}
	else{
	  a[b][c]=1;
	    }
      }
    }
    }
}
void PRINT(){
  for(int b=0;b<t;++b) //print����
    {
    for(int c=0;c<l;++c)
      {
	printf("%d ",a[b][c]);
    }
    printf("\n");
  }
}
*/
#include"stdio.h"

/*
int i;
int myfunc();

int main(void){

  myfunc(3,5,7);
  return 0;

}

int myfunc(int a,int b,int c){
  int i;
  for(i=0;i<1000;++i){
    if(i%a==0 && i%b==0 && i%c==0){
      printf("%d\n",i);
    }
  }
}
*/
/*
double MIN();
void PRINT();

int main(void){
  double a=20,b=37;
  double min;
  min=MIN(a,b);
  PRINT(min);
  return 0;
}

double MIN(double a,double b){
  return a>b?a:b;
}

void PRINT(double a){
  printf("%f",a);
}
*/
#include"string.h"
void PRINT();
void UPP();
int* findmax(int a,int b);
void printstr(char *str);
int main(void){
  int arr[6]={1,3,5,7,8,9};
  UPP(arr,6);
  PRINT(arr,6);
  int n=*findmax(20,5);

  printf("%d\n",n);
  char str[100]="";
  scanf("%s",str);
  printstr(str);
  printf("%s\n");
}

void PRINT(int *a,int n){
  for(int i=0;i<n;++i){
    printf("%d\n",*(a+i));
  }
}

void UPP(int *a,int n){
    for(int i=0;i<n;++i){
   a[i]*=10;
    }
}

int* findmax(int a,int b){
  int *result=NULL;
  if(a>b){
    result= &a;
    }
  else{
  result= &b;
}
  return result;
}

void printstr(char *str){
  int nlen=(int)strlen(str);
  for(int i=1;i<=nlen;++i){
    int flag=0;
    for(int j=0;j<nlen-i;++j){
      if(str[j]>str[j+1]){
	char temp=str[j];
	str[j]=str[j+1];
	str[j+1]=temp;
	flag=1;
      }
    }
    if(flag==0){
      break;
    }
  }
}
