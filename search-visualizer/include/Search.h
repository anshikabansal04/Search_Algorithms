#pragma once 
#include<queue>
#include<vector>
#include<climits>
#include<functional>
#include<iostream>
#include<stack>
#include "Grid.h"
using namespace std;
struct Node
{
    int row;
    int col;
    bool visited=false;
    int g = INT_MAX;  
    int h = 0;         
    int f = INT_MAX; 
    Node* parent=nullptr;
    int dis=INT_MAX;
    bool obstacle=false;
};
class Search{
   public:
   /**
    * @brief Executes a* path finidng algorithms 
    * A* uses :
    * f(n)=g(n)+h(n)
    * where g is distance from start and h is estimated distance to goal.
    * @param nodes 2 d containing grid 
    * @param   start starting node 
    * @param  end destination node 
    * @Param grid Grid used for visualization
    */
  void astar(vector<vector<Node>>& nodes, Node* start, Node* end,Grid &grid);
  /**
   * @brief executes bredth first search algorithm 
   * BFS explores nodes level by level using a queue.
   * It finds the shortest path in an unweighted grid
   *@param nodes 2D grid containing all nodes.
    * @param start Starting node.
    * @param end Destination node.
   * @param grid Grid object used for visualization.
   */
 void bfs(vector<vector<Node>>&nodes,Node* start,Node* end,Grid &grid);
 /**
     * @brief Executes Depth First Search algorithm.
     *
     * DFS explores as deep as possible before backtracking.
     *
     * @param nodes 2D grid containing all nodes.
     * @param start Starting node.
     * @param end Destination node.
     * @param grid Grid object used for visualization.
     */
    void dfs(vector<vector<Node>>& nodes, Node* start,Node* end,Grid& grid );
    /**
     * @brief Executes Dijkstra shortest path algorithm.
     *
     * Finds the shortest path by always selecting
     * the node with minimum current distance.
     *
     * @param nodes 2D grid containing all nodes.
     * @param start Starting node.
     * @param end Destination node.
     * @param grid Grid object used for visualization.
     */
void dijkstra( vector<vector<Node>>& nodes,Node* start,Node* end,Grid& grid);
private:
    /**
     * @brief Calculates Manhattan distance between two nodes.
     *
     * Used as heuristic function in A* algorithm.
     *
     * @param a First node.
     * @param b Second node.
     *
     * @return Estimated distance between nodes.
     */
    int heuristic(Node* a, Node* b);
};
