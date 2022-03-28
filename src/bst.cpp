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


BST::BST(std::initializer_list<int> values) : BST()
{   
    for(auto value:values)
        this->add_node(value);
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
            new_root->left=copy(node->left);
            new_root->right=copy(node->right);
            return new_root;
        }
        else
            return NULL;
    };
    root =copy(bst.root);
}

BST::BST(BST&& bst):
    root{std::move(bst.root)}
{
    bst.root = nullptr;
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
    if (node.value < 10)
        os << std::setw(14) << "left:" << node.left;
    else
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
    size_t tree_length{};
    std::function<void(Node* root)> length=[&](Node* root)->void
    {   
        if (root)
        {   
            tree_length++;
            length(root->right);
            length(root->left);
        }
        else
            return;
    };
    length(root);
    return tree_length;
}

bool BST::add_node(int value)
{   
    if (root == nullptr)
        {
            root = new Node{value};
            return true;
        }
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
    //Node** ptr = new Node*;
    if (root == nullptr) return nullptr;
    std::function<Node**(Node* root,int value,Node** ptr)> 
    find=[&find](Node* root, int value,Node** ptr)->Node**
    {   
        if (value == root->value)
        {
            return ptr;
        }
        if (value < root->value )
        {
            if (root->left == nullptr)
            {
                
                return nullptr;
            }
            else
                return find(root->left,value,&root->left);
        }
        else
        {
            if (root->right == nullptr)
            {
                
                return nullptr;
            }
            else
                return find(root->right,value,&root->right);
        }
    };
    return find(root,value,&root);
}

BST::Node** BST::find_parrent(int value)
{
    if (root == nullptr || find_node(value) == nullptr)
        return nullptr;
    std::function<Node**(Node* root,int value,Node** ptr)> 
    find=[&find](Node* root, int value,Node** ptr)->Node**
    {
        if (value < root->value )
            if(root->left->value == value)
                return ptr;
            else
                return find(root->left,value,&root->left);
        else if (value > root->value)
            if(root->right->value == value)
                return ptr;
            else
                return find(root->left,value,&root->left);
        else
            return ptr;
    };
    return find(root,value,&root);
}

BST::Node** BST::find_successor(int value)
{   
    if (root == nullptr || find_node(value) == nullptr)
        return nullptr;
    Node* node{ *find_node(value)};
    if (node->left != nullptr)
        return find_successor(node->left->value);
    else if (node->right != nullptr)
        return find_successor(node->right->value);
    else if(node->left != nullptr && node->right != nullptr)
        return find_successor(node->left->value);
    else
        return find_node(node->value);
}

bool BST::delete_node(int value)
{   
    if (root == nullptr || find_node(value) == nullptr)
        return false;
    Node*& node{ (*find_node(value)) };
    if(node->left == nullptr && node->right == nullptr)
        {   
            free(node);
            node=nullptr;
            return true;
        }
        
    else if (node->left == nullptr)
    {   
        node = (node->right);
        return true;
    }
    else if (node->right == nullptr)
    {   
        node = (node->left);
        return true;
    }
    else
    {   
        Node* max_node{node->left};
        while( max_node != nullptr && max_node->right != nullptr)
            max_node = max_node->right;
        int max_val{max_node->value};
        delete_node(max_node->value);
        //std::cout<< root->left->right->value << std::endl;
        //std::cout << min_val << std::endl;
        node->value = max_val;
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

BST& BST::operator=(BST&& bst)
{
    delete[] root;
    root = bst.root;
    bst.root = nullptr;
    return *this;
}

BST& BST::operator=(const BST& bst)
{
    if (this == &bst)
        return *this;
    delete[] root;
    std::function<Node*(Node* node)> 
    copy = [&copy](Node* node) -> Node*
    {   
        if(node)
        {   
            Node* new_root = {new Node};
            new_root->value = node->value;
            new_root->left=copy(node->left);
            new_root->right=copy(node->right);
            return new_root;
        }
        else
            return NULL;
    };
    root =copy(bst.root);
    return *this;
}