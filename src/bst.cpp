#include "bst.h"



BST::Node::Node(int value, Node* left, Node* right) // Node constructor
{
    this->value = value;
    this->left = left;
    this->right = right;
}

BST::Node::Node() // Node defualt constructor
{
    this->value = static_cast<int>(NULL);
    this->left = nullptr;
    this->right = nullptr;
}

BST::Node::Node(const Node& node) // Node copy constructor
{
    this->value = node.value;
    this->left = node.left;
    this->right = node.right;
}
BST::BST() // BST defualt constructor
{
    root = nullptr;
}
// constructor with variable number of parameters :
BST::BST(std::initializer_list<int> values) : BST()
{   
    for(auto value:values)
        this->add_node(value);
}

BST::BST(const BST& bst) // copy constructor
{   
    // recursive lambda function definition
    std::function<Node*(Node* node)> 
    copy = [&copy](Node* node) -> Node*
    {   
        if(node)
        {   
            Node* new_root = {new Node}; // dynamic allocating 
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

BST::BST(BST&& bst): // move constructor
    root{std::move(bst.root)}
{
    bst.root = nullptr;
}
// given destructor :
BST::~BST()
{
	std::vector<Node*> nodes;
 	bfs([&nodes](BST::Node*& node){nodes.push_back(node);});
 	for(auto& node: nodes)
 		delete node;
}
// std::cout for Node in one line :
std::ostream& operator<<(std::ostream& os, const BST::Node& node)
{   
    // all width seted due to std::cout for BST format
    // in given format the address has 8 byte but in my 
    // coputer they have 6 or sometime 7 bytes and i don't
    // know the reason :) so i'm sorry for possible off by one
    // happening in width
    os << &node ;
    os << std::setw(16) <<  "=> value:" << node.value ;
    if (node.value < 10) // one digit value
        os << std::setw(14) << "left:" << node.left;
    else
        os << std::setw(13) << "left:" << node.left;
    if (node.left==nullptr) // left nullptr 
        os << std::setw(20) <<"right:" << node.right  << std::endl;
    else
        os << std::setw(12) <<"right:" << node.right  << std::endl;
    return os;
}

std::ostream& operator<<(std::ostream& os, const BST& bst)
{   
    // std::cout for BST with lambda function and bfs memberfunction
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

const BST& BST::operator++() const // ++BST
{   
    // implementation by usege of bfs & lambda function
    std::function<void(Node* node)> 
    pluseOne = [](Node* node)
    {
        node->value += 1;
    };
    this->bfs(pluseOne);
    return *this;
}

const BST BST::operator++(int) // BST++
{   
    // implementation by usege of bfs & copy constructor
    BST temp {*this};
    ++*this;
    return temp;
}

BST& BST::operator=(BST&& bst) // move version
{
    delete[] root;
    root = bst.root;
    bst.root = nullptr;
    return *this;
}

BST& BST::operator=(const BST& bst) // copy version
{
    if (this == &bst)
        return *this;
    delete[] root;
    // i tried not to duplicate lambda 
    // function in copy constructor 
    // so i used dynamic allocation
    BST* bb{new BST{bst}}; 
    root = bb->root;
    return *this;
}

BST::Node*& BST::get_root() 
{   
    return root;
}

void BST::bfs(std::function<void(BST::Node*& node)> func) const 
{   
    // recursive lambda function to determine height of the tree
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
    // apply bfs allgoritem by height & recursive lambda function
    for(size_t level{1}; level <= tree_height ; level++)
    {   
        std::function<void(size_t level, Node* root)> 
        applyFunc=[&](size_t level, Node* root)->void
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
    // simple revursive lambda function
    // to determine the length of the tree
    // for making it simple tree_length
    // defined out of function then pass to it 
    // by refrence
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
    if (root == nullptr) // empty tree
        {
            root = new Node{value};
            return true;
        }
    bool flag{true}; // for output of the function
    Node* address{new Node {value}};
    // find suitable place for new node
    // then place it by assign it's address 
    // to the tree
    std::function<void(Node* &root,int value)>
    add=[&](Node* &root, int value)->void
    {
        if (value < root->value ) // new node must be in left subtree
        {
            if (root->left != nullptr) // we must go deeper in tree
                add(root->left, value); 
            else
            {   
                root->left = address; // suitable place have found
                return;
            }
        }
        else if (value > root->value) // new node must be in right subtree
        {
            if (root->right != nullptr) // we must go deeper in tree
                add(root->right, value);
            else
            {   
                root->right = address; // suitable place have found
                return;
            }
        }
        else // nodde with this value already exist
        {
            flag = false;
            return;
        }
            
    };
    add(root, value);
    // determining the output
    if (flag) 
        return true;
    else 
        return false;
}

BST::Node** BST::find_node(int value)
{       
    if (root == nullptr) return nullptr; // epmty tree
    std::function<Node**(Node* root,int value,Node** ptr)> 
    find=[&find](Node* root, int value,Node** ptr)->Node**
    {   
        if (value == root->value) // node have found
            return ptr;
        if (value < root->value )
            if (root->left == nullptr) // node doesn't exist
                return nullptr;
            else
                return find(root->left,value,&root->left); // search in left subtree
        else
            if (root->right == nullptr)
                return nullptr; // node does'nt exist
            else
                return find(root->right,value,&root->right); // search in right subtree
    };
    // passing root by refrence so don't get
    // to "returning refrence to local variable" situation
    return find(root,value,&root);
}

BST::Node** BST::find_parrent(int value)
{
    if (root == nullptr || find_node(value) == nullptr) // no parrent exists of the node does'nt exist
        return nullptr;
    std::function<Node**(Node* root,int value,Node** ptr)> 
    find=[&find](Node* root, int value,Node** ptr)->Node**
    {
        if (value < root->value )
            if(root->left->value == value) 
                return ptr;
            else
                return find(root->left,value,&root->left); // go deeper in left subtree to search
        else if (value > root->value)
            if(root->right->value == value)
                return ptr;
            else
                return find(root->left,value,&root->left); // go deeper in right subtree to search
        else
            return ptr; // if tree has only one node 
    };
    // passing root by refrence so don't get
    // to "returning refrence to local variable" situation
    return find(root,value,&root);
}

BST::Node** BST::find_successor(int value)
{   
    if (root == nullptr || find_node(value) == nullptr)// no succeesor exists of the node does'nt exist
        return nullptr;
    // it can be done by lampda function like 
    // like previous member functions too
    Node* node{ *find_node(value)}; // node defined to prevent repeatend call of find_node
    if (node->left != nullptr && node->right != nullptr)
        return find_successor(node->left->value);
    else if (node->right != nullptr)
        return find_successor(node->right->value);
    else if(node->left != nullptr)
        return find_successor(node->left->value);
    else
        return find_node(node->value); // can't return &node so called find_node again
}

bool BST::delete_node(int value)
{   
    if (root == nullptr || find_node(value) == nullptr) // can't delete what it does'nt exist
        return false;
    Node*& node{ (*find_node(value)) };
    if(node->left == nullptr && node->right == nullptr) // no child situation
        {   
            free(node); // free memory which node point too
            node=nullptr; 
            return true;
        }
        
    else if (node->left == nullptr) // only right child situation
    {   
        node = (node->right);
        return true;
    }
    else if (node->right == nullptr) // only left child situation
    {   
        node = (node->left);
        return true;
    }
    else
    {   
        Node* max_node{node->left}; // to store node with biggest value in left subtree
        while( max_node != nullptr && max_node->right != nullptr)
            max_node = max_node->right;
        int max_val{max_node->value}; // to store value of max_node so recursive call of delete does'nt change it
        delete_node(max_node->value);
        node->value = max_val;
        return true;
    }
}
