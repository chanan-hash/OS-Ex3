#include <iostream>
#include <poll.h>
#include <unistd.h>
#include <vector>
#include <unordered_map>

#define PORT 9031

using namespace std;
/**
 * This represents the Reactor design-pattern which is responsible for handling events with callbacks.
 * The Reactor is responsible for handling the events and dispatching them to the appropriate handlers.
 * Each time we're handling a new event, we're calling the appropriate handler.
 */

#ifndef REACTOR_HPP
#define REACTOR_HPP

// Function pointer type for handling events on file descriptors.
typedef void *(*reactorFunc)(int fd);

// Forward declaration of the reactor structure.
// typedef struct reactor;
typedef struct reactor
{
    // Maps file descriptors to their corresponding event handlers.
    unordered_map<int, reactorFunc> handlers;

    // List of pollfd structures for monitoring file descriptors.
    vector<pollfd> fds;

    // Indicates whether the reactor is currently running.
    bool isRunning;

    // Constructor initializes the reactor to a non-running state.
    reactor() : isRunning(false) {}
};

// Starts a new reactor and returns a pointer to it.
void *startReactor();

// Adds a file descriptor to the Reactor for reading; returns 0 on success.
int addFdToReactor(void *reactor, int fd, reactorFunc func);

// Removes a file descriptor from the Reactor.
int removeFdFromReactor(void *reactor, int fd);

// Stops the reactor and cleans up resources.
int stopReactor(void *reactor);

#endif // REACTOR_HPP