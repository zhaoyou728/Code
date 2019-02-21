/* 長方形ストリップパッキング問題に対する近似解法(サンプル) */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define MAX_N 1000  /* 長方形の最大数 */

double strip_width, strip_height;  /* 母材の幅，高さ */
int n;  /* 長方形の数 */
double w[MAX_N], h[MAX_N];  /* 長方形iの幅w[i]と高さh[i]を格納する配列 */
double x[MAX_N], y[MAX_N];  /* 長方形iの座標(x[i],y[i])を格納する配列 */

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
  fscanf(input_file, "w= %lf\n", &strip_width);
  fscanf(input_file, "n= %d\n",&n);
  for(i = 0; i < n; i++){
    fscanf(input_file, "%lf %lf\n",&(w[i]),&(h[i]));
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

  /********** アルゴリズム本体をここに記述 **********/
  x[0] = y[0] = 0.0;
  for(i = 1; i < n; i++){
    x[i] = 0.0;
    y[i] = y[i-1] + h[i-1];
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
