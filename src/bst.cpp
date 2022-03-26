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
    os << "node's address: " << &node << "  ****  ";
    os << "node's left child address: " << node.left << "  ****  ";
    os << "node's right child address: " << node.right << "  ****  ";
    os << "node's value: " << node.value;
    return os;
}

BST::Node*& BST::get_root()
{
    return root;
}

void BST::bfs(std::function<void(Node*& node)> func)
{
    std::function<size_t(Node*)> height = [&](Node* root)->size_t
    {
        if (root == nullptr)
            return 0;
        else
        {
            size_t left_height {height(root->left)};
            size_t right_height {height(root->right)};
        
        if (left_height > right_height)
            return (left_height+1);
        else
            return (right_height+1);
        }
    };
    size_t tree_height{height(root)};
    //std::cout << tree_height << std::endl;
    for(size_t level{1}; level <= tree_height -1; level++)
    {   
        std::function<void(size_t level, Node* root)> applyFunc=[&](size_t level, Node* root)->void
        {   
            if (root == nullptr)
                return;
            if (level == 1)
                func(root);
            else if (level > 1) 
            {
                applyFunc(level - 1, root->left);
                applyFunc(level - 1, root->right);
            }
        };
        applyFunc(level, root);
    }
}

BST::BST(Node* _root):root{_root}{}


