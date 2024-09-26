#include "Proactor.hpp"

// get sockaddr, IPv4 or IPv6, as the multithreading
void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET)
    {
        return &(((struct sockaddr_in *)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6 *)sa)->sin6_addr);
}

void ::Proactor::startProactor(int sockfd, proactorFunc func)
{
    while (true)
    {
        struct sockaddr_storage their_addr;
        socklen_t addr_size;
        int new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &addr_size);
        if (new_fd == -1)
        {
            perror("accept");
            continue;
        }
        char s[INET6_ADDRSTRLEN];
        cout << "server: got connection from " << inet_ntop(their_addr.ss_family, get_in_addr((struct sockaddr *)&their_addr), s, sizeof s) << endl;
        thread t(func, new_fd, ref(mtx));
        t.detach();
    }
}

void ::Proactor::stopProactor()
{
    mtx.unlock();
}

mutex &::Proactor::get_lock()
{
    return mtx;
}

::Proactor::~Proactor()
{
    stopProactor();
}