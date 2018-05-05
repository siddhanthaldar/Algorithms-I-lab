#include <iostream>
#include <string.h>
#include <stdio.h>

using namespace std;

typedef struct node{
  struct node *L;    
  struct node *R;
  struct node *P;
} tree;

typedef tree *bintree;

bintree X;

void printtree(bintree T, int level){
  if(T == NULL) {
    for(int i=0;i<level;i++){
    cout << "    ";
     }
    if(level!=0) cout << "+---";
    cout << "|"<<endl;
    return;
  }
  else {
    for(int i=0;i<level;i++){
    cout << "    ";
     }
    if(level!=0) cout << "+---";
    cout << "X"<<endl;
  }
  ++level;
  printtree(T->L,level);
  printtree(T->R, level);
}

void destroytree(bintree T){   
  if(T->L == NULL || T->R == NULL){
    bintree temp;
    temp = new tree;
    temp = T;
    delete temp;
    cout<<"destroyed"<<endl;
    return;
   }
   
  destroytree(T->L);
  destroytree(T->R);
}

void genenc1(bintree T){
  if(T->L != NULL){
    cout << "0";
    genenc1(T->L);
  }
  if(T->R != NULL){
    cout << "1";
    genenc1(T->R);
  }
  if(T->P != NULL){       //T->L == NULL || T->R == NULL
    cout << "2";
    //T = T->P;
    return;
  }
  
}

void genenc2(bintree T, int* flag){
  if(T->L != NULL){
    cout << "0";
    *flag = 0;
    genenc2(T->L, flag);
  }
  if(T->R != NULL){
    cout << "1";
    *flag = 1;
    genenc2(T->R, flag);
  }
  if(T->P != NULL){
    if(*flag) cout<< "1";
    else cout << "0";
    return;
  }
  
}

void buildtree1(char* a){
  bintree T,temph,templ;
  T = new tree;
  temph = new tree;
  
  int length;
  length = strlen(a);
  
  T->P = NULL;
  temph =T;
  for(int i=0; i<length; i++){
    if(a[i] == '0'){
      templ = new tree;
      templ->L = NULL;
      templ->R = NULL;
      
      temph->L = templ;
      templ->P = temph;
      temph = templ;

    }
    if(a[i] == '1'){
        templ = new tree;
	templ->L = NULL;
	templ->R = NULL;
	
	temph->R = templ;
	templ->P = temph;
	temph = templ;
      }
    if(a[i] == '2'){
	temph = temph->P;
      }
  }

  X = T;
  cout<<"The binary tree is:"<<endl;
  printtree(T, 0);
}

int main(){
  
  //buildtree1
  int n;
  cout<<"No. of nodes:";
  cin >> n;

  char* a;
  a = new char [30];
  cout << "Enter encoding: ";
  scanf("%s", a);
  /*for(int i=0;i<2*n;i++){
    cin >> a[i];
    cout<<"done"<<endl;
  }*/

  buildtree1(a);

  cout<<"Original Encoding:";
  printf("%s\n",a);
  
  cout<<"Final Encoding:";
  genenc1(X);
  cout << endl;

  
  cout<<"Final Encoding2:";
  int *flag;
  flag = new int;
  *flag = 0;
  genenc2(X,flag);
  cout<<endl;
  


  return 0;


}

