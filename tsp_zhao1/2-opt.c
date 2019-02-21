/*#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "math.h"

#define MAX_CITY_NUM 3000

struct point{
  double x;
  double y;
};
  
struct point city[MAX_CITY_NUM];
int city_num;
int tour[MAX_CITY_NUM];


double distance(int i, int j);
void random_tour();
void local_search();


int main(){
  int i;
  double length ;
  double start_time, search_time;
  FILE *pf ,*out;
  pf=fopen("berlin52.dat","r");
  fscanf(pf,"%d",&city_num);
  
  for(i=0;i<city_num;++i){
    fscanf(pf,"%lf %lf",&(city[i].x),&(city[i].y));
  }
  fclose(pf);
  
  printf("city_num=%d\n",city_num);
  for(i=0;i<city_num;++i){
    printf("%d\t%lf\t%lf\n",i,city[i].x,city[i].y);
  }

  start_time=(double)clock()/CLOCKS_PER_SEC;
  
  random_tour();
  
  local_search();

  search_time=(double)clock()/CLOCKS_PER_SEC -start_time;

  length=0.0;
  for(i=0;i<city_num;++i){

    length+=distance(tour[i%city_num],tour[(i+1)%city_num]);
  }

  out=fopen("result.dat","w");
  fprintf(out,"%d\n",city_num);
  for(i=0;i<city_num;i++){
    fprintf(out,"%f %f\n",city[i].x,city[i].y);
	    }
      length=0.0;
    printf("\ntour: ");
    for(i=0;i<city_num;++i){
      fprintf(out,"%d\n",tour[i]);
	printf("%d",tour[i]);
      length+=distance(tour[i],tour[(i+1)%city_num]);

    }
    fclose(out);
    printf("\nlength :%f\n",length);
    printf("CPU TIME :%f\n",search_time);
    return (0);
}



void random_tour(){
  int i,k,temp;
  for(i=0;i<city_num;++i){
    tour[i]=i;
  }
  for(i=0;i<city_num;++i){
    k=(int)((double)rand()/((double)RAND_MAX+1)*(city_num-i))+i;

    temp=tour[i];
    tour[i]=tour[k];
    tour[k]=temp;
	    
  }
}

double distance(int i, int j){

    double xd, yd;
    xd=city[i].x - city[j].y;
    yd=city[i].x - city[j].y;

    return((int)(sqrt(xd*xd-yd*yd)+0.5));

  }
void local_search(){
  int st,i,j,k;
  double delta,length;
  int temp;
  
  length=0.0;
  for(i=0;i<city_num;++i){
    length+=distance(tour[i%city_num],tour[(i+1)%city_num]);
  }
  st=0;
 RESTART:
  for(i=st;i<st+city_num;++i){
    for(j=i+2;i<i+city_num-1;++j){
      delta=distance(tour[i%city_num],tour[j%city_num])+distance(tour[i+1%city_num],tour[j+1%city_num])-distance(tour[i%city_num],tour[(i+1)%city_num])-distance(tour[j%city_num],tour[(j+1)%city_num]);
    
    if(delta<0){
      length+=delta;
      for(k=0;k<(j-i)/2;++k){
	temp=tour[(i+1+k)%city_num];
	tour[(i+1+k)%city_num]=tour[(j-k)%city_num];
	tour[(j-k)%city_num]=temp;
      }
      st=(i+1)%city_num;
      printf("the length of the current tour is %f.\n",length);
      goto RESTART;

     }
    }
  }
}
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#define MAX_CITY_NUM 3000  /* Å‘å“ss” */

struct point{  /* “ss‚ÌÀ•W‚ğŠi”[‚·‚é\‘¢‘Ì */
  double x;
  double y;
};

struct point city[MAX_CITY_NUM];  /* ŠO•”•Ï”: “ss‚ÌÀ•W‚ğŠi”[‚·‚é”z—ñ */
int city_num;  /* ŠO•”•Ï”: “ss” */
int tour[MAX_CITY_NUM];  /* ŠO•”•Ï”: “ss‚Ì„‰ñ‡‚ğŠi”[‚·‚é”z—ñ */

