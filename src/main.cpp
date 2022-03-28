#include <iostream>
#include <gtest/gtest.h>
#include "bst.h"



int main(int argc, char **argv)
{
    if (false) // make false to run unit-tests
    {
        BST bst{};
        bst.add_node(25);
        bst.add_node(10);
        bst.add_node(50);
        bst.add_node(53);
        bst.add_node(15);
        bst.add_node(7);
        BST::Node** node{bst.find_node(10)};
        //BST& bobo {bb};
        // std::cout << bb.add_node(7) << std::endl;
        // std::cout << bb.delete_node(5) << std::endl;
         std::cout<< (*node)->right->value << std::endl;
        // std::cout<< bb.get_root()->left->right->value << std::endl;
        // BST bobo {bb};
        // bobo = ++bb;
        //std::cout << bobo << std::endl;
        
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