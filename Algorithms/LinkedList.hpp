#ifndef LINKEDLIST_HPP_INCLUDED
#define LINKEDLIST_HPP_INCLUDED

/// TD
/*
    "linked arrays" / "linked lists of arrays" (many possible variants)
    type-templated, homogeneous-type array list
    size- and type- templated, homogeneous-type arary list
    heterogeneous size, homogeneous type array list
    heterogeneous (size, type) array list
*/
// struct /* Container */ /* Master */ /* Handler */ /* Encapsulate */ _RawLinkedList


#define count_type uint32_t
#define sizeof(cacheline) 64

struct RawSinglyLinkedNode {
    // non-allocating constructor -> it contains pointers, but they are just
        // ~ "soft references" and not ~ "hard-references", so there is nothing
        // to delete in the destructor
    RawSinglyLinkedNode* next {};

};

struct RawSinglyLinkedList {
    RawSinglyLinkedNode* head {};
    count_type length;

    // any destructor can technically still receive
        // parameters through the struct's attributes
    ~RawSinglyLinkedList() {
        PopNodes(length);
    }

    RawSinglyLinkedNode* GetLastNode() {
        RawSinglyLinkedNode* last= head;
        while(last->next != nullptr) last = last->next;
        return last;
    }

    void AppendNodes(count_type howMany) {
        RawSinglyLinkedNode* current = GetLastNode();

        while(howMany-- != 0) {
            current->next = new RawSinglyLinkedNode();
            length++;
            current = current->next;
        }
    }

    void UnappendNodes /* PopNodes */ (count_type howMany) {
        RawSinglyLinkedNode* current = GetLastNode();

        while(howMany-- != 0 && length != 0) {
            delete current;
            length--;
            current = GetLastNode();
        }
    }

    void PopNodes(count_type howMany) {
        UnappendNodes(howMany);
    }

    count_type GetSizeInBytes() {
        return sizeof(RawSinglyLinkedList) + length * sizeof(RawSinglyLinkedNode);
    }
};

    // this might be a definition internal to the corresponding list struct,
    // but at this point it's of little relevance; all the effect it has is
    // to hide an identifier, literally just that (?!)
template<typename T>
struct ArrayNode {
    T array[8 * sizeof(cacheline)] {};  // arbitrary choice, and also, doesn't generalize
        // to non0cacheline architectures of computers, neither dynamically querries the
        // processor for its cacheline size
    ArrayNode<T>* next;

    T& operator[] (count_type index) {
        return array[index];
    }
};

template<typename T>
struct ArrayList {
    ArrayNode<T>* head {};
    count_type length {};

    ArrayNode<T>& operator[] (count_type index) {
        ArrayNode<T>* current = head;

        while(current->next != nullptr && index-- != 0) {
            current = current->next;
        }

        return current; // both value to reference and pointer to reference seem to work
                // but that is possibly problematic, or ambiguous ?
    }
};

#endif // LINKEDLIST_HPP_INCLUDED
