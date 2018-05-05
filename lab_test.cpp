/* Name : Siddhant Haldar
   Roll No. : 16EE30025
   Machine No. : 91
   ODD PC
*/

#include <iostream>

using namespace std;

int greedy(int **C, int n){
  int cost, min_cost = 9999, j_chosen, j_pos=0, total_cost = 0, hor_cost = 0, hor = 0;
  
  for(int i=0; i<n-1; i++){
    for(int j=j_pos; j<n; j++){
      if(i==0){
	cost = C[0][j];
	if(cost < min_cost){
	  min_cost = cost;
	  j_chosen = j;
	  hor = 0;
	}
      }
      else{
	cost = (j-j_pos)*5 + C[i][j];
	if(cost<min_cost){
	  min_cost = cost;
	  j_chosen = j;
	  hor = (j-j_pos)*5;
	}
      }
    }
    cout<<"    Building flyover from ("<<i<<","<<j_chosen<<") to ("<<i+1<<","<<j_chosen<<") : Cost = "<<C[i][j_chosen]<<endl; 
    total_cost += min_cost;
    hor_cost += hor;
    hor = 0;
    j_pos = j_chosen;
    min_cost = 9999;
    
  }
  cout<<"    Total cost of the horizontal segments       = "<<hor_cost<<endl;
  return total_cost;
}

int DP(int **C, int n){
  int **T, cost1, cost2, min_cost=9999;
  
  T = new int* [n];
  for(int i=0; i<n; i++){
    T[i] = new int [n];
  }
  
  T[0][0] = 0;
  for(int i=1; i<n; i++){
    T[0][i] = 0;   // Initialize first row to sum of horizontal weights from (0,0) to (0,i)
    T[i][0] = C[i-1][0] + T[i-1][0] ;     // Initialize first column to sum of vertical weights from (0,0) to (i,0)
  }

  for(int i=1; i<n; i++){
    for(int j=1; j<n; j++){
      cost1 = C[i-1][j] + T[i-1][j];
      cost2 = 5 + T[i][j-1];
      T[i][j] = (cost1<cost2) ? cost1 : cost2;      
    }
  }

  for(int i=0;i<n; i++){
    if(T[n-1][i]<min_cost) min_cost = T[n-1][i];
  }

  return min_cost;

}

void DPsol(int **C, int n){  
  int **T, cost1, cost2, min_cost=9999;
  int **track;  //to keep track of left(1), up(2)
  
  T = new int* [n];
  for(int i=0; i<n; i++){
    T[i] = new int [n];
  }

  track = new int* [n];
  for(int i=0; i<n; i++){
    track[i] = new int [n];
  }
    
  T[0][0] = 0;
  for(int i=1; i<n; i++){
    T[0][i] = 0;   // Initialize first row to sum of horizontal weights from (0,0) to (0,i)
    T[i][0] = C[i-1][0] + T[i-1][0] ;     // Initialize first column to sum of vertical weights from (0,0) to (i,0)
  }

  track[0][0] = 0;
  for(int i=1; i<n; i++){
    track[0][i] = 0;   // start point
    track[i][0] = 2 ;     // always move up
  }

  for(int i=1; i<n; i++){
    for(int j=1; j<n; j++){
      cost1 = C[i-1][j] + T[i-1][j];
      cost2 = 5 + T[i][j-1];
      T[i][j] = (cost1<cost2) ? cost1 : cost2; 
      if(cost1<cost2) track[i][j] = 2;
      else track[i][j] = 1;
    }
  }
  
  int min_i;

  for(int i=0;i<n; i++){
    if(T[n-1][i]<min_cost) {
      min_cost = T[n-1][i];
      min_i = i;
    }
  }

  int *rec,hor_cost=0;
  rec = new int [n-1];
  for(int k = n-1; k>0; k--){
    while(track[k][min_i] == 1) {
      min_i-=1;
      hor_cost+=5;
    }
    if(track[k][min_i] == 2){
      rec[k-1]=min_i;
      continue;
    }
    if(track[k-1][min_i] == 0) break;
  }

  for(int i=0; i<n-1; i++){
    cout<<"    Building flyover from ("<<i<<","<<rec[i]<<") to ("<<i+1<<","<<rec[i]<<") : Cost = "<<C[i][rec[i]]<<endl;
  }

  cout<<"    Total cost of the horizontal segments      = "<<hor_cost<<endl;

  return; 

}

int main(){
  int n,**C,min_cost;
  
  cout<<"n : ";
  cin >> n;

  C = new int* [n-1];
  for(int i=0; i<n-1; i++){
    C[i] = new int [n];
  }

  cout<<"+++ Flyover building costs"<<endl;
  for(int i=0; i<n-1; i++){
    for(int j=0; j<n; j++){
      cin>>C[i][j];
    }
  }

  cout<<"+++ Part 1: Greedy Algorithm"<<endl;
  min_cost = greedy(C,n);
  cout<<"--- Total cost = "<<min_cost<<endl;

  cout<<endl<<"+++ Part 2: Dynamic programming algorithm"<<endl;
  min_cost = DP(C,n);
  cout<<"--- Total cost = "<<min_cost<<endl;

  cout<<endl<<"+++ Part 3: Dynamic programming algorithm with solution"<<endl;
  DPsol(C,n);

  return 0;
}
