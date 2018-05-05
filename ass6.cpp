// Siddhant Haldar  16EE30025  M/C No.: 91

#include <iostream>
#include <stdlib.h>

using namespace std;

typedef struct node{
  struct node *L;
  struct node *R;
  int key;
} tree;

typedef tree *bst;

bst T;

int binarysearch(int *a, int l, int r, int val){
  int mid;

  while(r>l+1){
    mid = (l+r)/2;
    if(a[mid] < val){
      l = mid;
    }
    else r = mid;
    }
  
  return l;
}

bst buildBST(int *a,int n, int l,int r){
  int mid;
  bst p = new tree;
  p -> key = a[l];
  p -> L = NULL;
  p -> R = NULL;
  
  if(n==1) return p;
  
  l = l+1;
  mid = binarysearch(a,l,r,p->key);  
  if(mid>=l) p->L = buildBST(a,mid-l+1,l,mid);
  if(mid<r) p->R = buildBST(a,r-mid,mid+1,r);
  //if(mid==l) p->L= NULL;
  //else p->L = buildBST(a,mid-l+1,l,mid);
  //if(mid==r) p->R= NULL;
  //else p->R = buildBST(a,r-mid,mid+1,r);

  return p;

}

void preorder(bst T){
  if(T==NULL) return;
  cout<<T->key<<" ";
  preorder(T->L);
  preorder(T->R);
}

void inorder(bst T){
  if(T==NULL) return;
  preorder(T->L);
  cout<<T->key<<" ";
  preorder(T->R);
}

int isBST(bst T, int l, int r){
  if(T==NULL) return 1;
  if( (T->key < l) || (T->key > r)) return 0;
  if(isBST(T->L,l,T->key) && isBST(T->R,T->key,r)) return 1;
  else return 0;
}

bst inorderSuccessor(bst T, int x){
  if(T==NULL) return NULL;
  bst p = new tree;
  bst succ = new tree;
  p = T;
  while(p){
    if(p->key == x) break;
    if(x<p->key) {
      succ = p;
      p = p->L;
    }
    else p=p->R;
  }
  
  if(p == NULL) return NULL;
  
  if(p->R != NULL){
    p = p->R;
    while(p->L!=NULL){
      p=p->L;
    }
    return p;
  }

  if(p->R==NULL) return succ;
  
}

bst preorderSuccessor(bst T, int x,int num){
  if(T==NULL) return NULL;
  bst p = new tree;
  p = T;
  while(p){
    if(p->key == x) break;
    if(x<p->key) {
 
      p = p->L;
    }
    else p=p->R;
  }
  if(p->L != NULL) return p->L;
  else if(p->R != NULL) return p->R;
  else{
    int i = 0;
    
  }
}

int main(){
  int n,*a;
  cout <<"n: ";
  cin >> n;

  cout<<"Enter preorder listing: "<<endl;
  a = (int*)malloc(n*sizeof(int));
  for(int i=0; i<n; i++){
    cin>>a[i];
  }
  
  bst T = new tree;
  T = buildBST(a,n,0,n-1);

  cout<<"Preorder listing after building tree: "<<endl;
  preorder(T);
  cout<<endl;

  cout<<"Inorder listing after building tree: "<<endl;
  inorder(T);
  cout<<endl;

  int check = isBST(T,-9999,9999);
  cout<<"check:"<<check<<endl;
  if(check==1) cout<<"BST is correct"<<endl;
  else cout<<"BST is incorrect"<<endl;
  
  int x;
  cout<<"Enter x:";
  cin >> x;
  cout<<"Inorder successor of "<<x<<" is";
  bst succ = new tree;
  succ = inorderSuccessor(T,x);
  int successor;
  if(succ == NULL){
   cout<<" does not exist"<<endl;
  }
  else{
    cout<<succ->key<<endl;;
  }
  return 0;
  
}
