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
    for(size_t level{1}; level <= tree_height ; level++)
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

size_t BST::length()
{
    std::function<size_t(Node* root)> length=[&length](Node* root)->size_t
    {
        if (root->left != nullptr && root->right != nullptr)
            return (2 + length(root->left) + length(root->right));
        else if (root->left != nullptr)
            return (1 + length(root->left));
        else if (root->right != nullptr)
            return (1 + length(root->right)); 
        else
            return 0;
    };
    return length(root) + 1;
}

bool BST::add_node(int value)
{
    if (root == nullptr)
        return false;
    bool flag{true};
    Node* address{new Node {value}};
    std::function<void(Node* &root,int value)> add=[&](Node* &root, int value)->void
    {
        if (value < root->value )
        {
            if (root->left != nullptr)
                add(root->left, value); 
            else
            {   
                root->left = address;
                return;
            }
        }
        else if (value > root->value)
        {
            if (root->right != nullptr)
                add(root->right, value);
            else
            {   
                root->right = address;
                return;
            }
        }
        else
        {
            flag = false;
            return;
        }
            
    };
    add(root, value);
    if (flag) 
        return true;
    else 
        return false;
}

BST::Node** BST::find_node(int value)
{   
    Node** address{nullptr};
    if (root == nullptr) return nullptr;
    std::function<void(Node* root,int value)> 
    find=[&find,&address](Node* root, int value)->void
    {
        if (value < root->value )
            if (root->left == nullptr)
                address = nullptr;
            else
                find(root->left,value);
        else if (value > root->value)
            if (root->right == nullptr)
                address = nullptr;
            else
                find(root->right,value);
        else
            address = &root;
    };
    find(root,value);
    return address;
}

BST::Node** BST::find_parrent(int value)
{
    Node** address{nullptr};
    if (root == nullptr || find_node(value) == nullptr)
        return nullptr;
    std::function<void(Node* root,int value)> 
    find=[&find,&address](Node* root, int value)->void
    {
        if (value < root->value )
            if(root->left->value == value)
                address = &root;
            else
                find(root->left,value);
        else if (value > root->value)
            if(root->right->value == value)
                address = &root;
            else
                find(root->right,value);
        else
            address = &root;
    };
    find(root,value);
    return address;
}

BST::Node** BST::find_successor(int value)
{   
    Node** address{};
    if (root == nullptr || find_node(value) == nullptr)
        return nullptr;
    Node* node{ *find_node(value)};
    if (node->left != nullptr)
        address = &(node->left);
    else if (node->right != nullptr)
        address = &(node->right);
    else
        address = nullptr;
    return address;
}