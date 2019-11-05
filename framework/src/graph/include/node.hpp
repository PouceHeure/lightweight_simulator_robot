#pragma once 
#include <vector>

class Node {
    private: 
        static int COUNTER;
        int id;

        std::vector<Node*> nodes;

    public:
        Node();
        void attachNode(Node* node);
};