#include "graph/node.hpp"



Node::Node():id(Node::COUNTER){
    Node::COUNTER++;
};

void Node::attachNode(Node *node){
    //billateral connection
    node->attachNode(this);
    nodes.push_back(node);
}