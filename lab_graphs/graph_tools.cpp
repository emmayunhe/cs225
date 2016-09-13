/**
 * @file graph_tools.cpp
 * This is where you will implement several functions that operate on graphs.
 * Be sure to thoroughly read the comments above each function, as they give
 *  hints and instructions on how to solve the problems.
 */

#include "graph_tools.h"

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
int GraphTools::findShortestPath(Graph & graph, Vertex start, Vertex end)
{
	vector<Vertex> vertices = graph.getVertices();

	for (size_t i=0; i < vertices.size(); i++){
		graph.setVertexLabel(vertices[i], "UNEXPLORED");
	}

	return BFS(graph, start, end);
}

//helpfer function for traversing the graph
//basic skeleton is the same for all the functions
int GraphTools::BFS(Graph &graph, Vertex start, Vertex end){
	std::unordered_map<Vertex, Vertex> vertices;
	int shortestPath = 0;

	queue<Vertex> q;
	q.push(start);
	graph.setVertexLabel(start, "VISITED");

	while(!q.empty()){
		Vertex v = q.front();
		q.pop();
		vector<Vertex> adjs = graph.getAdjacent(v);

		for(size_t i=0; i<adjs.size(); i++){
			if(graph.getVertexLabel(adjs[i])=="UNEXPLORED"){
				graph.setEdgeLabel(v, adjs[i], "DISCOVERY");				
				graph.setVertexLabel(adjs[i], "VISITED");
				vertices[adjs[i]] = v;
				q.push(adjs[i]);
			}
			else if(graph.getEdgeLabel(v, adjs[i])=="UNEXPLORED"){
				graph.setEdgeLabel(v, adjs[i], "CROSS");
			}
		}
	}
	Vertex curr = end;
	while(curr != start){
		graph.setEdgeLabel(curr, vertices[curr], "MINPATH");
		curr = vertices[curr];
		shortestPath++;
	}
	return shortestPath;
}

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
int GraphTools::findMinWeight(Graph & graph)
{
	Vertex a = Vertex(); 
	Vertex b = Vertex();
	vector<Vertex> vertices = graph.getVertices();
	int min;

	for(size_t i=0; i<vertices.size(); i++){
		graph.setVertexLabel(vertices[i], "UNEXPLORED");
	}
	for(size_t i=0; i<vertices.size(); i++){
		if(graph.getVertexLabel(vertices[i]) == "UNEXPLORED"){
			min = BFS(graph, vertices[i], a, b);
		}
	}

	graph.setEdgeLabel(a, b, "MIN");
	return min;
}

//helper function for traversing
int GraphTools::BFS(Graph &graph, Vertex vtx, Vertex &a, Vertex &b){
	int weight = INT_MAX;
	queue<Vertex> q;
	q.push(vtx);

	while(!q.empty()){
		Vertex v = q.front();
		q.pop();
		graph.setVertexLabel(v, "VISITED");
		vector<Vertex> adjs = graph.getAdjacent(v);

		for(size_t i=0; i<adjs.size(); i++){
			if(graph.getVertexLabel(adjs[i]) == "UNEXPLORED"){
				q.push(adjs[i]);
				int tempWeight = graph.getEdgeWeight(v, adjs[i]);
				//cout<<"here"<<endl;
				graph.setEdgeLabel(v, adjs[i], "DISCOVERY");
				if(weight > tempWeight){
					weight = tempWeight;
					a = v;
					b = adjs[i];
				}
			}
			else if(graph.getEdgeLabel(v, adjs[i]) == "UNEXPLORED"){
				graph.setEdgeLabel(v, adjs[i], "CROSS");
			}
		}
	}
	return weight;
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
 *  Kruskal's algorithm. Copy the files into the libdsets folder.
 * @note You may call std::sort (http://www.cplusplus.com/reference/algorithm/sort/)
 *  instead of creating a priority queue.
 */
void GraphTools::findMST(Graph & graph)
{
	vector<Edge> edges = graph.getEdges();
	std::sort(edges.begin(), edges.end(), checkWeight);
	DisjointSets set;
	vector<Vertex> vertices = graph.getVertices();
	set.addelements(vertices.size());

	for(size_t i=0; i<edges.size(); i++){
		Vertex x = edges[i].source;
		Vertex y = edges[i].dest;
		if(set.find(x) != set.find(y)){
			set.setunion(x, y);
			graph.setEdgeLabel(x, y, "MST");
		}
	}
}

//helper function for checking the weights
bool GraphTools::checkWeight(Edge a, Edge b){
	return (a.weight < b.weight);
}
