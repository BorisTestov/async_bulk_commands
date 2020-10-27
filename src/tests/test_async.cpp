#include "async.h"

#include <gtest/gtest.h>
#include <map>

TEST(async, bulk_5)
{
    testing::internal::CaptureStdout();
    std::size_t bulk = 5;
    auto h = async::connect(bulk);
    auto h2 = async::connect(bulk);
    async::receive(h, "command_1", 9);
    async::receive(h2,
                   "command_1\n"
                   "command_2\n"
                   "command_3\n"
                   "command_4\n",
                   40);
    async::receive(h,
                   "\n"
                   "command_2\n"
                   "command_3\n"
                   "command_4\n"
                   "command_5\n"
                   "command_6\n"
                   "{\n"
                   "a\n",
                   55);
    async::receive(h,
                   "b\n"
                   "c\n"
                   "d\n"
                   "}\n"
                   "42\n",
                   11);
    async::disconnect(h);
    async::disconnect(h2);
    std::string output = testing::internal::GetCapturedStdout();
    std::string expected_output =
        "bulk:command_1,command_2,command_3,command_4,command_5\n"
        "bulk:command_6\n"
        "bulk:a,b,c,d\n"
        "bulk:42\n"
        "bulk:command_1,command_2,command_3,command_4\n";
    ASSERT_EQ(output, expected_output);
}