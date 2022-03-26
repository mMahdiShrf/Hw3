#include "bst.h"


BST::Node::Node(int value, Node* left, Node* right)
{
    this->value = value;
    this->left = left;
    this->right = right;
}

BST::Node::Node()
{
    this->value = static_cast<int>(NULL);
    this->left = nullptr;
    this->right = nullptr;
}

BST::Node::Node(const Node& node)
{
    this->value = node.value;
    this->left = node.left;
    this->right = node.right;
}

std::ostream& operator<<(std::ostream& os, const BST::Node& node)
{
    os << "node's address: " << &node << " ** ** ";
    os << "node's left child address: " << node.left << " ** ** ";
    os << "node's right child address: " << node.right << " ** ** ";
    os << "node's value: " << node.value;
    return os;
}



