#include <iostream>
#include <gtest/gtest.h>
#include "bst.h"

void f(BST::Node* node){ node->value+=5;}

int main(int argc, char **argv)
{
    if (true) // make false to run unit-tests
    {
        BST::Node n1{3};
        BST::Node n2 {4,&n1};
        BST::Node n3{6};
        BST::Node n4{5,&n2,&n3};
        BST::Node n5{8,&n4};
        BST bb{&n5};
        std::cout << bb.add_node(7) << std::endl;
        std::cout << bb.delete_node(5) << std::endl;
        std::cout<< bb.find_node(5) << std::endl;
        std::cout<< bb.get_root()->left->right->value << std::endl;
        std::cout << bb << std::endl;
        
    }
    else
    {
        ::testing::InitGoogleTest(&argc, argv);
        std::cout << "RUNNING TESTS ..." << std::endl;
        int ret{RUN_ALL_TESTS()};
        if (!ret)
            std::cout << "<<<SUCCESS>>>" << std::endl;
        else
            std::cout << "FAILED" << std::endl;
    }
    return 0;   
}