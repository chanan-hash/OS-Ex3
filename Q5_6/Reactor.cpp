#include "Reactor.hpp"
#include <vector>
#include <unordered_map>
#include <poll.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

void *reactor::startReactor()
{
    isRunning = true;
    while (isRunning)
    {
        int numEvents = poll(fds.data(), fds.size(), -1);
        if (numEvents == -1)
        {
            cerr << "Error polling for events" << endl;
            exit(1);
        }
        for (auto &pfd : fds)
        {
            if (pfd.revents & POLLIN)
            {
                handlers[pfd.fd](pfd.fd);
            }
        }
    }
    return nullptr;
}

int reactor::addFdToReactor(int fd, reactorFunc func)
{
    pollfd pfd = {fd, POLLIN, 0};
    fds.push_back(pfd);
    handlers[fd] = func;
    return 0; // Success
}

int reactor::removeFdFromReactor(int fd)
{
    auto it = handlers.find(fd);
    if (it == handlers.end())
    {
        return -1; // Not found
    }
    handlers.erase(it);
    for (auto it = fds.begin(); it != fds.end(); ++it)
    {
        if (it->fd == fd)
        {
            fds.erase(it);
            break;
        }
    }
    return 0; // Success
}

int reactor::stopReactor()
{
    isRunning = false;
    return 0; // Success
}