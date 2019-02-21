/* �����`�X�g���b�v�p�b�L���O���ɑ΂���ߎ���@(�T���v��) */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define MAX_N 1000  /* �����`�̍ő吔 */

double strip_width, strip_height;  /* ��ނ̕��C���� */
int n;  /* �����`�̐� */
double w[MAX_N], h[MAX_N];  /* �����`i�̕�w[i]�ƍ���h[i]���i�[����z�� */
double x[MAX_N], y[MAX_N];  /* �����`i�̍��W(x[i],y[i])���i�[����z�� */

/* ���C���v���O���� */
int main(int argc, char *argv[]){

  FILE *input_file, *output_file;
  double start_time, search_time;
  double area, efficiency;
  int i;

  /* �����̃`�F�b�N */
  if(argc <= 1){
    fprintf(stderr,"Please input the name of data file!\n");
    exit(1);
  }

  /* ���̓f�[�^�̓Ǎ��� */
  input_file = fopen(argv[1], "r");
  fscanf(input_file, "w= %lf\n", &strip_width);
  fscanf(input_file, "n= %d\n",&n);
  for(i = 0; i < n; i++){
    fscanf(input_file, "%lf %lf\n",&(w[i]),&(h[i]));
  }
  fclose(input_file);

  /* ���̓f�[�^����ʂɕ\�� */
  printf("w= %f\n",strip_width);
  printf("n= %d\n",n);
  for(i = 0; i < n; i++){
    printf("%4d\t%f\t%f\n",i,w[i],h[i]);
  }

  /* �J�n�����̐ݒ� */
  start_time = (double)clock()/CLOCKS_PER_SEC;

  /********** �A���S���Y���{�̂������ɋL�q **********/
  x[0] = y[0] = 0.0;
  for(i = 1; i < n; i++){
    x[i] = 0.0;
    y[i] = y[i-1] + h[i-1];
  }

  /* ���s���Ԃ̑��� */
  search_time = (double)clock()/CLOCKS_PER_SEC - start_time;

  /* ��ނ̍������v�Z */
  strip_height = 0.0;
  for(i = 0; i < n; i++){
    if(y[i]+h[i] > strip_height){
      strip_height = y[i]+h[i];
    }
  }

  /* �[�U�����v�Z */
  area = 0.0;
  for(i = 0; i < n; i++){
    area += w[i] * h[i];    
  }
  efficiency = area / (strip_width * strip_height) * 100.0;

  /* ���f�[�^����ъe�����`�̔z�u���W���t�@�C���ɏo�� */
  output_file = fopen("result.dat","w");
  fprintf(output_file,"w= %f\n",strip_width);
  fprintf(output_file,"n= %d\n",n);
  for(i = 0; i < n; i++){
    fprintf(output_file,"%f\t%f\n",w[i],h[i]);
  }
  for(i = 0; i < n; i++){
    fprintf(output_file,"%f\t%f\n",x[i],y[i]);
  }
  fclose(output_file);

  /* ���s���ʂ���ʂɕ\�� */
  printf("Coordinates of rectangles:\n");
  for(i = 0; i < n; i++){
    printf("%d\t%f\t%f\n",i,x[i],y[i]);
  }
  printf("\nh= %f\n",strip_height);
  printf("time= %f\n",search_time);

  return(0);
}
