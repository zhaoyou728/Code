/* ����Z�[���X�}�����ɑ΂���Nearest Neighbor�@ */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <float.h>
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
void nearest_neighbor(int start_city);


/* ���C���v���O���� */
int main(int argc, char *argv[]){
	
  FILE *input_file, *output_file;
  double length;
  int i;
  double start_time, search_time;
	
  /* �����̃`�F�b�N */
  if(argc <= 1){
    fprintf(stderr,"Please input the name of data file!\n");
    exit(1);
  }
	
  /* ���̓f�[�^�̓ǂݍ��� */
  input_file = fopen(argv[1], "r");
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

  /* Nearest Neighbor�@�̎��s */
  nearest_neighbor(0);

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
  return((int)(sqrt(xd * xd + yd * yd) + 0.5));
}


/* Nearest Neighbor�@ */
void nearest_neighbor(int start_city){

  double min_dist;
  int arg_min_dist, temp;
  int i,j;

  /* ����H���i�[����z��̏����� */
  tour[0] = start_city;
  j = 1;
  for(i = 0; i < city_num; i++){
    if(i != start_city){
      tour[j] = i;
      j++;
    }
  }

  for(i = 1; i < city_num-1; i++){

    /* �s�stour[i-1]�ɍł��߂����K��̓s�s�������� */
    min_dist = FLT_MAX;
    arg_min_dist = -1;
    for(j = i; j < city_num; j++){
      if(distance(tour[i-1],tour[j]) < min_dist){
	min_dist = distance(tour[i-1],tour[j]);
	arg_min_dist = j;
      }
    }

    /* �s�stour[i]�Ɠs�stour[arg_min_dist]����ւ��� */
    temp = tour[i];
    tour[i] = tour[arg_min_dist];
    tour[arg_min_dist] = temp;
  }
}
