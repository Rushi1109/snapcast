#include "common/aixlog.hpp"
#include "port_manager.hpp"
#include <string>

static constexpr auto LOG_TAG = "PortManager";

PortManager& PortManager::GetInstance()
{
    static PortManager instance;
    return instance;
}
std::uint16_t PortManager::AllocatePort()
{
    std::lock_guard<std::mutex> lock(_portMutex);
    std::uint16_t port = _basePort;
    while (_acquiredPorts.find(port) != _acquiredPorts.end())
    {
        port += 2;
    }
    LOG(INFO, LOG_TAG) << "Port " << port << " allocated\n";
    _acquiredPorts.insert(port);
    return port;
}
bool PortManager::FreePort(std::uint16_t port)
{
    std::lock_guard<std::mutex> lock(_portMutex);
    if (_acquiredPorts.erase(port))
    {
        LOG(INFO, LOG_TAG) << "Port " << port << " freed\n";
        return true;
    }
    LOG(ERROR, LOG_TAG) << "Port " << port << " was not allocated\n";
    return false;
}
void PortManager::PrintAcquiredPorts() const
{
    std::lock_guard<std::mutex> lock(_portMutex);
    std::string ports{};
    for (std::uint16_t port : _acquiredPorts)
    {
        ports += std::to_string(port) + " ";
    }
    LOG(INFO, LOG_TAG) << "Currently acquired ports: " << ports << '\n';
}
