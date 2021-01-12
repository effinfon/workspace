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

#endif // GRAPH_HPP_INCLUDED
