/* �����_���ȏ���H�𐶐�����v���O���� */

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
void random_tour();  /* �����_���ȏ���H�̐��� */


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

  /* �����_���ȏ���H�̐��� */
  random_tour();

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


/* �����_���ȏ���H�̐��� */
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
