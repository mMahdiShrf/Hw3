#ifndef BST_H
#define BST_H

#include <iostream>
#include <compare>
#include <functional>
#include <iomanip>
#include <string>

class BST
{
public:
    class Node;
    BST(int root_value);
    BST();
    BST(const BST& bst);
    BST(BST&& bst);
    ~BST();
    Node*& get_root();
    void bfs(std::function<void(Node*& node)> func) const;
    size_t length() const;
    bool add_node(int value);
    Node** find_node(int value);
    Node** find_parrent(int value);
    Node** find_successor(int value);
    bool delete_node(int value);
    friend std::ostream& operator<<(std::ostream& os,const  BST& bst);
    const BST& operator++ () const;
    const BST operator++(int);
    //BST& operator=(const BST& bst);
    BST& operator=(BST&& bst);

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
    std::partial_ordering operator <=> (const int _value) const {return value <=> _value;}
    bool operator==(const int _value) const { return _value == value;}

    int value;
    Node* left;
    Node* right;
};




#endif //BST_H