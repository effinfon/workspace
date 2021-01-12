#ifndef LABWORK_HPP_INCLUDED
#define LABWORK_HPP_INCLUDED

#include <vector>
#include <math.h>
#include <random>

/*  GRAPH dts

    reading and writting tofrom files

    algorithms:
        // shortest chain
        // eulerian and hamiltonian paths
        // graph projection (I know they are asking for a stupid implementation to show-off the effort, but that's pointless; it's either industry-level, or it's nothing)
        // lee algorithm (maze search algorithms ?)
        // width and depth iteration
        // find islands, find connected "components" and "connected graphs", ?? etc. (connectivity algorithms ?)
        // graph construction according to a property (*?)
            <e.g.> generate random graphs: randomly connected (undirected, directed), random sized, etc.
            <e.g.> generate all undirected graphs with n vertices
            <e.g.> generate (random) bipartite / n-partite graphs (of random size)
        // (spanning trees algorithms ?)
        // identify planar graphs -> draw them using their class's specialized algorithm
    see what graph functionality is needed to assist with studying Uri Alon's POV of genetic circuite
    (*!?) draw graphs: large networks, genetic circuits, social relations,, structure, hierarchical arrangements, etc.
    ...
*/
/*  STATIC(-SIZE) and DYNAMIC(-SIZE) dts

    (*?) pointer container, deep-copy container

    lynked lists, stack, queue, heap, reallocating array, binary tree (+ transform from an array), multiway tree, red-black bts, self-balancing bts, ?? etc.
    (*?) a graph-like dts (or a sort of multi-way tree ?)
    dictionary, map, table
    bitmap (different variants)
*/
/*  PROBLEMS

    using the stack: (verify) paired parentheses in a text (and get the row and column for all the unpaired parentheses)
    using cyclic linked lists: "chocolate or prize distribution / cyclic shift on a shrinking list" (the order in which indices are visited is of interest here)
    (*?) generate graphs that are "space tilings" -> "open outer boundary, tiling graphs" and "closed boundary, tiling graphs" (these require solving the problem
        of "wrapping the space on itself at its boundaries and closing it")
    considering a hexagonal tiling of a game map, with some nodes being traversable and others being traversable, implement pathfinding from an origin node to a
        destination node (think of Civ. games); implement the square tiling variant as well, the triangle one

*/

/// Notes
/*
    all types created here will be "hard-copying" [not necessarely "deep-copying" though (*!?)]
*/

std::vector<std::pair<uint64_t, uint64_t>> edges {};
template<uint64_t nodes> uint8_t adjancency_matrix[nodes][nodes] {};
template<uint64_t nodes> float cost_matrix[nodes][nodes] {};
template<uint64_t nodes, uint64_t edges> uint8_t incidence_matrix[nodes][edges] {};
std::vector<std::pair<std::pair<uint64_t, uint64_t>, float>> edges_and_cost {};

void DebugPrint(bool verbose, char const * formatting_string, ... /* var_arg, of possibly different types; it should be the same as what printf() takes */) {
    if(verbose) {
    // (*?) I still don't know ow to make this work; there seem to be solutions relating to importing a type defined in the standard library,
        // but I have not yet understood the large ammount of data that has to be learnt related to it and "relatives"
//        printf(formatting_string, ...);
    }
}

void Log(char const * formatting_string, ...) {
    // (*?) a log type is required first; basically a string that can get very long;
        // it might also have some sort of "internal structure", "filtering messages based on origin or some property", etc.
}

template<typename T>
struct List {
    struct Node {
        T value;
        T* prev;
        T* next;
    };

    Node* head;
    Node* tail;

    void Stack() {}
    void Push() {}

    void Pop() {}

    void Queue() {}
    void Enque() {}

    void Deque() {}

    void Peek_head() {}
    void Peek_start() {}

    void Peek_tail() {}
    void Peek_end() {}

    void Insert() {}
    void Add() {}

    void Append() {}

    void Remove() {}
//    void Delete() {}   // (*?) language(-design) wise, this is very bad (!); it limits "freedom of expressivity / of wording" (*?)

    void Clear() {}

    void Empty() {}
    void Reset() {}

    void Fill() {}  // multiple elements simultaneously / in one call; it takes another list or array or etc. "collection type"

    void Merge() {}
    void Combine() {}

    void Decompose() {}
    void Separate() {}

    void Sublist() {}
};

