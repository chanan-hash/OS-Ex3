#include "Reactor.hpp"
#include <vector>
#include <unordered_map>
#include <poll.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

typedef struct reactor {
    vector<pollfd> fds;
    unordered_map<int, reactorFunc> handlers;
    bool isRunning;
};

void* startReactor() {
    reactor* r = new reactor();
    r->isRunning = false;
    return r;
}

int addFdToReactor(void* reactor, int fd, reactorFunc func) {
    reactor* r = static_cast<reactor*>(reactor);
    pollfd pfd = {fd, POLLIN, 0}; // Assuming we're only interested in read events for simplicity
    r->fds.push_back(pfd);
    r->handlers[fd] = func;
    return 0; // Success
}

int removeFdFromReactor(void* reactor, int fd) {
    reactor* r = static_cast<reactor*>(reactor);
    auto it = std::remove_if(r->fds.begin(), r->fds.end(), [fd](const pollfd& pfd) { return pfd.fd == fd; });
    if (it != r->fds.end()) {
        r->fds.erase(it, r->fds.end());
        r->handlers.erase(fd);
        return 0; // Success
    }
    return -1; // Failure
}

int stopReactor(void* reactor) {
    reactor* r = static_cast<reactor*>(reactor);
    r->isRunning = false;
    return 0; // Success
}