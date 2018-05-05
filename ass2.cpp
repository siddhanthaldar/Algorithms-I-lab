/* Name : Siddhant Haldar
   Roll No. : 16EE30025
   Maachine No. : 91 */


#include <iostream>
#include <stdio.h>

extern int registerme ( int );
extern void startsort ( );
extern int compareballs ( int, int );
extern void verifysort ( int*);
extern void startmatch ( int );
extern int fitsin ( int i, int j );
extern void verifymatch ( int*);

using namespace std;

void merge(int* arr, int l, int mid, int r){
  int size = r-l+1;

  int* extra_arr = new int[size];
  
  int i,j,k;
 
  i=l;
  j=mid+1;
  k=0;
  
  int compare;
  
  while(i<=mid && j<=r){
    compare = compareballs(arr[i],arr[j]);
    
    if(compare<=0){
      extra_arr[k++] = arr[i++];
    }
    else{
      extra_arr[k++] = arr[j++];
    }
  }
  
  while(i<=mid){
    extra_arr[k] = arr[i];
    i++;
    k++;
  }
  while(j<=r){
    extra_arr[k] = arr[j];
    j++;
    k++;
  }
  for(i=0; i<size ; i++){
    arr[l+i] = extra_arr[i];
  }

}

void indexedmergesort(int* arr, int l, int r){
  if(l<r){
    
    int mid = l + (r-l)/2;

    indexedmergesort(arr,l,mid);
    indexedmergesort(arr,mid+1,r);

    merge(arr,l,mid,r);
  }
}

void swap(int* a, int* b){
  int temp;
  temp = *a;
  *a = *b;
  *b = temp;
}

int partition(int* arr, int l, int r){
  int pivot = arr[r];
  int low = l -1;

  for(int i=l; i<=r-1; i++){
    if(fitsin(i,r)<=0){
      low++;
      swap(arr[low],arr[i]);
     }
    i++;
   }
  
  swap(arr[low+1],arr[r]);
  return (low+1);

}

void quicksort(int* arr,int l, int r){
  if(l<r){
    int pivot = partition(arr,l,r);
    
    quicksort(arr, l, pivot-1);
    quicksort(arr, pivot+1, r);
  }
}



/*void ball_pos(int* M,int* S1,int n){
  
  int* arr = new int[n];
  for(int i=0; i<n; i++){
    arr[S1[i]] = M[i];
  }
 
  for(int j=0; j<n; j++){
    M[j] = arr[j];
  }
  
}
*/

int main(){
  int n;
  cout << "n: ";
  cin >> n;

  registerme(n);

  printf("\n+++ Sorting the balls...\n");
  startsort();
  int* S1 = new int[n];
  for(int i=0;i<n;i++) S1[i] = i;
  indexedmergesort(S1,0,n-1);
  verifysort(S1);

  printf("\n+++ Finding the matching boxes...\n");
  startmatch(0);
  int* M = new int[n];
  for(int i=0;i<n;i++) M[i] = i;
  quicksort(M,0,n-1);
  // ball_pos(M,S1,n);
  verifymatch(M);
  

  return 0;
}
