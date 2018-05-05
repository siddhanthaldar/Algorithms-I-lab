// Siddhant Haldar 16EE30025 M/c no.: 91

#include <iostream>

using namespace std;

typedef struct{
  int i;
  int sigma; 
  int flag;
} hash;

int maximum(int a, int b){
  if(a>=b) return a;
  else return b;
}

int exhs(int *a, int n, int i, int t,int sum){
  if(i>=n) return sum;
  if(sum+a[i]>t) return sum;
  return maximum(exhs(a,n,i+1,t,sum),exhs(a,n,i+1,t,sum+a[i]));
}

int h(int i, int sigma, int size){
  return (100003*i + 103*sigma)%size;
}

hash* htinit(int size, hash *H){
  for(int i=0; i< size; i++){
    H[i].i = -1;
    H[i].sigma = -1;
    H[i].flag = -1;
  }
  return H;
}

int htsearch(hash *H, int i, int sigma, int size){
  int k;
  int idx;
  k = h(i,sigma,size);
  idx = k;

  if((H[idx].i == i) && (H[idx].sigma == sigma)) return idx+1;
  if((H[idx].i == -1)&&(H[idx].sigma == -1)&&(H[idx].flag == -1)) return 0;
  idx = (idx+1)%size;

  while(idx != k){
    if((H[idx].i == i) && (H[idx].sigma == sigma)) return 1;
    if(H[idx].i == -1) return 0;
    idx = (idx+1)%size;
  }
  return 0;

}

void htinsert(hash* H, int i, int sigma, int flag, int size){
  int k;
  int idx;
  k = h(i,sigma,size);
  idx = k;

  if((H[idx].i == -1)&&(H[idx].sigma == -1)&&(H[idx].flag == -1)){
    H[idx].i = i;
    H[idx].sigma = sigma;
    H[idx].flag = flag;
    return ;
  }
  if((H[idx].i == i) && (H[idx].sigma == sigma)) return;
  idx = (idx + 1)%size;
    
  while(idx != k){
    if((H[idx].i == -1)&&(H[idx].sigma == -1)&&(H[idx].flag == -1)){
      H[idx].i = i;
      H[idx].sigma = sigma;
      H[idx].flag = flag;
      return ;
    }
    if((H[idx].i == i) && (H[idx].sigma == sigma)) return ;
    idx = (idx+1)%size;
  }
  return;

}

int hashs(int *a, int n, int i, int t,int sum, hash* H, int flag, int size){
  int v0,v1;
  if(i==n) return sum;
  else {
    if(htsearch(H,i,sum,size)!=0) v0 = -1;
    else {
      htinsert(H,i,sum,0,size);
      v0 = hashs(a,n,i+1,t,sum,H,1,size);
    }    
    if((sum+a[i]<=t)&&(htsearch(H,i,sum+a[i],size)==0)) {
      htinsert(H,i,sum+a[i],1, size);
      v1 = hashs(a,n,i+1,t,sum+a[i],H,1,size);
    }  
    else v1 = -1;

    return maximum(v0,v1);
  }
  
}

int main(){
  int n, *a,s=0,t,p;
  cout<<"N:";
  cin >> n;
  a = new int [n];
  for(int i=0; i<n; i++){
    cin >> a[i];
    s+=a[i];
  }
  t = s / 2;
  cout << "S = "<<s<<endl;
  cout << "T = "<<t<<endl;

  cout << "++++ Exhaustive search" << endl;
  p = exhs(a,n,0,t,0);
  cout<<"Maximum P = "<<p<<endl;

  cout << "++++ Search with a hash table"<<endl;
  hash *H;
  int size = n*t; 
  H = new hash [size];
  H = htinit(size,H);

  p = hashs(a,n,0,t,0,H,0,size);
  cout<<"Maximum P = "<<p<<endl;
  
    
  return 0;

}
