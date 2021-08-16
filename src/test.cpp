#include <gtest/gtest.h>
#include "libmygraph.h"
#include "vertexBuffer.h"
#include "indexBuffer.h"

TEST(BaseTest, BasicAssertions)
{
    Graph g;
    EXPECT_STRNE("sdf", "sdfwe");
    EXPECT_EQ(3*4,12);
    EXPECT_EQ(g.print(),0);
}

// TEST(BaseTest, BasicAssertions){

// }