#include "Search.h"
#include <queue>
#include <stack>
#include <iostream>
#include <functional>
#include<cmath>
using namespace std;
int Search::heuristic(Node*a, Node*b)
{
      return abs(a->row - b->row) + abs(a->col - b->col);
}

void Search::astar(vector<vector<Node>>& nodes, Node* start, Node* end,Grid &grid){
      priority_queue<pair<int,Node*>,vector<pair<int,Node*>>, greater<pair<int,Node*>>> pq;
    start->g = 0;
    start->h = heuristic(start,end);
    start->f = start->g + start->h;
    pq.push({start->f,start});
    while(!pq.empty())
    {
         Node* current = pq.top().second;
         pq.pop();
        if(current->visited)
            continue;
        current->visited = true;
        grid.set(current->row,  current->col,BLUE);
        if(current == end)
            break;
 int directions[8][2] = { {-1,0},{1,0},{0,-1}, {0,1},{-1,-1},{-1,1},{1,-1}, {1,1} } ;
for(auto& dir : directions)
        {
int newrow = current->row + dir[0];
int newcol = current->col + dir[1];

if(newrow >=0 &&newrow < (int)nodes.size() &&newcol >=0 && newcol < (int)nodes[0].size())
            {
 Node* neighbour = &nodes[newrow][newcol];
 if(neighbour->obstacle){
      continue;
 }
                int newG = current->g + 1;
                if(newG < neighbour->g)
                {
neighbour->g = newG;
neighbour->h = heuristic(neighbour,end);
neighbour->f =neighbour->g + neighbour->h;
 neighbour->parent = current;
 pq.push({neighbour->f, neighbour});
                }
            }
     }
    }
   Node* current=end;
    while(current!=nullptr)
    {
        cout<<"("<<current->row<<","<<current->col<<")"<<endl;
        grid.set(current->row, current->col, YELLOW);
        current=current->parent;
    }
}
void Search::bfs(vector<vector<Node>>&nodes,Node* start,Node* end,Grid &grid){
queue<Node*>q;
 start->visited=true;
      q.push(start);
     while(!q.empty()){
 Node* current=q.front();
 q.pop();
 if(current==end){
    break;
}
int directions[8][2] = { {-1,0},{1,0},{0,-1}, {0,1},{-1,-1},{-1,1},{1,-1}, {1,1} } ;
 for(auto& dir:directions){
        int newrow=current->row+dir[0];
         int newcol=current->col+dir[1];
 if(newrow >=0 && newrow < (int)nodes.size() &&newcol >=0 &&newcol < (int)nodes[0].size()){
    Node* neighbour=&nodes[newrow][newcol];
    if(neighbour->obstacle){
      continue;
    }
    if(!neighbour->visited){
        neighbour->visited=true;
        grid.set(neighbour->row, neighbour->col, GREEN);
         neighbour->parent=current;
        q.push(neighbour);
    }
}
 }
 }
Node* current = end;
    while(current != nullptr)
    {
        cout << "(" << current->row << "," << current->col << ")" << endl;
        grid.set(current->row, current->col, RED);  
              current = current->parent;
     }
 }
void Search::dijkstra(vector<vector<Node>>& nodes,Node* start,Node* end,Grid &grid){
    priority_queue<pair<int, Node*>,
    vector<pair<int, Node*>>,
        greater<pair<int, Node*>>> pq;
start->dis=0;
pq.push({0,start});
while(!pq.empty())
{
    Node* current = pq.top().second;
    pq.pop();
if(current->visited){
    continue;
}
    current->visited=true;
    grid.set(current->row, current->col, BLUE);

if(current==end){
    break;
}
    int directions[8][2] = { {-1,0},{1,0},{0,-1}, {0,1},{-1,-1},{-1,1},{1,-1}, {1,1} } ;
    for(auto& dir:directions){
        int newrow=current->row+dir[0];
         int newcol=current->col+dir[1];
 if(newrow >=0 && newrow < (int)nodes.size() &&newcol >=0 &&newcol < (int)nodes[0].size()){
    Node* neighbour=&nodes[newrow][newcol];
    if(neighbour->obstacle){
      continue;
    }
    int newdistance=current->dis+1;
    if(newdistance < neighbour->dis)
{
    neighbour->dis = newdistance;
    neighbour->parent = current;

    pq.push({neighbour->dis, neighbour});
}
 }
    }
}
     Node* current = end;
    while(current != nullptr)
    {
        cout << "(" << current->row << "," << current->col << ")" << endl;
           grid.set(current->row, current->col, YELLOW);
        current = current->parent;
    }
}
void Search::dfs(vector<vector<Node>>&nodes,Node* start,Node* end,Grid &grid){
    stack<Node*>st;
    start->visited=true;
    st.push(start);
    while(!st.empty()){
        Node* current=st.top();
        st.pop();
        if(current==end){
            break;
        }
        int directions[8][2] = { {-1,0},{1,0},{0,-1}, {0,1},{-1,-1},{-1,1},{1,-1}, {1,1} } ;
for(auto& dir:directions){
         int newrow=current->row+dir[0];
         int newcol=current->col+dir[1];
 if(newrow >=0 && newrow < (int)nodes.size() &&newcol >=0 &&newcol < (int)nodes[0].size()){
    Node* neighbour=&nodes[newrow][newcol];
    if(neighbour->obstacle){
      continue;
    }
if(!neighbour->visited){
       neighbour->visited=true;
       grid.set(neighbour->row, neighbour->col, GREEN);
         neighbour->parent=current;
         st.push(neighbour);
    }
}
}
    }
    Node* current = end;

    while(current != nullptr)
    {
        cout << "(" << current->row << "," << current->col << ")" << endl;
current = current->parent;
    }
}