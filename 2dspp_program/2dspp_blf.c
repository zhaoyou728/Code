/* 長方形ストリップパッキング問題に対するBLF法 */

#include <stdlib.h>
#include <stdio.h>
#include <float.h>
#include <time.h>

#define FALSE 0
#define TRUE 1
#define NUM_ERROR 0.001
#define MAX_N 1000  /* 長方形の最大数 */

double strip_width, strip_height;  /* 母材の幅，高さ */
int n;  /* 長方形の数 */
double w[MAX_N], h[MAX_N];  /* 長方形iの幅w[i]と高さh[i]を格納する配列 */
double x[MAX_N], y[MAX_N];  /* 長方形iの座標(x[i],y[i])を格納する配列 */
double blx[MAX_N * MAX_N / 2 + 1], bly[MAX_N * MAX_N / 2 + 1];  /* BL安定点の候補を格納する配列 */
double blw[MAX_N * MAX_N / 2 + 1], blh[MAX_N * MAX_N / 2 + 1];  /* BL安定点の上，右方向の隙間の幅を格納する配列 */
int bl_num;  /* BL安定点の候補数 */

/* BLF法 */
void bottom_left_fill(int c){

  double min_x, min_y;  /* 長方形cの配置可能な座標 */
  int collision_flag;  /* 長方形cの重なり判定に用いるフラグ */
  int i,j;

  /* 長方形cを配置するBL安定点の候補を選ぶ */
  min_x = min_y = FLT_MAX;
  for(i = 0; i < bl_num; i++){

    /* BL安定条件のチェック */
    if(w[c] > blw[i]+NUM_ERROR && h[c] > blh[i]+NUM_ERROR){

      /* 制約条件のチェック */
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

  /* 長方形cの配置座標を決定 */
  if(min_x < FLT_MAX && min_y < FLT_MAX){
    x[c] = min_x;
    y[c] = min_y;
  }

  /* 長方形cと母材によって新たに生じるBL安定点の候補を追加 */
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

  /* 長方形cと他の長方形jによって生じるBL安定点の候補を追加 */
  for(j = 0; j < c; j++){

    /* 長方形cが長方形jの左側にある場合 */
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

    /* 長方形cが長方形jの右側にある場合 */
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

    /* 長方形cが長方形jの下側にある場合 */
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

    /* 長方形cが長方形jの上側にある場合 */
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

/* メインプログラム */
int main(int argc, char *argv[]){

  FILE *input_file, *output_file;
  double start_time, search_time;
  double area, efficiency;
  int i;

  /* 引数のチェック */
  if(argc <= 1){
    fprintf(stderr,"Please input the name of data file!\n");
    exit(1);
  }

  /* 入力データの読込み */
  input_file = fopen(argv[1], "r");
  fscanf(input_file,"w= %lf\n", &strip_width);
  fscanf(input_file,"n= %d\n",&n);
  for(i = 0; i < n; i++){
    fscanf(input_file,"%lf %lf\n",&(w[i]),&(h[i]));
  }
  fclose(input_file);

  /* 入力データを画面に表示 */
  printf("w= %f\n",strip_width);
  printf("n= %d\n",n);
  for(i = 0; i < n; i++){
    printf("%4d\t%f\t%f\n",i,w[i],h[i]);
  }

  /* 開始時刻の設定 */
  start_time = (double)clock()/CLOCKS_PER_SEC;

  /* BL安定点の候補を格納する配列を初期化 */
  blx[0] = bly[0] = blw[0] = blh[0] = 0.0;
  bl_num = 1;

  /* BLF法の実行 */
  for(i = 0; i < n; i++){
    bottom_left_fill(i);
  }

  /* 実行時間の測定 */
  search_time = (double)clock()/CLOCKS_PER_SEC - start_time;

  /* 母材の高さを計算 */
  strip_height = 0.0;
  for(i = 0; i < n; i++){
    if(y[i]+h[i] > strip_height){
      strip_height = y[i]+h[i];
    }
  }

  /* 充填率を計算 */
  area = 0.0;
  for(i = 0; i < n; i++){
    area += w[i] * h[i];
  }
  efficiency = area / (strip_width * strip_height) * 100.0;

  /* 例題データおよび各長方形の配置座標をファイルに出力 */
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

  /* 実行結果を画面に表示 */
  printf("Coordinates of rectangles:\n");
  for(i = 0; i < n; i++){
    printf("%d\t%f\t%f\n",i,x[i],y[i]);
  }
  printf("\nh= %f\n",strip_height);
  printf("time= %f\n",search_time);

  return(0);
}
