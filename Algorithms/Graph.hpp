#ifndef GRAPH_HPP_INCLUDED
#define GRAPH_HPP_INCLUDED

#include <iostream>

    // (?!) OOP-wise and ~ "auto-memory mangement"-wise, do all those allocated but unallocated heap calls get
        // delete-called at the end of this object's lifespan (?!); I mean, can it be statically analyzed (?!)
    // does returning an object by stack cause this chain of events: allocation on stack, computation of the function,
         // copying the result in the return, deleting the stack-allocated structure -> it causes the generation of a
         // value being transferred across stacks, which could have been done instead through the heap and not require
         // a deletion and another allocation (?!); unless the stack is structured differently, and returning a stack
         // structure from a function to another doesn't involve a redundant creation-deletion to effectively do the
         // ~ "stack exchange" (*?)
    // specification of a function with parameters either from value-types or reference-types; I do not want to
        // have to rewrite effectively the same code


/// TD
/*  POSSIBLE FUNCTIONALITY

    for each node, compute the shortest path from it to any other node (basically, to compute a sort of "map of shortest paths")
    find all unique cycles in the graph
    find the path(s ?) with the distance that has the property: longest, shortest, closest to an arbitrary value
    find all "islands" (usually there's only one...sad)
    sort edges -. ~ adjacency matrix; (*?) but how to design (as a matrix model) a graph with (possibly) multiple edges between the same nodes (?)
        // I guess, simply store a ~ "tuple" in their dot product (?) => for matrix multiplication, the logic needs to be able to handle this

*/
/*

    essentially, a graph does not require a struct Node, if there is no data pertaining to it; all that is needed are the edges, which
        hold relations (or rather a "connection") between two indices < number of nodes (there is no need to effectively store any nodes,
        just this ~ mapping);
    (*?) now, a graph seen as simply the abstraction for "connectivity" -> one can do isomorphism searches and checks, ?? etc.
*/
/*

    (*?) find the number of unique paths that can exist from a given node; find, count and enumerate the "branching points"; get the lengths of those paths;
        include as unique paths the root->branching point paths as well (?); ?? etc.
*/

namespace _v1 {
struct AdjacencyMatrix {
    uint32_t number_of_nodes {0};
    uint8_t ** table {nullptr};

    AdjacencyMatrix() {}
    AdjacencyMatrix(uint32_t number_of_nodes) : number_of_nodes(number_of_nodes) {
        table = new uint8_t* [number_of_nodes];

        for(uint32_t idx{0}; idx < number_of_nodes; idx++) { // (!?) idx < limit vs idx != limit -> uint type and new [due to the 0-count, by default there is a difference of 1 between the two, so a reserved value exists and idx , size is safe (!?)]
            table[idx] = new uint8_t[number_of_nodes];

            for(uint32_t idx_sec{0}; idx_sec < number_of_nodes; idx_sec++) {
                table[idx][idx_sec] = 0;    // at this point, uint32_t() by default is 0, but a proper abstraction / definition of the "type default state" is lacking, and what operations do in relation to this default state (?!); such a perspective is lacking
            }
        }
    }
    AdjacencyMatrix(AdjacencyMatrix const & matrix) : number_of_nodes(matrix.number_of_nodes) {
        table = new uint8_t* [number_of_nodes];

        for(uint32_t idx{0}; idx < number_of_nodes; idx++) { // (!?) idx < limit vs idx != limit -> uint type and new [due to the 0-count, by default there is a difference of 1 between the two, so a reserved value exists and idx , size is safe (!?)]
            table[idx] = new uint8_t[number_of_nodes];

            for(uint32_t idx_sec{0}; idx_sec < number_of_nodes; idx_sec++) {
                table[idx][idx_sec] = matrix.table[idx][idx_sec];    // at this point, uint32_t() by default is 0, but a proper abstraction / definition of the "type default state" is lacking, and what operations do in relation to this default state (?!); such a perspective is lacking
            }
        }
    }

    uint8_t* operator[](uint32_t index) {
        return table[index % this->number_of_nodes];
    }

    void ResetTable() {
        for(uint32_t idx{0}; idx < number_of_nodes; idx++) { // (!?) idx < limit vs idx != limit -> uint type and new [due to the 0-count, by default there is a difference of 1 between the two, so a reserved value exists and idx , size is safe (!?)]
            for(uint32_t idx_sec{0}; idx_sec < number_of_nodes; idx_sec++) {
                table[idx][idx_sec] = 0;    // at this point, uint32_t() by default is 0, but a proper abstraction / definition of the "type default state" is lacking, and what operations do in relation to this default state (?!); such a perspective is lacking
            }
        }
    }

    void LoadTableUndirectedGraph(std::pair<uint32_t, uint32_t>* edges, uint32_t number_of_edges) {
        ResetTable();

        for(uint32_t idx{0}; idx < number_of_edges; idx++) {
            table[edges[idx].first % this->number_of_nodes][edges[idx].second % this->number_of_nodes]
                = table[edges[idx].second % this->number_of_nodes][edges[idx].first % this->number_of_nodes]
                = uint8_t(1);
        }
    }

    void LoadTableDirectedGraph(std::pair<uint32_t, uint32_t>* edges, uint32_t number_of_edges) {
        for(uint32_t idx{0}; idx < number_of_edges; idx++) {
            table[edges[idx].first % this->number_of_nodes][edges[idx].second % this->number_of_nodes] = uint8_t(1);
        }
    }

    AdjacencyMatrix ComputeConnectivity() {
        return Power(this->number_of_nodes);    // (!?) overflow possibility; there is possibility that a (*) will produce a result that overflows into 0 (?!)
    }

    AdjacencyMatrix operator * (AdjacencyMatrix& matrix) {
        AdjacencyMatrix result = AdjacencyMatrix(*this);
        // ...

        return result;
    }

    uint32_t ConnectivityPathLength(uint32_t source_node, uint32_t target_node) {   // node_A -> node_B
        AdjacencyMatrix compute = AdjacencyMatrix(*this);

        for(uint32_t idx{0}; idx < this->number_of_nodes; idx++) {

        }
    }

    AdjacencyMatrix Power(uint32_t exponent) {
        AdjacencyMatrix result = AdjacencyMatrix(*this);
        // ...
        return result;
    }
};
};

namespace _v2 {
    #include <iostream>
#include <vector>
#include <string>
#include <queue>
using namespace std;

class vertex
{
	public:
		string title;

		vertex(string name)
		{
			title = name;
		}
};

class WeightedGraph
{
	private:
		static const int NULL_EDGE = 0;
		vector<vertex*> vertices;
		vector<bool> marks;			// marks[i] is mark for vertices[i]
		int nmbVertices;
		int maxVertices;
		vector< vector<int> > edges;

	public:
		// constructor
		WeightedGraph(int size)
		{
			nmbVertices = 0;
			maxVertices = size;

			vertices.resize(size);
			for (int i=0;i<size;i++)	// init vertices
				vertices[i] = NULL;

			marks.resize(size);

			int rows = size;
			int columns = size;
			edges.resize(rows, vector<int>(columns, 0));
		}

		bool is_empty()
		{
			if (nmbVertices == 0)
				return true;
			else
				return false;
		}

		bool is_full()
		{
			if (nmbVertices == maxVertices)
				return true;
			else
				return false;
		}

		void add_vertex(vertex* aVertex)
		{
			vertices[nmbVertices] = aVertex;
			for (int i=0; i<maxVertices; i++)
			{
				edges[nmbVertices][i] = NULL_EDGE;
				edges[i][nmbVertices] = NULL_EDGE;
			}
			nmbVertices++;
		}

		void add_edge(int fromVertex, int toVertex, int weight)
		{
			int row;
			int column;

			row = index_is(vertices[fromVertex]);
			column = index_is(vertices[toVertex]);
			edges[row][column] = weight;
		}

		int weight_is(int fromVertex, int toVertex)
			// If edge from fromVertex to toVertex exists, returns the weight of edge;
			// otherwise, returns a special “null-edge” value.
		{
			int row;
			int column;

			row = index_is(vertices[fromVertex]);
			column = index_is(vertices[toVertex]);
			return edges[row][column];
		}

		int index_is(vertex* aVertex)
		{
			int i = 0;
			while (i < nmbVertices)
			{
				if (vertices[i] == aVertex)
					return i;
				i++;
			}
			return -1;
		}

		//bool has_vertex(vertex* aVertex)
		//{

		//}

		void clear_marks()
		{
			for (int i=0;i<maxVertices;i++)
				marks[i] = false;
		}

		void mark_vertex(vertex* aVertex)
		{
			int ix = index_is(aVertex);
			marks[ix] = true;
		}

		bool is_marked(vertex* aVertex)
		// Returns true if vertex is marked; otherwise, returns false.
		{
			int index = index_is(aVertex);
			if (marks[index] == true)
				return true;
			else
				return false;
		}

		vertex* get_unmarked()
		{
			for (int i=0; i<nmbVertices; i++)
			{
				if (marks[i] == false)
					return vertices[i];
			}
			return NULL;
		}

		void DFS(vertex* aVertex)
		{
			int ix,ix2;
			if (aVertex == NULL) return;

			cout << aVertex->title << " ";
			ix = index_is(aVertex);
			marks[ix] = true;

			for (int i=0; i<nmbVertices; i++)
			{
				ix2 = index_is(vertices[i]);
				if (edges[ix][ix2] != NULL_EDGE)	// if adj vertex
				{
					if (marks[i] == false)
						DFS(vertices[i]);
				}
			}
		}

		void BFS(vertex* aVertex)
		{
			int ix, ix2;
			queue <vertex*> que;
			ix = index_is(aVertex);
			marks[ix] = true;
			que.push(aVertex);

			while (!que.empty())
			{
				vertex* node = que.front();
				que.pop();
				ix = index_is(node);
				cout << node->title << " ";
				for (int i=0; i<nmbVertices; i++)
				{
					ix2 = index_is(vertices[i]);
					if (edges[ix][ix2] != NULL_EDGE)	// if adj vertex
					{
						if (marks[i] == false)
						{
							marks[i] = true;
							que.push(vertices[i]);
						}
					}
				}
			}
		}


		~WeightedGraph()
		{
			for (int i=0;i<nmbVertices;i++)
			{
				delete vertices[i];
			}
		}
};

int main()
{
	WeightedGraph AdjMatrixGraph(10);
	vertex* root;
	vertex* pVertex;


	/* create the following graph in memory, position of the * represents the direction of edges
	   e.g  Edges are as following in the graph represented in the Adjacency Matrix A->B, A->C, B->D, D->C
			    (A)
			   /   \
			  *     *
			 (B)   (C)
			  \     *
			   *   /
			    (D)
	*/

	// Add vertices in memory
	root = new vertex("A");			// 0
	AdjMatrixGraph.add_vertex(root);
	pVertex = new vertex("B");		// 1
	AdjMatrixGraph.add_vertex(pVertex);
	pVertex = new vertex("C");		// 2
	AdjMatrixGraph.add_vertex(pVertex);
	pVertex = new vertex("D");		// 3
	AdjMatrixGraph.add_vertex(pVertex);

	// Add edges into memory
	AdjMatrixGraph.add_edge(0,1,1);
	AdjMatrixGraph.add_edge(0,2,1);
	AdjMatrixGraph.add_edge(1,3,1);
	AdjMatrixGraph.add_edge(3,2,1);

	// Print Depth first Search Graph Traversal
	AdjMatrixGraph.clear_marks();
	AdjMatrixGraph.DFS(root);

	cout << endl;

	// Print BFS Graph Traversal
	AdjMatrixGraph.clear_marks();
	AdjMatrixGraph.BFS(root);

	return 0;
}
};

namespace _v3 {
class Graph {
 public:
  Graph(std::vector<std::vector<int>> &adjacency) : adjacency_(adjacency) {}
  bool IsEulerWalkable();
  void PrintGraph();
  std::vector<std::vector<int>> adjacency_;
};

int main() {
  std::vector<std::vector<int>> adjacency = {{0, 1, 1, 0, 0},
                                             {1, 0, 1, 1, 1},
                                             {1, 1, 0, 1, 0},
                                             {0, 1, 1, 0, 1},
                                             {0, 1, 0, 1, 0}};
  Graph g(adjacency);
  std::cout << "g.isEulerWalkable(): " << g.IsEulerWalkable() << std::endl;
  return 0;
}
bool Graph::IsEulerWalkable() {
  // Create a table to hold degree of each vertex
  std::vector<int> degrees(v_.size());

  // Iterate vertices
  for (auto v : v_) {
    degrees[v.vertex_number] = v.adjacents.size();
  }

  // Iterate through degree table and count the number of odd ones

  int countOdds = 0;

  for (auto d : degrees) {
    if (d % 2 == 1) {
      countOdds++;
    }
  }
  return (countOdds == 0 || countOdds == 2);
}
struct Vertex {
  Vertex(int v, std::set<int> a) : vertex_number(v), adjacents(a) {}
  int vertex_number;
  std::set<int> adjacents;
};

class Graph {
 public:
  Graph(std::vector<Vertex> v) : v_(v) {}
  bool IsEulerWalkable();
  std::vector<Vertex> v_;
};

int main() {
  Graph g({Vertex(0, {1, 2, 3}), Vertex(1, {0, 2, 3}), Vertex(2, {0, 1, 3}),
           Vertex(3, {0, 1, 2})});
  std::cout << g.IsEulerWalkable() << std::endl;
}
bool Graph::IsEulerWalkable() {
  // Create a table to hold degree of each vertex
  std::vector<int> degrees(v_.size());

  // Iterate all edges
  for (auto e : e_) {
    degrees[e.first]++;
    degrees[e.second]++;
  }
  int countOdds = 0;

  // Iterate through degree table and count the number of odd ones
  for (auto d : degrees) {
    if (d % 2 == 1) {
      countOdds++;
    }
  }
  return (countOdds == 0 || countOdds == 2);
}
class Graph {
 public:
  Graph(std::vector<int> &v, std::vector<std::pair<int, int>> &e)
      : v_(v), e_(e) {}
  bool IsEulerWalkable();
  void PrintGraph();
  std::vector<int> v_;
  std::vector<std::pair<int, int>> e_;
};

int main() {
  std::vector<int> v = {0, 1, 2, 3};
  std::vector<std::pair<int, int>> e = {{1, 3}, {1, 3}, {3, 0}, {3, 0},
                                        {0, 2}, {2, 1}, {2, 3}};
  Graph g(v, e);
  std::cout << g.IsEulerWalkable() << std::endl;
}
class Graph {
 public:
  Graph(std::vector<int> &v, std::vector<std::pair<int, int>> &e)
      : v_(v), e_(e) {}
  bool IsEulerWalkable();
  void PrintGraph();
  std::vector<int> v_;
  std::vector<std::pair<int, int>> e_;
};
bool Graph::IsEulerWalkable() {
  // Create a table to hold degree of each vertex
  std::vector<int> degrees(adjacency_.size());

  // Iterate all edges
  for (int i = 0; i < adjacency_.size(); i++) {
    for (int j = 0; j < adjacency_.size(); j++) {
      if (adjacency_[i][j] == 1) {
        degrees[i]++;
      }
    }
  }

  int countOdds = 0;

  // Iterate through degree table and count the number of odd ones
  for (auto d : degrees) {
    if (d % 2 == 1) {
      countOdds++;
    }
  }
  return (countOdds == 0 || countOdds == 2);
}
// Shortest path using topological sort
vector<long> shortestPathTopo(vector<vector<int>> &graph, int source) {
    vector<long> d(graph.size(), INT_MAX);
    d[source] = 0;
    vector<int> sorted = topologicalSortDFS(graph);
    for (auto n : sorted) {
        for (int j = 0; j < graph.size(); j++) {
            // Relax outgoing edges of n
            if (graph[n][j] != INT_MAX) {
                d[j] = min(d[j], d[n] + graph[n][j]);
            }
        }
    }
    return d;
}
// Topological Sort Using DFS
vector<int> topologicalSortDFS(vector<vector<int>> &graph) {
    vector<int> result;

    // map of node to 0: not visited, 1: being visited, 2: visited
    unordered_map<int, int> visited;
    set<int> unvisited;

    for (int i = 0; i < graph.size(); i++) {
        unvisited.insert(i);
    }
    // While there is unvisited nodes
    while (!unvisited.empty()) {
        DFS(graph, visited, unvisited, result, *(unvisited.begin()));
    }

    std::reverse(result.begin(), result.end());
    return result;
}
//-----------------------------------------------------
// Recursively visits nodes
// If all children of a node is visited, adds it to sorted
// Marks nodes 0: not visited, 1: being visited, 2: visited
void DFS(vector<vector<int>> &graph, unordered_map<int, int> &visited,
         set<int> &unvisited, vector<int> &sorted, int n) {
    if (visited[n] == 1) {
        cout << "Detected cycle!" << endl;
        return;
    }

    if (visited[n] == 2) {
        return;
    }

    visited[n] = 1;

    for (int j = 0; j < graph.size(); j++) {
        if (j != n && graph[n][j] != INT_MAX) {
            DFS(graph, visited, unvisited, sorted, j);
        }
    }
    unvisited.erase(n);
    visited[n] = 2;
    sorted.push_back(n);
}

// BellmanFord Algorithm
vector<long> bellmanFord(vector<vector<int>> &graph, int source) {
    vector<long> d(graph.size(), INT_MAX);
    d[source] = 0;

    for (int i = 0; i < graph.size() - 1; i++) {
        for (int u = 0; u < graph.size(); u++)
            for (int v = 0; v < graph.size(); v++)
                d[v] = std::min(d[v], d[u] + graph[u][v]);
    }
    return d;
}
// Dijkstra shortest distance
vector<long> dijkstraPriorityQueue(vector<vector<int>> &graph,
                                   int source) {

    // Queue of pairs of distance to node number
    priority_queue<pair<int, int>, vector<pair<int, int>>,
                   greater<pair<int, int>>>
            q;
    vector<long> d(graph.size(), INT_MAX);
    d[source] = 0;

    q.push(make_pair(0, source));

    while (!q.empty()) {
        // Find minimum
        int u = q.top().second;
        q.pop();

        // Relax distances
        // Rather than decreasing the values in the queue,
        // we just add the updated distance to the queue again.
        for (int j = 0; j < graph.size(); j++) {
            if (d[j] > d[u] + graph[u][j]) {
                d[j] = d[u] + graph[u][j];
                q.push(make_pair(d[j], j));
            }
        }
    }
    return d;
}
// Floyd-Warshall Algorithm for finding the shortest distance

vector<vector<long long>> floydWarshal(vector<vector<int>> &graph) {
    vector<vector<long long>> d(graph.size(),
                                vector<long long>(graph.size()));

    //Initialize d
    for (int i = 0; i < graph.size(); ++i) {
        for (int j = 0; j < graph.size(); ++j) {
            d[i][j] = graph[i][j];
        }
    }

   for (int k = 0; k < graph.size(); k++)
    for (int i = 0; i < graph.size(); ++i)
      for (int j = 0; j < graph.size(); ++j)
        d[i][j] = std::min(d[i][j], d[i][k] + d[k][j]);

    return d;
}

{
    unsigned int c = std::thread::hardware_concurrency();
    std::cout << " number of cores: " << c << endl;;
}

std::mutex g_display_mutex;
thread_function()
{
    std::lock_guard<std::mutex> guard(g_display_mutex);
    std::thread::id this_id = std::this_thread::get_id();
    std::cout << "From thread " << this_id  << endl;
}

std::mutex g_display_mutex;
thread_function()
{

    g_display_mutex.lock();
    std::thread::id this_id = std::this_thread::get_id();
    std::cout << "My thread id is: " << this_id  << endl;
    g_display_mutex.unlock();
}

#include <future>
//Tasks, Future, and Promises
    {
        auto f1 = [](std::vector<int> &v,
            unsigned int left, unsigned int right) {
            unsigned long long acm = 0;
            for (unsigned int i = left; i < right; ++i)
            {
                acm += v[i];
            }

            return acm;
        };

        auto t1 = std::async(f1, std::ref(v),
            0, v.size() / 2);
        auto t2 = std::async(f1, std::ref(v),
            v.size() / 2, v.size());

        //You can do other things here!
        unsigned long long acm1 = t1.get();
        unsigned long long acm2 = t2.get();

        std::cout << "acm1: " << acm1 << endl;
        std::cout << "acm2: " << acm2 << endl;
        std::cout << "acm1 + acm2: " << acm1 + acm2 << endl;
    }

{
        unsigned long long acm1 = 0;
        unsigned long long acm2 = 0;
        std::thread t1([&acm1, &v] {
            for (unsigned int i = 0; i < v.size() / 2; ++i)
            {
                acm1 += v[i];
            }
        });
        std::thread t2([&acm2, &v] {
            for (unsigned int i = v.size() / 2; i < v.size(); ++i)
            {
                acm2 += v[i];
            }
        });
        t1.join();
        t2.join();

        std::cout << "acm1: " << acm1 << endl;
        std::cout << "acm2: " << acm2 << endl;
        std::cout << "acm1 + acm2: " << acm1 + acm2 << endl;
    }

//Creating Thread using Functor
    {

        CAccumulatorFunctor3 accumulator1 = CAccumulatorFunctor3();
        CAccumulatorFunctor3 accumulator2 = CAccumulatorFunctor3();
        std::thread t1(std::ref(accumulator1),
            std::ref(v), 0, v.size() / 2);
        std::thread t2(std::ref(accumulator2),
            std::ref(v), v.size() / 2, v.size());
        t1.join();
        t2.join();

        std::cout << "acm1: " << accumulator1._acm << endl;
        std::cout << "acm2: " << accumulator2._acm << endl;
        std::cout << "accumulator1._acm + accumulator2._acm : " <<
            accumulator1._acm + accumulator2._acm << endl;
    }

class CAccumulatorFunctor3
{
  public:
    void operator()(const std::vector<int> &v,
                    unsigned int beginIndex, unsigned int endIndex)
    {
        _acm = 0;
        for (unsigned int i = beginIndex; i < endIndex; ++i)
        {
            _acm += v[i];
        }
    }
    unsigned long long _acm;
};

//Pointer to function
    {
        unsigned long long acm1 = 0;
        unsigned long long acm2 = 0;
        std::thread t1(accumulator_function2, std::ref(v),
                        std::ref(acm1), 0, v.size() / 2);
        std::thread t2(accumulator_function2, std::ref(v),
                        std::ref(acm2), v.size() / 2, v.size());
        t1.join();
        t2.join();

        std::cout << "acm1: " << acm1 << endl;
        std::cout << "acm2: " << acm2 << endl;
        std::cout << "acm1 + acm2: " << acm1 + acm2 << endl;
    }

void accumulator_function2(const std::vector<int> &v, unsigned long long &acm,
                            unsigned int beginIndex, unsigned int endIndex)
{
    acm = 0;
    for (unsigned int i = beginIndex; i < endIndex; ++i)
    {
        acm += v[i];
    }
}


};

