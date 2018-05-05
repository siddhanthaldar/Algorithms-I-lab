// M/C No. : 91   Siddhant Haldar   16EE30025
#include <iostream>
#include <queue>

using namespace std;

typedef struct _node{
  int val;
  _node *next;
} node;

typedef node* graph;

int BFS(graph G, int u,int n,int n2){
  int *visited;
  queue <int> q;        //queue used for BFS
  int v;
  int *level;
  level = new int [n];
  
  visited = new int [n];
  for(int i=0; i<n; i++){
    visited[i] = 0;                //make visited array 0
  }
  
  q.push(u);                      // push first value
  visited[u] = 1;
  level[u] = 0;
  
  while(q.size()!=0){
    v = q.front();
    q.pop();                      // pop

    node *p;
    p = &G[v];
    p = p->next;
    while(p!=NULL){
      //p = p->next;
      if(visited[p->val] == 0){
	q.push(p->val);
	visited[p->val] = 1;
	level[p->val] =level[v]+1;
	if( p->val>=(n-n2)) return level[p->val];   //check if target reached
      }
      p = p->next;
    }
  }
  return 99999;
}

void readgraph(graph G, int m){
  cout <<" Enter edges: ";
  int a,b;
  node *p,*q;
  
  for(int i=0; i<m ; i++){
    cin>>a;
    cin>>b;
   
    p = &G[a];
    q = new node;
    q->val = b;
    q->next = p->next;
    p->next = q;
    
    p = &G[b];
    q = new node;
    q->val = a;
    q->next = p->next;
    p->next = q;
  }
}

void printgraph(graph G, int n){
  cout<<"+++ The constructed graph"<<endl;
  node *p;
  for(int i=0; i<n;i++){
    cout<<i<<" -> ";
    p = &G[i];
    while(p->next != NULL){
      p = p->next;
      cout<<p->val<<" ";
    }
    cout<< endl;    
  }
}

void computedist1(graph G, int n, int n1, int n2){
  int min,val;
  min = 99999;
  for(int i=0; i<n1; i++){
    val = BFS(G,i,n,n2);
    cout<<"BFS("<<i<<") returns ";
    if(val == 9999) cout<<"INFINITY"<<endl;
    else cout<< val<<endl;
    
    if(val<min) min = val;
  }
  cout<<"--- d(V1,V2) = "<<min<<endl;
}

void deletefromarray(graph G, int *store, int *trans, int n,int n1, int n2){
  int *visited;
  visited = new int [n];
  for(int i=0; i<n; i++) visited[i] = 0;
  for(int i=0; i<n; i++){
    if(store[i] != -1){
      node *p;
      p = &G[i];
      p = p->next;
      while(p!=NULL){
	if(p->val>=(n-n2)){
	  p->val = n-1;
	  visited[i] = 1;
	}
	p=p->next;
      }
      
    }
    if(trans[i] != -1){
      node *p;
      p = &G[i];
      p = p->next;
      while(p!=NULL){
	if((p->val<n1)){//&&(visited[i]==0)){
	  p->val = 0;
	  visited[i] = 1;
	}
	p=p->next;
      }
      
    }
  }
}

void computedist2(graph G,int n, int n2){
  cout<<endl<<"---  div(V1,V2) = "<<BFS(G,0,n,n2)<<endl;
}

void modifyG(graph G, int n, int n1, int n2){
  int *trans,*store;     //store is an array storing shifted elements
  trans = new int[n];
  store = new int [n];
  
  for(int i=0; i<n; i++){
    trans[i] = -1;
    store[i] = -1;
  }
  node *q,*x;
  q = &G[0];
  for(int i=1; i<n1; i++){
    node *p;
    p = &G[i];
    p = p->next;
    while(p != NULL){
      if(p->val < n1){
	p = p->next; continue;
      }
      if(trans[p->val] == -1){
	trans[p->val] = 0;
	x = new node;
	x->val = p->val;
	x->next =q->next;
	q->next = x;	
      }
      p = p->next;
    }
    (&G[i])->next = NULL;
    
  }
  
  q = &G[11];
  
   while(q->next!=NULL){
     q= q->next;
     store[q->val] = 11;
   }
  for(int i=n-n2; i<n-1; i++){
    node *p;
    p = &G[i];
    p = p->next;
    while(p != NULL){
      if(p->val >= n-n2){
	p = p->next; continue;
      }
      if(store[p->val] == -1){
	store[p->val] = 11;
	x = new node;
	x->val = p->val;
	x->next =q->next;
	q->next = x;	
      }
      p = p->next;
    }
    (&G[i])->next = NULL;
    
  }
  
  //Delete element
  deletefromarray(G,store,trans,n,n1,n2);

   printgraph(G,n);
   
   computedist2(G,n,n2);
   
}




int main(){
  int n,m,n1,n2;
  cout<<"n = ";
  cin >> n;
  cout << "m = ";
  cin >> m;
  cout << "n1 = ";
  cin >> n1;
  cout << "n2 = ";
  cin >> n2;

  graph G;
  G = new node [n];
  
  for(int i=0; i<n; i++){
    G[i].val = -1;
    G[i].next = NULL;
  }
  
  // Create and print adjlist
  readgraph(G,m);
  printgraph(G,n);

  //Method 1
  cout<<endl<<"+++ Method 1"<<endl;
  computedist1(G,n,n1,n2);
 
  //Method2
  cout<<endl<<"+++ Method 2"<<endl;
  modifyG(G,n,n1,n2);
  
  return 0;
}
