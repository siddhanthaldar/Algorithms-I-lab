#include <iostream>
#include <cmath>

using namespace std;

#define inf 65536

typedef struct _enode{
  int vwt;   // serves purpose of both vertex weight and vertex number
  float ewt; //edge weight
  _enode* next;
}node;

typedef node* graph;


void printgraph(graph G, int n){
  cout<<"+++ The constructed graph"<<endl;
  node *p;
  for(int i=0; i<n;i++){
    cout<<i<<" -> ";
    p = &G[i];
    while(p->next != NULL){
      p = p->next;
      cout<<p->vwt<<" ";    //print vertex number
    }
    cout<< endl;   
  }
}

graph readgraph(graph G, int n,int m){
  int a,b;
  node *p,*q;
 
  cout<<"+++ Reading edges"<<endl;
  for(int i=0; i<m ; i++){
    cin>>a;
    cin>>b;
  
    p = &G[a];
    q = new node;
    q->vwt = b;
    q->next = p->next;
    p->next = q;
  }
 
  cout<<"+++ The generated graph"<<endl;
  printgraph(G,n);

  cout<<endl<<"+++ Reading edge weights"<<endl;
  for(int i=0; i<n; i++){
    p = &G[i];
    p=p->next;
    while(p!=NULL){     
      cout<<"ewt ("<<i<<","<<p->vwt<<" ) = ";
      cin>>p->ewt;

      p=p->next;
    }
  }

  int wgt;
  cout<<"+++ Reading vertex weights"<<endl;
  for(int i=0; i<n; i++){
    cout<<"vwt ("<<i<<" ) = ";
    cin>>wgt;
    G[i].vwt = wgt;

  } 

 
  return G;
}

void heapify(int *pq, int i,float *dist,int *loc){
  int left,right,min;
  int p;

  while(1){
    left = 2*i;
    right = 2*i+1;
    if(left>pq[0]) break;
    if(right>pq[0]) min=left;
    else min = (dist[left] <= dist[right])?left:right;
   
    if(dist[i]<=dist[min]) break; 
    p = pq[i];
    pq[i] = pq[min] ;
    pq[min] = p;
    loc[pq[i]] = i; loc[pq[min]]=min;
   
    i = min;
  }
  return;
}


void deletemin(int *pq,float *dist,int *loc){
  if(pq[0] == 0){
    cout<<"*** Deletion from empty heap attempted..."<<endl;
    return ;
  }
 
  loc[pq[1]] = -1;
  pq[1] = pq[pq[0]];
  pq[0]-=1;
  if(pq[0]>1)heapify(pq,1,dist,loc);
  return;
}

void changepriority(int *heap, int i, float *dist, int *loc){
  int p,q,par = i/2;  //parent
  if(dist[heap[par]]>dist[heap[i]]){
    while(dist[heap[par]]>dist[heap[i]] && i>0){
      p = heap[par];
      heap[par] = heap[i];
      heap[i] = p;
      loc[heap[i]] = i; loc[heap[par]]=par;
      i = par;
    }
    return;
  }
  int left,right;
  left = 2*i; right = 2*i+1;     //Since only decrease priority may be called
  if(heap[i]>heap[left] || heap[i]>heap[right]) heapify(heap,i,dist,loc);
 
  return;
}

void insert(int *pq, int x, float *dist, int *loc){
  pq[0]+=1;
  pq[pq[0]] = x;
  loc[x] = pq[0];

  int i = pq[0];
  int par;
  int temp;

  while(1){
    if(i==1) break;
    par = i/2;
    if(dist[pq[par]] <= dist[pq[i]]) break;
    temp = pq[par];
    pq[par] = pq[i];
    pq[i] = temp;
    loc[pq[par]] = par;
    loc[pq[i]] = i;
    i = par;
  }
  return;
}

