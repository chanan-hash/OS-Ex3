#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <list>
#include <string>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <sstream>
#include <thread>
#include <mutex>
#include <functional>

using namespace std;

#define PORT "9031" // Port to listen on

typedef  function<void*(int, mutex&)> proactorFunc;

class Proactor
{
    private:
        mutex mtx;
    public:
        void startProactor(int sockfd, proactorFunc func);
        void stopProactor();
        ~Proactor();
};