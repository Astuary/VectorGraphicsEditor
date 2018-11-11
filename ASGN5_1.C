#include<stdio.h>
#include<graphics.h>
#include<math.h>
#include<stdlib.h>
#define DFSIZE 50

int df_op[DFSIZE], fre = 0;
float df_x[DFSIZE], df_y[DFSIZE];
int frame_pen_x, frame_pen_y;
int WIDTH, HEIGHT, WIDTH_START, WIDTH_END, HEIGHT_START, HEIGHT_END;

void putPoint(int op, float x, float y){
 if(fre >= DFSIZE){
  printf("Error: Display File Full.");
  return;
 }
 df_op[fre] = op;
 df_x[fre] = x;
 df_y[fre] = y;
 fre++;
}

void writeFile(){
 FILE *fp;
 int i;
 fp = fopen("demo.txt", "w");
 for(i = 0; i < fre - 1; i++){
  fprintf(fp, "%d %f %f\n", df_op[i], df_x[i], df_y[i]);
 }
 printf("Written Successfully.\n");
 fclose(fp);
}

void getPoint(int n, int *op, float *x, float *y){
 *op = df_op[n];
 *x = df_x[n];
 *y = df_y[n];
}

void readFile(){
 FILE *fp;
 int c, i = 0;
 int x; float y, z;
 fp = fopen("DEMO.txt", "r");

 do{
  c = fscanf(fp, "%d", &df_op[i]);
  c = fscanf(fp, "%f", &df_x[i]);
  c = fscanf(fp, "%f", &df_y[i]);
  //printf("%d %f %f", df_op[i], df_x[i], df_y[i]);
  i++;
 }while(c != EOF);
 printf("Read Successfully.\n");
 fre = i;
 fclose(fp);
}

void printArrays(){
 int i;
 for(i = 0; i < fre - 1; i++){
  printf("%d %f %f\n", df_op[i], df_x[i], df_y[i]);
 }
}

void doMove(float x, float y){
 frame_pen_x = max(WIDTH_START, min(WIDTH_END, x*WIDTH + WIDTH_START));
 frame_pen_y = max(HEIGHT_START, min(HEIGHT_END, y*HEIGHT + HEIGHT_START));
 frame_pen_x = x*getmaxx();
 frame_pen_y = getmaxy() - y*getmaxy();
 moveto(frame_pen_x, frame_pen_y);
}

void doLine(float x, float y){
 frame_pen_x = max(WIDTH_START, min(WIDTH_END, x*WIDTH + WIDTH_START));
 frame_pen_y = max(HEIGHT_START, min(HEIGHT_END, y*HEIGHT + HEIGHT_START));
 frame_pen_x = x*getmaxx();
 frame_pen_y = getmaxy() - y*getmaxy();
 lineto(frame_pen_x, frame_pen_y);
}

void interpret(){
 int i, op;
 float x, y;

 int gd = DETECT, gm;
 initgraph(&gd, &gm, "C:\\Turboc3\\BGI");

 for(i = 0; i < fre - 1; i++){
  getPoint(i, &op, &x, &y);
  /*if(op == 1){
   doMove(x, y);
  }else if(op == 2){
   doLine(x, y);
  }*/
  if(op == 2){
   doLine(x, y);
  }else{
   doMove(x, y);
  }
 }

 getch();
 closegraph();
}

void fillPolyeo(float minX, float minY){
 printf("%f %f", minX, minY);
}

void main(){
 int op, i;
 float minX = HUGE_VAL, minY = HUGE_VAL;
 float x, y;
 char c = 'a';
 //make a DFSIZE * 4 edge array, DFSIZE * 2 vertex array

 WIDTH = getmaxx(); HEIGHT = getmaxy();
 WIDTH_START = 0; HEIGHT_START = 0;
 WIDTH_END = getmaxx(); HEIGHT_END = getmaxy();
 printf("Enter opcode and x-y coordinates:\n");
 for(i = 0; i < DFSIZE && c != 'q' && c != 'Q'; i++){
  scanf("%d", &op);
  scanf("%f", &x);
  scanf("%f", &y);
  if(minX > x){ minX = x;}
  if(minY > y){ minY = y;}
  putPoint(op, x, y);
  printf("Finished? Enter to continue, Q to quit.");
  scanf("%c", &c);
 }
 printArrays();
 writeFile();
 readFile();
 printArrays();
 interpret();
 fillPolyeo(minX, minY);
}