/* グラフ彩色問題に対する近似解法: RLF(Recursive Largest First Algorithm) */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define TRUE 1
#define FALSE 0
#define MAX_N 2000  /* 最大の頂点数 */

int n;  /* 頂点数 */
int m;  /* 辺数 */
double x[MAX_N], y[MAX_N];  /* 各頂点の座標 */
int a[MAX_N][MAX_N];  /* 隣接行列 */
int color[MAX_N];  /* 色 */
int max_color;  /* 最大の色番号 */
int deg[MAX_N];  /* 各頂点の次数 */
int V[MAX_N], U[MAX_N];

/* アルゴリズム本体: RLF */
void rlf(){

  int max_deg, arg_max_deg;
  int cut[MAX_N], max_cut, arg_max_cut;
  int num_V, num_color;
  int i,j,k,c;

  /* 色の初期化 */
  max_color = -1;
  for(i = 0; i < n; i++){
    color[i] = -1;
  }  
  
  num_color = 0;
  for(c = 0; num_color < n; c++){
    
    /* 集合U,Vを初期化 */
    for(i = 0; i < n; i++){
      if(color[i] == -1){
	V[i] = TRUE;
      }else{
	V[i] = FALSE;
      }
      U[i] = FALSE;
    }
    
    /* 次数最大の頂点を探す */
    max_deg = -1;
    arg_max_deg = -1;
    for(i = 0; i < n; i++){
      if(V[i] == TRUE && deg[i] > max_deg){
	max_deg = deg[i];
	arg_max_deg = i;
      }
    }
    
    /* 1番目の頂点を彩色する */
    color[arg_max_deg] = c;
    V[arg_max_deg] = U[arg_max_deg] = FALSE;
    for(i = 0; i < n; i++){
      if(V[i] == TRUE && a[arg_max_deg][i] == TRUE){
	V[i] = FALSE;
	U[i] = TRUE;
      }
    }

    /* 集合V内の要素数を数える */
    num_V = 0;
    for(i = 0; i < n; i++){
      if(V[i] == TRUE){
	num_V++;
      }
    }

    /* 2番目以降の頂点を彩色する */
    while(num_V > 0){
      
      /* カットの更新 */
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
      
      /* カット最大の頂点を選択 */
      max_cut = -1;
      arg_max_cut = -1;
      for(j = 0; j < n; j++){
	if(V[j] == TRUE && cut[j] > max_cut){
	  max_cut = cut[j];
	  arg_max_cut = j;
	}
      }

      /* 選択した頂点を彩色 */
      color[arg_max_cut] = c;
      V[arg_max_cut] = U[arg_max_cut] = FALSE;
      for(j = 0; j < n; j++){
	if(V[j] == TRUE && a[arg_max_cut][j] == TRUE){
	  V[j] = FALSE;
	  U[j] = TRUE;
	}
      }            

      /* 集合V内の要素数を数える */
      num_V = 0;
      for(j = 0; j < n; j++){
	if(V[j] == TRUE){
	  num_V++;
	}
      }
    }

    /* 彩色済みの頂点数を数える */
    num_color = 0;
    for(i = 0; i < n; i++){
      if(color[i] > -1){
	num_color++;
      }
    }
  }
}


/* メインプログラム */
int main(int argc, char *argv[]){

  FILE *input_file, *output_file;
  double start_time, search_time;
  int i,j,k1,k2;

  /* 引数のチェック */
  if(argc <= 1){
    fprintf(stderr,"Please input the name of data file!\n");
    exit(1);
  }

  /* 入力データの読み込み */
  input_file = fopen(argv[1],"r");
  fscanf(input_file, "%d %d\n",&n, &m);
  for(i = 0; i < n; i++){
    fscanf(input_file,"%lf %lf\n",&(x[i]),&(y[i]));
  }
  for(i = 0; i < n; i++){  /* 隣接行列の初期化 */
    for(j = 0; j < n; j++){
      a[i][j] = FALSE;
    }
  }
  for(i = 0; i < n; i++){  /* 各頂点の次数の初期化 */
    deg[i] = 0;
  }
  for(i = 0; i < m; i++){
    fscanf(input_file,"%d %d\n",&k1,&k2);
    a[k1][k2] = a[k2][k1] = TRUE;
    deg[k1]++;
    deg[k2]++;
  }

  /* 入力データの表示 */
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

  /* 開始時刻の設定 */
  start_time = (double)clock()/CLOCKS_PER_SEC;

  /* アルゴリズム本体: RLF */
  rlf();

  /* 実行時間の測定 */
  search_time = (double)clock()/CLOCKS_PER_SEC - start_time;

  /* 制約条件のチェック */
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

  /* 入力データおよび解をファイルに出力 */
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

  /* 最大の色番号を求める */
  max_color = -1;
  for(i = 0; i < n; i++){
    if(color[i] > max_color){
      max_color = color[i];
    }
  }

  /* 実行結果を画面に出力 */
  printf("%d colors are used.\n",max_color+1);
  printf("Color assignment:\n");
  for(i = 0; i < n; i++){
    printf("%d ",color[i]);
  }
  printf("\n");

  /* 実行時間を画面に出力 */
  printf("CPU time: %f seconds.\n",search_time);

  return(0);
}
