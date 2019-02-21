/* �O���t�ʐF���ɑ΂���ߎ���@(�T���v���v���O����) */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define MAX_N 2000  /* �ő�̒��_�� */

int n;  /* ���_�� */
int m;  /* �Ӑ� */
double x[MAX_N], y[MAX_N];  /* �e���_�̍��W */
int a[MAX_N][MAX_N];  /* �אڍs�� */
int color[MAX_N];  /* �F */
int max_color;  /* �ő�̐F�ԍ� */

/* �A���S���Y���{�� */
void sample(){

  int i;

  for(i = 0; i < n; i++){
    color[i] = i % 6;
  }
}


/* ���C���v���O���� */
int main(int argc, char *argv[]){

  FILE *input_file, *output_file;
  double start_time, search_time;
  int i,j,k1,k2;

  /* �����̃`�F�b�N */
  if(argc <= 1){
    fprintf(stderr,"Please input the name of data file!\n");
    exit(1);
  }

  /* ���̓f�[�^�̓ǂݍ��� */
  input_file = fopen(argv[1],"r");
  fscanf(input_file, "%d %d\n",&n, &m);
  for(i = 0; i < n; i++){
    fscanf(input_file,"%lf %lf\n",&(x[i]),&(y[i]));
  }
  for(i = 0; i < n; i++){  /* �אڍs��̏����� */
    for(j = 0; j < n; j++){
      a[i][j] = 0;
    }
  }
  for(i = 0; i < m; i++){
    fscanf(input_file,"%d %d\n",&k1,&k2);
    a[k1][k2] = a[k2][k1] = 1;
  }

  /* ���̏����� */
  for(i = 0; i < n; i++){
    color[i] = -1;
  }

  /* ���̓f�[�^�̕\�� */
  printf("n= %d\n",n);
  printf("m= %d\n",m);
  /* for(i = 0; i < n; i++){
    printf("%f\t%f\n",x[i],y[i]);
  }
  for(i = 0; i < n; i++){
    for(j = i+1; j < n; j++){
      if(a[i][j] == TRUE){
	printf("%d\t%d\n",i,j);
      }
    }
    } */

  /* �J�n�����̐ݒ� */
  start_time = (double)clock()/CLOCKS_PER_SEC;

  /* �A���S���Y���{�� */
  sample();

  /* ���s���Ԃ̑��� */
  search_time = (double)clock()/CLOCKS_PER_SEC - start_time;

  /* ��������̃`�F�b�N */
  for(i = 0; i < n; i++){
    if(color[i] == -1){
      printf("No color is assigned!: %d\n",i);
    }
  }
  for(i = 0; i < n; i++){
    for(j = i+1; j < n; j++){
      if(a[i][j] == 1 && color[i] == color[j]){
	printf("%d and %d have the same color %d!\n",i,j,color[i]);
      }
    }
  }

  /* ���̓f�[�^����щ����t�@�C���ɏo�� */
  output_file = fopen("result.txt","w");
  fprintf(output_file,"%d\t%d\n",n,m);
  for(i = 0; i < n; i++){
    fprintf(output_file,"%f\t%f\n",x[i],y[i]);
  }
  for(i = 0; i < n; i++){
    for(j = i+1; j < n; j++){
      if(a[i][j] == 1){
	fprintf(output_file,"%d\t%d\n",i,j);
      }
    }
  }
  for(i = 0; i < n; i++){
    fprintf(output_file, "%d\n",color[i]);
  }

  /* �ő�̐F�ԍ������߂� */
  max_color = -1;
  for(i = 0; i < n; i++){
    if(color[i] > max_color){
      max_color = color[i];
    }
  }

  /* ���s���ʂ���ʂɏo�� */
  printf("%d colors are used.\n",max_color+1);
  printf("Color assignment:\n");
  for(i = 0; i < n; i++){
    printf("%d ",color[i]);
  }
  printf("\n");

  /* ���s���Ԃ���ʂɏo�� */
  printf("CPU time: %f seconds.\n",search_time);

  return(0);
}
