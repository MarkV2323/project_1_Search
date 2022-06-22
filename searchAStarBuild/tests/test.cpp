#include "gtest/gtest.h"
#include "testEx.h"

TEST(TestEx1, test1) { // NOLINT(cert-err58-cpp)
    EXPECT_EQ(1, 1);
}

// Primary function for running all tests that are included as headers.
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
