/* �����`�X�g���b�v�p�b�L���O���ɑ΂���BLF�@ */

#include <stdlib.h>
#include <stdio.h>
#include <float.h>
#include <time.h>

#define FALSE 0
#define TRUE 1
#define NUM_ERROR 0.001
#define MAX_N 1000  /* �����`�̍ő吔 */

double strip_width, strip_height;  /* ��ނ̕��C���� */
int n;  /* �����`�̐� */
double w[MAX_N], h[MAX_N];  /* �����`i�̕�w[i]�ƍ���h[i]���i�[����z�� */
double x[MAX_N], y[MAX_N];  /* �����`i�̍��W(x[i],y[i])���i�[����z�� */
double blx[MAX_N * MAX_N / 2 + 1], bly[MAX_N * MAX_N / 2 + 1];  /* BL����_�̌����i�[����z�� */
double blw[MAX_N * MAX_N / 2 + 1], blh[MAX_N * MAX_N / 2 + 1];  /* BL����_�̏�C�E�����̌��Ԃ̕����i�[����z�� */
int bl_num;  /* BL����_�̌�␔ */

/* BLF�@ */
void bottom_left_fill(int c){

  double min_x, min_y;  /* �����`c�̔z�u�\�ȍ��W */
  int collision_flag;  /* �����`c�̏d�Ȃ蔻��ɗp����t���O */
  int i,j;

  /* �����`c��z�u����BL����_�̌���I�� */
  min_x = min_y = FLT_MAX;
  for(i = 0; i < bl_num; i++){

    /* BL��������̃`�F�b�N */
    if(w[c] > blw[i]+NUM_ERROR && h[c] > blh[i]+NUM_ERROR){

      /* ��������̃`�F�b�N */
      if(blx[i] >= 0.0 && blx[i]+w[c] <= strip_width && bly[i] >= 0.0){
	collision_flag = FALSE;
	for(j = 0; j < c; j++){
	  if(blx[i] < x[j]+w[j]-NUM_ERROR && blx[i]+w[c] > x[j]+NUM_ERROR && bly[i]+h[c] > y[j]+NUM_ERROR && bly[i] < y[j]+h[j]-NUM_ERROR){	  
	    collision_flag = TRUE;
	  }
	}
	if(collision_flag == FALSE && (bly[i] < min_y || (bly[i] < min_y + NUM_ERROR && blx[i] < min_x))){
	  min_x = blx[i];
	  min_y = bly[i];
	}
      }
    }    
  }

  /* �����`c�̔z�u���W������ */
  if(min_x < FLT_MAX && min_y < FLT_MAX){
    x[c] = min_x;
    y[c] = min_y;
  }

  /* �����`c�ƕ�ނɂ���ĐV���ɐ�����BL����_�̌���ǉ� */
  blx[bl_num] = x[c]+w[c];
  bly[bl_num] = 0.0;
  blw[bl_num] = 0.0;
  blh[bl_num] = y[c];
  bl_num++;
  blx[bl_num] = 0.0;
  bly[bl_num] = y[c]+h[c];
  blw[bl_num] = x[c];
  blh[bl_num] = 0.0;
  bl_num++;

  /* �����`c�Ƒ��̒����`j�ɂ���Đ�����BL����_�̌���ǉ� */
  for(j = 0; j < c; j++){

    /* �����`c�������`j�̍����ɂ���ꍇ */
    if(x[c]+w[c] < x[j]+NUM_ERROR && y[c]+h[c] > y[j]+h[j]+NUM_ERROR){
      blx[bl_num] = x[c]+w[c];
      bly[bl_num] = y[j]+h[j];
      blw[bl_num] = x[j] - (x[c]+w[c]);
      if(y[c] > y[j]+h[j]){
	blh[bl_num] = y[c] - (y[j]+h[j]);
      }else{
	blh[bl_num] = 0.0;
      }
      bl_num++;
    }

    /* �����`c�������`j�̉E���ɂ���ꍇ */
    if(x[j]+w[j] < x[c]+NUM_ERROR && y[j]+h[j] > y[c]+h[c]+NUM_ERROR){
      blx[bl_num] = x[j]+w[j];
      bly[bl_num] = y[c]+h[c];
      blw[bl_num] = x[c] - (x[j]+w[j]);
      if(y[j] > y[c]+h[c]){
	blh[bl_num] = y[j] - (y[c]+h[c]);
      }else{
	blh[bl_num] = 0.0;
      }
      bl_num++;
    }

    /* �����`c�������`j�̉����ɂ���ꍇ */
    if(y[c]+h[c] < y[j]+NUM_ERROR && x[c]+w[c] > x[j]+w[j]+NUM_ERROR){
      blx[bl_num] = x[j]+w[j];
      bly[bl_num] = y[c]+h[c];
      if(x[c] > x[j]+w[j]){
	blw[bl_num] = x[c] - (x[j]+w[j]);
      }else{
	blw[bl_num] = 0.0;
      }
      blh[bl_num] = y[j] - (y[c]+h[c]);
      bl_num++;
    }

    /* �����`c�������`j�̏㑤�ɂ���ꍇ */
    if(y[j]+h[j] < y[c]+NUM_ERROR && x[j]+w[j] > x[c]+w[c]+NUM_ERROR){
      blx[bl_num] = x[c]+w[c];
      bly[bl_num] = y[j]+h[j];
      if(x[j] > x[c]+w[c]){
	blw[bl_num] = x[j] - (x[c]+w[c]);
      }else{
	blw[bl_num] = 0.0;
      }
      blh[bl_num] = y[c] - (y[j]+h[j]);
      bl_num++;
    }
  }
}

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
  fscanf(input_file,"w= %lf\n", &strip_width);
  fscanf(input_file,"n= %d\n",&n);
  for(i = 0; i < n; i++){
    fscanf(input_file,"%lf %lf\n",&(w[i]),&(h[i]));
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

  /* BL����_�̌����i�[����z��������� */
  blx[0] = bly[0] = blw[0] = blh[0] = 0.0;
  bl_num = 1;

  /* BLF�@�̎��s */
  for(i = 0; i < n; i++){
    bottom_left_fill(i);
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
