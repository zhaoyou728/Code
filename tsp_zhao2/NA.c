/*

#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "math.h"
#include "float.h"

#define MAX_CITY_NUM 3000

struct point{
  double x;
  double y;
};

struct point city[MAX_CITY_NUM];
int city_num;
int tour[MAX_CITY_NUM];

double distance(int i, int j);
void nearest_addition(int start_city);


int main(){
  int i;
  double start_time,search_time;
  double length;
  FILE *input,*output;
  input=fopen("berlin52.dat","r");
  fscanf(input,"%d",&city_num);
  for(i=0;i<city_num;++i){
    fscanf(input,"%lf %lf",city[i].x,city[i].y);
  }
  fclose(input);
  printf("city number is:%d\n",city_num);
  for(i=0;i<city_num;++i){
    printf("%d\tcity x is %lf\t y is %lf\n",i,city[i].x,city[i].y);
  }
  start_time=(double)clock()/CLOCKS_PER_SEC;

  nearest_addition(0);


  search_time=(double)clock()/CLOCKS_PER_SEC-start_time;

  output=fopen("result.dat","w");
  fprintf(output,"%d\n",city_num);
  for(i=0;i<city_num;++i){

    fprintf(output,"%f %f\n",city[i].x,city[i].y);

  }
  length=0.0;
  printf("\ntour: ");
  for(i=0;i<city_num;++i){
    fprintf(output,"%d",tour[i]);
    printf("%d",tour[i]);
    length+=distance(tour[i],tour[(i+1)%city_num]);

  }
  fclose(output);
  printf("\n length :%f\n",length);
  printf("cpu time is:%f\n",search_time);

  return(0);
  
}



void nearest_addition(int start_city){

  int part_tour_list[MAX_CITY_NUM];
  int part_num;
  int nearest_city[MAX_CITY_NUM];
  double nearest_city_distance[MAX_CITY_NUM];
  int min_distance_city;
  double min_distance;
  int i,j;
  for(i=0;i<city_num;++i){
    part_tour_list[i]=-1;
  }
  part_tour_list[start_city]=start_city;
  part_num=1;

  min_distance_city=-1;
  min_distance=FLT_MAX;
  for(i=0;i<city_num;++i){
    nearest_city_distance[i]=distance(i,start_city);
    nearest_city[i]=start_city;
    if(nearest_city[i]!=i&&nearest_city[i]<min_distance){

      min_distance_city=i;
      min_distance=nearest_city_distance[i];

    }

  }
  nearest_city[start_city]=start_city;
  nearest_city_distance[start_city]=0.0;
    while(part_num<city_num){
      part_tour_list[min_distance_city]=part_tour_list[nearest_city[min_distance_city]];
      part_tour_list[nearest_city[min_distance_city]]=min_distance_city;
      nearest_city[min_distance_city]=min_distance_city;
      nearest_distance_city[min_distance_city]=0.0;
      part_num++;
    }
  j=min_distance_city;
  min_distance_city=-1;
  min_distance_city=FLT_MAX;
  for(i=0;i<city_num;++i){
    if(nearest[i]!=i){
      if(nearest_city_distance[i]>distance(i,j)){
	nearest_city_distance[i]=distance(i,j);
	nearest_city[i]=j;

      }
      if(nearest_city_distance[i]<min_distacne){
	min_distance=nearest_city_distance[i];
	min_distance_city=i;

      }

    }

  }
}
tour[0]=0;
for(i=1;i<city_num;++i){
  tour[i]=part_tour_list[i-1];

 }
}



double distance(int i,int j){
  double xd,yd;
  xd=city[i].x-city[j].x;
  yd=city[i].y-city[j].y;

  return ((int)sqrt(xd*xd - yd*yd)+0.5);
}
*/


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
void nearest_addition(int start_city);

/* メインプログラム */
int main(int argc, char *argv[]){

  FILE *input_file, *output_file;
  double length;
  double start_time, search_time;
  int i;

  // if(argc <= 1){
  // fprintf(stderr,"Please input the name of data file!\n");
  //  exit(1);
  // }
	
  /* 入力データの読み込み */
  input_file = fopen("berlin52.dat", "r");
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

  /* Nearest Addition法の実行 */
  start_time = (double)clock()/CLOCKS_PER_SEC;
  nearest_addition(6);
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


/* Nearest Addition法 */
void nearest_addition(int start_city){

  int ptour_list[MAX_CITY_NUM];  /* 部分巡回路を格納するリスト */
  int pnum;  /* 部分巡回路に含まれる都市数 */
  int ncity[MAX_CITY_NUM];  /* 部分巡回路内の最も近い都市を格納する配列 */
  double ncity_dist[MAX_CITY_NUM];  /* 部分巡回路内の最も近い都市までの距離を格納する配列 */
  int min_dist_city;  /* 部分巡回路Tまでの距離が最小となる都市 */
  double min_dist;  /* 部分巡回路Tまでの距離が最小となる都市とTの間の距離 */
  int i,j;

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
  
    /* 部分巡回路Tに最も近い都市kをTに加える */
    ptour_list[min_dist_city] = ptour_list[ncity[min_dist_city]];
    ptour_list[ncity[min_dist_city]] = min_dist_city;
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
