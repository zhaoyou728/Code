/* グラフ彩色問題に対する逐次法 */

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
int order[MAX_N];  /* 各頂点の彩色順 */

/* 挿入ソート */
void inssort_value(){

  int i,j,x1,x2;
  
  for(i = 0; i < n; i++){
    order[i] = i;
  }
  for(i = 0; i < n; i++){
    x1 = deg[i];
    x2 = order[i];
    for(j = i-1; j >= 0 && deg[j] < x1; j--){
      deg[j+1] = deg[j];
      order[j+1] = order[j];
    }
    deg[j+1] = x1;
    order[j+1] = x2;
  }
}

/* 逐次法 */
void seq(){

  int safe_color[MAX_N];  /* 安全な色番号 */
  int i,j,k;

  /* 色の初期化 */
  max_color = -1;
  for(i = 0; i < n; i++){
    color[i] = -1;
  }  
  
  /* 逐次法 */
  for(i = 0; i < n; i++){
    k = order[i];

    /* 安全な色番号を調べる */
    for(j = 0; j < n; j++){
      safe_color[j] = TRUE;
    }
    for(j = 0; j < n; j++){
      if(a[k][j] == TRUE && color[j] > -1){
	safe_color[color[j]] = FALSE;
      }
    }

    /* 安全な最小色番号を見つける */
    for(j = 0; j < n; j++){
      if(safe_color[j] == TRUE){
	color[k] = j;
	if(color[k] > max_color){
	  max_color = color[k];
	}
	break;
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

  /* 頂点を次数の降順にソート */
  inssort_value();

  /* 逐次法の実行 */
  seq();

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
