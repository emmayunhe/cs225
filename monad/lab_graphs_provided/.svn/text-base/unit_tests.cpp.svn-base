/**
 * @file unit_tests.cpp
 * @date Fall 2012
 * @author Sean Massung
 */

#include "graph.h"
#include "graph_tools.h"
#include "proxy.h"

//  minWeight - one edge - return value
#if MONAD_SPLIT
UNIT_TEST(minWeight_OneEdge_ReturnValue, 5, 11, 1000)
{
    Graph graph(true, 2, 789);
    int minWeight = GraphTools::findMinWeight(graph);
    ASSERT(minWeight == 145);
}
#endif

//  minWeight - one edge - edge label
#if MONAD_SPLIT
UNIT_TEST(minWeight_OneEdge_EdgeLabel, 5, 11, 1000)
{
    Graph graph(true, 2, 789);
    GraphTools::findMinWeight(graph); // ignore return value
    ASSERT(graph.getEdgeLabel(0, 1) == "MIN");
}
#endif

//  minWeight - multiple edges - return value
#if MONAD_SPLIT

bool minEdge(const Edge & a, const Edge & b)
{
    return a.weight < b.weight;
}

UNIT_TEST(minWeight_MultiEdge_ReturnValue, 5, 11, 1000)
{
    Graph graph(true, 12, 12345); // 66 on (10, 11)
    int minWeight = GraphTools::findMinWeight(graph);
    ASSERT(minWeight == 66);

    vector<Edge> edges = graph.getEdges();
    std::sort(edges.begin(), edges.end(), minEdge);

    Edge minEdge = *edges.begin();
    ASSERT(minEdge.label == "MIN");
    vector<Edge>::iterator nonMinEdge;
    for(nonMinEdge = edges.begin() + 1; nonMinEdge != edges.end(); ++nonMinEdge)
        ASSERT(nonMinEdge->label != "MIN");
}
#endif

//  minWeight - multiple edges - edge labels
#if MONAD_SPLIT
UNIT_TEST(minWeight_MultiEdge_EdgeLabels, 5, 11, 1000)
{
    Graph graph(true, 12, 12345); // 66 on (10, 11)
    graph.print();
    GraphTools::findMinWeight(graph); // ignore return value
    vector<Edge> edges = graph.getEdges();
    vector<Edge>::iterator edge;
    for(edge = edges.begin(); edge != edges.end(); ++edge)
    {
        if((edge->source == 6  && edge->dest == 9) || (edge->source == 9 && edge->dest == 6))
        {
            // this is the min edge; is it labeled?
            if(edge->label != "MIN")
                FAIL("did not label the correct minimum edge");
        }
        else if(edge->label == "MIN")
        {
            // this is *not* the min edge, it shouldn't be labeled as such
            FAIL("labeled a non-minimum edge weight as \"MIN\"");
        }
    }
}
#endif

//  minPath - one edge - return value
#if MONAD_SPLIT
UNIT_TEST(minPath_OneEdge_ReturnValue, 5, 11, 1000)
{
    Graph graph(false, 2, 135);
    ASSERT(GraphTools::findShortestPath(graph, 0, 1) == 1);
}
#endif

//  minPath - one edge - edge label
#if MONAD_SPLIT
UNIT_TEST(minPath_OneEdge_EdgeLabel, 5, 11, 1000)
{
    Graph graph(false, 2, 135);
    GraphTools::findShortestPath(graph, 0, 1); // ignore return value
    ASSERT(graph.getEdgeLabel(0, 1) == "MINPATH");
}
#endif

//  minPath - multiple edges - return value
#if MONAD_SPLIT
UNIT_TEST(minPath_MultiEdge_ReturnValue, 5, 11, 1000)
{
    Graph graph(false, 9, 99877);
    ASSERT(GraphTools::findShortestPath(graph, 2, 8) == 2);
}
#endif

//  minPath - multiple edges - edge labels
#if MONAD_SPLIT
UNIT_TEST(minPath_MultiEdge_EdgeLabels, 5, 11, 1000)
{
    Graph graph(false, 9, 99877);
    GraphTools::findShortestPath(graph, 2, 8); // ignore return value
    vector<Edge> edges = graph.getEdges();
    vector<Edge>::iterator edge;
    for(edge = edges.begin(); edge != edges.end(); ++edge)
    {
        if( ((edge->source == 2 && edge->dest == 4) ||
             (edge->source == 4 && edge->dest == 2 ))   ||
             
            ((edge->source == 8 && edge->dest == 4) ||
             (edge->source == 4 && edge->dest == 8 ))
          )
        {
            // this edge is on the min path; is it labeled?
            if(edge->label != "MINPATH")
                FAIL("did not label the correct minimum path");
        }
        else if(edge->label == "MINPATH")
        {
            // this is *not* on the minimum path, it shouldn't be labeled as such
            FAIL("labeled a non-minimum path edge as \"MIN\"");
        }
    }
}
#endif

//  Test Kruskal's
#if MONAD_SPLIT
bool edge_is( Edge & e, int s, int d ) {
    return (e.source == s && e.dest == d) || (e.dest == s && e.source == d);
}

UNIT_TEST(kruskal_all, 5, 12, 1000)
{
    // there are no duplicate weights in this graph
    //  (i.e., there is only one solution)
    Graph graph(true, 9, 846811127);
    GraphTools::findMST(graph);
    // edges in the MST are: 
    // (8, 5), (8, 7), (7, 0), (7, 4), (6, 0), (5, 2), (5, 3), (1, 0)
    vector<Edge> edges = graph.getEdges();
    vector<Edge>::iterator edge;
    for(edge = edges.begin(); edge != edges.end(); ++edge)
    {
        if( edge_is(*edge, 8, 5) || edge_is(*edge, 8, 7)
                || edge_is(*edge, 7, 0) || edge_is(*edge, 7, 4)
                || edge_is(*edge, 6, 0) || edge_is(*edge, 5, 2)
                || edge_is(*edge, 5, 3) || edge_is(*edge, 1, 0) ) {
            ASSERT( edge->label == "MST" );
        } else {
            ASSERT( edge->label != "MST" );
        }
    }
}
#endif
