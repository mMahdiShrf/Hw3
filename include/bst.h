#ifndef BST_H
#define BST_H

#include <iostream>
#include <compare>
#include <functional>
#include <iomanip>
#include <string>
#include <initializer_list>

class BST
{
public:
    class Node; // Node decleration
    BST();  // default constructor
    BST(const BST& bst); // copy constructor
    BST(BST&& bst); // move constructor
    ~BST(); // destructor
    BST(std::initializer_list<int> values);
    friend std::ostream& operator<<(std::ostream& os,const  BST& bst); // std::cout << BST
    const BST& operator++ () const; // ++BST
    const BST operator++(int); // BST++
    BST& operator=(const BST& bst); // copy version
    BST& operator=(BST&& bst); // move version
    Node*& get_root();
    void bfs(std::function<void(Node*& node)> func) const;
    size_t length() const;
    bool add_node(int value);
    Node** find_node(int value);
    Node** find_parrent(int value);
    Node** find_successor(int value);
    bool delete_node(int value);
    
private:
    Node* root;
};

class BST::Node // Node definition
{
public:
    Node(int value, Node* left=nullptr, Node* right=nullptr);
    Node();
    Node(const Node& node);
    friend std::ostream& operator<<(std::ostream& os, const Node& node); // std::cout << Node
    // all kinds of comparing :
    std::partial_ordering operator <=> (const int _value) const {return value <=> _value;}
    bool operator==(const int _value) const { return _value == value;}

    int value;
    Node* left;
    Node* right;
};




#endif //BST_H