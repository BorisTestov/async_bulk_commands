#include "stream.h"

Stream::Stream(size_t bulk_size) :
    _mutex(),
    _input(""),
    _observers()
{
    _observers.push_back(std::make_shared<CommandProcessor>(static_cast<void*>(this), bulk_size));
    _observers.push_back(std::make_shared<BlockProcessor>(this));
}

void Stream::addToBuffer(const char* buffer, const size_t buf_size)
{
    std::lock_guard<std::mutex> guard(_mutex);
    _input.append(buffer, buf_size);
    auto posNewLine = _input.find("\n");
    while (posNewLine != std::string::npos)
    {
        std::string command = _input.substr(0, posNewLine);
        _input.erase(0, posNewLine + 1);
        std::for_each(_observers.begin(), _observers.end(), [command](auto ptrProcessor) {
            ptrProcessor->parseCommand(command);
        });
        posNewLine = _input.find("\n");
    }
}