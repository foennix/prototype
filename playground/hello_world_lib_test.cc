#include <limits.h>
#include "hello_world_lib.h"
#include "googletest/include/gtest/gtest.h"

namespace {


TEST(AddTest, Add) {
  // This test is named "Negative", and belongs to the "FactorialTest"
  // test case.
  EXPECT_EQ(1, Add(1,0));
  EXPECT_EQ(2, Add(1,1));
}

}
