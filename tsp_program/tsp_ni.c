/* 巡回セールスマン問題に対するNearest Insertion法 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <float.h>
#include <time.h>
#define MAX_CITY_NUM 3000  /* 都市数の上限 */

struct point{  /* 都市の座標 */
  double x;
  double y;
};

struct point city[MAX_CITY_NUM];  /* 外部変数: 各都市の座標を格納する配列 */
int city_num;  /* 外部変数: 都市数 */
int tour[MAX_CITY_NUM];  /* 外部変数: 都市の巡回順を格納する配列 */

/* 関数の宣言 */
double distance(int i, int j);
void nearest_insertion(int start_city);

/* メインプログラム */
int main(int argc, char *argv[]){

  FILE *input_file, *output_file;
  double length;
  double start_time, search_time;
  int i;

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

  /* Nearest Insertion法の実行 */
  start_time = (double)clock()/CLOCKS_PER_SEC;
  nearest_insertion(0);
  search_time = (double)clock()/CLOCKS_PER_SEC - start_time;

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
  return((int)(sqrt(xd * xd + yd * yd)+0.5));
}


/* Nearest Insertion法 */
void nearest_insertion(int start_city){

  int ptour_list[MAX_CITY_NUM];  /* 部分巡回路を格納するリスト */
  int pnum;  /* 部分巡回路に含まれる都市数 */
  int ncity[MAX_CITY_NUM];  /* 部分巡回路内の最も近い都市を格納する配列 */
  double ncity_dist[MAX_CITY_NUM];  /* 部分巡回路内の最も近い都市までの距離を格納する配列 */
  int min_dist_city;  /* 部分巡回路Tまでの距離が最小となる都市 */
  double min_dist;  /* 部分巡回路Tまでの距離が最小となる都市とTの間の距離 */
  double delta, min_delta;
  int min_delta_city;
  int i,j,k;

  /* start_cityのみからなる部分巡回路Tを作成する */
  for(i = 0; i < city_num; i++){
    ptour_list[i] = -1;
  }
  ptour_list[start_city] = start_city;  
  pnum = 1;

  /* 各都市から部分巡回路Tへの距離を計算し，Tに最も近い都市およびその距離を求める */
  min_dist_city = -1;
  min_dist = FLT_MAX;
  for(i = 0; i < city_num; i++){
    ncity_dist[i] = distance(i, start_city);
    ncity[i] = start_city;
    if(ncity[i] != i && ncity_dist[i] < min_dist){
      min_dist_city = i;
      min_dist = ncity_dist[i];
    }
  }
  ncity[start_city] = start_city;
  ncity_dist[start_city] = 0.0;

  while(pnum < city_num){

    /* 都市min_dist_cityを挿入する場所を決定する */
    min_delta_city = -1;
    min_delta = FLT_MAX;
    k = 0;
    for(i = 0; i < pnum; i++){
      delta = distance(k,min_dist_city) + distance(min_dist_city, ptour_list[k]) - distance(k,ptour_list[k]);
      if(delta < min_delta){
	min_delta = delta;
	min_delta_city = k;
      }
      k = ptour_list[k];
    }

    /* 部分巡回路Tに最も近い都市min_dist_cityを加える */
    ptour_list[min_dist_city] = ptour_list[min_delta_city];
    ptour_list[min_delta_city] = min_dist_city;
    ncity[min_dist_city] = min_dist_city;
    ncity_dist[min_dist_city] = 0.0;
    pnum++;

    /* 部分巡回路Tに含まれない各都市の部分巡回路までの距離を更新する */
    j = min_dist_city;
    min_dist_city = -1;
    min_dist = FLT_MAX;
    for(i = 0; i < city_num; i++){
      if(ncity[i] != i){
	if(ncity_dist[i] > distance(i,j)){
	  ncity_dist[i] = distance(i,j);
	  ncity[i] = j;
	}
	if(ncity_dist[i] < min_dist){
	  min_dist = ncity_dist[i];
	  min_dist_city = i;
	}
      }
    }
  }
  
  /* 部分巡回路リストから巡回路を作成する */
  tour[0] = 0;
  for(i = 1; i < city_num; i++){    
    tour[i] = ptour_list[tour[i-1]];
  }
}