template<typename T>
struct ReallocatingArray {
    // (*?) can have different scaling functions
    // thus, make multiple static functions and have it decide based on its size and available space on the heap
    // (*?) it should have multi-threading support
    // (*?) memory allocation should occur pre-emptively, and be multi-threaded
    // (*?) it will need to change its own type at some point, into a linked list, because reallocating large ammounts
        // of space is problematic (especially without defragmentation; and yet, defragmentation does actually occur
        // with a granularity of 4 KB, in the kernel, based on memory pages, and with the help of the MMU)
    /// TD: for now it only knows how to grow
    // (*?) design problem: how to force all implementations that add or remove elements to first check the count vs capacity
        // and reallocate at need (?), while maximizing code reusability [at the level of the programmer's language, not necessarely
        // the translated result (!?)] and even code integration (*?)

    T* array {new T[capacity]}; // (*?) so does it automatically arrange initializations in an attempt to make this sequence valid ?
    uint64_t capacity {1};  // elements
//    uint64_t size {sizeof(T) + sizeof(ReallocatingArray);  // bytes: object + array -> total size; it is related to capacity, not count
    uint64_t count {0}; // elements

    ReallocatingArray() {}

    inline float Scaling() {
        if(capacity < 1024) {
            return 2.0f;
        } else if (capacity < 1048576) {
            return 1.414213562f;
        } else if (capacity < 1073741824) {
            return 1.25992105f;
        }
        // effectively, return pow(2, 1 / log(1024, capacity))
            // it would seem that log2 is available, but there isn't a log() function that
            // also takes the base as a parameter (?)
        // well, use log(1024, x) = log(2, x) / 10, because the exponent of 1024 is 10 times smaller than the exponent of 2
        return pow(2.0f, 1.0f / (log2(float(capacity)) / 10.0f));
    }

        // TD: have some error handling in case no more memory is available;
            // also, probably all calls to copy more data into the object will have to fail
        // Note: this reallocation can occur pre-emptively, which is why idx < count is being used,
            // to only copy what is strictly necessary and because count is not guarantedd to be count == capacity
    void Reallocate() {
        uint64_t new_capacity = uint64_t(float(capacity) * Scaling());
//        T* new_array = new T[uint64_t(float(capacity) * Scaling())];  // (*?) compiler optimization: to compute an expression, first search for any previously
                                // defined memory instances and see what computation is needed to append to thos to obtain the needed expression; also, a lossless
                                // computation analysis would be needed (*?)
        T* new_array = new T[new_capacity];
        for(uint64_t idx {0}; idx < count; idx++) {
            new_array[idx] = array[idx];
        }

        // (*?) I thought I could safely call delete here, because the object does not get destructed; (*?) but this seems to cause an error,
            // so my hypothesis is that the compiler monitors all allocations done through the new allocator, per object, and will deallocate
            // all of them at the end of the object's lifetime (?); even if there are more allocations than the object has attributes (!?)
        // (*?) would a  smart pointer, unique_ptr<T>, also be referenced to the object or would it recognize the "unused attribute which has been replaced" (?)
//        delete[] array;
        array = new_array;

        capacity = new_capacity;
    }

    void DecideReallocation() {
        // (*?) preferable: start a new thread that (maybe locks the object and) checks [count == capacity - f_pre-emptive()],
            // and then calls Reallocate(); while this happens, all parallel calls to append data to the object will
            // be buffered in the ammount of memory reserved by the pre-emptive function (*?), so that the object can actually
            // still be used in the meantime; when the "queue" is empty and the new memory space has been allocated, a lock is applied
            // and the reallocation actually occurs [basically, changing the pointer and deleting the old pointer; copying the data
            // can actually be done in parallel, but there are still some restraints, such as the object not changing non-buffer data (*?)]
        // (*?) a write_lock, but with read_permissions ?

        if(count == capacity) {
            Reallocate();
        }
    }

    void Stack() {}
    void Push() {}

    void Pop() {}

    void Queue() {}
    void Enque() {}

    void Deque() {}

    void Peek_head() {}
    void Peek_start() {}

    void Peek_tail() {}
    void Peek_end() {}

    void Insert() {}
    void Add() {}

    void Append(T value) {
//        printf("called Append\n");
        DecideReallocation();
//        printf("DecideReallocation() returned\n");

        // (*?) template programming: if T is a pointer / reference type, then it needs to be introspected (more complex, this is an actual
            // "deep-copy"), or at least dereference once and copied (this would be a "hard-copy")
//        array[count++] = value; // for now it's just a "soft-copy"

        // (*?) actually, let's use a copy constructor, which is defined in the type, and which I will take care to be a "deep-copy constructor"
        array[count++] = T(value);
    }
    void Append(T* array, uint64_t count) {}
    void Append(ReallocatingArray<T> realloc_array) {}
    void Append(std::vector<T> vector_array) {}
    // and then other collection types...

