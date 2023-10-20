#include <gtest/gtest.h>

#include "point.hpp"

TEST (Points, Equality)
{

    Point <double> pt_1     {1.0, 2.0, 3.0};
    Point <double> pt_2     {2.0, 3.0, 1.0};
    Point <double> pt_3     {1.000001, 2.000002, 3.000003};
    Point <double> pt_sum   {3.0, 5.0, 4.0};
    Point <double> pt_dif   {1.0, 1.0, -2.0};

    EXPECT_TRUE (pt_1.x() == 1.0);
    EXPECT_TRUE (pt_1.y() == 2.0);
    EXPECT_TRUE (pt_1.z() == 3.0);
    EXPECT_TRUE (pt_dif.z() == -2.0);
    EXPECT_TRUE (pt_1.x() == pt_1.x());
    EXPECT_TRUE (pt_3.x() == pt_3.x());

    EXPECT_FALSE (pt_1.x() == pt_3.x());
    EXPECT_FALSE (pt_1.y() == pt_1.x());
    EXPECT_FALSE (pt_1.z() == pt_3.z());
}

TEST (Points, Inequality)
{
    Point <double> pt_1     {1.0, 2.0, 3.0};
    Point <double> pt_2     {2.0, 3.0, 1.0};
    Point <double> pt_3     {1.000001, 2.000002, 3.000003};
    Point <double> pt_sum   {3.0, 5.0, 4.0};
    Point <double> pt_dif   {1.0, 1.0, -2.0};

    EXPECT_FALSE (pt_1.x() != 1.0);
    EXPECT_FALSE (pt_1.y() != 2.0);
    EXPECT_FALSE (pt_1.z() != 3.0);
    EXPECT_FALSE (pt_dif.z() != -2.0);
    EXPECT_FALSE (pt_1.x() != pt_1.x());
    EXPECT_FALSE (pt_3.x() != pt_3.x());

    EXPECT_TRUE (pt_1.x() != pt_3.x());
    EXPECT_TRUE (pt_1.y() != pt_1.x());
    EXPECT_TRUE (pt_1.z() != pt_3.z());
}

TEST (Points, Summary_ans_difference)
{
    Point <double> pt_1     {1.0, 2.0, 3.0};
    Point <double> pt_2     {2.0, 3.0, 1.0};
    Point <double> pt_sum   {3.0, 5.0, 4.0};
    Point <double> pt_dif   {1.0, 1.0, -2.0};

    EXPECT_TRUE (pt_1 + pt_2 == pt_sum);
    EXPECT_TRUE (pt_2 - pt_1 == pt_dif);

}
