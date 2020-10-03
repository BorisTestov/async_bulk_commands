#pragma once

#include "block_processor.h"
#include "command_processor.h"
#include "observer.h"

#include <algorithm>
#include <exception>
#include <iostream>
#include <mutex>
#include <vector>

class Stream
{
public:
    Stream(size_t bulk_size);
    void addToBuffer(const char* buffer, const size_t buf_size);

private:
    std::mutex _mutex;
    std::string _input;
    std::vector<observerPtr> _observers;
};
