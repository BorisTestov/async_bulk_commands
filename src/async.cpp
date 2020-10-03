#include "async.h"

#include "stream.h"

#include <cassert>
#include <map>
#include <memory>
#include <mutex>

namespace async
{
    std::mutex async_mutex;

    using StreamPtr = std::shared_ptr<Stream>;
    using mapConsole = std::map<handle_t, StreamPtr>;

    mapConsole allConsoles;

    handle_t connect(std::size_t bulk)
    {
        std::lock_guard<std::mutex> lock(async_mutex);
        StreamPtr newConsole = std::make_shared<Stream>(bulk);
        handle_t handle = static_cast<void*>(newConsole.get());
        assert(allConsoles.count(handle) == 0);
        allConsoles[handle] = newConsole;
        return handle;
    }

    void receive(handle_t handle, const char* data, std::size_t size)
    {
        std::lock_guard<std::mutex> lock(async_mutex);
        StreamPtr console = allConsoles.at(handle);
        console->addToBuffer(data, size);
    }

    void disconnect(handle_t handle)
    {
        std::lock_guard<std::mutex> lock(async_mutex);
        assert(allConsoles.count(handle) != 0);
        allConsoles.erase(handle);
    }
} // namespace async