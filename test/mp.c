#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define I 3
#define K 3


int m[I][K];
void beginning();
int swap(int m[I][K],int row1,int col1,int row2,int col2);
int function(int [I][K]);
int main(){
  srand((unsigned int)time(0));
  beginning();
  swap(m,0,0,0,2);
  for(int i=0;i<I;i++){
    for(int k=0;k<K;k++){
      printf("m[%d][%d]=%d\n",i,k,m[i][k]);
    }
  }
  
  printf("%d",function(m));
  return 0;
}


void beginning(){
  
  int i,k;
  for(i=0;i<I;i++){
    for(k=0;k<K;k++){
      m[i][k]=0;
    }

  }
  
  for( k=0;k<K;k++){
    m[rand()%I][k]=1;
    }
  for(i=0;i<I;i++){
    for(k=0;k<K;k++){
      printf("m[%d][%d]=%d\n",i,k,m[i][k]);
    }

  }
  printf("#######################\n");

}

int swap(int m[I][K],int row1,int col1,int row2,int col2){
  int temp;
  temp=m[row1][col1];
  m[row1][col1]=m[row2][col2];
  m[row2][col2]=temp;
}

int function(int m[I][K]){
  int f[I][K]={{3,4,5},{4,5,6},{5,6,7}};
  int result=0;
  for(int i=0;i<I;i++){
    for(int k=0;k<K;k++){
      result+=m[i,k]*f[i,k];
     }
  }
  return result;

}
