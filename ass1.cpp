/* Name :Siddhant Haldar / Roll NO: 16EE30025 / Machine number : 91 */

#include <iostream>
#include <stdio.h>
#include <time.h>
#include <cmath>
#include <cstdlib>

using namespace std;

extern void registerme ( );
extern void startgame ( int );
extern int guess ( int );
extern void verifysoln ( int );

int count = 0;

int playgame1(){
  int n = (int)pow(10.0,8.0);
  int i,k;
  for(i = 1; i < n; i++){
    k = guess(i);
    if(k) return i;
  }
}

int playgame2(){
  int n = (int)pow(10.0,8.0);
  int i;
  while(1){
    i = rand()%n + 1;
    if(guess(i)) return i;
  }
}

int playgame3(int min, int max){
  int min_val = guess(min);
  int max_val = guess(max);
  int mid = (min+max)/2;

  if(min_val == 1) return min;
  if(max_val == 1) return max;
  if(max_val == 2){
    return playgame3(mid, max);
  }
  else if(max_val == 3){
    return playgame3(min,mid);
  }
  
}
/*
int playgame4(int min, int max, int flag){
  int min_val,max_val;
  //if(min == max) return min;
  if(flag == 2){
    min_val = guess(min);
    cout << ++count<<"   min:"<<min<<"  max:"<<max<<endl;
    if(min_val == 1) return min;
    flag = 1;                //flag is 0 for min and 1 for max         
  }
  
  if(flag == 1){
    max_val = guess(max);
    cout << ++count<<"   min:"<<min<<"  max:"<<max<<endl;
    if(max_val == 1) return max;
    else if(max_val == 2) return playgame4((min+max)/2+1,max,0);
    else return playgame4(min,(min+max)/2,0);
  }

   if(flag == 0){
    min_val = guess(min);
    cout << ++count<<"   min:"<<min<<"  max:"<<max<<endl;
    if(min_val == 1) return min;
    else if(min_val == 2) return playgame4(min,(min+max)/2,1);
    else return  playgame4((min+max)/2+1,max,1);
  }
}
*/

int playgame4(int min, int max){ 
// Here we try to increase the range thus trying to be the required number at the middle of the range

  int max_val, min_val;
  int mid = (min + max)/2;
  
  if(guess(mid)==1) return mid;

  min_val = guess(min);
  max_val = guess(max);
  
  if(max_val == 2) return playgame4(min,max + (min+max)/2);
  else return playgame4(min - (max+min)/2, max);
}

int main(){
  clock_t c1, c2;
  int a;

  registerme();
  
  startgame(1);
  c1 = clock(); a = playgame1(); c2 = clock();
  printf("\n+++ Game 1\n    a1 = %d\n", a);
  printf("    Time taken = %lf sec\n", (double)(c2-c1)/(double)CLOCKS_PER_SEC);
  verifysoln(a);

  startgame(2);
  c1 = clock(); a = playgame2(); c2 = clock();
  printf("\n+++ Game 2\n    a2 = %d\n", a);
  printf("    Time taken = %lf sec\n", (double)(c2-c1)/(double)CLOCKS_PER_SEC);
  verifysoln(a);

  startgame(3);
  c1 = clock(); a = playgame3(1,100000000); c2 = clock();
  printf("\n+++ Game 3\n    a3 = %d\n", a);
  printf("    Time taken = %lf sec\n", (double)(c2-c1)/(double)CLOCKS_PER_SEC);
  verifysoln(a);

  startgame(4);
  c1 = clock(); a = playgame4(1, 100000000); c2 = clock();
  printf("\n+++ Game 4\n    a4 = %d\n", a);
  printf("    Time taken = %lf sec\n", (double)(c2-c1)/(double)CLOCKS_PER_SEC);
  verifysoln(a);

  return 0;
}
