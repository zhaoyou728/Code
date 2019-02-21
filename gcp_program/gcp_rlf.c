/* �O���t�ʐF���ɑ΂���ߎ���@: RLF(Recursive Largest First Algorithm) */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define TRUE 1
#define FALSE 0
#define MAX_N 2000  /* �ő�̒��_�� */

int n;  /* ���_�� */
int m;  /* �Ӑ� */
double x[MAX_N], y[MAX_N];  /* �e���_�̍��W */
int a[MAX_N][MAX_N];  /* �אڍs�� */
int color[MAX_N];  /* �F */
int max_color;  /* �ő�̐F�ԍ� */
int deg[MAX_N];  /* �e���_�̎��� */
int V[MAX_N], U[MAX_N];

/* �A���S���Y���{��: RLF */
void rlf(){

  int max_deg, arg_max_deg;
  int cut[MAX_N], max_cut, arg_max_cut;
  int num_V, num_color;
  int i,j,k,c;

  /* �F�̏����� */
  max_color = -1;
  for(i = 0; i < n; i++){
    color[i] = -1;
  }  
  
  num_color = 0;
  for(c = 0; num_color < n; c++){
    
    /* �W��U,V�������� */
    for(i = 0; i < n; i++){
      if(color[i] == -1){
	V[i] = TRUE;
      }else{
	V[i] = FALSE;
      }
      U[i] = FALSE;
    }
    
    /* �����ő�̒��_��T�� */
    max_deg = -1;
    arg_max_deg = -1;
    for(i = 0; i < n; i++){
      if(V[i] == TRUE && deg[i] > max_deg){
	max_deg = deg[i];
	arg_max_deg = i;
      }
    }
    
    /* 1�Ԗڂ̒��_���ʐF���� */
    color[arg_max_deg] = c;
    V[arg_max_deg] = U[arg_max_deg] = FALSE;
    for(i = 0; i < n; i++){
      if(V[i] == TRUE && a[arg_max_deg][i] == TRUE){
	V[i] = FALSE;
	U[i] = TRUE;
      }
    }

    /* �W��V���̗v�f���𐔂��� */
    num_V = 0;
    for(i = 0; i < n; i++){
      if(V[i] == TRUE){
	num_V++;
      }
    }

    /* 2�Ԗڈȍ~�̒��_���ʐF���� */
    while(num_V > 0){
      
      /* �J�b�g�̍X�V */
      for(j = 0; j < n; j++){
	if(V[j] == TRUE){
	  cut[j] = 0;
	  for(k = 0; k < n; k++){
	    if(a[j][k] == TRUE && U[k] == TRUE){
	      cut[j]++;
	    }
	  }
	}
      }
      
      /* �J�b�g�ő�̒��_��I�� */
      max_cut = -1;
      arg_max_cut = -1;
      for(j = 0; j < n; j++){
	if(V[j] == TRUE && cut[j] > max_cut){
	  max_cut = cut[j];
	  arg_max_cut = j;
	}
      }

      /* �I���������_���ʐF */
      color[arg_max_cut] = c;
      V[arg_max_cut] = U[arg_max_cut] = FALSE;
      for(j = 0; j < n; j++){
	if(V[j] == TRUE && a[arg_max_cut][j] == TRUE){
	  V[j] = FALSE;
	  U[j] = TRUE;
	}
      }            

      /* �W��V���̗v�f���𐔂��� */
      num_V = 0;
      for(j = 0; j < n; j++){
	if(V[j] == TRUE){
	  num_V++;
	}
      }
    }

    /* �ʐF�ς݂̒��_���𐔂��� */
    num_color = 0;
    for(i = 0; i < n; i++){
      if(color[i] > -1){
	num_color++;
      }
    }
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
      a[i][j] = FALSE;
    }
  }
  for(i = 0; i < n; i++){  /* �e���_�̎����̏����� */
    deg[i] = 0;
  }
  for(i = 0; i < m; i++){
    fscanf(input_file,"%d %d\n",&k1,&k2);
    a[k1][k2] = a[k2][k1] = TRUE;
    deg[k1]++;
    deg[k2]++;
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

  /* �A���S���Y���{��: RLF */
  rlf();

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
