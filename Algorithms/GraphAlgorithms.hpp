#ifndef GRAPHALGORITHMS_HPP_INCLUDED
#define GRAPHALGORITHMS_HPP_INCLUDED

#include <vector>
#include <random>
#include <algorithm>

/// TD
/*
    longest cycles, which terminate at "bridge points", ~ like "islands"
    shortest cycle in graph

*/
namespace GraphAlgo {
    struct Node {
        std::vector<Node*> conn {}; // (*?) this pisses me off that I can't use Node& and have to keep in mind that I have to switch syntax when dealing
                                    // with .conn; what is it that C++ assumes about references that prevents me from using std::vector<Node&> here (?!)
    };

    struct Graph_NodeConn {
        std::vector<Node*> nodes {};    // (*?) for syntax uniformity, the above forces me to turn this too into a std::vector<Node*>,
                                        // instead of std::vector<Node> which would have been a more "direct accessing" and with less memory;
                                        // (*?) on the other hand, this way, if the nodes exist in some space, they can actually be easily re-used
                                        // in multiple graphs (?!); but functions with side-effects would essentially affect the other graphs as well,
                                        // => ~ "node sharing, parallel (partially / totally overlapping) graphs"

        // (*?) due to the current nature of connections (they are stored in the node), it's more natural
        // to implement directed graphs than undirected graphs (which would otherwise store the connections
        // in a global, graph-based storage; (*?) but, direct graphs could also do the same, and besides,
        // in "parallel graphs" the only shared property are the nodes themselves, thus the connections
        // should not be stored in the nodes (?!), only the relevant "node (state-)data"

        // (*?) also note that in this graph structure, the nodes have essentially no (intrinsic) state, so this graph
        // is essentially just a list of connections to points that need not even be stored (?!)
        void AddEdge(uint64_t indexA, uint64_t indexB) {
            Node* a = nodes[indexA % nodes.size()]; // so because of the above, the vector's size would not even matter
            Node* b = nodes[indexB % nodes.size()];

//            if()
        }
    };

    struct Graph_Conn {
        // (*?) this kind of graph has the benefit of arbitrarily being either directed or undirected,
        // and it can all be modularized by the use of a "property verifier function", such as one which
        // checks if a commutation of an edge-to-be-added already exists (implying an undirected graph) or an
        // order-dependent-edge-to-be-added already exists (implying a directed graph)

        std::vector<std::pair<int64_t, int64_t>> edges {}; // at this point, just use whichever underlying type is fastest,
                                                // because the "count" property is irrelevant; what matters is fast
                                                // index <-> index mapping; for example, some indices could be negative
                                                // while others positive, and this could make comparisions much faster because
                                                // they'd be done based on just the MSBit

        bool directed = true;

        bool VerifyProperty_Directedness(int64_t indexA, int64_t indexB) {
            if(directed) {
                if(std::find(edges.begin(), edges.end(), std::pair<int64_t, int64_t>(indexA, indexB)) != edges.end()) {
                    // found
                    return false;    // cannot be added again
                } else {
                    // not found
                    return true;   // can be added
                }
            }
            else {
                if( std::find(edges.begin(), edges.end(), std::pair<int64_t, int64_t>(indexA, indexB)) != edges.end() ||
                    std::find(edges.begin(), edges.end(), std::pair<int64_t, int64_t>(indexB, indexA)) != edges.end()) {
                    // found
                    return false;   // cannot be added again
                } else {
                    // not found
                    return true;    // can be added
                }
            }
        }

        void AddEdge(int64_t indexA, int64_t indexB) {
            if(VerifyProperty_Directedness(indexA, indexB)) {
                edges.push_back(*(new std::pair<int64_t, int64_t>(indexA, indexB)));
            }
        }

        void RandomFill(uint64_t howMany, int64_t minIndex, int64_t maxIndex) {
            std::mt19937 rng {};
            while(howMany) {
                howMany--;

                // (*?) warning: this needs to ensure ~ "saturated / cyclic arithemtic on arbitrary interval", so the arithmetic
                // doesn't overflow and actually get out of the expected interval; (*?) well, saturated arithmetic would actually
                // affect the randomness of the sequence, so it's not a solution; instead, a cyclic arithmetic on arbitrary intervals
                // is what's required

//                int64_t leftNode = *(int64_t*)(&((*(uint64_t*)(&minIndex) + *(uint64_t*)(&rng())) % *(uint64_t*)(&maxIndex)));
                int64_t leftNode = 0;
                int64_t rightNode = 0;
                AddEdge(leftNode, rightNode);
            }
        }
    };
};


#endif // GRAPHALGORITHMS_HPP_INCLUDED
