#include <cstdint>
#include <mutex>
#include <set>

/**
 * This class provides mechanisms to allocate and free ports sequentially
 * starting from a given base port, ensuring safe multithreaded access.
 */
class PortManager
{
public:
    // Deleted copy c'tor
    PortManager(const PortManager&) = delete;
    PortManager& operator=(const PortManager&) = delete;
    /**
     * Allocates a port by finding the first available one.
     * \return The allocated port number.
     */
    std::uint16_t AllocatePort();
    /**
     * Frees a previously allocated port.
     * \param port The port number to free.
     * \return True if the port was successfully freed, false if the port was not allocated.
     */
    bool FreePort(std::uint16_t port);
    /**
     * Prints the list of currently acquired ports.
     */
    void PrintAcquiredPorts() const;
    /**
     * Provides access to the singleton instance of PortManager.
     * \return The singleton instance of PortManager.
     */
    static PortManager& GetInstance();

private:
    PortManager() = default;
    /**
     * Base port number for port assignments.
     */
    std::uint16_t _basePort{8000};
    /**
     * Set of ports that have been acquired and are currently in use.
     */
    std::set<std::uint16_t> _acquiredPorts;
    /**
     * Mutex for thread-safe access to port-related operations.
     */
    mutable std::mutex _portMutex;
};