    void Remove() {}
//    void Delete() {}   // (*?) language(-design) wise, this is very bad (!); it limits "freedom of expressivity / of wording" (*?)

    void Clear() {}

    void Empty() {}
    void Reset() {}

    void Fill() {}  // multiple elements simultaneously / in one call; it takes another list or array or etc. "collection type"

    void Merge() {} // (*?) it takes a variable length argument list, and merges them in the order specified in the call
    void Combine() {}

    void Decompose() {}
    void Separate() {}

    void Sublist() {}

    void Search() {
        // decision logic, select one of the multiple search implementations
    }

    void SearchAndReplace() {}

    void SearchAndDelete() {}
    void SearchAndRemove() {}

    void Sort() {
        // decision logic, select one of the multiple sorting implementations
    }

    // I needed to make sure I could introduce a line at a certain index, "pushing forward" the other lines
    void InsertInbetween() {}
    void Replace() {}

    void InsertSorted(T value) {

    }

    T& operator [] (uint64_t index) {
        // (*?) ~ "saturated addition" applied on the index;
        if (index > count) {
            if(count == 0) { return array[0]; }
            else { return array[count - 1]; }
        } else {
            return array[index];
        }
    }

    void operator += (T element) {
//        InsertSorted();   // (*?) well, I don't see how I could also signal it through some manner of "operator super-overloading"
                            // which of the implementations of += to select (simply append, or insert_sorted, or etc.)
//        printf("called +=\n");
        Append(element);
    }

    // (*!?) this kind of code needs to be easily writtable and conveniently turned on/off; it should be easily definable as
        // part of the type's program; it should even integrate with the compiler (!?), as a sort of testing at compile time which
        // gets redone only when some parts of the type change, and only after having identified what aspects of the test the changing
        // parts do affect (or it that computation is too complex, simply re-execute all the tests, as a sort of "Rebuild Project" in CodeBlocks)
    static void DebugTest() {
        // (*?) tests can be independent, or they can pass the (state of the) object and further processs it, etc. (~ chaining testing properties)
//        AppendOneByOne(verbose:true); // (*?) localy be aware of the identifiers for each argument's parameter
        AppendOneByOne(true);
    }

    static void AppendOneByOne(bool verbose) {
        ReallocatingArray<T> test_array;
        uint64_t last_capacity = test_array.capacity;
        uint64_t last_count = test_array.count;
        uint64_t total_allocated_size {sizeof(ReallocatingArray<T>) + sizeof(last_capacity * sizeof(T))};

        // (*?) a DebugPrint() which implicitly verifies for the context (whether it should be verbose or not, ~ "environment variables")
        DebugPrint(verbose, "init capacity: %lu, init count: %lu\n", last_capacity, last_count);
        printf("init capacity: %lu, init count: %lu\n", last_capacity, last_count);

        // (*?) or maybe instead log the data, and display it if requested
        Log("init capacity: %lu, init count: %lu\n", last_capacity, last_count);

        // (*?) timing analysis, verbose of state, check for data integrity, etc.
        for(uint64_t idx {0}; idx < 1024 * 1024 * 64; idx++) {
            test_array += int(idx);

            if(test_array.count == last_count) {
                printf("Unexpected state, the count didn't update properly; last_count: %lu, current_count: %lu\n", last_count, test_array.count);
                DebugPrint(verbose, "Unexpected state, the count didn't update properly; last_count: %lu, current_count: %lu\n", last_count, test_array.count); }

            if(last_capacity != test_array.capacity) {
                printf("Reallocation seems to have occured in the context of last_count: %lu, current_count: %lu\nlast_capacity: %lu, current_capacity: %lu\n",
                            last_count, test_array.count, last_capacity, test_array.capacity);
                DebugPrint(verbose, "Reallocation seems to have occured in the context of last_count: %lu, current_count: %lu\nlast_capacity: %lu, current_capacity: %lu\n",
                            last_count, test_array.count, last_capacity, test_array.capacity);
                last_capacity = test_array.capacity;
                total_allocated_size += sizeof(T) * last_capacity; }

            last_count = test_array.count;
        }

        printf("Total allocated bytes (including all the non-deallocated arrays when reallocating): %luB, %luKB, %luMB, %luGB\n",
                total_allocated_size, total_allocated_size / 1024, total_allocated_size / (1024 * 1024), total_allocated_size / (1024 * 1024 * 1024));
        printf("The size of the current arary is %luB, %luKB, %luMB, %luGB\n",
                sizeof(T) * last_capacity, (sizeof(T) * last_capacity) / 1024, (sizeof(T) * last_capacity) / (1024 * 1024), (sizeof(T) * last_capacity) / (1024 * 1024 * 1024));
    }
};

