#ifndef BST_H
#define BST_H

#include <iostream>
#include <compare>
#include <functional>

class BST
{
public:
    class Node;
    BST(Node* _root);
    Node*& get_root();
    void bfs(std::function<void(Node*& node)> func);
    size_t length();
    bool add_node(int value);
    Node** find_node(int value);
    Node** find_parrent(int value);
    Node** find_successor(int value);
    // bool delete_node(int value);

private:

    Node* root;
};

class BST::Node
{
public:
    Node(int value, Node* left=nullptr, Node* right=nullptr);
    Node();
    Node(const Node& node);
    friend std::ostream& operator<<(std::ostream& os, const Node& node);
    std::partial_ordering operator <=> (const int _value) const {return _value <=> value;}
    bool operator==(const int _value) const { return _value == value;}

    int value;
    Node* left;
    Node* right;
};




#endif //BST_H