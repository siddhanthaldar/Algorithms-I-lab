#include <iostream>

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
    if(arr[i]<=arr[j]){
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

void mergesort(int* arr, int l, int r){
  if(l<r){
    
    int mid = l + (r-l)/2;

    mergesort(arr,l,mid);
    mergesort(arr,mid+1,r);

    merge(arr,l,mid,r);
  }
}

void solveGRD(int n, int M, int *m){
  mergesort(m,0,n-1);
  /*
  for(int i=0; i<n; i++)
    cout<<m[i]<<"  ";
  */
  
  int sum=0,i;
  for(i = 0; i<n;i++){
    if((sum + m[i]) > M) break;
    sum += m[i];
  }
  cout << "Minimum Effort = "<<sum<<" = ";
  for(int k = 0; k < i; k++){
    cout << m[k];
    if(k==i-1) break;
    cout << " + ";
  }
  cout << endl;
}


void solveDP(int n, int M, int P, int *p, int *e){
  int **t = new int* [n+1];
  int inf = M+1;
  for(int i=0; i<n+1; i++){
    t[i] = new int [P+1];
  }
  
  for(int i=0;i<n+1;i++){
    t[i][0] = 0;
  }

  for(int i=1;i<P+1;i++){
    t[0][i] = inf;
  }

  int m0,m1,max_p, min_e;
  
  for(int i=1;i<n+1;i++){
    for(int j=1; j<P+1;j++){
      if(j<p[i-1]) t[i][j] = t[i-1][j];
      else{
	m0 = t[i-1][j];
	m1 = e[i-1] + t[i-1][j-p[i-1]];
	if(m1<=M){
	  if(m0<m1) t[i][j] = m0;
	  else t[i][j] = m1;
	}
	else t[i][j] = m0;
      }
    }
  }
  


  int flag = 0;
  min_e = M;

  for(int i = P; i>0;i--){
      for(int j = 0; j<=n;j++){
	if(t[j][i]!=inf){
	  if(t[j][i] <= min_e){
	    min_e = t[j][i];
	    max_p = i;
	    flag = 1;
	  }
      }
    }
    if(flag == 1) break ;
    
  }
  
  cout<<"Minimum effort: "<< min_e<<endl;
  cout<<"Maximum points: "<< max_p<<endl;
  

  
  

}

int main(){
  int n,M, *m;

  cout<<"n = ";
  cin >> n;
  cout<<"M = ";
  cin >> M;
 
  cout << "Part1 (Greedy)"<<endl;
  
  m = new int [n];
  cout<<"+++ Efforts : ";
  for(int i=0; i<n; i++){
    cin >> m[i];
  }

  solveGRD(n,M,m);
 
  int *p,*e, P=0;
  p = new int [n];
  e = new int [n];
  cout<<"+++ Points : ";
  for(int i=0; i<n; i++){
    cin >> p[i];
    P += p[i];
  }
 
  cout<<"+++ Efforts : ";
  for(int i=0; i<n; i++){
    cin >> e[i];
  }
  
  cout << "Part 2 (DP)"<<endl;
  solveDP(n, M, P, p, e);


  return 0;
}