namespace _v4 {
#include "AdjMatrix.h"
#include <iostream>

using namespace std;

int main(int argc, char ** argv)
{
	int numNodes;
	cout << "How many nodes are in the graph?: "; cin >> numNodes;

	AdjMatrix matrix(numNodes);
	matrix.inputEdges();
	matrix.runDFS();
	matrix.runPrims();
	matrix.runDijkstras();

	return 0;
}

using namespace std;

template<class E>

class Vertex
{
	private:
		E element;
		int index;

		bool wasVisited;
		//List of edges (if Edge class not used).
	public:
		Vertex(E data, int position);
		~Vertex();
};

template<class E>
Vertex<E>::Vertex(E data, int position)
{
	element = data;
	index = position;

	wasVisited = false;
}

template<class E>
Vertex<E>::~Vertex()
{
	//Delete vertex.
}


template<class E>
int GenStack<E>::getSize()
{
	return (top + 1);
}

template<class E>
bool GenStack<E>::isEmpty()
{
	return(top == -1); 			//Returns binary values of true/false for the equation.
}

template<class E>
int GenStack<E>::isFull()
{
	return(top == (max - 1));
}

template<class E>
void GenStack<E>::expand()		//Expands the size of *myArray by 10 whenever called.
{
	tempArray = new E[max];

	for(int i = top; i > -1; --i)	//Copies all values starting from top over to a temporary array.
	{
		tempArray[i] = myArray[i];
	}

	max += 10;						//Adds 10 more spaces to max size.
	myArray = new E[max];

	for(int i = top; i > -1; --i)	//Copies over all the elements back into bigger myArray.
	{
		myArray[i] = tempArray[i];
	}
}

class AdjMatrix
{
	private:
		int numNodes;	//Used to initialize the matrix and other collections.

	  //char* nodeLabels;	  Array used to keep track of node labels, should you want one.
		bool* wasVisited;	//Array used to mark visited nodes.

		int** matrix; 		//2D int array used as the matrix; ints will be 0/1 for unweighted edges.
		int** primsMatrix;
	public:
		AdjMatrix(int n);
		~AdjMatrix();

		void setEdge(int source, int dest);
		void inputEdges();
		void runDFS();
		void runPrims();
		void runDijkstras();

		void resetVisited();
};

#include "AdjMatrix.h"
#include "GenStack.h"
#include <iostream>

using namespace std;

AdjMatrix::AdjMatrix(int n)			//Constructor for the matrix class.
{
	numNodes = n;
	wasVisited = new bool[numNodes];		//Initialized visited array with number of nodes.
	for(int i = 0; i < numNodes; ++i)
	{
		wasVisited[i] = false;			//Defaults every node to unvisited.
	}

	matrix = new int*[numNodes];			//Initialized a new array of arrays to set up matrix.
	for(int i = 0; i < numNodes; ++i)
	{
		matrix[i] = new int[numNodes];
		for(int j = 0; j < numNodes; ++j)
		{
			matrix[i][j] = 0;			// Defaults every edge in the matrix to 0.
		}
	}

	primsMatrix = new int*[numNodes];
	for(int i = 0; i < numNodes; ++i)
	{
		primsMatrix[i] = new int[numNodes];
		for(int j = 0; j < numNodes; ++j)
		{
			primsMatrix[i][j] = 0;
		}
	}
}

AdjMatrix::~AdjMatrix() {}

void AdjMatrix::setEdge(int source, int dest)				//Setting unweighted edges.
{
	if(source > numNodes || source < 1 || dest > numNodes || dest < 1)	//Error checking to prevent ArrayIndexOutOfBounds.
	{
		cout << "This is not a valid edge." << endl;
	}
	else
	{
		matrix[source - 1][dest - 1] = 1;					//Sets the corresponding slot in the matrix to 1.
	}
}

void AdjMatrix::inputEdges()
{
	cout << "Enter edges (source index followed by destination index). Enter -1 for both to stop." << endl;

	bool done = false;
	while(!done)		//Keeps prompting for edges while done is false.
	{
		int source; int dest;

		cout << "Enter edge: ";
		cin >> source >> dest;

		if(source == -1 && dest == -1)		//Exit condition.
		{
			done = true;
			continue;
		}

		setEdge(source, dest);				//Calls setEdge() from above.
	}
}

void AdjMatrix::runDFS()
{
	int startNode;
	cout << "Choose a node (#) to start a depth first-search of your graph: ";
	cin >> startNode;

	GenStack<int> nodeStack(numNodes);		//Initializes a stack used for DFS algorithm.

	int discovered[numNodes];				//Keeps track of nodes in order of discovery.
	for(int i = 0; i < numNodes; ++i)
	{
		discovered[i] = 0;
	}

	int order = 0;							//Index for discovered nodes array.

	int current = startNode;

	bool done = false;
	while(!done)
	{
		if(wasVisited[current - 1] == false)
		{
			discovered[order] = current;
			order++;
		}

		wasVisited[current - 1] = true;		//Marks the current node as visited (will only change unvisited nodes).

		bool nextNode = false;
		for(int i = 0; i < numNodes; ++i)
		{
			if(matrix[current - 1][i] != 0)
			{
				if(wasVisited[i] == false)
				{
					nodeStack.push(current);		//Pushes the current node onto a stack.

					current = ++i;			//If there is an unvisited adjacent node, sets that to current
					nextNode = true;		//and indicates that the search has progressed.

					break;
				}
			}
		}

		if(!nextNode)						//If there are no unvisited edges, pops a node off the stack and
		{									//sets current node to it.
			if(nodeStack.isEmpty())	//Stops the search once there is nothing left in the stack.
			{
				done = true;
			}
			else
			{
				current = nodeStack.pop();
			}
		}
	}

	cout << "The order of discovered nodes using Depth First-Search is: " << endl;
	for(int i = 0; i <= order; ++i)
	{
		if(discovered[i] > 0 && discovered[i] <= numNodes)
		{
			cout << discovered[i] << " -> ";	//Prints out the order of discovered nodes.
		}
	}
	cout << endl;
}

void AdjMatrix::runPrims()
{
	resetVisited();
	int discovered[numNodes];
	for(int i = 0; i < numNodes; ++i)
	{
		discovered[i] = 0;
	}
	int order = 0;

	int startNode;
	cout << "Choose a node (#) to start a Prim's Algorithm analysis: ";
	cin >> startNode;

	bool done = false;
	int sourceNode;

	wasVisited[startNode - 1] = true;
	discovered[order] = startNode;
	order++;

	while(!done)
	{
		int cheapestNode = numNodes + 1;			//Initializes the cheapest Node to an unexisting node (guarantees all existing nodes will be lower index).
		int cheapestNodeWeight = 1000;				//Initializes the cheapest NodeWeight to 1000 (assuming all edges in the graph are <1000).

		for(int i = 0; i < numNodes; ++i)		//Searches through all discovered nodes for the cheapest adjacent node.
		{
			if(discovered[i] != 0)
			{
				for(int j = 0; j < numNodes; ++j)
				{
					if((matrix[discovered[i]-1][j] != 0) && (wasVisited[j] != true))
					{
						if(matrix[discovered[i]-1][j] < cheapestNodeWeight)
						{
							sourceNode = discovered[i] - 1;
							cheapestNodeWeight = matrix[discovered[i]-1][j];
							cheapestNode = j;
						}
					}
				}
			}
		}
		discovered[order] = cheapestNode + 1; order++;
		primsMatrix[sourceNode][cheapestNode] = cheapestNodeWeight;
		wasVisited[cheapestNode] = true;
		done = true;
		for(int i = 0; i < numNodes; ++i)
		{
			if(wasVisited[i] == false)
			{
				done = false;
				break;
			}
		}
	}

	cout << "The order of discovered nodes using Prim's Algorithm is: " << endl;
	for(int i = 0; i < numNodes; ++i)
	{
		if(discovered[i] != 0)
		{
			cout << discovered[i] << " -> ";
		}
	}
	cout << endl;

	cout << "The adjacency matrix for Prim's Algorithm subtree is: " << endl;
	for(int i = 0; i < numNodes; ++i)
	{
		for(int j = 0; j < numNodes; ++j)
		{
			cout << primsMatrix[i][j] << "   ";
		}
		cout << endl << endl;
	}
}

void AdjMatrix::runDijkstras()
{
	resetVisited();
	int discovered[numNodes];
	for(int i = 0; i < numNodes; ++i)
	{
		discovered[i] = 0;
	}
	int order = 0;

	int startNode;
	cout << "Choose a node (#) to start a Dijkstra's Algorithm analysis: ";
	cin >> startNode;

	int prevNode = startNode;
	int current = startNode;

	int distance = 0;

	bool done = false;

	while(!done)
	{
		if(wasVisited[current - 1] != true)
		{
			wasVisited[current - 1] = true;
			discovered[order] = current;
			order++;
		}

		bool adjacentNodes = false;					//Checks if there are any existing adjacent nodes.
		for(int i = 0; i < numNodes; ++i)
		{
			if(matrix[current - 1][i] != 0)
			{
				adjacentNodes = true;
				break;
			}
		}
		if(!adjacentNodes)
		{
			if(current = startNode)
			{
				done = true;
			}
			else
			{
				current = prevNode;
			}
			continue;
		}


		bool allNodesVisited = true;
		for(int i = 0; i < numNodes; ++i)
		{
			if(matrix[current - 1][i] != 0)
			{
				if(wasVisited[i] == false)
				{
					allNodesVisited = false;
				}
			}
		}
		if(allNodesVisited)
		{
			done = true;
			continue;
		}


		int cheapestNode = numNodes + 1;
		int cheapestNodeWeight = 1000;

		for(int i = 0; i < numNodes; ++i)
		{
			if((matrix[current - 1][i] != 0) && (wasVisited[i] == false) && (matrix[current - 1][i] < cheapestNodeWeight))
			{
				cheapestNode = i;
				cheapestNodeWeight = matrix[current - 1][i];
			}
		}

		prevNode = current;
		current = cheapestNode + 1;
		distance += cheapestNodeWeight;
	}

	cout << "The order of discovered nodes using Dijkstra's algorithm is: " << endl;
	for(int i = 0; i < numNodes; ++i)
	{
		if(discovered[i] != 0)
		{
			cout << discovered[i] << " -> ";
		}
	}
	cout << endl;
	cout << "The distance is: " << distance << endl;
}

void AdjMatrix::resetVisited()
{
	for(int i = 0; i < numNodes; ++i)
	{
		wasVisited[i] = false;			//Defaults every node to unvisited.
	}
}


};

