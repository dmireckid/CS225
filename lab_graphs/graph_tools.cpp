/**
 * @file graph_tools.cpp
 * This is where you will implement several functions that operate on graphs.
 * Be sure to thoroughly read the comments above each function, as they give
 *  hints and instructions on how to solve the problems.
 */

#include "graph_tools.h"
#include "edge.h"

/**
 * Finds the minimum edge weight in the Graph graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @return the minimum weighted edge
 *
 * @todo Label the minimum edge as "MIN". It will appear blue when
 *  graph.savePNG() is called in minweight_test.
 *
 * @note You must do a traversal.
 * @note You may use the STL stack and queue.
 * @note You may assume the graph is connected.
 *
 * @hint Initially label vertices and edges as unvisited.
 */
int GraphTools::findMinWeight(Graph& graph)
{
    vector<Vertex> vertexes = graph.getVertices();
    vector<Edge> edges = graph.getEdges();

    for(size_t i=0; i<vertexes.size(); i++){
      graph.setVertexLabel(vertexes[i], "UNEXPLORED");
    }
    for(size_t i=0; i<edges.size(); i++){
      Vertex a = edges[i].source;
      Vertex b = edges[i].dest;
      graph.setEdgeLabel(a, b, "UNEXPLORED");
    }

    Vertex start = graph.getStartingVertex();
    vector<Vertex> adj = graph.getAdjacent(start);
    int minWeight = graph.getEdgeWeight(start, adj[0]);

    queue<Vertex> que;
    que.push(start);
    graph.setVertexLabel(start, "VISITED");

    Vertex min, min2;

    while(!que.empty()){
       Vertex temp = que.front();
       vector<Vertex> adjac = graph.getAdjacent(temp);
       que.pop();
       for(size_t i=0; i<adjac.size(); i++){
         if(graph.getVertexLabel(adjac[i]) == "UNEXPLORED"){
           graph.setEdgeLabel(temp, adjac[i], "DISCOVERY");
           graph.setVertexLabel(adjac[i], "VISITED");
           que.push(adjac[i]);
         }
         else if(graph.getEdgeLabel(temp, adjac[i]) == "UNEXPLORED"){
           graph.setEdgeLabel(temp, adjac[i], "CROSS");
         }

         if(graph.getEdgeWeight(temp, adjac[i]) <= minWeight){
           minWeight = graph.getEdgeWeight(temp, adjac[i]);
           min = temp;
           min2 = adjac[i];
         }
       }
    }
    graph.setEdgeLabel(min, min2, "MIN");
    return minWeight;
}

/**
 * Returns the shortest distance (in edges) between the Vertices
 *  start and end.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @param start - the vertex to start the search from
 * @param end - the vertex to find a path to
 * @return the minimum number of edges between start and end
 *
 * @todo Label each edge "MINPATH" if it is part of the minimum path
 *
 * @note Remember this is the shortest path in terms of edges,
 *  not edge weights.
 * @note Again, you may use the STL stack and queue.
 * @note You may also use the STL's unordered_map, but it is possible
 *  to solve this problem without it.
 *
 * @hint In order to draw (and correctly count) the edges between two
 *  vertices, you'll have to remember each vertex's parent somehow.
 */
int GraphTools::findShortestPath(Graph& graph, Vertex start, Vertex end)
{
    //TODO: YOUR CODE HERE
    vector<Vertex> vertexes = graph.getVertices();
    vector<Edge> edges = graph.getEdges();

    for(size_t i=0; i<vertexes.size(); i++){
      graph.setVertexLabel(vertexes[i], "UNEXPLORED");
    }
    for(size_t i=0; i<edges.size(); i++){
      Vertex a = edges[i].source;
      Vertex b = edges[i].dest;
      graph.setEdgeLabel(a, b, "UNEXPLORED");
    }
    int path =0;
    unordered_map<Vertex, Vertex> mapp;
    queue<Vertex> que;
    que.push(start);
    graph.setVertexLabel(start, "VISITED");

    // Vertex min, min2;
    // return -1;
    while(!que.empty()){
       Vertex temp = que.front();
       vector<Vertex> adjac = graph.getAdjacent(temp);
       que.pop();
       for(size_t i=0; i<adjac.size(); i++){
         if(graph.getVertexLabel(adjac[i]) == "UNEXPLORED"){
           mapp[adjac[i]] = temp;
           graph.setEdgeLabel(temp, adjac[i], "DISCOVERY");
           graph.setVertexLabel(adjac[i], "VISITED");
           que.push(adjac[i]);
         }
         else if(graph.getEdgeLabel(temp, adjac[i]) == "UNEXPLORED"){
           graph.setEdgeLabel(temp, adjac[i], "CROSS");
         }

         // if(graph.getEdgeWeight(temp, adjac[i]) <= minWeight){
         //   minWeight = graph.getEdgeWeight(temp, adjac[i]);
         //   min = temp;
         //   min2 = adjac[i];
         // }
       }
    }
    while(start != end){
      graph.setEdgeLabel(end, mapp[end], "MINPATH");
      end = mapp[end];
      path++;
    }
    return path;
}

/**
 * Finds a minimal spanning tree on a graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to find the MST of
 *
 * @todo Label the edges of a minimal spanning tree as "MST"
 *  in the graph. They will appear blue when graph.savePNG() is called.
 *
 * @note Use your disjoint sets class from MP 7.1 to help you with
 *  Kruskal's algorithm. Copy the files into the dsets.h and dsets.cpp .
 * @note You may call std::sort instead of creating a priority queue.
 */

void GraphTools::findMST(Graph& graph)
{
    //TODO: YOUR CODE HERE
    // vector<Vertex> vertexes = graph.getVertices();
    // vector<Edge> edges = graph.getEdges();
    // int vert = vertexes.size(), ed = edges.size();
    // DisjointSets dip;
    // dip.addelements(vert);
    // sort(edges.begin(), edges.end());
    //
    // for(size_t i=0; i<edges.size(); i++){
    //   Vertex a = edges[i].source;
    //   Vertex b = edges[i].dest;
    //   if(dip.find(a) != dip.find(b)){
    //     dip.setunion(a, b);
    //     graph.setEdgeLabel(a, b, "MST");
    //   }
    // }
}
