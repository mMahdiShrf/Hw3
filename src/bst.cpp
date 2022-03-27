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
BST::BST()
{
    root = nullptr;
}

BST::BST(const BST& bst)
{   
    
    std::function<Node*(Node* node)> 
    copy = [&copy](Node* node) -> Node*
    {   
        if(node)
        {   
            Node* new_root = {new Node};
            new_root->value = node->value;
            std::cout << new_root->value << std::endl;
            new_root->left=copy(node->left);
            new_root->right=copy(node->right);
            return new_root;
        }
        else
            return NULL;
    };
    root =copy(bst.root);
}

BST::BST(int root_value)
{
    root = new Node {root_value};
}

BST::BST(BST&& bst):
    root{std::move(bst.root)}
{
}

 BST::~BST()
 {
 	std::vector<Node*> nodes;
 	bfs([&nodes](BST::Node*& node){nodes.push_back(node);});
 	for(auto& node: nodes)
 		delete node;
 }

std::ostream& operator<<(std::ostream& os, const BST::Node& node)
{
    os << &node ;
    os << std::setw(16) <<  "=> value:" << node.value ;
    os << std::setw(13) << "left:" << node.left;
    if (node.left==nullptr)
        os << std::setw(20) <<"right:" << node.right  << std::endl;
    else
        os << std::setw(12) <<"right:" << node.right  << std::endl;
    return os;
}

std::ostream& operator<<(std::ostream& os, const BST& bst)
{
    std::function<void(BST::Node*)> printer = [](BST::Node* node)
    {
        std::cout << *node ;
    };
    os << std::string(76, '*') << std::endl;
    bst.bfs(printer);
    os << "binary search tree size: " << bst.length() << std::endl;
    os << std::string(76, '*') << std::endl;
    return os;
}

BST::Node*& BST::get_root() 
{   
    return root;
}

void BST::bfs(std::function<void(BST::Node*& node)> func) const
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

size_t BST::length() const
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

bool BST::delete_node(int value)
{   
    if (root == nullptr || find_node(value) == nullptr)
        return false;
    Node* node{ (*find_node(value)) };
    if(node->left == nullptr && node->right == nullptr)
        {   
            *node = Node{};
            return true;
        }
        
    else if (node->left == nullptr)
    {   
        *node = *(node->right);
        return true;
    }
    else if (node->right == nullptr)
    {   
        *node = *(node->left);
        return true;
    }
    else
    {   
        Node* min_node{node->right};
        while( min_node != nullptr && min_node->left != nullptr)
            min_node = min_node->left;
        int min_val{min_node->value};
        delete_node(min_node->value);
        //std::cout<< root->left->right->value << std::endl;
        //std::cout << min_val << std::endl;
        node->value = min_val;
        return true;
    }
}

const BST& BST::operator++() const
{
    std::function<void(Node* node)> 
    pluseOne = [](Node* node)
    {
        node->value += 1;
    };
    this->bfs(pluseOne);
    return *this;
}

const BST BST::operator++(int)
{
    BST temp {*this};
    ++*this;
    return temp;
}


