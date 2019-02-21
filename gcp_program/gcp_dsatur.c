/* グラフ彩色問題に対する近似解法: DSATUR */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define MAX_N 2000  /* 最大の頂点数 */

int n;  /* 頂点数 */
int m;  /* 辺数 */
double x[MAX_N], y[MAX_N];  /* 各頂点の座標 */
int a[MAX_N][MAX_N];  /* 隣接行列 */
int color[MAX_N];  /* 色 */
int max_color;  /* 最大の色番号 */
int deg[MAX_N];  /* 各頂点の次数 */
int rdeg[MAX_N];  /* 残余グラフにおける各頂点の次数 */
int slist[MAX_N][MAX_N];  /* 各頂点の飽和リスト */
int sdeg[MAX_N];  /* 各頂点の飽和次数 */
int safe_color[MAX_N];  /* 安全な色番号 */

/* アルゴリズム本体: DSATUR */
void dsatur(){

  int max_sdeg, arg_max_sdeg;
  int i,j;

  /* 色，残余次数の初期化 */
  for(i = 0; i < n; i++){
    color[i] = -1;
    rdeg[i] = deg[i];
  }
  max_color = 0;

  /* 飽和リスト，飽和次数の初期化 */
  for(i = 0; i < n; i++){
    sdeg[i] = 0;
    for(j = 0; j < n; j++){
      slist[i][j] = 0;
    }
  }
  
  for(i = 0; i < n; i++){

    /* 飽和次数最大の頂点を選択(タイの場合は残余次数が大きいものを優先) */
    max_sdeg = -1;
    arg_max_sdeg = -1;
    for(j = 0; j < n; j++){
      if(color[j] == -1){
	if(sdeg[j] > max_sdeg || (sdeg[j] == max_sdeg && rdeg[j] > rdeg[arg_max_sdeg])){
	  max_sdeg = sdeg[j];
	  arg_max_sdeg = j;
	}
      }
    }

    /* 安全な色番号の更新 */
    for(j = 0; j < n; j++){
      safe_color[j] = 1;
    }
    for(j = 0; j < n; j++){
      if(a[arg_max_sdeg][j] == 1 && color[j] > -1){
	safe_color[color[j]] = 0;
      }
    }

    /* 安全な最小の色番号を見つける */
    for(j = 0; j < n; j++){
      if(safe_color[j] == 1){
	color[arg_max_sdeg] = j;
	if(color[arg_max_sdeg] > max_color){
	  max_color = color[arg_max_sdeg];
	}
	break;
      }
    }

    /* 飽和リスト，飽和次数の更新 */
    for(j = 0; j < n; j++){
      if(a[arg_max_sdeg][j] == 1){
	if(slist[j][color[arg_max_sdeg]] == 0){
	  sdeg[j]++;
	}
	slist[j][color[arg_max_sdeg]] = 1;	
      }
    }

    /* 残余次数の更新 */
    for(j = 0; j < n; j++){
      if(a[arg_max_sdeg][j] == 1){
	rdeg[j]--;
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
      a[i][j] = 0;
    }
  }
  for(i = 0; i < n; i++){  /* 各頂点の次数の初期化 */
    deg[i] = 0;
  }
  for(i = 0; i < m; i++){
    fscanf(input_file,"%d %d\n",&k1,&k2);
    a[k1][k2] = a[k2][k1] = 1;
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
      if(a[i][j] == 1){
	printf("%d\t%d\n",i,j);
      }
    }
    } */

  /* 開始時刻の設定 */
  start_time = (double)clock()/CLOCKS_PER_SEC;

  /* アルゴリズム本体: dsatur */
  dsatur();

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
