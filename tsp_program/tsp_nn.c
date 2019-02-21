/* 巡回セールスマン問題に対するNearest Neighbor法 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <float.h>
#define MAX_CITY_NUM 3000  /* 最大都市数 */

struct point{  /* 都市の座標を格納する構造体 */
  double x;
  double y;
};

struct point city[MAX_CITY_NUM];  /* 外部変数: 都市の座標を格納する配列 */
int city_num;  /* 外部変数: 都市数 */
int tour[MAX_CITY_NUM];  /* 外部変数: 都市の巡回順を格納する配列 */

/* 関数の宣言 */
double distance(int i, int j);  /* 都市(i,j)間のユークリッド距離 */
void nearest_neighbor(int start_city);


/* メインプログラム */
int main(int argc, char *argv[]){
	
  FILE *input_file, *output_file;
  double length;
  int i;
  double start_time, search_time;
	
  /* 引数のチェック */
  if(argc <= 1){
    fprintf(stderr,"Please input the name of data file!\n");
    exit(1);
  }
	
  /* 入力データの読み込み */
  input_file = fopen(argv[1], "r");
  fscanf(input_file,"%d", &city_num);
  for(i = 0; i < city_num; i++){
    fscanf(input_file,"%lf %lf",&(city[i].x),&(city[i].y));
  }
  fclose(input_file);

  /* 入力データの表示 */
  printf("city_num= %d\n",city_num);
  for(i = 0; i < city_num; i++){
    printf("%4d\t%f\t%f\n",i,city[i].x,city[i].y);
  }

  /* 開始時刻の設定 */
  start_time = (double)clock()/CLOCKS_PER_SEC;

  /* Nearest Neighbor法の実行 */
  nearest_neighbor(0);

  /* 終了時刻の設定 */
  search_time = (double)clock()/CLOCKS_PER_SEC - start_time;

  /* 巡回路長の計算 */
  length = 0.0;
  for(i = 0; i < city_num; i++){
    length += distance(tour[i % city_num], tour[(i+1) % city_num]);
  }
  /* 都市データの出力 */
  output_file = fopen("result.dat","w");
  fprintf(output_file,"%d\n",city_num);
  for(i = 0; i < city_num; i++){
    fprintf(output_file,"%f %f\n",city[i].x,city[i].y);
  }

  /* 巡回路の出力 */
  length = 0.0;
  printf("\nTour: ");
  for(i = 0; i < city_num; i++){
    fprintf(output_file,"%d\n",tour[i]);
    printf("%d ",tour[i]);
    length += distance(tour[i],tour[(i+1) % city_num]);
  }
  fclose(output_file);
  printf("\nLength: %f\n",length);
  printf("CPU Time: %f\n",search_time);

  return(0);
}


/* 都市(i,j)間のユークリッド距離(小数以下は切上げ) */
double distance(int i, int j){

  double xd, yd;

  xd = city[i].x - city[j].x;
  yd = city[i].y - city[j].y;
  return((int)(sqrt(xd * xd + yd * yd) + 0.5));
}


/* Nearest Neighbor法 */
void nearest_neighbor(int start_city){

  double min_dist;
  int arg_min_dist, temp;
  int i,j;

  /* 巡回路を格納する配列の初期化 */
  tour[0] = start_city;
  j = 1;
  for(i = 0; i < city_num; i++){
    if(i != start_city){
      tour[j] = i;
      j++;
    }
  }

  for(i = 1; i < city_num-1; i++){

    /* 都市tour[i-1]に最も近い未訪問の都市を見つける */
    min_dist = FLT_MAX;
    arg_min_dist = -1;
    for(j = i; j < city_num; j++){
      if(distance(tour[i-1],tour[j]) < min_dist){
	min_dist = distance(tour[i-1],tour[j]);
	arg_min_dist = j;
      }
    }

    /* 都市tour[i]と都市tour[arg_min_dist]を入替える */
    temp = tour[i];
    tour[i] = tour[arg_min_dist];
    tour[arg_min_dist] = temp;
  }
}
