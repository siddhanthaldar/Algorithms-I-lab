/* Name : Siddhant Haldar
   Roll no. : 16EE30025 
   Machine no. : 91 */

#include <iostream>

using namespace std;

typedef struct{
  int l,r,c;
} node;

void heapify(node *H, int i, int n){
  int left,right,min;
  int p,q,s;
  while(1){
    left = 2*i;
    right = 2*i+1;
    if(left>n) break;
    if(right>n) min=left;
    else min = (H[left].c <= H[right].c)?left:right;
    
    if(H[i].c<=H[min].c) break;
    p = H[i].l, q = H[i].r, s = H[i].c;
    H[i].l = H[min].l, H[i].r = H[min].r, H[i].c = H[min].c;
    H[min].l = p, H[min].r = q, H[min].c = s;

    i = min;
  }
}

void makeheap(node *H, int n){
  for(int i=n/2+1;i>=1;i--){
    heapify(H,i,n);
  }
}

void insert(node *H, int n,node x){
  H[0].c++;
  ++n;
  H[n]=x;
  int i = n,par;
  int p,q,s;
  node *temp;
  
  while(1){
    if(i==1) break;
    par=i/2;
    if(H[par].c<=H[i].c) break;
    
    p = H[par].l, q = H[par].r, s = H[par].c;
    H[par].l = H[i].l, H[par].r = H[i].r, H[par].c = H[i].c;
    H[i].l = p, H[i].r = q, H[i].c = s;

    i=par;
  }
}

void deletemin(node* H){
  int p,q,s;
  int size = H[0].c-1;
  p = H[1].l, q = H[1].r, s = H[1].c;
  H[1].l =  H[size].l, H[1].r =  H[size].r, H[1].c =  H[size].c;
  H[size].l = p, H[size].r = q, H[size].c = s;
  
  H[0].c--;
  if(H[0].c>1)  heapify(H,1,H[0].c);

}

void greedy(node* H, int k){
  int arr[200];
  int cost = 0;
  int size = H[0].c; 

  for(int i=1; i<=size;i++){
    arr[i] = 0;
   }
 
  while(k>0){         
    if(arr[H[1].l] == 0 && arr[H[1].r] == 0){
	cost += H[1].c;
	arr[H[1].l] = 1;
	arr[H[1].r] = 1;
    
	cout<< "("<<H[1].l<<","<<H[1].r<<"): "<< H[1].c<< "  ";
	k--;
    } 
    deletemin(H);
  }
  cout<<endl<<"Total cost = "<< cost<<endl;
   
}
  

int main(){
  int n,k,*d;
  
  cout <<"N: ";
  cin>>n;
  cout << "K: ";
  cin>>k;
  
  d =  new int [n-1];
  for(int i=0; i<n-1; i++){
    cin>>d[i];
  }

  node *H;
  H = new node [n];
  H[0].l = H[0].r = 0;
  H[0].c = n;             //storing size at 0th index
  for(int i=1;i<n;i++){
    H[i].l = i-1;
    H[i].r = i;
    H[i].c = d[i-1];
  }

  makeheap(H,n);

  cout <<"+++ Part 1: Greedy Algorithm"<<endl<<"---Adding Connections"<<endl;
  greedy(H,k);

     
  return 0;

}
