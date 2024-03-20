#include <gtest/gtest.h>
#include "rosneuro_windows/Window.hpp"

namespace rosneuro {

template <typename T>
class WindowTest : public Window<T> {
    public:
        WindowTest() : Window<T>() {}
        ~WindowTest() {}
        bool configure() { return true; }
        DynamicMatrix<T> apply(const DynamicMatrix<T>& in) { return in; }
};

class WindowTestSuite : public ::testing::Test {
    public:
        WindowTestSuite() {}
        ~WindowTestSuite() {}
        void SetUp() { window_filter = new WindowTest <double>(); }
        void TearDown() { delete window_filter; }
        WindowTest <double>* window_filter;
};

TEST_F(WindowTestSuite, Constructor) {
    ASSERT_EQ(window_filter->name_, "Window");
    ASSERT_FALSE(window_filter->is_window_set_);
}

TEST_F(WindowTestSuite, GetWindowNorm) {
    ASSERT_EQ(window_filter->GetWindowNorm(), 0);
}

TEST_F(WindowTestSuite, Configure) {
    ASSERT_TRUE(window_filter->configure());
}

TEST_F(WindowTestSuite, Apply) {
    DynamicMatrix<double> input(2, 2);
    DynamicMatrix<double> output = window_filter->apply(input);
    ASSERT_EQ(output, input);
}

}

int main(int argc, char **argv) {
    ros::init(argc, argv, "test_window");
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}