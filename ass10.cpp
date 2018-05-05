// Siddhant Haldar   16EE30025  M/C No.: 91
#include <iostream>

using namespace std;

#define OR 1
#define XOR 0
extern void registerme ( );
extern int rangequery ( int, int, int );
extern void verifysoln ( int [] );


int* find2(int *I,int k, int l ,int r, int* i){
  if((*i)>3) return I;
  if(l == r-1){
    if(rangequery(l,l,OR)){
      I[*i] = l;
      *i +=1;
    }
    return I;
  }

  if(!rangequery(l,r,XOR)){
    cout<<l<<"     "<<r<<endl;
    if(rangequery(l,(l+r)/2,XOR)){
      find2(I,k,l,(l+r)/2,i);
      find2(I,k,(l+r)/2+1,r,i);
    }
    else{
      if(!rangequery(l,(l+r)/2,OR)){
	find2(I,k,(l+r)/2+1,r,i);
      }
    else{
       if(rangequery((l+r)/2,r,OR)){
	  find2(I,k,l,(l+r)/2,i);
	  find2(I,k,(l+r)/2+1,r,i);
	}
      }
    }
  }
  
  else {
    cout<<l<<"     "<<r<<endl;
    if(!rangequery(l,(l+r)/2,XOR)){
      if(rangequery(l,(l+r)/2,OR)){
	find2(I,k,l,(l+r)/2,i);
	find2(I,k,(l+r)/2+1,r,i);
      }
      else find2(I,k,(l+r)/2+1,r,i);
    }
    else{
	if(rangequery((l+r)/2+1,r,OR)){
	  find2(I,k,l,(l+r)/2,i);
	  find2(I,k,(l+r)/2+1,r,i);
	}
	else
	  find2(I,k,(l+r)/2+1,r,i);
      }
      
   }
 
  
  return I;

}

int* find(int* I, int k,int l, int r, int *i){
  if((*i)>3) return I;
  if(l==r){
    I[*i] = l;
    (*i) +=1;
    return I;
  }
  if(l<r){
    if(rangequery(l,(l+r)/2,OR)) find(I,k,l,(l+r)/2,i);
    if(rangequery((l+r)/2+1,r,OR)) find(I,k,(l+r)/2+1,r,i);
  }
  return I;
}

int main(){
  registerme();
  int* I;
  int n=65536, k=10;

  I = new int [k];
  
  int *i;
  i = new int;
  *i = 0;

  //find2(I,k,0,n-1,i);
  find(I,k,0,n-1,i);

  int temp;
  
  for(int i=3;i<k;i++) I[i] = 65535 + i;


  for(int i=k-2;i>=0;i--){
    for(int j=0;j<i;j++){
      if(I[j]>I[j+1]){
	temp = I[j];
	I[j] = I[j+1];
	I[j+1] = temp;
      }
    }
  }
  for(int i=0;i<k;i++) cout<<I[i]<<endl;


  verifysoln(I);


  return 0;
}


