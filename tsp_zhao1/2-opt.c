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
#define MAX_CITY_NUM 3000  /* �ő�s�s�� */

struct point{  /* �s�s�̍��W���i�[����\���� */
  double x;
  double y;
};

struct point city[MAX_CITY_NUM];  /* �O���ϐ�: �s�s�̍��W���i�[����z�� */
int city_num;  /* �O���ϐ�: �s�s�� */
int tour[MAX_CITY_NUM];  /* �O���ϐ�: �s�s�̏��񏇂��i�[����z�� */

/* �֐��̐錾 */
double distance(int i, int j);  /* �s�s(i,j)�Ԃ̃��[�N���b�h���� */
void random_tour();  /* ��������H */
void local_search();  /* �Ǐ��T���@(2-opt�ߖT) */

/* ���C���v���O���� */
int main(int argc, char *argv[]){
	
  FILE *input_file, *output_file;
  double length;
  int i;
  double start_time, search_time;
	
     /* �����̃`�F�b�N */
  // if(argc <= 1){
  // fprintf(stderr,"Please input the name of data file!\n");
  // exit(1);
  //}
	
  /* ���̓f�[�^�̓ǂݍ��� */
  input_file = fopen("berlin52.dat", "r");
  fscanf(input_file,"%d", &city_num);
  for(i = 0; i < city_num; i++){
    fscanf(input_file,"%lf %lf",&(city[i].x),&(city[i].y));
  }
  fclose(input_file);

  /* ���̓f�[�^�̕\�� */
  printf("city_num= %d\n",city_num);
  for(i = 0; i < city_num; i++){
    printf("%4d\t%f\t%f\n",i,city[i].x,city[i].y);
  }

  /* �J�n�����̐ݒ� */
  start_time = (double)clock()/CLOCKS_PER_SEC;

  /* ��������H�̐��� */
  random_tour();

  /* �Ǐ��T���@(2-opt�ߖT) */
  local_search();

  /* �I�������̐ݒ� */
  search_time = (double)clock()/CLOCKS_PER_SEC - start_time;

  /* ����H���̌v�Z */
  length = 0.0;
  for(i = 0; i < city_num; i++){
    length += distance(tour[i % city_num], tour[(i+1) % city_num]);
  }
  /* �s�s�f�[�^�̏o�� */
  output_file = fopen("result.dat","w");
  fprintf(output_file,"%d\n",city_num);
  for(i = 0; i < city_num; i++){
    fprintf(output_file,"%f %f\n",city[i].x,city[i].y);
  }

  /* ����H�̏o�� */
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


/* �s�s(i,j)�Ԃ̃��[�N���b�h����(�����ȉ��͐؏グ) */
double distance(int i, int j){

  double xd, yd;

  xd = city[i].x - city[j].x;
  yd = city[i].y - city[j].y;
  return((int)(sqrt(xd * xd + yd * yd)+0.5));
}


/* ��������H */
void random_tour(){

  int i,k;
  int temp;

  /* ����������� */
  for(i = 0 ; i < city_num; i++){
    tour[i] = i;
  }

  /* �����_��������쐬 */
  for(i = 0; i < city_num; i++){
    k = (int)((double)rand() / ((double)RAND_MAX + 1) * (city_num - i)) + i;
    temp = tour[i];
    tour[i] = tour[k];
    tour[k] = temp;
  }
}


/* �Ǐ��T���@(2-opt�ߖT) */
void local_search(){

  int temp;
  double length, delta;
  int st,i,j,k;
  
  /* ��������H���̌v�Z */
  length = 0.0;
  for(i = 0; i < city_num; i++){
    length += distance(tour[i % city_num], tour[(i+1) % city_num]);
  }
  
  st = 0;
 RESTART:	
  for(i = st; i < st+city_num; i++){
    for(j = i+2; j < i+city_num-1; j++){
      
      /* ����H���̑������v�Z */
      delta = distance(tour[i % city_num], tour[j % city_num]) + distance(tour[(i+1) % city_num], tour[(j+1) % city_num]) - distance(tour[i % city_num], tour[(i+1) % city_num]) - distance(tour[j % city_num], tour[(j+1) % city_num]);
      
      if(delta < 0){
	
	/* ���݂̉��̏���H�����X�V */
	length += delta;
	
	/* �s�s(i+1, ... , j)�̋�Ԃ𔽓] */
	for(k = 0; k < (j-i)/2; k++){
	  temp = tour[(i+1+k) % city_num];
	  tour[(i+1+k) % city_num] = tour[(j-k) % city_num];
	  tour[(j-k) % city_num] = temp;
	}
	
	/* 2-opt�ߖT�T���̊J�n�s�s���Đݒ� */
	st = (i+1) % city_num;	
	printf("The length of the current tour is %f.\n",length);
	goto RESTART;
      }
    }
  }
}
