#include <iostream>
#include <gtest/gtest.h>
#include "bst.h"

int main(int argc, char **argv)
{
    if (true) // make false to run unit-tests
    {
        // BST::Node n1{},n2{};
        // BST::Node n3{3,&n1,&n2};
        // std::cout << n3 << std::endl;
        // std::cout << n2 << std::endl;
        // std::cout << n1 << std::endl;
        // std::cout << (2 <= n2) << std::endl;

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