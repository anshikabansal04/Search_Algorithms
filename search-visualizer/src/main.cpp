#include "raylib.h"

#include "Grid.h"
#include<queue>
#include<vector>
#include<climits>
#include<functional>
#include<iostream>
#include<stack>
using namespace std;
// struct Node
// {
// int row;
// int col;
// bool visited=false;
// int dis=INT_MAX;
// Node* parent=nullptr;
// };
struct Node
{
    int row;
    int col;
    bool visited=false;
    int g = INT_MAX;  
    int h = 0;         
    int f = INT_MAX;   

    Node* parent=nullptr;
};
int heuristic(Node* a, Node* b)
{
    return abs(a->row - b->row) + abs(a->col - b->col);
}
void astar(vector<vector<Node>>& nodes, Node* start, Node* end,Grid &grid)
{
    priority_queue<pair<int,Node*>,
    vector<pair<int,Node*>>,
    greater<pair<int,Node*>>> pq;
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
// void bfs(vector<vector<Node>>&nodes,Node* start,Node* end,Grid &grid){
//     queue<Node*>q;
//     start->visited=true;
//     q.push(start);
//     while(!q.empty()){
// Node* current=q.front();
// q.pop();
// if(current==end){
//     break;
// }
// int directions[8][2] = { {-1,0},{1,0},{0,-1}, {0,1},{-1,-1},{-1,1},{1,-1}, {1,1} } ;
// for(auto& dir:directions){
//         int newrow=current->row+dir[0];
//          int newcol=current->col+dir[1];
//  if(newrow >=0 && newrow < (int)nodes.size() &&newcol >=0 &&newcol < (int)nodes[0].size()){
//     Node* neighbour=&nodes[newrow][newcol];
//     if(!neighbour->visited){
//         neighbour->visited=true;
//         grid.set(neighbour->row, neighbour->col, GREEN);
//         neighbour->parent=current;
//         q.push(neighbour);
//     }
// }
// }
// }
// Node* current = end;
//     while(current != nullptr)
//     {
//         cout << "(" << current->row << "," << current->col << ")" << endl;
//         grid.set(current->row, current->col, RED);
//         current = current->parent;
//     }
// }
// void dfs(vector<vector<Node>>&nodes,Node* start,Node* end){
//     stack<Node*>st;
//     start->visited=true;
//     st.push(start);
//     while(!st.empty()){
//         Node* current=st.top();
//         st.pop();
//         if(current==end){
//             break;
//         }
//         int directions[8][2] = { {-1,0},{1,0},{0,-1}, {0,1},{-1,-1},{-1,1},{1,-1}, {1,1} } ;
// for(auto& dir:directions){
//          int newrow=current->row+dir[0];
//          int newcol=current->col+dir[1];
//  if(newrow >=0 && newrow < nodes.size() &&newcol >=0 &&newcol < nodes[0].size()){
//     Node* neighbour=&nodes[newrow][newcol];
// if(!neighbour->visited){
//        neighbour->visited=true;
//          neighbour->parent=current;
//          st.push(neighbour);
//     }
// }
// }
//     }
//     Node* current = end;

//     while(current != nullptr)
//     {
//         cout << "(" << current->row << "," << current->col << ")" << endl;
// current = current->parent;
//     }
// }
// void dijkstra(vector<vector<Node>>& nodes,Node* start,Node* end,Grid &grid)
// {
//     priority_queue<pair<int, Node*>,
//     vector<pair<int, Node*>>,
//         greater<pair<int, Node*>>> pq;
// start->dis=0;
// pq.push({0,start});
// while(!pq.empty())
// {
//     Node* current = pq.top().second;
//     pq.pop();
// if(current->visited){
//     continue;
// }
//     current->visited=true;
//     grid.set(current->row, current->col, BLUE);

// if(current==end){
//     break;
// }
//     int directions[8][2] = { {-1,0},{1,0},{0,-1}, {0,1},{-1,-1},{-1,1},{1,-1}, {1,1} } ;
//     for(auto& dir:directions){
//         int newrow=current->row+dir[0];
//          int newcol=current->col+dir[1];
//  if(newrow >=0 && newrow < (int)nodes.size() &&newcol >=0 &&newcol < (int)nodes[0].size()){
//     Node* neighbour=&nodes[newrow][newcol];
//     int newdistance=current->dis+1;
//     if(newdistance < neighbour->dis)
// {
//     neighbour->dis = newdistance;
//     neighbour->parent = current;

//     pq.push({neighbour->dis, neighbour});
// }
//  }
//     }
// }
//      Node* current = end;
//     while(current != nullptr)
//     {
//         cout << "(" << current->row << "," << current->col << ")" << endl;
//            grid.set(current->row, current->col, YELLOW);
//         current = current->parent;
//     }
// }

int main() {
    // --- grid setup ---------------------------------------------------------
    constexpr int kRows = 20;
    constexpr int kCols = 30;
    constexpr int kCellSize = 28;

    Grid grid(kRows, kCols, kCellSize);

    // --- window -------------------------------------------------------------
    InitWindow(grid.pixelWidth(), grid.pixelHeight(), "Search Visualizer");
    SetTargetFPS(60);
vector<vector<Node>> nodes(
    kRows,
    vector<Node>(kCols)
);
for(int r = 0; r < kRows; r++)
{
    for(int c = 0; c < kCols; c++)
    {
        nodes[r][c].row = r;
        nodes[r][c].col = c;
    }
}
Node* start = &nodes[0][0];
Node* end = &nodes[19][29];
//bfs(nodes, start, end,grid);
astar(nodes,start,end,grid);
    // --- render loop --------------------------------------------------------
    // Everything algorithm-related goes in here: read input, update cell
    // colours via grid.set(...), and it draws automatically.
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        grid.draw();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