void dijkstra(graph G, int n, int s, int t){
  int *pq, *prev,*visited;

    //required arrays
  float *dist;
  int *loc;

  //initialize heap
  pq = new int [n+1];
  pq[0] = 1;
  pq[1] = s;

  //initialize dist
  dist = new float [n];
  for(int i=0;i<n;i++){
    dist[i] = inf;
  } 
  dist[s] = 0;

  //initialize locator array
  loc = new int [n];
  for(int i=0;i<n;i++){
    loc[i] = -1;
  }
  loc[s] = 1;

  //initialize visited array
  visited = new int [n];
  for(int i=0;i<n;i++){
    visited[i] = 0;           //0:unvisited, 1:visited
  }  
  visited[0] = 1;
  //initialize prev array
  prev = new int [n];
  prev[s] = -1;

  graph p;

  int i;

  while(pq[0]!=0){
    i = pq[1];
    if(i==t) break;    //target reached
    deletemin(pq,dist,loc);

    p = &G[i];
    p = p->next;

    while(p!=NULL){
      if(visited[p->vwt] == 0){
        insert(pq,p->vwt,dist,loc);
      } 
      if(dist[i]+p->ewt < dist[p->vwt]){
        prev[p->vwt] = i;
        dist[p->vwt] = dist[i]+p->ewt;
        changepriority(pq, p->vwt,dist,loc);
      }
      p = p->next;
    }
    visited[i] = 1;
  }

  cout<<"--- Shortest ("<<s<<","<<t<<") distance is "<<dist[t]<<endl;

  int *track,size=0;
  track = new int [n];
  i=t;
  while(1){
    track[size] = i;
    if(i==0) break;
    i=prev[i];
    size++;

  }

  cout<<"--- Shortest ("<<s<<","<<t<<") path: ";
  for(int i=size;i>=0;i--){
    cout<<track[i];
    if(i!=0) cout<<" - ";
  }
  cout<<endl;

  return;

}

void dijkstra_log(graph G, int n, int s ,int t){
  graph p,q;
  //graph G1;
  //G2 = new graph [n];
  cout<<endl<<"+++ Changing the edge weights"<<endl;
  for(int i=0; i<n;i++){
    p = &G[i];
    p=p->next;
    while(p!=NULL){
      cout<<"Edge weight ("<<i<<","<<p->vwt<<") changes from "<<p->ewt<<" to ";
      p->ewt = -log(p->ewt);
      cout <<p->ewt<<endl;
      p=p->next;
    }
  }

  cout<<endl<<"+++ Running Dijkstra on the log-converted graph"<<endl;
  dijkstra(G,n,s,t);

  return;
}

void modified_graph(graph G, int n, int s, int t){
  graph H;
  H = new node [2*n];
  for(int i=0;i<2*n;i++){
    H[i].vwt=H[i].ewt=-1;
    H[i].next=NULL;
  }

  /* The graph is consructed in the following way:
     If a points to b,c and e,f point to a, then a_out points
     to b,c and e,f point to a_in. Also if a_in has index i in
     adjacency list, then a_out has index i+n in the adjacency list
  */
  graph p,q,r;
  for(int i=0;i<n;i++){
    p=&G[i];

    q=&H[2*i];
    r=new node;
    r->vwt=(2*i+1);
    r->ewt=p->vwt;
    r->next=q->next;
    q->next=r;

    p=p->next;


    while(p!=NULL){
      q = &H[(2*i+1)];
      r = new node;
      r->vwt=p->vwt * 2;
      r->ewt=0;
      r->next = q->next;
      q->next = r;

      p=p->next;
    }
  }

  cout<<endl<<"+++ Converting vertex weights to edge weights"<<endl;
  printgraph(H, 2*n);

  dijkstra(H,2*n,s,t+5);
  

  return;
}

int main(){
  int n,m,s,t;

  cout<<"n = ";
  cin>>n;
  cout<<"m = ";
  cin>>m;
  cout<<"s = ";
  cin>>s;
  cout<<"t = ";
  cin>>t;


  graph  G;
  G = new node [n];

  for(int i=0; i<n; i++){
    G[i].vwt = -1;
    G[i].ewt = -1;
    G[i].next = NULL;
  }

  readgraph(G,n,m);

  cout<<endl<<endl<<"+++ Running Dijktra on the original graph"<<endl;
  dijkstra(G,n,s,t);

  dijkstra_log(G,n,s,t);
  //PLease comment dijkstra_log(G,n,s,t) to run modified_graph(G,n,s,t) as dijkstra_log modifies the graph 
  modified_graph(G,n,s,t);

  return 0;
}