namespace _v5 {
#include <iostream>
using namespace std;
struct vertix
{
    int v;
    int weight;
    vertix *next;
};
vertix *creatnode(int v, int w)
{
    vertix *temp;
    temp = new vertix;
    temp->v = v;
    temp->weight = w;//
    temp->next = NULL;
    return temp;
}
void insertnode(vertix **vt, int v, int w)
{
    vertix *temp = *vt;
    if (temp == NULL)
        *vt = creatnode(v, w);
    else
    {
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = creatnode(v, w);
    }
}
int main()
{
    cout << "Enter the number of vertices"
         << "\n";
    int n, u, v, w, t;
    cin >> n;
    vertix *vertices[n + 1];
    for (int i = 0; i < n + 1; i++)
        vertices[i] = NULL;
    cout << "Enter the number of connection"
         << "\n";
    cin >> t;
    cout << "Enter the edges->weight"
         << "\n";
    for (int i = 0; i < t; i++)
    {
        cin >> u >> v >> w;
        insertnode(&vertices[u], v, w);
        insertnode(&vertices[v], u, w);
    }
    cout << "Enter the runvertix"
         << "\n";
    int runvertix;
    cin >> runvertix;
    int weight[n + 1];
    int parent[n + 1];
    int minspantree[t][3];
    int r = 0;
    for (int i = 0; i < n + 1; i++)
    {
        weight[i] = 1000000;
        parent[i] = -1;
    }
    weight[runvertix] = 0;
    minspantree[r][0] = 0;
    minspantree[r][1] = runvertix;
    minspantree[r][2] = 0;
    weight[runvertix] = -1;
    r++;
    int minweightvertix;
    int minweight;
    int m = 1;
    while (m < n)
    {
        minweight = 1000000;
        vertix *temp;
        temp = vertices[runvertix];
        while (temp != NULL)
        {
            if (temp->weight < weight[temp->v])
            {
                weight[temp->v] = temp->weight;
                parent[temp->v] = runvertix;
            }
            temp = temp->next;
        }
        for (int i = 1; i < n + 1; i++)
        {
            if (minweight > weight[i] && weight[i] != -1)
            {
                minweight = weight[i];
                minweightvertix = i;
            }
        }
        minspantree[r][0] = parent[minweightvertix];
        minspantree[r][1] = minweightvertix;
        minspantree[r][2] = minweight;
        r++;
        weight[minweightvertix] = -1;
        runvertix = minweightvertix;
        m++;
    }
    cout << "minspanning tree edges:"
         << "\n";
    cout << "u----v"
         << "\n";
    for (int i = 1; i < r; i++)
    {
        cout << minspantree[i][0] << "----" << minspantree[i][1];
        cout << "\n";
    }
    return 0;
}

#include <iostream>
#include <queue>
using namespace std;

struct vertix
{
    int v;
    vertix *next;
};

vertix *creatvertix(int i)
{
    vertix *temp;
    temp = new vertix;
    temp->v = i;
    temp->next = NULL;
    return temp;
}


vertix *insertvertix(vertix *temp, int i)
{
    if (temp == NULL)
        return creatvertix(i);
    else
    {
        vertix *flag;
        flag = temp;
        while (flag->next != NULL)
            flag = flag->next;
        flag->next = creatvertix(i);
        return temp;
    }
}

////////////////////////////////////////////////////////////////////////////////////////
void BFSvisit(vertix *vertices[], int v, int predecessor[], int red[], int bfs[], int pathlength[], int n)
{
    for (int i = 0; i < n + 1; i++)
    {
        pathlength[i] = 0;
        predecessor[i] = 0;
        red[i] = 0; // initialization red[i]=0 means i vertix has not been visited yet
    }
    red[0] = 1;
    for (int i = 0; i < n; i++)
        bfs[i] = 0;
    int b = 0;
    queue<int> Q;
    Q.push(v);
    red[v] = 1;
    predecessor[v] = 0;
    while (Q.empty() != 1)
    {
        vertix *temp;
        temp = vertices[Q.front()];
        while (temp != NULL)
        {
            if (red[temp->v] == 0)
            {
                Q.push(temp->v);
                red[temp->v] = 1;
                predecessor[temp->v] = Q.front();
                pathlength[temp->v] = pathlength[Q.front()] + 1;
            }
            temp = temp->next;
        }
        bfs[b] = Q.front();
        b++;
        Q.pop();
    }
}

//////////////////////////////////////////////////////////////////////////
void NotconnBFS(vertix *vertices[], int runvertix, int red[], int n) // for not connected graph and non recursive BFS visit
{
    queue<int> Q;
    Q.push(runvertix);
    red[runvertix] = 1;
    for (int i = 1; i < n + 2; i++)
    {
        while (Q.empty() == 0)
        {

            vertix *temp;
            temp = vertices[Q.front()];
            while (temp != NULL)
            {
                if (red[temp->v] == 0)
                {
                    red[temp->v] = 1;
                    Q.push(temp->v);
                }
                temp = temp->next;
            }

            cout << Q.front() << " ";

            Q.pop();
        }
        if (i <= n)
        {
            if (red[i] == 0)
            {
                Q.push(i);
                red[i] = 1;
            }
        }
    }
}

//////////////////////////////////////////////////////////////
void DFSvisit(int runvertix, int red[], vertix *vertices[], int predecessor[], int heightvertix[])
{
    cout << runvertix << " ";
    red[runvertix] = 1;
    vertix *temp;
    temp = vertices[runvertix];
    if (temp != NULL)
    {
        while (temp != NULL)
        {
            if (red[temp->v] == 0)
            {
                predecessor[temp->v] = runvertix;
                heightvertix[temp->v] = heightvertix[runvertix] + 1;
                DFSvisit(temp->v, red, vertices, predecessor, heightvertix);
            }
            temp = temp->next;
        }
    }
}

///////////////////////////////for cycle////////////////////////
void DFScyclevisit(int runvertix, int red[], vertix *vertices[], vertix *Extraedges[], int predecessor[], int heightvertix[], int start[], int finish[], int *timme)
{
    *timme = *timme + 1;
    start[runvertix] = *timme;
    red[runvertix] = 1;
    vertix *temp;
    temp = vertices[runvertix];
    if (temp != NULL)
    {
        while (temp != NULL)
        {
            if (red[temp->v] == 0)
            {
                predecessor[temp->v] = runvertix;
                heightvertix[temp->v] = heightvertix[runvertix] + 1;
                DFScyclevisit(temp->v, red, vertices, Extraedges, predecessor, heightvertix, start, finish, timme);
            }
            else
            {
                Extraedges[runvertix] = insertvertix(Extraedges[runvertix], temp->v);
            }
            temp = temp->next;
        }
    }
    *timme = *timme + 1;
    finish[runvertix] = *timme;
}

/////////////////////////////////////////////for strongly connected component//////////////////
void DFSforstronglyconnected(int runvertix, int trred[], vertix *transposevertices[])
{
    trred[runvertix] = 1;
    vertix *temp = transposevertices[runvertix];
    if (temp != NULL)
    {
        while (temp != NULL)
        {
            if (trred[temp->v] == 0)
            {
                DFSforstronglyconnected(temp->v, trred, transposevertices);
            }
            temp = temp->next;
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////
int main()
{
    int n, t, u, v;
    cout << "Enter the number of vertices: ";
    cin >> n;

    vertix *vertices[n + 1];
    vertix *unvertices[n + 1];
    vertix *transposevertices[n + 1];
    vertix *Extraedges[n + 1];

    cout << "Enter the numbers of connections or the edges: ";
    cin >> t;
    cout << "Enter the " << t << " edges"
         << "\n";
    for (int i = 0; i < n + 1; i++)
    {
        vertices[i] = NULL;
        unvertices[i] = NULL;
        Extraedges[i] = NULL;
        transposevertices[i] = NULL;
    }
    for (int i = 0; i < t; i++)
    {
        cin >> u >> v;
        if (u != v)
        {
            unvertices[u] = insertvertix(unvertices[u], v); // for the undirected graph
            unvertices[v] = insertvertix(unvertices[v], u);
        }
        vertices[u] = insertvertix(vertices[u], v);                   // for the directed graph
        transposevertices[v] = insertvertix(transposevertices[v], u); //for the transpose graph
    }

    int red[n + 1] = {0}; // Node which are not visited yet; red[i]=0 means visited;
    int pathlength[n + 1];
    int predecessor[n + 1];
    int bfs[n];
    int heightvertix[n + 1] = {0};

    cout << "operation 1 : Run the BFS"
         << "\n"; //////for the the not connected graph also
    cout << "operation 2 : Run the DFS"
         << "\n"; //////for the the not connected graph also
    cout << "operation 3 : to compute shortest distance between two vertices u and v"
         << "\n";
    cout << "operation 4 : to compute the diameter of a tree"
         << "\n";
    cout << "operation 5 : To check whether the graph has cycle or not"
         << "\n";
    cout << "operation 6 : Compute total strongly connected component"
         << "\n";
    cout << "operation 0 : To exit"
         << "\n";

    ///////////////////////////////////////////////////////////////////////////////////////////////////
    int a;
    int q = 0;
    while (q <= 100)
    {
        q++;
        cout << "select the operation: ";
        cin >> a;

        ///////////////////////////////////////////////////////////////////////////////////////////////
        if (a == 1)
        {
            for (int i = 0; i < n + 1; i++)
                red[i] = 0;
            int runvertix;
            cout << "Enter the vertix from where you want to run the vertix: ";
            cin >> runvertix;
            NotconnBFS(vertices, runvertix, red, n);
            cout << "\n";
        }

        //////////////////////////////////////////////////////////////////////////////
        else if (a == 2)
        {
            int runvertix;
            cout << "Enter the vertix from where you want to run the DFS"
                 << ": ";
            cin >> runvertix;
            for (int i = 0; i < n + 1; i++)
            {
                red[i] = 0;
                heightvertix[i] = 0;
            }
            red[0] = 1;
            cout << "DFS traversal from the vertix " << runvertix << ": \n";
            DFSvisit(runvertix, red, vertices, predecessor, heightvertix);
            for (int i = 1; i < n + 1; i++) // for the not connected graph it will give the the two DFS tree starting
            {
                if (red[i] == 0)
                    DFSvisit(i, red, vertices, predecessor, heightvertix);
            }
            cout << "\n";
        }

        ////////////////////////////////////////////////////////////////////////////////////////////
        else if (a == 3)
        {
            cout << "Enter the two vertices"
                 << "\n";
            cin >> u >> v;
            int b = 0;
            BFSvisit(vertices, u, predecessor, red, bfs, pathlength, n);
            for (int i = 0; i < n; i++)
            { //cout<<pathlength[i]<<" ";
                if (bfs[i] == v)
                {
                    b++;
                    cout << "The shortest distance: " << pathlength[v] << "\n";
                    cout << "The shortest path:\n"
                         << v;
                    int x = v;
                    while (predecessor[x] != u)
                    {
                        cout << "->" << predecessor[x];
                        x = predecessor[x];
                    }
                    cout << "->" << predecessor[x] << "\n";
                    break;
                }
            }
            if (b == 0)
                cout << "NO: the path does not exist"
                     << "\n";
        }

        //////////////////////////////////////////////////////////////////
        else if (a == 4)
        {
            int max = 0;
            int U, V;
            for (int i = 1; i < n + 1; i++)
            {
                BFSvisit(unvertices, i, predecessor, red, bfs, pathlength, n);
                for (int j = 1; j < n + 1; j++)
                {
                    if (max < pathlength[j])
                    {
                        max = pathlength[j];
                        U = i;
                        V = j;
                    }
                }
            }
            cout << "The diameter of the tree: " << max << " between vertix " << U << " and vertix " << V << "\n";
        }

        /////////////////////////////////////////////////////////////////////////////////////////////////
        else if (a == 5)
        {
            int finish[n + 1];
            int start[n + 1];
            for (int i = 0; i < n + 1; i++)
            {
                predecessor[i] = 0;
                heightvertix[i] = 0;
                finish[i] = 0;
                start[i] = 0;
                red[i] = 0;
            }
            predecessor[0] = -1;
            heightvertix[0] = -1;
            finish[0] = -1;
            start[0] = -1;
            red[0] = -1;
            int runvertix = 1;
            start[runvertix] = 1;
            int timme = 0;
            int x = 0;
            DFScyclevisit(runvertix, red, vertices, Extraedges, predecessor, heightvertix, start, finish, &timme);
            for (int i = 1; i < n + 1; i++)
            {
                if (red[i] == 0)
                {
                    timme = 0;
                    DFScyclevisit(i, red, vertices, Extraedges, predecessor, heightvertix, start, finish, &timme);
                }
            }
            int s = 0;
            for (int i = 1; i < n + 1; i++)
            {
                vertix *temp = Extraedges[i];
                while (temp != NULL)
                {
                    if (start[temp->v] < start[i] && start[i] < finish[i] && finish[i] < finish[temp->v])
                    {
                        cout << "Yes cycle is present and backpath from decendent to ancestor is \n";
                        t = i;
                        s++;
                        cout << temp->v << " <- " << t << " <- ";
                        while (predecessor[t] != temp->v)
                        {
                            cout << predecessor[t] << " <- ";
                            t = predecessor[t];
                        }
                        cout << temp->v << "\n";
                    }
                    temp = temp->next;
                }
            }
            if (s == 0)
                cout << "There is no cycle in the graph!"
                     << "\n";
        }

        ///////////////////////////////////////////////////////////////////////////////////////////////////
        else if (a == 6)
        {

            int trred[n + 1];
            int strong = 0;
            for (int i = 1; i < n + 1; i++)
            {
                trred[i] = 0;
                red[i] = 0;
            }
            trred[0] = -1;
            red[0] = -1;
            DFSforstronglyconnected(1, red, vertices);
            strong++;
            DFSforstronglyconnected(1, trred, transposevertices);
            int i = 1;
            while (i < n + 1)
            {
                if (red[i] == 1 && trred[i] == 0 || red[i] == 0 && trred[i] == 1 || red[i] == 0 && trred[i] == 0)
                {
                    strong++;
                    for (int j = 1; j < n + 1; j++)
                    {
                        if (red[j] == 1 && trred[j] == 0 || red[j] == 0 && trred[j] == 1 || red[j] == 0 && trred[j] == 0)
                        {
                            red[j] = 0;
                            trred[j] = 0;
                        }
                    }
                    DFSforstronglyconnected(i, trred, transposevertices);
                    DFSforstronglyconnected(i, red, vertices);
                }
                i++;
            }
            if (strong == 1)
                cout << "The Graph is strongly connected\n";
            else
            {
                cout << "The Graph is not strongly connected and total strongly connected component: " << strong << "\n";
            }
        }

        /////////////////////////////////////////////////////////////////////////////////////////////
        else if (a == 0)
        {
            return 0;
        }
    }

    return 0;
}
};

namespace _v6 {
/*
	Adjacency List of a graph
	- Ajinkya Sonawane [AJ-CODE-7]
*/

#include<iostream>
#include<queue>
#define INFINITY 9999	//Defining INFINITY to 9999
using namespace std;

class node
{
		int data;	//data field for a node
		int distance;	//distance field from a particular node
		node *next;	//link to the next node in adjacency list
		friend class graph;	//Allow class graph to access private members of class node
		public:
			node(){ distance = INFINITY;}	//initializing distance to INFINITY
};

class graph
{
	private:
		int **mat;	//decalring double pointer for a 2D array
		int check;	//flag to check whether Direcred or Undirected
		int total,*v;	//array (v) for keeping track of visited nodes
		node **arr;	//Array of Pointer for Adjacency List
		queue<int> q;	//STL queue for BFS traversal
	public:
		graph();
		inline int get_flag() { return check; }	//Getter method for flag
		void accept();		//Method to accept elements and creating a adjacency matrix
		void create_list();	//Method to create the adjacency list
		void display();		//Method to display Adjacency list
		void bfs();		//Method to print BFS traversal of the graph
		~graph();
};

graph :: graph()
{
	int ch;
	cout<<"\n\t\t|| Adjacency List ||\n";
	cout<<"\n\n1.Directed Graph";
	cout<<"\n2.Undirected Graph";
	cout<<"\n>>";
	cin>>ch;
	switch(ch)
	{
		case 1:
			check = 1;
			break;
		case 2:
			check = 0;
			break;
		default:
			check = 2;
			cout<<"\n\t********Invalid Choice*********\n";
			return;
	}

	//Accepting total number of cities
	cout<<"\nEnter the total number of cities : ";
	cin>>total;

	mat = new int*[total+1];
	v = new int[total+1];	//dynamically allocating memory for visited array
	arr = new node*[total+1];

	//dynamically allocating memory for adjacency matrix
	for(int i=1;i<=total;++i)
		mat[i]= new int[total];


	for(int i=1;i<=total;i++)
	{
		v[i] = 0;
		arr[i] = new node;
		arr[i]->next = NULL;
		for(int j=1;j<=total;j++)
		{
			mat[i][j] = 0;	//Initializing all values of the adjacency matrix to 0
		}
	}

}

void graph :: accept()
{
	int a,b,dis;
	char ch;
	node *temp;
	//Displaying Names of cities as numeric values
	cout<<"\nNames of cities are : ";
	for(int i =1;i<=total;i++)
	{
		arr[i]->data = i;
		cout<<"\t"<<i;
	}
	cout<<endl;

	//Acceptin Connections between cities
	cout<<"\nEnter the connected cities as (1 2) : ";
	do
	{
	next:
		cout<<"\nEnter the cities : ";
		cin>>a>>b;
		if(a < 1 || b < 1 || a > total || b > total)
		{
			cout<<"\nInvalid City ,Enter again\n";
			goto next;
		}
		cout<<"\nEnter the distance in kms : ";
		cin>>dis;

		//Storing Distance in adjacency matrix
		mat[a][b] = dis;
		if(check == 0)
			mat[b][a] = dis;
		cout<<"\ny to add more .... n to exit : ";
		cin>>ch;
	}while(ch=='y');

	//Calling create_list method to create adjacency list
	create_list();
}

void graph :: create_list()
{
	node *cur,*temp;
	for(int i=1;i<=total;i++)
	{
		cur = arr[i];	//cur is node pointer to traverse the array of nodes
		for(int j=1;j<=total;j++)
		{
			if(mat[i][j] != 0)
			{
				temp = new node;	//temp is a node pointer to traverse each linked list
				temp->data = j;
				temp->distance = mat[i][j];
				cur->next = temp;
				temp->next = NULL;
				cur = temp;
			}
		}
	}
}

void graph :: bfs()
{
	//Method to display BFS traversal
	node* cur;
	for(int i=1;i<=total;i++)
	{
		cur = arr[i];
		while(cur != NULL)
		{
			if(!v[cur->data])
			{
				q.push(cur->data);	//pushing element in queue
				v[cur->data] = 1;	//setting visited node to 1
			}
			cur = cur->next;
		}
	}

	cout<<"\n|| BFS : ||\t";
	for(int i=0;i<total;i++)
	{
		int x = q.front();
		q.pop();
		cout<<x<<"\t";
	}
	cout<<endl;
}

void graph :: display()
{
	node *cur;

	//display adjacency matrix
	cout<<"\n\t\t|| The Adjacency Matrix ||\n\n";
	for(int i=1;i<=total;i++)
	{
		for(int j=1;j<=total;j++)
		{
			cout<<mat[i][j]<<"\t";
		}
		cout<<endl;
	}

	//display adjacency list
	cout<<"\n\t\t|| Adjacency List ||\n";
	cout<<"\n\t\tCity , Distance in kms \n";
	for(int i=1;i<=total;i++)
	{
		cur = arr[i];	//Traversing array of nodes to print the linked list
		cout<<"\nAdjacent cities of ";
		while(true)
		{
			cout<<cur->data;
			if(cur->distance == INFINITY)
			{
				if(cur->next != NULL)
					cout<<"-->";
			}
			else
			{
				if(cur->next != NULL)
					cout<<","<<cur->distance<<"kms-->";
				else
					cout<<","<<cur->distance<<"kms";
			}
			if(cur->next != NULL)
				cur = cur->next;
			else
				break;
		}
	}
	cout<<endl;
}

graph :: ~graph()
{
	delete arr;
	delete mat;
	delete v;
}
int main()
{
start:	//label to start if choice is not valid

	graph *g = new graph(); //allocating memory to object of class graph

	if(g->get_flag() == 2)
	{
		delete g;
		goto start;
	}
	//calling methods for performing the actions
	g->accept();
	g->display();
	g->bfs();

	cout<<"\n\t\t*********Exit*******\n";
}
};

namespace _v7 {
#include <iostream>
#include <cstdlib>
using namespace std;
#define MAX 20

class AdjacencyMatrix
{
    private:
        int n;
        int **adj;
        bool *visited;
    public:
        AdjacencyMatrix(int n)
        {
            this->n = n;
            visited = new bool [n];
            adj = new int* [n];
            for (int i = 0; i < n; i++)
            {
                adj[i] = new int [n];
                for(int j = 0; j < n; j++)
                {
                    adj[i][j] = 0;
                }
            }
        }

void add_edge(int origin, int destin)
        {
            if( origin > n || destin > n || origin < 0 || destin < 0)
            {
                cout<<"Invalid edge!\n";
            }
            else
            {
                adj[origin - 1][destin - 1] = 1;
            }
        }

void display()
        {
            int i,j;
            for(i = 0;i < n;i++)
            {
                for(j = 0; j < n; j++)
                    cout<<adj[i][j]<<"  ";
                cout<<endl;
            }
        }
};

int main()
{
    int nodes, max_edges, origin, destin;
    cout<<"Enter number of nodes: ";
    cin>>nodes;
    AdjacencyMatrix am(nodes);
    max_edges = nodes * (nodes - 1);
    for (int i = 0; i < max_edges; i++)
    {
        cout<<"Enter edge (-1 -1 to exit): ";
        cin>>origin>>destin;
        if((origin == -1) && (destin == -1))
            break;
        am.add_edge(origin, destin);
    }
    am.display();
    return 0;
}
};

namespace _v8 {
#pragma once

#include <vector>

class MSTCluster
{
	private:
	int _numVertices;
	std::vector<std::vector<int>> _adjMatrix;

	public:
		MSTCluster(int numVertices, std::vector<std::vector<int>> adjMatrix);
        int minKey(int key[], bool vertSet[]);
		std::vector<std::vector<int>> primMST();
        std::vector<std::vector<int>> KCluster(int clusters);

};
#include "MSTCluster.h"
#include <vector>
#include <iostream>
#include <bits/stdc++.h>

MSTCluster::MSTCluster(int numVertices, std::vector<std::vector<int>> adjMatrix)
{
	_numVertices = numVertices;
	_adjMatrix = adjMatrix;
}

// A function to find the vertex with
// minimum key value, from the set of vertices
// not yet included in MST
int MSTCluster::minKey(int key[], bool vertSet[])
{
	// Initialize min value
	int min = INT_MAX, min_index;

	for (int v = 0; v < _numVertices; v++)
		if (vertSet[v] == false && key[v] < min)
			min = key[v], min_index = v;

	return min_index;
}

// A function to find the MST from a weighted non-directional graph
// returns the adjacency matrix of the MST
// time complexity of O(n^2)
std::vector<std::vector<int>> MSTCluster::primMST()
{

	// 2D vector to store MST adjacency matrix
	std::vector<int> rowVec(_numVertices, 0);
	std::vector<std::vector<int>> mstAdjMatrix(_numVertices, rowVec);

	// Array to store constructed MST
	int parent[_numVertices];

	// Key values used to pick minimum weight edge in cut
	int key[_numVertices];

	// To represent set of vertices not yet included in MST
	bool vertSet[_numVertices];

	// Initialize all keys as max int (infinite)
	for (int i = 0; i < _numVertices; i++)
	{
		key[i] = INT_MAX, vertSet[i] = false;
	}

	// Always include first 1st vertex in MST.
	// Make key 0 so that this vertex is picked as first vertex.
	key[0] = 0;

	// set first node as root of MST
	parent[0] = -1;

	// The MST will have _numVertices vertices
	for (int count = 0; count < _numVertices - 1; count++)
	{
		// Pick the minimum key vertex from the
		// set of vertices not yet included in MST
		int u = minKey(key, vertSet);

		// Add the picked vertex to the vertex set
		vertSet[u] = true;

		// Update key value and parent index of
		// the adjacent vertices of the picked vertex.
		// Consider only those vertices which are not
		// yet included in MST

		for (int v = 0; v < _numVertices; v++)
		{

			// _adjMatrix[u][v] is non zero only for adjacent vertices of m
			// vertSet[v] is false for vertices not yet included in MST
			// Update the key only if _adjMatrix[u][v] is smaller than key[v]
			if (_adjMatrix[u][v] && vertSet[v] == false && _adjMatrix[u][v] < key[v])
			{
				parent[v] = u, key[v] = _adjMatrix[u][v];
			}
		}
	}

	// set values of the MST adjacency matrix
	for (int i = 1; i < _numVertices; i++)
	{
		mstAdjMatrix[parent[i]][i] = _adjMatrix[i][parent[i]];
		mstAdjMatrix[i][parent[i]] = _adjMatrix[i][parent[i]];
	}

	return mstAdjMatrix;
}

// A function to find the adjacency matrix representation of
// a graph with k-clusters derived from the MST of the graph
std::vector<std::vector<int>> MSTCluster::KCluster(int clusters)
{

	// calculate the MST adjacency matrix of the weighted graph
	std::vector<std::vector<int>> clusterMatrix = primMST();

	std::cout << "Edges removed and their weights:" << std::endl;

	// find edges with maximum weight
	for (int k = 0; k < clusters - 1; k++)
	{

		// set the current maximum edge weight to 0
		int maxWeight = 0;

		// set the current vertices adjacent to maximum weight edge to 0
		int maxX = 0;
		int maxY = 0;

		for (int i = 1; i < _numVertices; i++)
		{
			for (int j = i + 1; j < _numVertices; j++)
			{

				// if the current edge weight is greater than the current max weight
				if (clusterMatrix[i][j] > maxWeight)
				{

					// set the maximum edge weight to the current edge weight
					maxWeight = clusterMatrix[i][j];

					// set the vertices adjacent to maximum weight edge
					maxX = i;
					maxY = j;
				}
			}
		}

		// remove the maximum weight edge from adjacency matrix
		clusterMatrix[maxX][maxY] = 0;
		clusterMatrix[maxY][maxX] = 0;

		std::cout << maxX << ":" << maxY << " (" << maxWeight << ")" << std::endl;
	}

	return clusterMatrix;
}
// MSTProj.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include "MSTCluster.h"

void printMatrix(int numVertices, std::vector<std::vector<int>> matrix) {
	for (int i = 0; i < numVertices; i++) {
		for (int j = 0; j < numVertices; j++) {
			std::cout << matrix[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

int main()
{
	// TODO add check for symmetry when creating mst class (b/c graphs are non-directional)

	int numVertices = 5;

	// must be symmetric
	std::vector<std::vector<int>> vec{
	 {0 ,0 ,9 ,11,2 },
	 {0 ,0 ,4 ,2 ,5 },
	 {9 ,4 ,0 ,0 ,6 },
	 {11,2 ,0 ,0 ,0 },
	 {2 ,5 ,6 ,0 ,0 },
	};

	MSTCluster newMST = MSTCluster(numVertices, vec);

	// determine adjacency matrix representation of a 2-cluster graph
	std::vector<std::vector<int>> kClusters = newMST.KCluster(2);

	printMatrix(numVertices, kClusters);
}

};

namespace _v9 {
#include <iostream>
#include <stack>
using namespace std;


// Abstraction of a graph

class Graph
{
private:
	int n;							// Number of vertices
	int** adj;						// Adjacency matrix
public:
	Graph(int size);				// Constructor
	~Graph();						// Destructor
	void addEdge(int x, int y); 	// Add an edge the the graph
	bool isConnected(int x, int y);	// Check if two vertices are connected
	void DFS(int start, int end);	// Depth first search
};


// Constructor

Graph::Graph(int size)
{
	if(size < 2)				// The graph must have at least 2 vertices
	{
		n = 2;
	}
	else
	{
		n = size;
	}

	adj = new int*[n];			// Allocate memory for adjacency matrix

	for(int i=0; i<n; ++i)
	{
		adj[i] = new int[n];	// Allocate memory for adjacency matrix
	}

	for(int i=0; i<n; ++i)
	{
		for(int j=0; j<n; ++j)
		{
			adj[i][j] = 0;		// Initialize the vertices to 0
		}
	}
}


// Destructor

Graph::~Graph()
{
	for(int i=0; i<n; ++i)
	{
		delete [] adj[i];
	}
	delete [] adj;
}


// Add an edge to the graph

void Graph::addEdge(int x, int y)
{
	adj[x-1][y-1] = adj[y-1][x-1] = 1;
}


// Check if two vertices are connected

bool Graph::isConnected(int x, int y)
{
	return (adj[x-1][y-1] == 1);
}


// Depth first search

void Graph::DFS(int start, int end)
{
	stack <int> s;									// Create a stack of ints
	bool* visited = new bool[n+1];					// Boolean array to represent which vertices we've visited

	for(int i=0; i<=n; ++i)							// Initialize all elements of visited to false
	{
		visited[i] = false;
	}

	s.push(start);									// Push the vertex onto the stack
	visited[start] = true;							// Mark this node as visited

	if(start == end)								// End the function if we're at our destination
	{
		return;
	}

	cout << "Depth-first search starting from point: " << start << endl;

	while(!s.empty())								// While the stack is not empty
	{
		int k = s.top();							// Save the top element before popping it off
		s.pop();

		if(k == end)								// Break out of the loop if we've reached our destination
		{
			break;
		}

		cout << k << " ";

		for(int i=n; i>=0; --i)						// For all adjacent vertices
		{
			if(isConnected(k, i) && !visited[i])	// If they're connected and we haven't visited it yet
			{
				s.push(i);							// Add it to our stack, and mark that we've visited it
				visited[i] = true;
			}
		}
	}
	cout << end << endl;
	delete [] visited;								// De-allocate the visited array
}


// Main function

int main()
{
	Graph g(8);
	g.addEdge(1, 2);
	g.addEdge(1, 3);
	g.addEdge(2, 4);
    g.addEdge(2, 5);
    g.addEdge(2, 6);
    g.addEdge(3, 7);
    g.addEdge(7, 8);
    g.DFS(1, 7);
    return 0;
}
};

namespace _v10 {
/* Homework 2: Implement Dijkstra's Algorithm
 * Author: Oleh Pomazan <oleh.pomazan@gmail.com>
 *
 * Description
 *
 * The graph ADT was implemented both using adjacency lists and matrix
 * in two classes inherited from AbstractGraph: AdjListGraph and MatrixGraph.
 * Neighbor helper class is used to store vertex and weight of the edge pointed into it.
 *
 * The Dijkstra algorithm is in ShortestPath class and it uses std::priority_queue
 * as min-heap. Priority queue stores the pair of minimal distance and vertex number,
 * also there's "previous" vector to store the path of visited nodes which is used to
 * obtain the shortest path.
 *
 * Random graphs are produced in the MonteCarloSimulation class, average path length is calculated
 * in random_graph method.
 *
 * Also there're two test functions to check the correctness of the implementation of Dijkstra algorithm
 * for both list and matrix based graphs.
*/

#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <queue>
#include <limits>
#include <utility>
#include <algorithm>
#include <iterator>
#include <cassert>
#include <random>

/* Store the end of the edge and weight of the edge */
template <typename weight_type>
struct Neighbor
{
    int vertex;
    weight_type weight;
    Neighbor(int v) : vertex(v) {}
    Neighbor(int v, weight_type w) : vertex(v), weight(w) {}
};

/* Abstract graph class provides general interface for derived list
 * and matrix based classes. Template's argument "vertex_type" is used
 * as node's value (number, string), "weight_type" is used as edge distance (double)
*/
template <typename vertex_type, typename weight_type>
class AbstractGraph
{
private:
    void operator=(const AbstractGraph&) = delete; // protect assignment
    AbstractGraph(const AbstractGraph&) = delete;  // protect copy constructor

public:
    AbstractGraph() {}
    virtual ~AbstractGraph() {}

    virtual int V() const =0; // returns the number of vertices in the graph
    virtual int E() const =0; // returns the number of edges in the graph

    virtual bool adjacent(int x, int y) const =0; // tests whether there is an edge from node "x" to node "y"
    virtual std::vector< Neighbor<weight_type> > neighbors(int x) const =0; // return list of all vertices which have edge with "x"

    virtual void addEdge(int x, int y) =0; // adds to graph the edge from x to y, if it is not there
    virtual void deleteEdge(int x, int y) =0; // removes the edge from x to y, if it is there

    virtual vertex_type get_node_value(int x) const =0; // returns the value associated with the node x
    virtual void set_node_value(int x, vertex_type value) =0; // sets the value associated with the node x to a

    virtual weight_type get_edge_value(int x, int y) =0; // returns the value associated to the edge (x,y)
    virtual void set_edge_value(int x, int y, weight_type v) =0; // sets the value associated to the edge (x,y) to v
};

/* Adjacency list-based implementation of graph ADT */
template <typename vertex_type, typename weight_type>
class AdjListGraph : public AbstractGraph<vertex_type, weight_type>
{
private:
    int numVertex, numEdge;
    // stores vector of lists of neighbors (using std::list would be less time consuming for insertion operations,
    // but it not so imporatant because we only insert edges at the end of vector and never in the middle and never delete edges in this task)
    std::vector< std::vector<Neighbor<weight_type> > > AdjacencyList;
    std::vector<vertex_type> vertices; // store nodes values

public:
    AdjListGraph() {}
    AdjListGraph(int numVert) : numVertex(numVert), numEdge(0)
    {
        vertices.reserve(numVertex);
        AdjacencyList.reserve(numVertex);

        for (int i = 0; i < numVertex; i++)
        {
            AdjacencyList.push_back(std::vector< Neighbor<weight_type> >());
            AdjacencyList[i].reserve(numVertex);
        }
    }
    ~AdjListGraph() { }

    int V() const { return numVertex; }
    int E() const { return numEdge; }

    bool adjacent(int x, int y) const
    {
        // return true if adjacency list for "x" node contains "y" node
        // lambda function checks every element of list for condition
        // std::find_if returns iterator which is equal to end() if "y" was not found
        return std::find_if(AdjacencyList[x].begin(), AdjacencyList[x].end(), [&y](Neighbor<weight_type> elem){
            return elem.vertex == y;
        }) != AdjacencyList[x].end();
    }

    std::vector<Neighbor<weight_type> > neighbors(int x) const
    {
        return AdjacencyList[x];
    }

    void addEdge(int x, int y)
    {
        assert(x >= 0 || y >= 0);
        addEdge(x,y,weight_type()); // cannot predict default value for "weight_type", use possible default constructor
                                    // it's assumed weight_type = double, it's just 0.0
    }

    // overloaded version with edge value for 3rd argument
    void addEdge(int x, int y, weight_type w)
    {
        assert(x >= 0 || y >= 0 || w >= 0);
        for (auto &it : AdjacencyList[x])
        {
            if (it.vertex == y)
            {
                it.weight = w;
                return;
            }
        }
        numEdge++;
        AdjacencyList[x].push_back(Neighbor<weight_type>(y,w));
    }

    void deleteEdge(int x, int y)
    {
        assert(x >= 0 || y >= 0);
        // look for the "y" vertex in the adj list
        auto nit = std::find_if(AdjacencyList[x].begin(), AdjacencyList[x].end(), [&y](Neighbor<weight_type> elem){
                return elem.vertex == y;
        });
        if (nit != AdjacencyList[x].end()) // if find - erase
        {
            numEdge--;
            AdjacencyList[x].erase(nit);
        }
    }

    vertex_type get_node_value(int x) const
    {
        assert(x >= 0);
        return vertices[x];
    }

    void set_node_value(int x, vertex_type value)
    {
        if (x >= 0) return;
        vertices[x] = value;
    }

    weight_type get_edge_value(int x, int y)
    {
        assert(x >= 0 || y >= 0);
        auto nit = std::find_if(AdjacencyList[x].begin(), AdjacencyList[x].end(), [&y](Neighbor<weight_type> elem){
                return elem.vertex == y;
        });
        if (nit != AdjacencyList[x].end())
            return nit->weight;
        return weight_type(); // return 0.0 if there's no edge
    }

    void set_edge_value(int x, int y, weight_type w)
    {
        assert(x >= 0 || y >= 0);
        auto nit = std::find_if(AdjacencyList[x].begin(), AdjacencyList[x].end(), [&y](Neighbor<weight_type> elem){
                return elem.vertex == y;
        });
        if (nit != AdjacencyList[x].end())
            nit->weight = w;
    }

    void print()
    {
        std::cout << "Adjacency list graph\n";
        std::cout << "Number of vertices: " << numVertex << std::endl;
        std::cout << "Number of edges: " << numEdge << std::endl;
        for (int i = 0; i < numVertex; i++)
        {
            std::cout << "V" << i << ": ";
            for (auto &elem : AdjacencyList[i])
                std::cout << "[" << elem.vertex << ", w" << elem.weight << "] ";
            std::cout << std::endl;
        }
    }
};

/* Matrix based graph class */
template <typename vertex_type, typename weight_type>
class MatrixGraph : public AbstractGraph<vertex_type, weight_type>
{
private:
    int numVertex, numEdge;
    std::vector< std::vector<weight_type> > matrix; // adjacency matrix
    std::vector<vertex_type> vertices; // store nodes values
public:
    MatrixGraph(int numVert) : numVertex(numVert), numEdge(0)
    {
        matrix.reserve(numVertex);
        for (int i = 0; i < numVertex; i++)
        {
            matrix.push_back(std::vector<weight_type>());
            matrix[i].reserve(numVertex);
            for (int j = 0; j < numVertex; j++)
            {
                matrix[i].push_back(0.0); // initialize by zero
            }
        }
    }
    ~MatrixGraph() {}

    int V() const { return numVertex; }
    int E() const { return numEdge; }

    bool adjacent(int x, int y) const
    {
        assert(x >= 0 || y >= 0);
        return matrix[x][y] != 0.0;
    }

    std::vector<Neighbor<weight_type> > neighbors(int x) const
    {
        assert(x >= 0);
        std::vector<Neighbor<weight_type> > nbrs;
        for (int i = 0; i < numVertex; i++)
            if (matrix[x][i] != 0)
                nbrs.push_back(Neighbor<weight_type>(i,matrix[x][i]));
        return nbrs;
    }

    void addEdge(int x, int y)
    {
        assert(x >= 0 || y >= 0);
        addEdge(x,y,weight_type());
    }

    void addEdge(int x, int y, weight_type w)
    {
        assert(x >= 0 || y >= 0);
        if (matrix[x][y] == 0.0)
            numEdge++;
        matrix[x][y] = w;
    }

    void deleteEdge(int x, int y)
    {
        assert(x >= 0 || y >= 0);
        if (matrix[x][y] != 0.0)
            numEdge--;
        matrix[x][y] = 0.0;
    }

    weight_type get_edge_value(int x, int y)
    {
        assert(x >= 0 || y >= 0);
        return matrix[x][y];
    }

    void set_edge_value(int x, int y, weight_type w)
    {
        assert(x >= 0 || y >= 0 || w >= 0);
        matrix[x][y] = w;
    }

    vertex_type get_node_value(int x) const
    {
        assert(x >= 0);
        return vertices[x];
    }

    void set_node_value(int x, vertex_type value)
    {
        assert(x >= 0);
        vertices[x] = value;
    }

    void print()
    {
        std::cout << "Matrix-based graph\n";
        std::cout << "Number of vertices: " << numVertex << std::endl;
        std::cout << "Number of edges: " << numEdge << std::endl;
        for (int i = 0; i < numVertex; i++)
        {
            std::cout << "V" << i << ": ";
            for (int j = 0; j < numVertex; j++)
            {
                if (matrix[i][j] != 0)
                    std::cout << "[" << j << ",w" << matrix[i][j] << "] ";
            }
            std::cout << std::endl;
        }
    }
};

/* Class containing implementation of Dijkstra algorithm */
template <typename vertex_type, typename weight_type>
class ShortestPath
{
    AbstractGraph<vertex_type, weight_type> *g;
    std::vector<weight_type> min_distance; // store distances from source veritice
    std::vector<int> previous; // store history of visiting, helps to restore the shortest path
    std::vector<int> _path; // store shortest path
public:
    ShortestPath(AbstractGraph<vertex_type, weight_type> *_g) : g(_g) {}

    // Dijkstra algorithm implementation similarly to http://rosettacode.org/wiki/Dijkstra%27s_algorithm#C.2B.2B
    std::vector< int > path(int source, int target)
    {
        int n = g->V(); // number of vertices
        min_distance.clear();
        min_distance.resize(n, std::numeric_limits<double>::infinity()); // set distances to infinity
        min_distance[source] = 0;

        previous.clear();
        previous.resize(n, -1); // store vertices to reproduce the shortest path
        _path.clear();

        std::priority_queue< std::pair<weight_type, int>,
                std::vector<std::pair<weight_type, int> >,
                std::greater<std::pair<weight_type, int> > > vertex_queue; // min-heap
        vertex_queue.push(std::make_pair(min_distance[source], source)); // put the start vertice to queue

        // iterate until queue is empty
        while (!vertex_queue.empty())
        {
            weight_type dist = vertex_queue.top().first; // distance
            int u = vertex_queue.top().second; // vertex
            vertex_queue.pop();

            if (dist < min_distance[u])
                continue;

            const std::vector<Neighbor<weight_type>> &neighbors = g->neighbors(u); // get all neighbors of "u"
            for (auto &neighbor : neighbors) // iterate over neighbors
            {
                int v = neighbor.vertex;
                weight_type weight = neighbor.weight;
                weight_type distance_through_u = dist + weight; // calcualate the cost
                if (distance_through_u < min_distance[v])
                {
                    min_distance[v] = distance_through_u;
                    previous[v] = u;
                    vertex_queue.push(std::make_pair(min_distance[v], v)); // push on top of heap the most "effective" vertex
                }
            }
        }
        // retrieve the path vertices
        int targetVertex = target;
        for (; target != -1; target = previous[target])
        {
            _path.push_back(target);
        }
        std::reverse(_path.begin(), _path.end()); // set correct order for path vertices
        if (_path.size() < 2)
            std::cout << "There's no path to " << targetVertex << ".\n";
        return _path;
    }

    // Calculate the cost as sum of distances between path vertices
    weight_type path_size(int source, int target)
    {
        path(source, target);
        weight_type sum = 0;

        for (int i = 0; i < _path.size() - 1; i++)
        {
            sum += g->get_edge_value(_path[i], _path[i+1]);
        }
        if (sum == 0) return -1;
        return sum;
    }
};

// Test for graph as used in http://rosettacode.org/wiki/Dijkstra%27s_algorithm#C.2B.2B
// Correct path is 0 2 5 4, cost is 20
void test1()
{
    AdjListGraph<int,double> g(6);
    // 0
    g.addEdge(0,1,7);
    g.addEdge(0,2,9);
    g.addEdge(0,5,14);
    // 1
    g.addEdge(1,0,7);
    g.addEdge(1,2,10);
    g.addEdge(1,3,15);
    // 2
    g.addEdge(2,0,9);
    g.addEdge(2,1,10);
    g.addEdge(2,3,11);
    g.addEdge(2,5,2);
    // 3
    g.addEdge(3,1,15);
    g.addEdge(3,2,11);
    g.addEdge(3,4,6);
    // 4
    g.addEdge(4,3,6);
    g.addEdge(4,5,9);
    // 5
    g.addEdge(5,0,14);
    g.addEdge(5,2,2);
    g.addEdge(5,4,9);

    g.print();

    ShortestPath<int, double> sp(&g);
    auto path = sp.path(0, 4);
    std::cout << "Path: ";
    std::copy(path.begin(), path.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
    std::cout << "Path cost: " << sp.path_size(0, 4) << std::endl;
}

void test2()
{
    MatrixGraph<int,double> g(6);
    // 0
    g.addEdge(0,1,7);
    g.addEdge(0,2,9);
    g.addEdge(0,5,14);
    // 1
    g.addEdge(1,0,7);
    g.addEdge(1,2,10);
    g.addEdge(1,3,15);
    // 2
    g.addEdge(2,0,9);
    g.addEdge(2,1,10);
    g.addEdge(2,3,11);
    g.addEdge(2,5,2);
    // 3
    g.addEdge(3,1,15);
    g.addEdge(3,2,11);
    g.addEdge(3,4,6);
    // 4
    g.addEdge(4,3,6);
    g.addEdge(4,5,9);
    // 5
    g.addEdge(5,0,14);
    g.addEdge(5,2,2);
    g.addEdge(5,4,9);

    g.print();

    ShortestPath<int, double> sp(&g);
    auto path = sp.path(0, 4);
    std::cout << "Path: ";
    std::copy(path.begin(), path.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
    std::cout << "Path cost: " << sp.path_size(0, 4) << std::endl;
}

/* Graph of given size and edge density is created using random numbers generator.
 * The average path length is calculated and printed out.
 */
class MonteCarloSimulation
{
public:
    void random_graph(int graph_size, double edge_dens, double min_dist, double max_dist)
    {
        AdjListGraph<int, double> g(graph_size);
        // http://en.cppreference.com/w/cpp/numeric/random/uniform_real_distribution
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> distance_distribution(min_dist, max_dist);
        std::uniform_real_distribution<> edge_distribution(0.0, 1.0);
        for (int i = 0; i < graph_size; ++i)
        {
            for (int j = 0; j < graph_size; j++)
            if (edge_distribution(gen) <= edge_dens)
            {
                if (!(g.adjacent(i,j) && g.adjacent(j,i)))
                {
                    double dist = distance_distribution(gen);
                    g.addEdge(i,j, dist); // set two directed edges as one undirected
                    g.addEdge(j,i, dist);
                }
            }
        }
        std::cout << "Number of edges: " << g.E()/2 << std::endl; // half of edges due to graph is undirected

        ShortestPath<int,double> sp(&g);
        double sum = 0;
        int count = 0;
        for (int i = 1; i < graph_size; i++)
        {
            int path_len = sp.path_size(0,i);
            if (path_len != -1)
            {
                sum += path_len;
                count++;
            }
        }
        std::cout << "Average path length: " << sum / count << std::endl;
    }
};

int main()
{
//    test1();
//    test2();

    MonteCarloSimulation ms;
    ms.random_graph(50, 0.2, 1.0, 10.0); // graph size, edge density, min distance, max distance
    ms.random_graph(50, 0.4, 1.0, 10.0);

    return 0;
}
};

namespace _v11 {
/*
A simple implementation of a Graph class.  It uses an adjacency matrix that is
built using std::vector<std::vector<int> >, so that it is unnecessary to know
ahead of time how many vertices will be added.  User may add as many as he
wants so long as memory holds out.

The Graph class is template based so that the class user may specify what
type of object a vertex should be.  My driver program instantiates using
'string's as vertices.

The class also encapsulates a std::map to map vertex names to indices, and
a std::vector to map indices to vertex names for crossreference purposes.

I implemented a fairly complete graph.  Just check the header to see what
member functions are available.  edge_exists() and delete_edge() are
implemented.  However, I permit the user to specify an integer edge weight,
so in addition to edge_exists(), I also implemented edge_weight() to get
the weight.

I implemented a get_adjacencies() function, and it returns a priority queue
of vertices that are adjacent to the specified vertex.  For each adjacency,
a weight is also returned.  I implemented a custom comparator in order that
the PQ always returns the lowest-weight element next, but it is possible for
the class user to specify his own comparator if a different criteria are
desirable.



The driver...

The driver starts off by offering some brief instructions.  Here's how to
get started:

At the prompt type 'av' and enter.  You will be prompted to add a vertex
name (a string).  Type 'av' again to enter another, and another.  Vertices
may be added at any time, and the matrix will just grow to accommodate them.

After adding a few vertices, you may type 'ae' at the prompt to add an edge.
You will then be prompted for the first vertex, and the second one, and
a weight.  If weight isn't interesting, just enter a 1.

At the main prompt you may always type 'hh' to get the list of options and
what they're for.  There are many options.  'ee' is for testing edge_exists().
'de' is for testing delete_edge().  There are others, so go ahead and explore.

I tried to cover every base with respect to recovering from user errors.  For
example, I throw exceptions if someone tries to add an edge for which no
vertex exists.  But I catch the exception and use it to display a warning
message before moving on.


Version: 0.02 -- Change log:
    -- Const correctness in Graph class
    -- Const iterators in display-only functions within driver program.
    -- General code cleanup (formatting, etc.)
    -- Now compiles under g++ and MSVS C++.
*/
// David Oswald
// CSIT 832
// Assignment 2: Graphs.


// Version 0.02: See graph.h for explanation.


#include <stdexcept>                // runtime_error()
#include <vector>                   // vector, vector<>::iterator
#include <map>                      // map, pair

#include <iostream>                 // cerr.

// Add vertices, one at a time.  Returns false if vertex already existed.
// Throws under the impossible condition of an attempt to add to same
// index twice.
// Also throws if is_full() returns true, or if any memory allocation fails.
template<class VertexT>
bool Graph<VertexT>::add_vertex( VertexT v )
{
    using std::map;
    using std::vector;
    using std::pair;
    using std::runtime_error;

    // is_full() *should* catch out of memory before we attempt to allocate,
    // but we will also trap std::bad_alloc's later on just in case.
    if( is_full() )
        throw( runtime_error(
            "add_vertex(): No room for more vertices."
        ) );  // This should be difficult but NOT impossible to reach.

    // Note: v_to_i.size() will return number of elements, which we can use
    // as the index number of the new element.

    // Add the vertex to our crossreference lookups.
    // First, the vertex to index crossref.
    pair<
        typename map<
            VertexT,
            std::vector<int>::size_type
        >::iterator,
        bool
    > v_to_i_ret;
    try
    {
        v_to_i_ret
            = v_to_i.insert( pair< VertexT, std::vector<int>::size_type >( v, v_to_i.size() ) );
    }
    catch( std::bad_alloc& ba )
    {
        std::cerr << "Bad Allocation caught adding to map: "
                  << ba.what() << std::endl;
        throw( runtime_error(
            "add_vertex(): Failed to allocate memory for new vertex."
        ) );
    }

    if( !v_to_i_ret.second )
        return false; // The vertex already existed.

    // Next, the index to vertex crossref.
    try
    {
        i_to_v.push_back( v );
    }
    catch( std::bad_alloc& ba )
    {
        std::cerr << "Bad Allocation caught adding to index: "
                  << ba.what() << std::endl;
        throw( runtime_error(
            "add_vertex(): Failed to allocate memory for new vertex."
        ) );
    }

    // Add a column to each existing row of the matrix for this new vertex.
    vector<vector<int> >::iterator it;
    for( it=matrix.begin(); it != matrix.end(); ++it )
    {
        try
        {
            it->push_back( NON_EDGE );
        }
        catch( std::bad_alloc& ba )
        {
            std::cerr << "Bad Allocation caught adding to matrix: "
                      << ba.what() << std::endl;
            throw( runtime_error(
                "add_vertex(): Failed to allocate memory for new vertex."
            ) );
        }
    }

    // Note: v_to_i.size() will now return the number of elements inclusive
    // of the new vertex, so we can use that as the number of columns for
    // our new row.

    // Add a new row to the matrix for this new vertex.
    vector<int> row( v_to_i.size(), NON_EDGE ); // Create a new row to insert
    matrix.push_back( row );

    return true;
}


// Passes by reference a vector containing all the vertex names.
// Returns a vertex count.
template<class VertexT>
int Graph<VertexT>::get_vertices( std::vector<VertexT>& vertices ) const
{
    using std::vector;
    int size = num_vertices();
    typename vector<VertexT>::const_iterator vit;
    for( vit = i_to_v.begin(); vit != i_to_v.end(); ++vit )
    {
        vertices.push_back( *vit );
    }
    return size;
}

// Returns a vertex count.
template<class VertexT>
int Graph<VertexT>::num_vertices() const
{
    using std::runtime_error;
    if( i_to_v.size() != v_to_i.size() || v_to_i.size() != matrix.size() )
        throw( runtime_error(
            "Graph components out of sync: Detected in num_vertices()"
        ) ); // Should be impossible.  Just a sanity check.
    return i_to_v.size();
}

// Removes all vertices.
// Clears the matrix.
template<class VertexT>
void Graph<VertexT>::make_empty()
{
    using std::runtime_error;
    v_to_i.clear();
    i_to_v.clear();
    matrix.clear();
    if( ! v_to_i.empty() || ! i_to_v.empty() || ! matrix.empty() )
        throw( runtime_error(
            "make_empty(): One or more components of Graph failed to clear"
        ) );  // Impossible, but never hurts to be careful.
    return;
}

// Returns true if the graph is empty.
template<class VertexT>
bool Graph<VertexT>::is_empty() const
{
    using std::runtime_error;
    if(
        i_to_v.empty() != v_to_i.empty()    ||
        v_to_i.empty() != matrix.empty()
    )
        throw( runtime_error(
            "Graph components out of sync: detected in is_empty()"
        ) );    // This should be impossible.  Just a sanity check.
    return matrix.empty(); // Returns true for empty, false otherwise.
}

// Check whether the Graph is full.  Because our graph is implemented with
// a vector matrix and maps, running out of room is synonymous with running
// out of heap space (memory).  We probably should just be handling that sort
// of situation via exceptions, since memory shortages are exceptional cases.
template<class VertexT>
bool Graph<VertexT>::is_full() const
{
    // First, check to see if we can fit another vertex in our maps.
    // Also check whether our matrix can hold another row.  We subtract one
    // from the max_size to accommodate an extra column per existing row.
    if(
        v_to_i.size() >= v_to_i.max_size()    ||
        i_to_v.size() >= i_to_v.max_size()    ||
        matrix.size() >= matrix.max_size() - 1
    )
        return true;
    else
        // We should be ok.  Return false, indicating there's room for
        // another vertex.
        return false;
}


// Get the index of a vertex v.  Return -1 if not found.
template<class VertexT>
int Graph<VertexT>::index_is( VertexT v ) const
{
    using std::map;
    typename map<
        VertexT,
        std::vector<int>::size_type
    >::const_iterator idx_it
        = v_to_i.find( v );
    if( idx_it == v_to_i.end() )
        return -1;  // Sentinal flag: Vertex doesn't exist!
    else
        return idx_it->second;
}

// Get the vertex for index i.  Throw if vertex not found.
template<class VertexT>
VertexT Graph<VertexT>::vertex_is( std::vector<int>::size_type i ) const
{
    using std::map;
    using std::runtime_error;
    if( i > i_to_v.size() - 1 )
        throw( runtime_error(
            "vertex_is() called on an out of range index: "
            "No vertex by that index."
        ) );
    else
        return i_to_v[i];
}


// Adds an edge.  Returns false under the condition that either vertex
// doesn't exist.  Will blindly modify an existing edge.
template<class VertexT>
bool Graph<VertexT>::add_edge( VertexT va, VertexT vb, int weight )
{
    int row = index_is( va );
    int col = index_is( vb );
    if( row < 0 || col < 0 )
        return false;
    else {
        matrix[row][col] = weight;
        // We implement non-directed as auto-two-way-direction.
        if( !directed ) matrix[col][row] = weight;
        return true;
    }
}


// Returns true if an edge exists.  False if edge doesn't exist, or
// also if one of the specified vertices doesn't exist.
template<class VertexT>
bool Graph<VertexT>::edge_exists( VertexT va, VertexT vb ) const
{
    int row = index_is( va );
    int col = index_is( vb );
    if( row >= 0 && col >= 0 && matrix[row][col] != NON_EDGE )
        return true;
    else
        return false;
}

// Deletes an edge by setting its position in matrix to zero.
// Fails silently if edge doesn't exist
// Throws if one or more of the vertices doesn't exist.
// While that should reflect a logic error, it's not necessarily
// a fatal issue.  Perhaps I could re-implement as a bool return.
template<class VertexT>
void Graph<VertexT>::delete_edge( VertexT va, VertexT vb )
{
    using std::runtime_error;
    int row = index_is( va );
    int col = index_is( vb );
    if( row < 0 || col < 0 )
        throw( runtime_error(
            "delete_edge(): Attempt to delete an edge with invalid vertex."
        ) );
    matrix[row][col] = NON_EDGE;
    // non-directed implemented as automatic direct-back (2-way direction).
    if( !directed ) matrix[col][row] = NON_EDGE;
    return;
}


// Returns the weight of an edge.  Throws if a vertex doesn't exist.
// If an edge doesn't exist, returns NON_EDGE, which is defined as 0.
template<class VertexT>
int Graph<VertexT>::get_weight( VertexT va, VertexT vb ) const
{
    using std::runtime_error;
    int row = index_is( va );
    int col = index_is( vb );
    if( row < 0 || col < 0 )
        throw( runtime_error(
            "get_weight(): Can't get a weight of edge with invalid vertex."
        ) );
    else
        return matrix[row][col];
}


// Scan all the columns for the Vertex's row in the matrix.
// Any non-zero column is an edge.
template<class VertexT>
void Graph<VertexT>::get_adjacent(
    VertexT v,
    std::priority_queue< std::pair<VertexT,int>,
                         std::vector< std::pair<VertexT,int> >,
                         PairComparator< VertexT > >& pq
) const
{
    using std::runtime_error;
    using std::pair;
    int r_ix = index_is( v );
    if( r_ix < 0 )
        throw( runtime_error(
            "get_adjacent(): Invalid vertix."
        ) );
    for( unsigned c_ix = 0; c_ix < matrix[r_ix].size(); c_ix++ )
        if( int weight = matrix[r_ix][c_ix] )
        {
            VertexT vb = vertex_is( c_ix );
            pq.push( pair<VertexT,int>( vb, weight ) );
        }
    return;
}
// Version: 0.02
// Version notes:
//    Changes from 0.01:
//        Const correctness in Graph class.
//        General code cleanup.


// graph.h.  Template class declarations for the Graph class.
// "#include"s the graph.cpp file at the end of this file.


#include <vector>                   // vector, vector<>::iterator
#include <map>                      // map, map<>::iterator, pair
#include <queue>                    // priority_queue


// Some constants that will be useful:
const bool DIRECTED     = true;
const bool DIGRAPH      = true;
const bool UNDIRECTED   = false;
const bool NONDIRECTED  = false;
const bool NOT_DIRECTED = false;
const bool NON_DIRECTED = false;

const int  NON_EDGE     = 0;


// A comparator class for priority queues.
template< typename VertexT >
struct PairComparator {
    bool operator()(
        const std::pair<VertexT,int>& p1,
        const std::pair<VertexT,int>& p2
    ) const
    {
        if( p1.second > p2.second )
            return true;
        else
            return false;
    }
};


// Implement something similar to the following typedef within the calling
// code for Graph to facilitate cleaner syntax in using
// Graph::get_adjacent().
// typedef std::priority_queue< std::pair< string, int >,
//                              std::vector< std::pair< string, int > >,
//                              PairComparator< string >
// > charPQ;



// Our cool Graph class. ;)
template< class VertexT=char >
class Graph {
  public:
    Graph( bool is_directed = true ) { directed = is_directed; return; }
    virtual ~Graph(){ return; }
    virtual bool add_vertex( VertexT V );
    virtual int  get_vertices( std::vector<VertexT>& vertices ) const;
    virtual int  num_vertices() const;
    virtual void make_empty();
    virtual bool is_empty()     const;
    virtual bool is_full ()     const;
    virtual bool add_edge   ( VertexT va, VertexT vb, int weight = 1 );
    virtual bool edge_exists( VertexT va, VertexT vb ) const; // Assignment 2.
    virtual void delete_edge( VertexT va, VertexT vb );       // Assignment 2.
    virtual int  get_weight ( VertexT va, VertexT vb ) const; // Even better.
    virtual void get_adjacent(
        VertexT v,
        std::priority_queue< std::pair<VertexT,int>,
                             std::vector< std::pair<VertexT,int>
        >,
        PairComparator< VertexT > >& pq
    ) const;
  private:
    virtual int     index_is ( VertexT  v ) const;
    virtual VertexT vertex_is( std::vector<int>::size_type i ) const;

    bool directed;
    std::vector< std::vector< int > >             matrix; // Adjacency matrix.
    std::map<VertexT,std::vector<int>::size_type> v_to_i; // Verts to idx's.
    std::vector< VertexT >                        i_to_v; // idx's to Verts.
};


#include "graph.cpp"
// Menu/Prompt-driven test driver for Graph class.
// The graph class is template based so that the user may decide what type
// of object should be used as vertices.  This driver uses a string vertex.
// Edges have an integer weight.  Weights of 1 can be used to emulate a
// non-weighted graph if that is preferred.

// The Graph class uses an adjacency matrix stored as a vector of vectors.
// It is not necessary to know beforehand how many vertices will be stored.
// The user may keep adding them as long as memory permits.  With each new
// vertex, a new row and column are added to the matrix, as well as a new
// index/map to crossreference vertex names with matrix positions.

// The Graph class also allows the user to specify (via the constructor)
// whether the class should instantiate as a directed graph (default) or
// an undirected graph.  This driver instantiates one of each for
// comparison purposes.

// User will be prompted for input.  The first thing to do would be to
// type 'av', and follow the prompts to add a vertex.  Repeat that a few
// times.  Then 'ae' to add an edge.  ...repeat that a few times too.
// 'de' to delete an edge, if you wish.  'ee' to check edge existance.

// Many other options are also available.  Have fun.
//     -- Dave


// Version 0.02: Code cleanup, and const correctness in Graph class.


#include "graph.h"

#include <string>
#include <iostream>
#include <vector>   // std::vector
#include <queue>    // std::priority_queue
#include <map>      // std::map, std::pair

using namespace std;


// This facilitates passing our own comparator function to the priority queue
// used by Graph::get_adjacent().
// While a typedef is never essential, it cleans up the syntax within the
// program's main logic.  See 'graph.h' for details.
typedef std::priority_queue<
            std::pair<string,int>,
            std::vector< std::pair<string,int> >,
            PairComparator< string >
> string_intPQ;



// Display helper functions.
void output_intro();
void status_summary( Graph<string>& dg, Graph<string>& ug );
void display_adjacencies( Graph<string>& graph, string va );
void display_vertices( Graph<string>& graph );
void list_commands();



// Menu items (all functions beginning with option_XX)
// Setters.
void option_av( Graph<string>& dg, Graph<string>& ug ); // Add Vertex.
void option_ae( Graph<string>& dg, Graph<string>& ug ); // Add Edge.
void option_de( Graph<string>& dg, Graph<string>& ug ); // Delete Edge.
void option_me( Graph<string>& dg, Graph<string>& ug ); // Make graphs Empty.

// Getters.
void option_gv( Graph<string>& dg, Graph<string>& ug ); // Get list of Verts.
void option_gn( Graph<string>& dg, Graph<string>& ug ); // Get Num. of Verts.
void option_ee( Graph<string>& dg, Graph<string>& ug ); // Edge Exists
void option_gw( Graph<string>& dg, Graph<string>& ug ); // Get edge Weight.
void option_ga( Graph<string>& dg, Graph<string>& ug ); // Get Adjacencies.
void option_em( Graph<string>& dg, Graph<string>& ug ); // Is EMpty?
void option_fl( Graph<string>& dg, Graph<string>& ug ); // Is FulL?
void option_st( Graph<string>& dg, Graph<string>& ug ); // STatus summaryl

// Miscellaneous.
// void option_qq() {} // Quit test application
// -- Implemented in-line, not as function.

void option_hh(); // Display this help.




// I don't think I like this "Enumeration hack", but it seemed
// ugly declaring fourteen constants.
enum command_option
{
// Value:0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13 ... Lucky day!
    av = 0, ae, de, me, gv, gn, ee, gw, ga, em, fl, st, qq, hh
};

int prompt( std::map<string,int>& options );

int main()
{
    // Set up some option keys.
    // Enumerates as:          0     1     2     3     4     5     6     7     8     9    10    11    12    13
    string option_keys[] = { "av", "ae", "de", "me", "gv", "gn", "ee", "gw", "ga", "em", "fl", "st", "qq", "hh" };
    std::map<string,int> option_map;
    for(  size_t ix = 0;  ix < 14;  ++ix  )
        option_map[ option_keys[ix] ] = ix;

    output_intro();
    list_commands();

    cout << "- Instantiating directed graph, 'digraph', "
         << "and undirected graph, 'udgraph'." << endl;

    Graph<string> digraph(DIRECTED);
    Graph<string> udgraph(UNDIRECTED);

    bool keep_going = true;

    while( keep_going )
    {
        int command = prompt( option_map );
        switch( command )
        {
        case qq:    // Quit.
            keep_going = false;
            cout << "\nThanks for playing.  Have a nice day!"
                 << endl;
                                            break;
        case hh:    // Help (display options).
            option_hh();                    break;
        case av:    // Add vertex.
            option_av( digraph, udgraph );  break;
        case ae:    // Add edge.
            option_ae( digraph, udgraph );  break;
        case de:    // Delete edge.
            option_de( digraph, udgraph );  break;
        case me:    // Make empty.
            option_me( digraph, udgraph );  break;
        case gv:    // Get Vertices (list)
            option_gv( digraph, udgraph );  break;
        case gn:    // Get Number of Vertices.
            option_gn( digraph, udgraph );  break;
        case ee:    // Edge exists?
            option_ee( digraph, udgraph );  break;
        case gw:    // Get (edge) Weight.
            option_gw( digraph, udgraph );  break;
        case ga:    // Get Adjacencies.
            option_ga( digraph, udgraph );  break;
        case em:    // Graph is EMpty?
            option_em( digraph, udgraph );  break;
        case fl:    // Graph is FulL?
            option_fl( digraph, udgraph );  break;
        case st:    // Status update.
            option_st( digraph, udgraph );  break;
        default:    // Should be unreachable.
            cout << "Unrecognized command.  This shouldn't happen!" << endl;
        }
    }
    return 0;
}


// Introduction to the driver program.
void output_intro()
{
    cout << "----------------------------------------------------------"
         << "---------------------"    << endl;
    cout << "|   graphtest: Explore the implementation of a Graph class by "
         << "David Oswald.   |"        << endl;
    cout << "----------------------------------------------------------"
         << "---------------------"    << endl  << endl;
    cout << "Two Graph objects will be instantiated: One directed, and "
         << "one undirected graph."    << endl;
    cout << "You will be given options to manipulate and inspect the Graphs."
         << endl  << endl;
    cout << "Actions will be applied to both Graphs.  "
         << "Output will be generated to "
         << endl;
    cout << "show how the action transformed each Graph." << endl << endl;
    cout << "The Graph objects expect 'string' vertices, and integer edges."
         << endl << endl;
    return;
}


// Invoked whenever a status summary is needed.
void status_summary( Graph<string>& dg, Graph<string>& ug )
{
    int dg_v_num = dg.num_vertices();
    int ug_v_num = ug.num_vertices();
    cout << "- Number of vertices: (digraph="
         << dg_v_num << "), (udgraph="
         << ug_v_num << ")." << endl;
    if( dg_v_num || ug_v_num )
    {
        cout << "\t(digraph vertices: ";
        display_vertices( dg );
        cout << ")" << endl;
        cout << "\t(udgraph vertices: ";
        display_vertices( ug );
        cout << ")" << endl;
    }
    return;
}


// display the list of commands that the user may invoke.
void list_commands()
{
    cout << "Options are:"                                                                   << endl
         << "   Setters:   av = add vertex.        ae = add edge.         de = delete edge." << endl
         << "              me = make graphs empty."                                          << endl
         << "   Accessors: gv = get vertex list.   gn = get vertex count. ee = edge exists?" << endl
         << "              gw = edge weight.       ga = list adjancies.   em = Graph empty?" << endl
         << "              fl = Graph full?        st = status summary."                     << endl
         << "   Misc:      qq = quit testing.      hh = display this help."                  << endl << endl;
    return;
}


// Simple prompt for user to select an option.
int prompt( std::map<string,int>& options )
{
    string option    = "";
    bool   do_prompt = true;

    while( do_prompt )
    {
        cout << "\nSelect an option (";
        for(
            std::map<string,int>::const_iterator mit = options.begin();
            mit != options.end();
            ++mit
        )
        {
            string op_name = mit->first;
            if( op_name == "qq" || op_name == "hh" )
                continue;
            cout << op_name << ",";
        }
        cout << " qq=quit, hh=help): ";
        getline(cin, option);
        if( !options.count( option ) )
        {
            cout << "\n" << option
                 << " is an invalid option.  Please choose again."
                 << endl;
            continue;
        }
        do_prompt = false;
    }
    return options.find( option )->second;
}


// Setters.

// Prompt for a vertex name, and add it to the graphs.
void option_av( Graph<string>& dg, Graph<string>& ug )
{
    cout << "Enter a unique vertex (implemented as a string): ";
    string vertex = "";
    cin >> vertex;
    cin.ignore();
    try
    {
        if( dg.add_vertex(vertex) )
            cout << vertex << " added to directed graph."     << endl;
        else
            cout << vertex
                 << " is already a member of directed graph." << endl;
    }
    catch( std::runtime_error& re )
    {
        cout << re.what()
             << ": Vertex not added to directed graph."       << endl;
        return;
    }
    try
    {
        if( ug.add_vertex(vertex) )
            cout << vertex << " added to undirected graph."   << endl;
        else
            cout << vertex
                 << " is already a member of directed graph." << endl;
    }
    catch( std::runtime_error& re )
    {
        cout << re.what()
             << ": Vertex not added to undirected graph."     << endl;
        return;
    }
    status_summary( dg, ug );
    return;
}


// Prompt for an edge (described by two vertices) and add it to the graph.
void option_ae( Graph<string>& dg, Graph<string>& ug )
{
    cout << "Add an edge by entering the first vertex name: ";
    string va, vb;
    int weight = 1;
    getline( cin, va );
    cout << "Now enter the second vertex name: ";
    getline( cin, vb );
    cout << "Enter a non-zero positive integral weight: ";
    cin  >> weight;
    if( weight < 1 )
    {
        cout << "Invalid weight.  No edge added." << endl;
        return;
    }
    bool dg_added = true;
    bool ug_added = true;
    if( dg.add_edge( va, vb, weight ) )
        cout << "Edge ("
             << va << "," << vb
             << ") added to directed graph with "
             << "weight of " << weight
             << "." << endl;
    else
    {
        cout << "Either vertex "
             << va << " or " << vb
             << " doesn't exist in the directed graph."
             << endl;
        dg_added = false;
    }
    if( ug.add_edge( va, vb, weight ) )
        cout << "Edge ("
             << va << "," << vb
             << ") added to undirected graph with weight of "
             << weight
             << "." << endl;
    else
    {
        cout << "Either vertex "
             << va << " or " << vb
             << " doesn't exist in the undirected graph."
             << endl;
        ug_added = false;
    }

    if( dg_added )
    {
        cout << "Directed graph adjacencies for " << va << ": ";
        display_adjacencies( dg, va );
    }

    if( ug_added )
    {
        cout << "Undirected graph adjacencies for " << va << ": ";
        display_adjacencies( ug, va );
    }
    cin.ignore();
    return;
} // Add edge.



// Prompt for an edge (described by two vertex names) and delete that edge.
void option_de( Graph<string>& dg, Graph<string>& ug )
{
    string va, vb;
    cout << "Delete an edge by entering the first vertex's name: ";
    getline( cin, va );
    cout << "Now enter the second vertex's name: ";
    getline( cin, vb );
    bool dg_success = true;
    bool ug_success = true;
    try
    {
        dg.delete_edge( va, vb );
    }
    catch( std::runtime_error& re )
    {
        cout << re.what() << "\nNothing deleted from directed graph.\n";
        dg_success = false;
    }
    try
    {
        ug.delete_edge( va, vb );
    }
    catch( std::runtime_error& re )
    {
        cout << re.what() << "\nNothing deleted from undirected graph.\n";
        ug_success = false;
    }
    if( dg_success )
    {
        cout << "Directed graph adjacencies for "
             << va << " are:" << endl;
        display_adjacencies( dg, va );
    }
    if( ug_success )
    {
        cout << "Undirected graph adjacencies for "
             << va << " are:" << endl;
        display_adjacencies( ug, va );
    }
    return;
} // Delete edge.



// Make the graphs empty.
void option_me( Graph<string>& dg, Graph<string>& ug ) {
    cout << "Clearing directed graph." << endl;
    try
    {
        dg.make_empty();
    }
    catch( std::runtime_error& re )
    {
        cout << re.what() << "\nFailed to clear directed graph."   << endl;
    }
    cout << "Clearing undirected graph." << endl;
    try
    {
        ug.make_empty();
    }
    catch( std::runtime_error& re )
    {
        cout << re.what() << "\nFailed to clear undirected graph." << endl;
    }
    return;
} // Make [graphs] empty.


// Getters.


// Display the names of vertices in each graph.
void option_gv( Graph<string>& dg, Graph<string>& ug ) {
    cout << "Directed graph vertices: "   << endl << "\t";
    display_vertices(dg);
    cout << endl;
    cout << "Undirected graph vertices: " << endl << "\t";
    display_vertices(ug);
    cout << endl;
    return;
}


// Display how many vertices each graph contains.
void option_gn( Graph<string>& dg, Graph<string>& ug )
{
    cout << "The directed graph contains "   << dg.num_vertices()
         << " vertices." << endl;
    cout << "The undirected graph contains " << ug.num_vertices()
         << " vertices." << endl;
    return;
}


// Prompt for an edge (described by two vertices) and display whether
// that edge exists.
void option_ee( Graph<string>& dg, Graph<string>& ug )
{
    string va, vb;
    cout << "Check if an edge exists by entering the first vertex: ";
    getline( cin, va );
    cout << "Now specify the second vertex: ";
    getline( cin, vb );
    cout << "Directed graph: edge ("
         << va << "," << vb
         << ") ";
    if( dg.edge_exists(va,vb) )
        cout << "exists."        << endl;
    else
        cout << "doesn't exist." << endl;
    cout << "Undirected graph: edge ("
         << va << "," << vb
         << ") ";
    if( ug.edge_exists(va,vb) )
        cout << "exists."        << endl;
    else
        cout << "doesn't exist." << endl;
    return;
}


// Prompt for an edge (pair of vertices) and display the
// weight for that edge.
void option_gw( Graph<string>& dg, Graph<string>& ug )
{
    string va, vb;
    cout << "Check an edge's weight by entering the first vertex: ";
    getline( cin, va );
    cout << "Now specify the second vertex: ";
    getline( cin, vb );
    cout << "Directed graph: edge ("
         << va << "," << vb
         << ") ";
    try
    {
        int weight = dg.get_weight(va,vb);
        cout << "has weight of " << weight << "." << endl;
    }
    catch( std::runtime_error& re )
    {
        cout << re.what() << endl
             << "One or more of the vertices doesn't exist in "
             << "directed graph."
             << endl;
    }
    cout << "Undirected graph: edge ("
         << va << "," << vb
         << ") ";
    try
    {
        int weight = ug.get_weight(va,vb);
        cout << "has weight of " << weight << "." << endl;
    }
    catch( std::runtime_error& re )
    {
        cout << re.what() << endl
             << "One or more of the vertices doesn't exist in "
             << "undirected graph."
             << endl;
    }
    return;
}


// Prompt for a vertex and display an adjacency list for it.
void option_ga( Graph<string>& dg, Graph<string>& ug ) {
    cout << "Enter vertex name to view adjacency list: ";
    string vertex;
    getline( cin, vertex );
    cout << "Directed graph adjacencies for "   << vertex << ": ";
    display_adjacencies( dg, vertex );
    cout << endl;
    cout << "Undirected graph adjacencies for " << vertex << ": ";
    display_adjacencies( ug, vertex );
    cout << endl;
    return;
} // Get adjacency list.


// Display whether or not the graphs are empty.
void option_em( Graph<string>& dg, Graph<string>& ug )
{
    cout << "Directed graph is ";
    if( dg.is_empty() )
        cout << "empty."     << endl;
    else
        cout << "not empty." << endl;
    cout << "Undirected graph is ";
    if( ug.is_empty() )
        cout << "empty."     << endl;
    else
        cout << "not empty." << endl;
    return;
}


// Display whether or not either graph is full.
// This should be difficult but not impossible to reach.
// I suspect there would be a lot of agony from swapfile
// churning before we ever saw this report full.
void option_fl( Graph<string>& dg, Graph<string>& ug )
{
    cout << "Directed graph is ";
    if( dg.is_full() )
        cout << "full."     << endl;
    else
        cout << "not full." << endl;
    cout << "Undirected graph is ";
    if( ug.is_full() )
        cout << "full."     << endl;
    else
        cout << "not full." << endl;
    return;
}


// Display a status summary.
void option_st( Graph<string>& dg, Graph<string>& ug ) {
    status_summary( dg, ug );
    return;
}


// Miscellaneous.

// void option_qq() {} -- Quit test application.
// -- Implemented inline, not as function.

void option_hh()
{
    list_commands();
    return;
} // Display this help.



// Displays a list of adjacencies for a given vertex.
// Adjacencies are wrapped in [] square brackets.
void display_adjacencies( Graph<string>& graph, string va )
{
    string_intPQ pq;
    try
    {
        graph.get_adjacent( va, pq );
        while( !pq.empty() )
        {
            pair<string,int> edge = pq.top();
            cout << " ["
                 << edge.first
                 << " => "
                 << edge.second
                 << "]";
            pq.pop();
        }
        cout << "." << endl;
    }
    catch( std::runtime_error& re )
    {
        cout << re.what();
    }
    return;
}


// Just displays a list of vertices with each element wrapped in [] brackets.
void display_vertices( Graph<string>& graph )
{
    std::vector<string> vertices;
    graph.get_vertices( vertices );
    for(
        std::vector<string>::const_iterator it = vertices.begin();
        it != vertices.end();
        ++it
    )
        cout << "[" << *it << "] ";
    return;
}
};

namespace _v12 {
networkx.convert_matrix.from_numpy_matrix

from_numpy_matrix(A, parallel_edges=False, create_using=None)[source]

    Returns a graph from numpy matrix.

    The numpy matrix is interpreted as an adjacency matrix for the graph.

    Parameters

        Anumpy matrix

            An adjacency matrix representation of a graph
        parallel_edgesBoolean

            If True, create_using is a multigraph, and A is an integer matrix, then entry (i, j) in the matrix is interpreted as the number of parallel edges joining vertices i and j in the graph. If False, then the entries in the adjacency matrix are interpreted as the weight of a single edge joining the vertices.
        create_usingNetworkX graph constructor, optional (default=nx.Graph)

            Graph type to create. If graph instance, then cleared before populated.

    See also

    to_numpy_recarray

    Notes

    For directed graphs, explicitly mention create_using=nx.DiGraph, and entry i,j of A corresponds to an edge from i to j.

    If create_using is networkx.MultiGraph or networkx.MultiDiGraph, parallel_edges is True, and the entries of A are of type int, then this function returns a multigraph (constructed from create_using) with parallel edges.

    If create_using indicates an undirected multigraph, then only the edges indicated by the upper triangle of the matrix A will be added to the graph.

    If the numpy matrix has a single data type for each matrix entry it will be converted to an appropriate Python data type.

    If the numpy matrix has a user-specified compound data type the names of the data fields will be used as attribute keys in the resulting NetworkX graph.

    Examples

    Simple integer weights on edges:
    >>>

import numpy as np

A = np.array([[1, 1], [2, 1]])

G = nx.from_numpy_matrix(A)

If create_using indicates a multigraph and the matrix has only integer entries and parallel_edges is False, then the entries will be treated as weights for edges joining the nodes (without creating parallel edges):
>>>

A = np.array([[1, 1], [1, 2]])

G = nx.from_numpy_matrix(A, create_using=nx.MultiGraph)

G[1][1]
AtlasView({0: {'weight': 2}})

If create_using indicates a multigraph and the matrix has only integer entries and parallel_edges is True, then the entries will be treated as the number of parallel edges joining those two vertices:
>>>

A = np.array([[1, 1], [1, 2]])

temp = nx.MultiGraph()

G = nx.from_numpy_matrix(A, parallel_edges=True, create_using=temp)

G[1][1]
AtlasView({0: {'weight': 1}, 1: {'weight': 1}})

User defined compound data type on edges:
>>>

dt = [("weight", float), ("cost", int)]

A = np.array([[(1.0, 2)]], dtype=dt)

G = nx.from_numpy_matrix(A)

list(G.edges())
[(0, 0)]

G[0][0]["cost"]
2

G[0][0]["weight"]
1.0
};

namespace _v13 {
Clustering with the Leiden Algorithm in R

This package allows calling the Leiden algorithm for clustering on an igraph object from R. See the Python and Java implementations for more details
This package requires the 'leidenalg' and 'igraph' modules for python (2) to be installed on your system. For example:

pip install leidenalg igraph

If you do not have root access, you can use pip install --user or pip install --prefix to install these in your user directory (which you have write permissions for) and ensure that this directory is in your PATH so that Python can find it.

The 'devtools' package will be used to install 'leiden' and the dependancies (igraph and reticulate). To install the development version:

if (!requireNamespace("devtools"))
    install.packages("devtools")
devtools::install_github("TomKellyGenetics/leiden")

The current release on CRAN can be installed with:

install.packages("leiden")

library("leiden")

Usage
Running the Leiden algorithm in R

First set up a compatible adjacency matrix:

adjacency_matrix <- rbind(cbind(matrix(round(rbinom(4000, 1, 0.8)), 20, 20),
                                matrix(round(rbinom(4000, 1, 0.3)), 20, 20),
                                matrix(round(rbinom(400, 1, 0.1)), 20, 20)),
                          cbind(matrix(round(rbinom(400, 1, 0.3)), 20, 20),
                                matrix(round(rbinom(400, 1, 0.8)), 20, 20),
                                matrix(round(rbinom(4000, 1, 0.2)), 20, 20)),
                          cbind(matrix(round(rbinom(400, 1, 0.3)), 20, 20),
                                matrix(round(rbinom(4000, 1, 0.1)), 20, 20),
                                matrix(round(rbinom(4000, 1, 0.9)), 20, 20)))
str(adjacency_matrix)
#>  num [1:60, 1:60] 1 1 1 1 0 1 0 1 1 1 ...
dim(adjacency_matrix )
#> [1] 60 60

An adjacency matrix is any binary matrix representing links between nodes (column and row names). It is a directed graph if the adjacency matrix is not symmetric.

library("igraph")
rownames(adjacency_matrix) <- 1:60
colnames(adjacency_matrix) <- 1:60
graph_object <- graph_from_adjacency_matrix(adjacency_matrix, mode = "directed")
graph_object
#> IGRAPH afd5b20 DN-- 60 1511 --
#> + attr: name (v/c)
#> + edges from afd5b20 (vertex names):
#>   [1] 1->1  1->3  1->4  1->5  1->6  1->8  1->9  1->10 1->11 1->13 1->14 1->15 1->16 1->17 1->18 1->19 1->20 1->28 1->29
#>  [20] 1->37 1->40 1->51 2->1  2->2  2->3  2->4  2->6  2->7  2->8  2->10 2->11 2->12 2->13 2->14 2->15 2->16 2->17 2->18
#>  [39] 2->19 2->20 2->31 2->34 2->35 2->36 2->37 2->53 3->1  3->2  3->3  3->5  3->6  3->7  3->8  3->9  3->10 3->11 3->13
#>  [58] 3->14 3->15 3->16 3->17 3->20 3->28 3->32 3->33 3->39 3->40 3->48 4->1  4->3  4->4  4->5  4->6  4->7  4->9  4->10
#>  [77] 4->11 4->12 4->14 4->15 4->18 4->19 4->24 4->35 4->38 4->39 5->3  5->4  5->5  5->6  5->8  5->9  5->11 5->13 5->14
#>  [96] 5->16 5->18 5->19 5->22 5->23 5->29 5->35 5->42 5->44 6->1  6->2  6->3  6->4  6->5  6->6  6->7  6->8  6->10 6->11
#> [115] 6->14 6->15 6->17 6->18 6->19 6->21 6->24 6->37 6->40 6->47 6->50 7->2  7->5  7->6  7->7  7->8  7->9  7->11 7->12
#> [134] 7->14 7->15 7->16 7->17 7->18 7->19 7->20 7->25 7->28 7->38 7->44 7->45 7->59 8->1  8->3  8->4  8->5  8->6  8->7
#> + ... omitted several edges

This represents the following graph structure.

plot(graph_object, vertex.color = "grey75")

This can be a shared nearest neighbours matrix derived from a graph object.

library("igraph")
adjacency_matrix <- igraph::as_adjacency_matrix(graph_object)

Then the Leiden algorithm can be run on the adjacency matrix.

partition <- leiden(adjacency_matrix)

table(partition)
#> partition
#>  1  2  3
#> 20 20 20

Here we can see partitions in the plotted results. The nodes that are more interconnected have been partitioned into separate clusters.

library("RColorBrewer")
node.cols <- brewer.pal(max(c(3, partition)),"Pastel1")[partition]
plot(graph_object, vertex.color = node.cols)
Running Leiden with arguments passed to leidenalg

Arguments can be passed to the leidenalg implementation in Python:

#run with defaults
  partition <- leiden(adjacency_matrix)


#run with ModularityVertexPartition"
  partition <- leiden(adjacency_matrix, partition_type = "ModularityVertexPartition")


#run with resolution parameter
  partition <- leiden(adjacency_matrix, resolution_parameter = 0.95)

In particular, the resolution parameter can fine-tune the number of clusters to be detected.

partition <- leiden(adjacency_matrix, resolution_parameter = 0.5)
node.cols <- brewer.pal(max(c(3, partition)),"Pastel1")[partition]
plot(graph_object, vertex.color = node.cols)

partition <- leiden(adjacency_matrix, resolution_parameter = 1.8)
node.cols <- brewer.pal(max(c(3, partition)),"Pastel1")[partition]
plot(graph_object, vertex.color = node.cols)

partition <- leiden(adjacency_matrix, max_comm_size = 12)
node.cols <- brewer.pal(max(c(10, partition)),"Pastel1")[partition]
plot(graph_object, vertex.color = node.cols)

Weights for edges an also be passed to the leiden algorithm either as a separate vector or weights or a weighted adjacency matrix.

#generate example weights
weights <- sample(1:10, sum(adjacency_matrix!=0), replace=TRUE)
partition <- leiden(adjacency_matrix, weights = weights)
table(partition)
#> partition
#>  1  2  3
#> 20 20 20

#generate example weighted matrix
adjacency_matrix[adjacency_matrix == 1] <- weights
partition <- leiden(adjacency_matrix)
table(partition)
#> partition
#>  1  2  3
#> 20 20 20

See the documentation on the leidenalg Python module for more information: https://leidenalg.readthedocs.io/en/latest/reference.html
Running on a Seurat Object
Seurat version 2

To use Leiden with the Seurat pipeline for a Seurat Object object that has an SNN computed (for example with Seurat::FindClusters with save.SNN = TRUE). This will compute the Leiden clusters and add them to the Seurat Object Class.

adjacency_matrix <- as.matrix(object@snn)
membership <- leiden(adjacency_matrix)
object@ident <- as.factor(membership)
names(object@ident) <- rownames(object@meta.data)
object@meta.data$ident <- as.factor(membership)

Note that this code is designed for Seurat version 2 releases.
Seurat version 3 or later

Note that the object for Seurat version 3 has changed. For example an SNN can be generated:

library("Seurat")
FindClusters(pbmc_small)
membership <- leiden(pbmc_small@graphs$RNA_snn)
table(membership)

For Seurat version 3 objects, the Leiden algorithm has been implemented in the Seurat version 3 package with Seurat::FindClusters and algorithm = "leiden"). See the documentation for these functions.

FindClusters(pbmc_small, algorithm = "leiden")
table(pbmc_small@active.ident)
};

namespace _v14 {
#include <iostream>
#include <conio.h>
#include <math.h>
using namespace std;

int menu() {
	int task;
	cout << "\n\n\t\t\t*****************************************************";
	cout << "\n\t\t\t*****************************************************";
	cout << "\n\t\t\t\t\t\tHi!";
	cout << "\n\t\t\t\t Welcom to the Graph Solution App!\n\t\t\t\t   press any key to continue...";
	cout << "\n\t\t\t*****************************************************";
	cout << "\n\t\t\t*****************************************************";
	_getch();



	system("cls");
	cout << "\n\n\t\t***************************************************************************";
	cout << "\n\t\t**  \t\t\tSelect What You Want To Do:\t\t\t **\n\t\t** <<The Program Will Automaticly Ask For The Matris In The Next Step!>> **\n";
	cout << "\t\t**-----------------------------------------------------------------------**\n";
	cout << "\t\t**   1.                                                                  **\n";
	cout << "\t\t**                                                                       **\n";
	cout << "\t\t**   2. Hamilton Tour                                                    **\n";
	cout << "\t\t**                                                                       **\n";
	cout << "\t\t**   3. Oyler Tour                                                       **\n";
	cout << "\t\t**                                                                       **\n";
	cout << "\t\t**   4. Kootah tarin masir beyne 2 raas                                  **\n";
	cout << "\t\t**                                                                       **\n";
	cout << "\t\t**   5. Ghotre Graph                                                     **\n";
	cout << "\t\t**                                                                       **\n";
	cout << "\t\t**   6. Hambandi                                                         **\n";
	cout << "\t\t**                                                                       **\n";
	cout << "\t\t**   7. Check if the Graph is a Tree!                                    **\n";
	cout << "\t\t**                                                                       **\n";
	cout << "\t\t**   8. Max and Min P(daraje rouse geraph)                               **\n";
	cout << "\t\t**                                                                       **\n";
	cout << "\t\t**   9. Kamel Boodane Graph                                              **\n";
	cout << "\t\t**                                                                       **\n";
	cout << "\t\t**   10.Andaze Graph                                                     **\n";
	cout << "\t\t**                                                                       **\n";
	cout << "\t\t**   11.EXIT                                                             **\n";
	cout << "\t\t**                                                                       **\n";
	cout << "\t\t***************************************************************************\n";
	cin >> task;
	if (task == 11) {
		system("cls");
		cout << "Thanks For Using Our App! :D\n press any key to exit...";
		cin.get();
		cin.get();
		exit(1);
	}
	return task;
}


void inputmatris(int, int**);
void outputmatris(int, int**);
void matris_2(int, int**, int**);
bool check(int, int**);

void task1() {

}

void task2(int p, int i, int j, int**matrischeck, int *A, int counter) {
	counter = 0;
	bool dol = true;
	i = 0;
	j = 0;
	A[0] = 0;
	int counter2 = 0;
	bool sol = true;

	while (counter < p - 1) {
		counter2++;
		if (counter2>p + p) { //for breaking the loop if Hamiltoni Tour/Path didnt exist
			sol = false;
			break;
		}
		j = 0;
		for (; j < p; j++) {
			dol = true;
			if (*(*(matrischeck + i) + j) == 1) {
				for (int g = 0; g <= counter; g++) {
					if (A[g] == j)
						dol = false;
				}
				if (dol) {
					i = j;
					counter++;
					A[counter] = j;
					for (int h = 0; h < p; h++) {
						*(*(matrischeck + h) + j) = 0;
					}
					break;
				}
			}
		}
	}
	if (*(*(matrischeck + i) + A[0]) == 1 && sol == true) {
		cout << "Hamiltoni Tour Exists!\n" << endl;
		counter++;
		A[counter] = A[0];
	}
	else if (sol == false) {
		cout << "Hamilton Path/Tour Dosent Exist!\n\n";
	}

	else
		cout << "Hamilton Path Exists!\n" << endl;


	for (int k = 0; k < counter + 1; k++) {
		cout << A[k] + 1 << " ";
	}


	cout << endl;
}
int task6(int p, int i, int j, int**matrischeck) {
	int counter = 0;
	i = 0;
	while (counter < p*p) {
		j = 0;
		for (; j < p; j++) {
			if (*(*(matrischeck + i) + j) == 1) {
				i = j;
				counter++;
				for (int h = 0; h < p; h++) {
					*(*(matrischeck + h) + j) = 0;
				}
			}
			else
				counter++;
		}
	}
	//outputmatris(p, matrischeck);

	int a = 0;
	for (int i = 0; i < p; i++) {
		for (int j = i + 1; j < p; j++) {
			if (*(*(matrischeck + i) + j) != 0) {
				a++;
				break;
			}
		}
	}
	if (a == 0) {
		cout << "\n\nHamband!!!\n";
		system("pause");
		return 5;
	}
	else if (a != 0) {
		cout << "\n\nNa hamband!!!\n";
		system("pause");
		system("cls");
		return 4;
	}
	else {
		cout << "error!!!";
	}

	return 0;
}
int task7(int p, int q, int **matrischeck) {
	int counter = 0;
	int c = 0;
	while (c <= p) {
		for (int i = 0; i < p; i++) {
			int a = 0;
			int po = 0;
			for (int j = 0; j < p; j++) {
				if (*(*(matrischeck + i) + j) == 1) {
					a++;
					po = j;
				}
			}
			if (a == 1) {
				*(*(matrischeck + i) + po) = 0;
				*(*(matrischeck + po) + i) = 0;
			}
		}
		c++;
	}
	for (int i = 0; i < p; i++) {
		for (int j = i + 1; j < p; j++) {
			if (*(*(matrischeck + i) + j) != 0) {
				cout << "Its Not a Tree!!!\n";
				return 0;
			}
		}
	}
	cout << "Its a Tree!!!\n";
	return 0;
}
void task8(int p, int **matris2) {
	int min, max;
	min = *(*(matris2 + 0) + 0);
	max = min;
	for (int i = 1; i < p; i++) {
		if (*(*(matris2 + i) + i) > max) {
			max = *(*(matris2 + i) + i);
		}
		if (*(*(matris2 + i) + i) < min) {
			min = *(*(matris2 + i) + i);
		}
	}
	cout << "\n\n\t|Max is:" << max;
	cout << "\n\t|Min is:" << min << "\n\n";
}
void task9(int p, int **matrischeck) {
	int a = 0;
	for (int i = 1; i < p; i++)
		for (int j = 1 + i; j < p; j++)
			if (*(*(matrischeck + i) + j) != 1)
				a++;
	if (a == 0) {
		cout << "Graph kamel ast!\n";
	}
	else {
		cout << "Graph kamel nist!\n";
	}
}
int task10(int p, int **matris2) {
	int sum = 0;
	for (int i = 0; i < p; i++) {
		sum += *(*(matris2 + i) + i);
	}
	int q = sum / 2;
	return q;
}
void matrischecktask(int p, int **matris, int **matrischeck) {
	for (int i = 0; i < p; i++) {
		for (int j = 0; j < p; j++) {
			*(*(matrischeck + i) + j) = *(*(matris + i) + j);
		}
	}
}




int main() {

	int task, q = 0;
	task = menu();
	system("cls");
	cout << "Graph chand raas darad?\n";
	int p;
	cin >> p;
	int *A = new int[p + 1];
	int **matris = new int *[p];
	for (int i = 0; i < p; i++) {
		matris[i] = new int[p];
	}
	int **matris2 = new int *[p];
	for (int i = 0; i < p; i++) {
		matris2[i] = new int[p];
	}
	for (int i = 0; i < p; i++) {
		for (int j = 0; j < p; j++) {
			*(*(matris2 + i) + j) = 0;
		}
	}




	inputmatris(p, matris);
	if (check(p, matris)) {
		cout << "This is wrong! \nDo you want to try again? (Y/N)";
		switch (_getch()) {
		case 'y':
			system("cls");
			main();
			break;
		case 'n':
			system("cls");
			cout << "Thanks For Using Our App! :D\n press any key to exit...";
			cin.get();
			cin.get();
			exit(1);
			break;
		}
	}




	int **matrischeck = new int *[p];
	for (int i = 0; i < p; i++) {
		matrischeck[i] = new int[p];
	}
	//int s, e, z;
	matrischecktask(p, matris, matrischeck);
	int x2 = 0;
	int counter = 0;
	int i1 = 0, j1 = 0;
	matris_2(p, matris, matris2);
	switch (task) {

	case 2:
		i1 = 0;
		//  matrischecktask(p,matris, matrischeck);
		//	x2=task6(p,i1,j1,matrischeck);
		//	if (x2==5){
		matrischecktask(p, matris, matrischeck);
		task2(p, i1, j1, matrischeck, A, counter);
		//	    }
		//  else
		//   	   cout<<"ERROR a0001xd\nMatris Cannot be checked for Hamilton Tour/Path!\n ";
		break;
	case 6:
		task6(p, i1, j1, matrischeck);
		break;
	case 7:
		q = task10(p, matris2);
		matrischecktask(p, matris, matrischeck);
		task7(p, q, matrischeck);
		break;
	case 8:
		task8(p, matris2);
		break;
	case 9:
		matrischecktask(p, matris, matrischeck);
		task9(p, matrischeck);
		break;
	case 10:
		q = task10(p, matris2);
		cout << "Andaze Graph: " << 2 * q << endl;
		break;
	}

	outputmatris(p, matris);
	cout << "\n\n\t\t\t\t";
	system("pause");
	for (int del=0; del<p; del++) {
		delete[] matrischeck[del];
		delete[] matris[del];
		delete[] matris2[del];
	}
	delete matrischeck;
	delete matris;
	delete matris2;
	delete A;
}





void inputmatris(int p, int**matris) {
	cout << "enter your matris:\n";
	for (int i = 0; i < p; i++) {
		cout << "colum " << i + 1 << endl;
		for (int j = 0; j < p; j++) {
			cin >> *(*(matris + i) + j);
		}
		system("cls");
	}
	system("cls");
}
void outputmatris(int p, int**matris) {
	cout << "your matris is:\n\n";


	cout << "   ";
	int counter = 0;
	for (char ch = 'a'; ch <= 'z'; ch++) {
		counter++;
		if (counter <= p)
			cout << ch << " ";
		else {
			cout << endl;
			counter = 0;
			break;
		}
	}


	char ch = 'a';


	for (int i = 0; i < p; i++) {
		counter++;
		if (counter <= p) {
			cout << ch;
		}
		ch++;
		cout << "| ";
		for (int j = 0; j < p; j++) {

			cout << *(*(matris + i) + j) << " ";
		}
		cout << "|";
		cout << endl;
	}
}
void matris_2(int p, int **matris, int **matris2) {
	int m = 0, n = 0, x, y;
	for (int m = 0; m < p; m++)
		for (int n = 0; n < p; n++)
			for (int i = 0; i < p; i++) {
				x = *(*(matris + m) + i);
				y = *(*(matris + i) + n);
				*(*(matris2 + m) + n) += x * y;
			}
}
bool check(int p, int **matris) {
	int a, b;
	for (int i = 0; i < p; i++) {
		if (*(*(matris + i) + i) != 0) {
			return true;
		}
		for (int j = 0; j < p; j++) {
			a = *(*(matris + i) + j);
			b = *(*(matris + j) + i);
			if (a != b) {
				return true;
			}
		}
	}
	return false;
}
};

namespace _v15 {
#ifndef ADJACENCYMATRIX_H
#define ADJACENCYMATRIX_H

#include <vector>
using namespace std;


class adjacencyMatrix
{
    public:
        adjacencyMatrix();
        /**
        * Constructor
        */
        adjacencyMatrix(int);
        /**
        * Constructor, giving the original size of the matrix.
        */
        virtual ~adjacencyMatrix();
        /**
        * Destructor
        */
		void resize(int);
		/**
		* Change the size of the adjacency matrix.
		**/
        bool get(int id1, int id2);
        /**
        * Returns true if the entry exists in the adjacency matrix.
        */
        bool get(int id1, int id2, int&);
        /**
        * Returns true if the entry exists in the adjacency matrix and gives the ID of the existing entry.
        */
        int add(int id1, int id2);
        /**
        * Add a new entry to the adjacency matrix and returns its ID.
        */
        void del(int id1, int id2);
        /**
        * Deletes an entry in the adjacency matrix.
        */
        int size();
        /**
        * Returns the size of the adjacency matrix (number of columns).
        */
        int nEdges();
        /**
        * Returns the number of edges
        */
        void print();
        /**
        * Prints out the content of the adjacency matrix.
        */
    private:
        vector<vector<int> > mat_;
        int max_id_;
};

#endif // ADJACENCYMATRIX_H

#include "adjacencyMatrix.h"
#include <vector>
#include <iostream>
using namespace std;


adjacencyMatrix::adjacencyMatrix()
{
/**
 * Constructor
 */
	max_id_=0;
}

adjacencyMatrix::adjacencyMatrix(int n)
{
/**
 * Constructor
 * \param[in] n Original size of the matrix.
 */
	resize(n);
	max_id_=0;
}

void adjacencyMatrix::resize(int n_new){
/**
 * Resizes the matrix so that it contains n vertices.
 * \param[in] n_new New size of the matrix
 */
	int n_old=size();
	if(n_new>n_old){
		for(int i=n_old;i<n_new;i++){	// Enlarge the matrix
			vector<int> bottom(i,0);
			mat_.push_back(bottom);
		}
	} else if(n_new<n_old) {			// Shrink the matrix
		mat_.resize(n_new);
		for(int i=0;i<n_new;i++){
			mat_.at(i).resize(n_new-1);
		}
	}
}


bool adjacencyMatrix::get(int id1, int id2){
/**
 * Checks if two nodes are connected. Returns true if yes, false otherwise.
 * \param[in]   id1 ID of the first node
 * \param[in]   id2 ID of the second node
 */
	int ide;
	return get(id1,id2,ide);
}

bool adjacencyMatrix::get(int id1, int id2, int& ide){
/**
 * Gets the id of the edge connecting two nodes in the graph. Returns true if the edge exists, false otherwise.
 * \param[in]   id1 ID of the first node
 * \param[in]   id2 ID of the second node
 * \param[out]  ide edge ID, if it exists in the adjacency matrix
 */
	int id1_s=max(id1,id2);
	int id2_s=min(id1,id2);
	int n=size();
	if( (id1_s>n-1) || (id2_s<0) || (id1==id2) ){
		ide=0;
	} else {
		int val=mat_.at(id1_s).at(id2_s);
		if(id1>=id2){
			ide=val;
		}else{
			ide=-val;
		}
	}
	if (ide==0){
		return false;
	} else {
		return true;
	}
}

int adjacencyMatrix::add(int id1,int id2){
/**
 * Add new entry to the adjacency matrix and returns the edge ID. If the entry already exists, it returns the corresponding ID; otherwise, it increments the max ID and uses it.
 * If any of the imput argument is negative, it increments the max ID but returns 0.
 * \param[in] id1 ID of the first node
 * \param[in] id2 ID of the second node
 */
	int ide;
	int n=size();
	int id1_s=max(id1,id2);
	int id2_s=min(id1,id2);
	if ( (id2_s<0) || (id1==id2) ){// Any negative input index, or trying to add self loop (forbidden in skew-matrices)
		max_id_++;
		ide=max_id_;
	} else {								// Both positive and different to each other
		if( !( get(id1,id2,ide) ) ){		// If the entry already exists, just get the edge ID; new edge otherwise
			max_id_++;
			if(id1_s+1>n){
				resize(id1_s+1);			// If the matrix is too small, enlarge it
			}
			if(id1>=id2){
				mat_.at(id1).at(id2)=max_id_;
			} else {
				mat_.at(id2).at(id1)=-max_id_;
			}
			ide=max_id_;
		}
	}
	return ide;
}

void adjacencyMatrix::del(int id1,int id2){
/**
 * Deletes an entry (edge) from the adjacency matrix.
 * \param[in] id1 ID of the first node
 * \param[in] id2 ID of the second node
 */
	int n=size();
	int id1_s=max(id1,id2);
	int id2_s=min(id1,id2);
	if ( (id2_s>=0) && (id1_s<n-1) ){
		mat_.at(id1_s).at(id2_s)=0;
	}
}


int adjacencyMatrix::size(){
/**
 * Gets the size of the adjacency matrix.
 */
    return mat_.size();
}

void adjacencyMatrix::print(){
/**
 * Prints the adjacency matrix
 */
    int n=size();
	int id;
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			get(i,j,id);
			cout<<id<<"\t";
		}
		cout<<endl;
	}
}

int adjacencyMatrix::nEdges(){
/**
 * Returns the number of edges
 */
    return max_id_;
}

adjacencyMatrix::~adjacencyMatrix()
{
/**
 * Destructor
 */
}
};

namespace _v16 {
""" One Example of how to implement a Adjacency Matrix implementation of a Graph Data Structure
    that matches the Abstract Data Type as defined in the eBook
    https://runestone.academy/runestone/static/pythonds/index.html
    and goes with the video course at http://youtube.com/gjenkinslbcc channel
    """


class Vertex(object):
    """vertex with key and optional data payload"""

    def __init__(self, key, index, payload=None):
        self.key = key
        self.payload = payload  # data associated with Vertex
        self.index = index

    def __str__(self):
        return self.key

    def __repr__(self):
        return str(self)


class Graph(object):

    def __init__(self, max_vertexes=100):
        self.matrix = [[None] * max_vertexes for _ in range(max_vertexes)]  # 2d array (list of lists)
        self.num_vertexes = 0  # current number of vertexes
        self.vertexes = {}  # vertex dict
        self.i_to_key = []  # list of keys to look up from index

    def add_vertex(self, key, payload=None):
        """ add vertex named key if it is not already in graph"""
        assert self.num_vertexes < len(self.matrix), "max vertexes reached,  can not add more!"
        if key not in self.vertexes:
            self.i_to_key.append(key)
            i = self.num_vertexes
            self.vertexes[key] = Vertex(key, i, payload)
            self.num_vertexes = i + 1

    def add_edge(self, from_key, to_key, weight=None):
        """ create vertexes if needed and then set weight into matrix"""
        self.add_vertex(from_key)
        self.add_vertex(to_key)
        self.matrix[self.vertexes[from_key].index][self.vertexes[to_key].index] = weight

    def get_vertex(self, key):
        return self.vertexes[key]

    def get_vertices(self):
        """returns the list of all vertices in the graph."""
        return self.vertexes.values()

    def __contains__(self, key):
        return key in self.vertexes

    def edges(self, from_key):
        """ return list of tuples (to_vertex, weight) of all edges from vertex_key key"""
        to_dim = self.matrix[self.vertexes[from_key].index]
        return [(g.vertexes[g.i_to_key[i]], w) for i, w in enumerate(to_dim) if w]
        # result = []
        # for i,w in enumerate(to_dim):
        #     if w:  # if weigh not None
        #         result.append((self.vertexes[self.i_to_key[i]], w))
        # return result


if __name__ == '__main__':
    # test case figure 2 @
    # https://runestone.academy/runestone/static/pythonds/Graphs/VocabularyandDefinitions.html#fig-dgsimple

    g = Graph()
    g.add_edge('v0', 'v1', 5)
    g.add_edge('v1', 'v2', 4)
    g.add_edge('v2', 'v3', 9)
    g.add_edge('v3', 'v4', 7)
    g.add_edge('v4', 'v0', 1)
    g.add_edge('v0', 'v5', 2)
    g.add_edge('v5', 'v4', 8)
    g.add_edge('v3', 'v5', 3)
    g.add_edge('v5', 'v2', 1)
    g.add_vertex('v6')  # extra vertex with no connections

    print("The Matrix from this graph:")
    print(" ", " ".join([v.key for v in g.get_vertices()]))
    for i in range(g.num_vertexes):
        row = map(lambda x: str(x) if x else '.', g.matrix[i][:g.num_vertexes])
        print(g.i_to_key[i], "  ".join(row))

    print('\ng.edges("v5")', g.edges("v5"))
    print('"v5" in g', "v5" in g)
    print('"v6" in g', "v6" in g)
    print('"v7" in g', "v7" in g)
};

namespace _v17 {
import java.util.*;

/*
 * Developer: Mustafa Saraç
 * Data Structure: Graph (implemented as Adjacency Matrix)
 *
 * --- IMPORTANT ---
 *
 * This code was implemented by making changes to the starter code given by the instructor
 * for COMP 202 (Algorithms and Data Structures, Koç University) course project.
 */

public class Graph {

	private int vertice;
	private int[][] adjacencyMatrix;

	// create an empty graph with V vertices
	public Graph(int V) {
		this.vertice = V;
		adjacencyMatrix = new int[V][V];

		for(int i=0; i<V; i++){
			for(int j=0; j<V; j++){
				adjacencyMatrix[i][j] = 0;
			}
		}
	}

	// return the number of vertices
	public int getNumVertices() {
		return this.vertice;
	}

	// return the number of edges
	public int getNumEdges() {
		int edgeNumber = 0;

		for(int i=0; i<this.vertice; i++){
			for(int j=0; j<this.vertice; j++){
				if(adjacencyMatrix[i][j] == 1){
					edgeNumber++;
				}
			}
		}

		edgeNumber = edgeNumber/2; // in order to prevent counting the same edge twice.
		// in order to change it to DIRECTED GRAPH
		// you should delete this line.

		return edgeNumber;
	}

	// add a new vertex to the graph
	public void addVertex() {
		int[][] tempArray = new int[this.vertice][this.vertice];

		for(int i=0; i<this.vertice; i++){
			for(int j=0; j<this.vertice; j++){
				tempArray[i][j] = adjacencyMatrix[i][j];
				}
			}

		this.vertice++;
		adjacencyMatrix = new int[this.vertice][this.vertice];

		for(int i=0; i<this.vertice - 1; i++){
			for(int j=0; j<this.vertice - 1; j++){
				adjacencyMatrix[i][j] = tempArray[i][j];
				}
			}

		for(int k=0; k<this.vertice; k++){
			adjacencyMatrix[this.vertice-1][k] = 0;
		}
	}

	// add a new edge between vertices v and w
	public void addEdge(int v, int w) {
		adjacencyMatrix[v][w] = 1;
		adjacencyMatrix[w][v] = 1; 		 // in order to change it to DIRECTED GRAPH
										 // you should delete this line.
	}

	// remove the edge between vertices v and w
	public void removeEdge(int v, int w) {
		adjacencyMatrix[v][w] = 0;
		adjacencyMatrix[w][v] = 0;		// in order to change it to DIRECTED GRAPH
										// you should delete this line.
	}

	// return the list of vertices which are adjacent to vertex v
	public Iterable<Integer> getNeighbors(int v) {
		ArrayList<Integer> neighborOfVertice = new ArrayList<Integer>();

		for(int i=0; i<this.vertice; i++){
			if(adjacencyMatrix[v][i] == 1){
				neighborOfVertice.add(i);
			}
		}

		return neighborOfVertice;
	}

	// return the list of the degrees of the vertices in this graph in sorted order (from largest to smallest)
	public List<Integer> degreeSequence() {
		List<Integer> degreeSequence = new ArrayList<Integer>();
		List<Integer> temp = new ArrayList<Integer>();
		int size;

		for(int i=0; i<this.vertice; i++){
			size = ((ArrayList<Integer>) this.getNeighbors(i)).size();
			temp.add(size);
			degreeSequence.add(size);
		}
		Collections.sort(degreeSequence);
		Collections.reverse(degreeSequence);

		return degreeSequence;
	}

	// return the list of the vertices which are at distance 2 away from the vertex v
	public List<Integer> verticesWithinDistance2(int v) {
	List<Integer> distance2List = new ArrayList<Integer>();

	if(this.getNumEdges() == 0){
		distance2List.add(v);
	} else {
		distance2List.add(v);
		for(Integer j: this.getNeighbors(v)){
			distance2List.add(j);
			for(Integer k: this.getNeighbors(j)){
				distance2List.add(k);
			}
		}
	}
	return distance2List;
	}

	// return the string representation of the graph in adjacency matrix format
	public String showAsMatrix() {
		String string = "";
		for(int i=0; i<this.vertice; i++){
			for(int j=0; j<this.vertice; j++){
				string = string.concat(adjacencyMatrix[i][j]  + "-");
			}
			string = string.concat("\n");
			if(string.isEmpty()){
				string = string.concat("-");
			}
		}
		return string;
	}

	// return the string representation of the graph in adjacency list format
	public String showAsAdjacencyList() {
		String string = "";

		for(int i=0; i<this.vertice; i++){
			for(Integer j: this.getNeighbors(i)){
				string = string.concat(j + "-");
			}
			if(((ArrayList<Integer>) this.getNeighbors(i)).size() == 0){
				string = string.concat("-");
				if(i == this.vertice){
					break;
				}
			}
			string = string.concat("\n");
		}
		return string;
	}

}
};

namespace _v18 {
import matplotlib.pyplot as plt
import networkx as nx
import sys

class Graph(object):
    def __init__(self, adjmat):
        self.n = len(adjmat)
        self.adjmat = adjmat
        self.degree = [sum(row) for row in self.adjmat]

    def show(self):
        G = nx.Graph()
        for i in range(self.n):
            G.add_node(i)
        for i in range(self.n):
            for j in range(i+1, self.n):
                if self.adjmat[i][j]:
                    G.add_edge(i, j)
        nx.draw_networkx(G, pos=nx.circular_layout(G))
        plt.show()

def read_instance(lines):
    lines = [line.strip().split() for line in lines]
    p_line = [line for line in lines if line[0]=="p"][0]
    e_lines = [line for line in lines if line[0]=="e"]
    n = int(p_line[2])
    print "Number of vertices:", n
    print "Number of edges:", len(e_lines)
    adjmat = [[False] * n for _ in range(n)]
    for e in e_lines:
        v, w = int(e[1])-1, int(e[2])-1
        if v==w:
            print "Loop detected", v
        if adjmat[v][w]:
            print "Duplicate edge", v, w
        adjmat[v][w] = adjmat[w][v] = True
    print "Finished reading instance."
    return Graph(adjmat)

if __name__ == "__main__":
    with open(sys.argv[1], "r") as f:
        g = read_instance([line for line in f.readlines()])
    g.show()

from collections import deque
from PIL import Image
import sys

class Graph(object):
    def __init__(self, adjmat):
        self.n = len(adjmat)
        self.adjmat = adjmat
        self.degree = [sum(row) for row in self.adjmat]

    def sort_by_degree(self):
        v_and_deg = zip(range(self.n), self.degree)
        v_and_deg.sort(key=lambda x: x[1], reverse=True)
        vv = [x[0] for x in v_and_deg]
        self.adjmat = [[self.adjmat[v][w] for v in vv] for w in vv]

    def show(self):
        img = Image.new('RGB', (self.n*3, self.n*3), "white")
        pixels = img.load()

        for i in range(self.n):
            for j in range(self.n):
                if self.adjmat[i][j]:
                    for k in range(3):
                        for l in range(3):
                            colour = (0,0,0)
                            if k==2 or l==2:
                                colour = (80,80,80)
                            if (k==2 and i%10==9) or (l==2 and j%10==9):
                                colour = (150,150,150)
                            pixels[i*3+k, j*3+l] = colour

        img.show()

def read_instance(lines):
    lines = [line.strip().split() for line in lines]
    p_line = [line for line in lines if line[0]=="p"][0]
    e_lines = [line for line in lines if line[0]=="e"]
    n = int(p_line[2])
    print "Number of vertices:", n
    print "Number of edges:", len(e_lines)
    adjmat = [[False] * n for _ in range(n)]
    for e in e_lines:
        v, w = int(e[1])-1, int(e[2])-1
        if v==w:
            print "Loop detected", v
        if adjmat[v][w]:
            print "Duplicate edge", v, w
        adjmat[v][w] = adjmat[w][v] = True
    print "Finished reading instance."
    return Graph(adjmat)

if __name__ == "__main__":
    with open(sys.argv[1], "r") as f:
        g = read_instance([line for line in f.readlines()])
    if len(sys.argv) < 3:
        g.sort_by_degree()
    g.show()
};

namespace _v19 {
import networkx as nx
import matplotlib.pyplot as plt
import pylab
import csv
from random import random
G=nx.Graph()

with open('ai3.csv', 'rb') as csvfile:
	spamreader = csv.reader(csvfile, delimiter=',')
	for row in spamreader:
		node = row[0]
		i=1;
		print node
		while(True):
			if(i>5 or row[2*i-1]==""):
				break

			G.add_edge(node,row[2*i-1], weight=row[2*i])
			i+=1


pos=nx.circular_layout(G)

# version 2
pylab.figure(1,figsize=(40,40))
nx.draw_circular(G)
# specifiy edge labels explicitly
edge_labels=dict([((u,v,),d['weight'])
             for u,v,d in G.edges(data=True)])
nx.draw_networkx_nodes(G,pos,node_size=1000)
nx.draw_networkx_edge_labels(G,pos,edge_labels=edge_labels)
nx.draw_networkx_labels(G,pos,font_size=10,font_family='sans-serif')
# show graphs
pylab.show()
#plt.show()
plt.savefig("graph.png", dpi=1000)
};

namespace _v20 {
package JGraph;

// Class To Create An Adjacency Matrix For A Graph
// If The Total Number Of Vertices Be N. Then The Graph Will Have Vertex Values From 0 To N-1

// Importing required packages
import java.io.*;
import java.util.*;

public class AdjacencyMatrix{

    public int N; // To store the total number of vertices
    public int[][] adj_matrix; // Adjacency Matrix
    public AdjacencyMatrix(int n){ // Constructor  n : Total number of vertices
        N=n;
        adj_matrix=new int[N][N];
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++)
                adj_matrix[i][j]=0;
        }
    }

    public int[][] create_edge(int from, int to, boolean weighted, int weight){ // To create the edge
        // from : Source Vertex,  to : Destination Vertex,  weighted : Whether it is a weighted edge,  weight : If weighted is true then value of weight
        try{
            if(weighted==true) // If weighted edge
                adj_matrix[from][to]=weight;
            else
                adj_matrix[from][to]=1;
        }
        catch(ArrayIndexOutOfBoundsException index){ // If invalid index
            System.out.println(" Invalid Vertex!");
        }
        return adj_matrix;
    }

    public int get_edge(int from, int to){ // To get the value of the edge
        // from : Source Vertex,  to : Destination Vertex
        int temp=0;
        try{
            temp=adj_matrix[from][to];
        }
        catch(ArrayIndexOutOfBoundsException index){ // If invalid index
            System.out.println(" Invalid Vertex!");
        }
        return temp;
    }

    public void display(){ // To display the adjacency matrix
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++)
                System.out.print(adj_matrix[i][j]+" ");
            System.out.println();
        }
    }
}
};

namespace _v21 {
#include<bits/stdc++.h>
using namespace std;

int add_edge(vector<vector<int> >&adj_matrix, int u, int v){
	adj_matrix[u][v]=1;
	//adj_matrix[v][u]=1; if it's undirected graph
	return 0;
}

int traverse(int n, vector<vector<int> >adj_matrix)
{
	for (int i=1; i<n; i++){
		cout<<"vetex "<<i<<" is connected to: ";
		for(int j=1;j<n;j++){
			if(adj_matrix[i][j]==1)
				cout<<j<<" ";
		}
		cout<<endl;
	}
	return 0;
}

int main() {
	int n = 6;

	vector<vector<int> > adj_matrix(n, vector<int> (n));

	add_edge(adj_matrix,1,2);
	add_edge(adj_matrix,1,3);
	add_edge(adj_matrix,1,4);
	add_edge(adj_matrix,2,3);
	add_edge(adj_matrix,3,4);
	add_edge(adj_matrix,4,4);
	add_edge(adj_matrix,5,2);

	traverse(n, adj_matrix);

	return 0;
}
};

namespace _v22 {
11
A B C D E F G H I J K
0 0 0 0 0 0 0 0 0 0 0
1 0 1 1 0 0 0 0 0 0 0
1 1 0 1 0 0 0 0 0 0 0
1 1 1 0 0 0 0 0 0 0 0
0 0 0 0 0 1 0 0 0 0 0
0 1 0 0 1 0 0 0 0 1 0
0 0 0 0 0 0 0 1 0 0 0
0 0 0 0 1 1 0 0 0 0 0
0 0 0 0 0 0 0 1 0 0 0
0 0 0 0 0 1 0 0 0 0 0
0 0 0 0 0 0 0 0 0 1 0

#include "Graph.h"

#include <iostream>
#include <string>
#include <vector>
using namespace std;

const string FILE_NAME = "graph_data.txt";

int main()
{
	Graph g1;
	g1.createGraph(FILE_NAME);
	cout << g1 << endl;

	vector<char> bfsSequence;

	cout << "\nBFS traversal: ";
	g1.bfsTraversal('A', bfsSequence);		// 0 is the first vertex of the BFS

	for (char vertex : bfsSequence)
		cout << vertex << " ";

	cout << endl;
	system("Pause");
    return 0;
}

#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

const int MAX_VERTICES = 20;

class Graph
{
	friend ostream& operator<<(ostream& out, const Graph& g);

public:
    Graph( );
    Graph(int totalVertices);

	void createGraph(const string& fileName);

	/*************************************************************
	*
	*	Write your function declarations below this block.
	*
	**************************************************************/

	// Declaration function clearGraph
	void clearGraph();

	// Declaration of destructor
	~Graph();

	// Declaration function bfsTraversal
	void bfsTraversal(char vertex, vector<char>& bfs) const;

private:

	char *vertices;			//will point to an array of vertices
    int **matrix;			//will point to the adjacency matrix
    int maxVertices;		//max number of vertices the graph can hold (capacity)
    int numOfVertices;		//total number of vertices

};

#endif

#include "Graph.h"

ostream& operator<<(ostream& out, const Graph& g)
{
	for (int i = 0; i < g.numOfVertices; ++i)
	{
		out << g.vertices[i] << ": ";
		for (int j = 0; j < g.numOfVertices; ++j)
			out << g.matrix[i][j] << " ";
		out << endl;
	}

	return out;
}

Graph::Graph( )
{
	numOfVertices = 0;
	maxVertices = MAX_VERTICES;

	vertices = new char[maxVertices];

	matrix = new int *[maxVertices];
	for (int i = 0; i < maxVertices; ++i)
		matrix[i] = new int[maxVertices](); // The parenthesis will initialize the array to 0
}

Graph::Graph(int totalVertices)
{
	numOfVertices = 0;
	maxVertices = totalVertices;

	vertices = new char[maxVertices];

	matrix = new int *[maxVertices];
	for (int i = 0; i < maxVertices; ++i)
		matrix[i] = new int[maxVertices]();  // The parenthesis will initialize the array to 0
}

void Graph::createGraph(const string& fileName)
{
	if (numOfVertices != 0)		//if the graph is not empty, make it empty
		clearGraph();

	ifstream infile;

	infile.open(fileName);

	if (!infile)
	{
		cerr << "Cannot open the input file." << endl;
		system("Pause");
		exit(0);
	}

	infile >> numOfVertices;

	char vertex;

	for (int i = 0; i < numOfVertices; ++i)
	{
		infile >> vertex;
		vertices[i] = vertex;
	}

	int adjacentVertex = 0;

	for (int i = 0; i < numOfVertices; ++i)
	{
		for (int j = 0; j < numOfVertices; ++j)
		{
			infile >> adjacentVertex;
			matrix[i][j] = adjacentVertex;
		}
	}

	infile.close();
}

/*
	Lauguico, Marco
	Orellana, Romario
	CS A200
	March 10, 2017
	Lab 7
*/

#include "Graph.h"

// Definition function clearGraph
void Graph::clearGraph()
{
	for (int i = 0; i < maxVertices; ++i)
	{
		delete matrix[i];
		matrix[i] = new int[maxVertices](); // The parenthesis will initialize the array to 0
	}
	numOfVertices = 0;
}

// Definition of destructor
Graph::~Graph()
{
	delete[] vertices;
	vertices = nullptr;

	for (int i = 0; i < maxVertices; ++i)
	{
		delete matrix[i];
	}
	delete[] matrix;
	matrix = nullptr;

	numOfVertices = 0;
}


// Definition function bfsTraversal
void Graph::bfsTraversal(char vertex, vector<char>& bfs) const
{
	// if numOfVertices == 0 or less than 0 then do nothing.
	if (numOfVertices > 0)
	{
		if (numOfVertices == 1)
		{
			bfs.push_back(vertex);
		}
		else
		{
			queue<int> bfsQueue;
			// Dynamic array of visited vertices.
			// Sets to true if index of the vertex has been visited.
			bool* visited = new bool[numOfVertices]();
			// Finds the index of the char vertex.
			int index = 0;
			// This will loop until it finds vertices[index] that is equals to vertex.
			// Increments index everytime vertices[index] != vertex
			while (!visited[index])
			{
				// If this condition has been met, turns visited[index] to true
				// and loop ends.
				if (vertices[index] == vertex)
					visited[index] = true;
				else
					++index;
			}
			// Pushes the index of the first vertex into the queue.
			bfsQueue.push(index);
			int visitedCounter = 1;
			// This loops until all vertexes are in the BFS.
			do
			{
				index = bfsQueue.front();
				bfs.push_back(vertices[index]);
				// Won't traverse anymore if all vertices has already been added to the queue.
				if (visitedCounter != numOfVertices)
				{
					int col = index;
					// Traverses through the matrix and search for the successors of the bfsQueue.front();
					for (int row = 0; row < numOfVertices; ++row)
					{
						// If this condition is true, add the index of vertex in the queue
						// row == successor's index
						if ((matrix[row][col] == 1) && (!visited[row]))
						{
							bfsQueue.push(row);
							++visitedCounter;
							visited[row] = true;
							// This condition will force stop the for loop if it's true.
							// This will avoid unecessary traversal in the matrix.
							if (visitedCounter == numOfVertices)
								row = numOfVertices;
						}
					}
				}
				bfsQueue.pop();
			} while (!bfsQueue.empty());
			delete[] visited;
		}
	}
}
};

namespace _v23 {

String2AdjMatrix

This package has been designed to provide functions which enable the construction of adjacency matrices, from a specified string of characters. It contains functions to generate an empty adjacency matrix (with each unique substring as a row name or column name) from a given list of strings. This is useful when performing social network anaylsis. In this current release, the strings are bidirectional, meaning it doesn't matter where two unique substrings occur in the string.

The output matrices can be used directly with packages such as igraph()

Generating large matrices is computationally intensive and may take a while.
Example
Start with data to generate an adjacency matrix from

string_in = c('apples, pears, bananas', 'apples, bananas', 'apples, pears')
Generate a new blank matrix

blank_matrix = generate_adj_matrix(string_in)
Now fill the matrix

string_2_matrix(blank_matrix, string_in)
Installation instructions
From CRAN - stable release

install.packages('String2AdjMatrix')
From GitHub - development version

devtools::install_github('tomdrake\String2AdjMatrix')
Dependencies

Requires stringr
Overview

This package comprises three functions; generate_adj_matrix, string_2_matrix and string_2_matrix_x.
1. generate_adj_matrix()

Generates an adjacency matrix from a given string. Detects unique values and generates a blank matrix with colnames and rownames of each unique value in supplied string.

The string_data argument is the string from which the unique values and matrix will be generated.
2. string_2_matrix()

Iteratively applies string_2_matrix_x() to each column of a matrix. Use to generate an entire adjacency matrix.

The new_matrix element of the function should be either the matrix generated by generate_adj_matrix() or an empty data matrix of equal number of rows and columns. These should have unique values specified as the row names and column names.

The supplied_string element refers to the string in which the search is to be performed. i.e list = c('apples, pears, bananas', 'apples, bananas', 'apples, pears')

Generating large matrices is computationally intensive and may take a while.
3. string_2_matrix_x()

This function takes a specified column in a matrix and identifies how many times that substring appears with each row name for a given set of strings. Use to generate one column of adjacency data. Also used iteratively as part of string_2_matrix()

The new_matrix element of the function should be either the matrix generated by generate_adj_matrix() or an empty data matrix of equal number of rows and columns. These should have unique values specified as the row names and column names.

The supplied_string element refers to the string in which the search is to be performed. i.e list = c('apples, pears, bananas', 'apples, bananas', 'apples, pears')

The coord_x argument specifies the number column for which to convert. i.e. coord_x = 1 is the first column of a data matrix, coord_x = 12 is the twelfth column of a data matrix.


#generate_adj_matrix

generate_adj_matrix <-function(string_data, data_separator = ',', remove_spaces = F){
  if(remove_spaces == F){
string_in = string_data

string_a = paste0(string_in, collapse = data_separator)

string_b = unique(unlist(strsplit(string_a, data_separator)))

empty_matrix = matrix(data = NA, length(string_b), length(string_b))

rownames(empty_matrix) = string_b
colnames(empty_matrix) = string_b
result = empty_matrix
  }
  if(remove_spaces == T){
    string_in = string_data

    string_a = paste0(string_in, collapse = data_separator)

    string_b = unique(unlist(strsplit(string_a, data_separator)))

    empty_matrix = matrix(data = NA, length(string_b), length(string_b))

    rownames(empty_matrix) = gsub(' ', '', string_b)
    colnames(empty_matrix) = gsub(' ', '', string_b)
    result = empty_matrix
  }
  return(result)
}

#Function
string_2_matrix <- function(new_matrix, supplied_string, self = 0){
    result.matrix = new_matrix
  for (i in 1:length(colnames(new_matrix))){
    result.matrix[,i] = string_2_matrix_x(new_matrix, supplied_string, coord_x = i, self = self)
  }
  return(result.matrix)
}

#Function x
string_2_matrix_x <- function(new_matrix, supplied_string,  coord_x = 1, self = 0){
    result = list()
  reference_string = colnames(new_matrix)[coord_x]
  for (i in 1:length(rownames(new_matrix))){
    str1 = reference_string
    str2 = rownames(new_matrix)[i]
    string_search = paste0('^(?=.*', str1, ')(?=.*', str2, ')')
    result[[i]] = ifelse((str1 == str2), self, sum(str_count(supplied_string, string_search)))
  }
  return(unlist(result))
}
};

#endif // GRAPH_HPP_INCLUDED
