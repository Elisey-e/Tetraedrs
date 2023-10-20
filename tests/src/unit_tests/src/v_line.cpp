#include <gtest/gtest.h>

#include "v_line.hpp"
#include "cmath"

TEST (V_Line, Functions)
{
    V_Line <double> l0{{0, 0, 0}, {0, 0, 0}};
    V_Line <double> l1{{0, 0, 0}, {1.0, 1.0, 1.0}};
    V_Line <double> l2{{0, 0, 0}, {-1.0, -2.0, -3.0}};
    V_Line <double> l3{{0, 0, 0}, {1.0000001, 1.0000001, 1.0000001}};
    V_Line <double> l4{{0, 0, 0}, {0.0, 0.0, 0.0}};

    V_Line <double> l5{{1.0, 1.0, 1.0}, {0, 0, 0}};
    V_Line <double> l6{{-1.0, -2.0, -3.0}, {0, 0, 0}};
    V_Line <double> l7{{1.0000001, 1.0000001, 1.0000001}, {0, 0, 0}};
    V_Line <double> l8{{0.0, 0.0, 0.0}, {0, 0, 0}};
    V_Line <double> l9{{-1.0, -1.0, -1.0}, {0, 0, 0}};

    EXPECT_TRUE(l1.first() == l2.first());
    EXPECT_TRUE(l1.last() != l3.last());
    EXPECT_TRUE(l1.first() == l1.first());
    EXPECT_FALSE(l1.first() == l2.last());
    EXPECT_FALSE(l3.first() != l4.last());

    EXPECT_TRUE(l0 == l0);
    EXPECT_TRUE(l5 == l5);
    EXPECT_TRUE(l7 == l7);

    EXPECT_TRUE(l0 + l1 == l1);
    EXPECT_TRUE(l0 - l1 != l9);
    EXPECT_FALSE(l0 + l3 == l1);
    EXPECT_TRUE(l0 - l1 + l1 == l0);

    EXPECT_TRUE(l0.calc_len().len() == 0);
    EXPECT_TRUE(l1.calc_len().len() == std::sqrt(3));
    EXPECT_TRUE(l2.calc_len().len() == std::sqrt(14));
    EXPECT_TRUE(l4.calc_len().len() == 0);
    EXPECT_TRUE(l5.calc_len().len() == std::sqrt(3));
    EXPECT_TRUE(l6.calc_len().len() == std::sqrt(14));
    
    
}
