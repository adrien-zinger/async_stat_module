#include <gtest/gtest.h>
#include "../src/hello.hpp"

TEST(BasicTest, CheckGetHelloFct) {
  EXPECT_EQ(getHello(), "Hello world");
}