template<typename T>
struct Stack {
    // (*?) the substrate can be: reallocating array, fixed-size array, linked list, etc.
};

template<typename T>
struct Heap {

};

// (*?) there is nothing to be stored in a vertex, except its very existence; but, for now, let's store
    // the count of neighbours that it has (or "edges that contain it")
struct Vertex {
    uint64_t count_neighbours {};

    Vertex() { }
    Vertex(Vertex const & vertex) { // again, a deep-copy constructor; not much "depth" in this type though
                                    // (*?) is this effectively an "integral type", even though it is a struct ? when does a type
                                        // start having "depth" ? when it contains pointers ? and then, if the type to which they contain pointers
                                        // also contains pointers ?
                                     // (*!?) then, what happens if one tries to deep-copy a list by using deep-copy constructors of the nodes ? wouldn't
                                        // that copy the list multiple times ? or if the list is cyclic, it would turn into a non-halting program (!?)
                                    // (*?) it thus becomes apparent that deep-copy procedures require ~ "cycle detection"; also, there might also be feasible
                                        // to have mechanisms for specifying the "depth" to which a deep-copy should occur (whether it be an explicit "depth",
                                        // or some data that acts as a reference, or some other property)
        this->count_neighbours = vertex.count_neighbours;
    }
};

// (*?) an edge type needs to contain two vertices; it could also contain a "cost" or "weight"
struct Edge {
    uint64_t vertexA {};
    uint64_t vertexB {};
    double cost {};

    // (*?) this created a problem as it is (a) "non-copyable (member attribute)"
//    double& weight = cost;  // (*?) data member, aliasing (?); there could be verification based on which aliasing is being used
                            // and the consistency of using it correctly, according to context (!?), using the type system
    Edge() {}
    Edge(uint64_t A, uint64_t B, uint64_t cost = 0) : vertexA(A), vertexB(B), cost(cost) {}
    Edge(Edge const & edge) {   // (*?) is this the copy constructor ? let's make it a deep-copy constructor
        this->vertexA = edge.vertexA;
        this->vertexB = edge.vertexB;
        this->cost = edge.cost;
    }
};

struct Graph {
    ReallocatingArray<Vertex> vertices {};

    ReallocatingArray<Edge> edges {};

    Graph() {}

    uint64_t AddVertex() {
        // return the index of the new vertex
//        vertices += vertices.count++; // (*?) this would have been a mistake; could the type system catch this, if there was some specification of
            // ~ "intended usage" (?)
        vertices += Vertex(); // because the += operator implicitly handles the increase of this.count, internally
//        printf("ctor returned\n");
        return vertices.count - 1;  // do not use the array, that would require another memory query; instead, this.count is already in the cache (*?), or is it (?)
                                    // the complication lies in the fact that += actually can cause a "cache disturbance", when it reallocates the internal array
    }

    void AddEdge(uint64_t vertexA, uint64_t vertexB, double cost = 0) {
        // (*?) what if an edge already exists ? well, that is not a problem, it's not excluded that multiple paths can exist between two vertices; my actual
            // problem is how to generalize this dts to "naturaly" handle both undirected and directed graphs; handling "multi-edge graphs" seems simpler, because
            // one effectively just adds them and that's that; the problem with directed vs undirected is the logic actually, there would be an additional boolean
            // for the 2-state attribute, and then all the logic of the implementation would have to accomodate for the two cases (*?), which is exactly what I'd like
            // not to have to do
        edges += Edge(vertexA, vertexB, cost);

    }

    static void DebugTest() {
        std::mt19937 gen;
        uint64_t n = (gen() + 5) % 20;
        printf("Graph scale: %lu nodes.\n", n);

        Graph graph;
//        printf("Graph constructed.\n");

        for(uint64_t idx {0}; idx < n; idx++) {
            printf("Added vertex %lu.\n", graph.AddVertex());
        }

        uint64_t num_edges = gen() % 57;
        printf("Edges number: %lu.\n", num_edges);

        for(uint64_t idx {0}; idx < num_edges; idx++) {
            uint64_t A = gen() % n;
            uint64_t B = gen() % n;
            if(B < A) { A ^= B ^= A ^= B; }

            double cost = gen() % 1000;

            printf("Edge between vertices %lu and %lu, with cost %lf.\n", A, B, cost);

            graph.AddEdge(A, B, cost);
        }
    }
};

#endif // LABWORK_HPP_INCLUDED