/* ŠÖ”‚ÌéŒ¾ */
double distance(int i, int j);  /* “ss(i,j)ŠÔ‚Ìƒ†[ƒNƒŠƒbƒh‹——£ */
void random_tour();  /* ‰Šú„‰ñ˜H */
void local_search();  /* ‹ÇŠ’Tõ–@(2-opt‹ß–T) */

/* ƒƒCƒ“ƒvƒƒOƒ‰ƒ€ */
int main(int argc, char *argv[]){
	
  FILE *input_file, *output_file;
  double length;
  int i;
  double start_time, search_time;
	
     /* ˆø”‚Ìƒ`ƒFƒbƒN */
  // if(argc <= 1){
  // fprintf(stderr,"Please input the name of data file!\n");
  // exit(1);
  //}
	
  /* “ü—Íƒf[ƒ^‚Ì“Ç‚İ‚İ */
  input_file = fopen("berlin52.dat", "r");
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

  /* ŠJn‚Ìİ’è */
  start_time = (double)clock()/CLOCKS_PER_SEC;

  /* ‰Šú„‰ñ˜H‚Ì¶¬ */
  random_tour();

  /* ‹ÇŠ’Tõ–@(2-opt‹ß–T) */
  local_search();

  /* I—¹‚Ìİ’è */
  search_time = (double)clock()/CLOCKS_PER_SEC - start_time;

  /* „‰ñ˜H’·‚ÌŒvZ */
  length = 0.0;
  for(i = 0; i < city_num; i++){
    length += distance(tour[i % city_num], tour[(i+1) % city_num]);
  }
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


/* ‰Šú„‰ñ˜H */
void random_tour(){

  int i,k;
  int temp;

  /* ‡—ñ‚ğ‰Šú‰» */
  for(i = 0 ; i < city_num; i++){
    tour[i] = i;
  }

  /* ƒ‰ƒ“ƒ_ƒ€‡—ñ‚ğì¬ */
  for(i = 0; i < city_num; i++){
    k = (int)((double)rand() / ((double)RAND_MAX + 1) * (city_num - i)) + i;
    temp = tour[i];
    tour[i] = tour[k];
    tour[k] = temp;
  }
}


/* ‹ÇŠ’Tõ–@(2-opt‹ß–T) */
void local_search(){

  int temp;
  double length, delta;
  int st,i,j,k;
  
  /* ‰Šú„‰ñ˜H’·‚ÌŒvZ */
  length = 0.0;
  for(i = 0; i < city_num; i++){
    length += distance(tour[i % city_num], tour[(i+1) % city_num]);
  }
  
  st = 0;
 RESTART:	
  for(i = st; i < st+city_num; i++){
    for(j = i+2; j < i+city_num-1; j++){
      
      /* „‰ñ˜H’·‚Ì‘•ª‚ğŒvZ */
      delta = distance(tour[i % city_num], tour[j % city_num]) + distance(tour[(i+1) % city_num], tour[(j+1) % city_num]) - distance(tour[i % city_num], tour[(i+1) % city_num]) - distance(tour[j % city_num], tour[(j+1) % city_num]);
      
      if(delta < 0){
	
	/* Œ»İ‚Ì‰ğ‚Ì„‰ñ˜H’·‚ğXV */
	length += delta;
	
	/* “ss(i+1, ... , j)‚Ì‹æŠÔ‚ğ”½“] */
	for(k = 0; k < (j-i)/2; k++){
	  temp = tour[(i+1+k) % city_num];
	  tour[(i+1+k) % city_num] = tour[(j-k) % city_num];
	  tour[(j-k) % city_num] = temp;
	}
	
	/* 2-opt‹ß–T’Tõ‚ÌŠJn“ss‚ğÄİ’è */
	st = (i+1) % city_num;	
	printf("The length of the current tour is %f.\n",length);
	goto RESTART;
      }
    }
  }
}
