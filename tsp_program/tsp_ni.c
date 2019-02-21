/* „‰ñƒZ[ƒ‹ƒXƒ}ƒ“–â‘è‚É‘Î‚·‚éNearest Insertion–@ */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <float.h>
#include <time.h>
#define MAX_CITY_NUM 3000  /* “ss”‚ÌãŒÀ */

struct point{  /* “ss‚ÌÀ•W */
  double x;
  double y;
};

struct point city[MAX_CITY_NUM];  /* ŠO•”•Ï”: Še“ss‚ÌÀ•W‚ğŠi”[‚·‚é”z—ñ */
int city_num;  /* ŠO•”•Ï”: “ss” */
int tour[MAX_CITY_NUM];  /* ŠO•”•Ï”: “ss‚Ì„‰ñ‡‚ğŠi”[‚·‚é”z—ñ */

/* ŠÖ”‚ÌéŒ¾ */
double distance(int i, int j);
void nearest_insertion(int start_city);

/* ƒƒCƒ“ƒvƒƒOƒ‰ƒ€ */
int main(int argc, char *argv[]){

  FILE *input_file, *output_file;
  double length;
  double start_time, search_time;
  int i;

  if(argc <= 1){
    fprintf(stderr,"Please input the name of data file!\n");
    exit(1);
  }
	
  /* “ü—Íƒf[ƒ^‚Ì“Ç‚İ‚İ */
  input_file = fopen(argv[1], "r");
  fscanf(input_file,"%d", &city_num);
  for(i = 0; i < city_num; i++){
    fscanf(input_file,"%lf %lf",&(city[i].x),&(city[i].y));
  }
  fclose(input_file);

  /* “ü—Íƒf[ƒ^‚Ì•\¦ */
  printf("city_num= %d\n",city_num);
  for(i = 0; i < city_num; i++){
    printf("%4d\t%f\t%f\n",i,city[i].x,city[i].y);
  }

  /* Nearest Insertion–@‚ÌÀs */
  start_time = (double)clock()/CLOCKS_PER_SEC;
  nearest_insertion(0);
  search_time = (double)clock()/CLOCKS_PER_SEC - start_time;

  /* “ssƒf[ƒ^‚Ìo—Í */
  output_file = fopen("result.dat","w");
  fprintf(output_file,"%d\n",city_num);
  for(i = 0; i < city_num; i++){
    fprintf(output_file,"%f %f\n",city[i].x,city[i].y);
  }

  /* „‰ñ˜H‚Ìo—Í */
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


/* “ss(i,j)ŠÔ‚Ìƒ†[ƒNƒŠƒbƒh‹——£(¬”ˆÈ‰º‚ÍØã‚°) */
double distance(int i, int j){

  double xd, yd;

  xd = city[i].x - city[j].x;
  yd = city[i].y - city[j].y;
  return((int)(sqrt(xd * xd + yd * yd)+0.5));
}


/* Nearest Insertion–@ */
void nearest_insertion(int start_city){

  int ptour_list[MAX_CITY_NUM];  /* •”•ª„‰ñ˜H‚ğŠi”[‚·‚éƒŠƒXƒg */
  int pnum;  /* •”•ª„‰ñ˜H‚ÉŠÜ‚Ü‚ê‚é“ss” */
  int ncity[MAX_CITY_NUM];  /* •”•ª„‰ñ˜H“à‚ÌÅ‚à‹ß‚¢“ss‚ğŠi”[‚·‚é”z—ñ */
  double ncity_dist[MAX_CITY_NUM];  /* •”•ª„‰ñ˜H“à‚ÌÅ‚à‹ß‚¢“ss‚Ü‚Å‚Ì‹——£‚ğŠi”[‚·‚é”z—ñ */
  int min_dist_city;  /* •”•ª„‰ñ˜HT‚Ü‚Å‚Ì‹——£‚ªÅ¬‚Æ‚È‚é“ss */
  double min_dist;  /* •”•ª„‰ñ˜HT‚Ü‚Å‚Ì‹——£‚ªÅ¬‚Æ‚È‚é“ss‚ÆT‚ÌŠÔ‚Ì‹——£ */
  double delta, min_delta;
  int min_delta_city;
  int i,j,k;

  /* start_city‚Ì‚İ‚©‚ç‚È‚é•”•ª„‰ñ˜HT‚ğì¬‚·‚é */
  for(i = 0; i < city_num; i++){
    ptour_list[i] = -1;
  }
  ptour_list[start_city] = start_city;  
  pnum = 1;

  /* Še“ss‚©‚ç•”•ª„‰ñ˜HT‚Ö‚Ì‹——£‚ğŒvZ‚µCT‚ÉÅ‚à‹ß‚¢“ss‚¨‚æ‚Ñ‚»‚Ì‹——£‚ğ‹‚ß‚é */
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

    /* “ssmin_dist_city‚ğ‘}“ü‚·‚éêŠ‚ğŒˆ’è‚·‚é */
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

    /* •”•ª„‰ñ˜HT‚ÉÅ‚à‹ß‚¢“ssmin_dist_city‚ğ‰Á‚¦‚é */
    ptour_list[min_dist_city] = ptour_list[min_delta_city];
    ptour_list[min_delta_city] = min_dist_city;
    ncity[min_dist_city] = min_dist_city;
    ncity_dist[min_dist_city] = 0.0;
    pnum++;

    /* •”•ª„‰ñ˜HT‚ÉŠÜ‚Ü‚ê‚È‚¢Še“ss‚Ì•”•ª„‰ñ˜H‚Ü‚Å‚Ì‹——£‚ğXV‚·‚é */
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
  
  /* •”•ª„‰ñ˜HƒŠƒXƒg‚©‚ç„‰ñ˜H‚ğì¬‚·‚é */
  tour[0] = 0;
  for(i = 1; i < city_num; i++){    
    tour[i] = ptour_list[tour[i-1]];
  }
}
