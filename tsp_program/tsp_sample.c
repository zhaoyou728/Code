/* ランダムな巡回路を生成するプログラム */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
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
void random_tour();  /* ランダムな巡回路の生成 */


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

  /* ランダムな巡回路の生成 */
  random_tour();

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


/* ランダムな巡回路の生成 */
void random_tour(){

  int i,k;
  int temp;

  /* 順列を初期化 */
  for(i = 0 ; i < city_num; i++){
    tour[i] = i;
  }

  /* ランダム順列を作成 */
  for(i = 0; i < city_num; i++){
    k = (int)((double)rand() / ((double)RAND_MAX + 1) * (city_num - i)) + i;
    temp = tour[i];
    tour[i] = tour[k];
    tour[k] = temp;
  }
}
