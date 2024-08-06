#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

class Guard
{
private:
    mutex &mutex_;

public:
    // Constructor that locks the mutex
    explicit Guard(mutex &m) : mutex_(m)
    {
        mutex_.lock();
    }

    // Destructor that unlocks the mutex
    ~Guard()
    {
        mutex_.unlock();
    }

    // Delete copy constructor and assignment operator to prevent copying
    Guard(const Guard &) = delete;
    Guard &operator=(const Guard &) = delete;
};

class Example
{
private:
    int count_;
    mutex mutex_; // mutex to protect access to count_.
public:
    Example() : count_(0) {} // initialize  list

    void increment()
    {
        Guard guard(mutex_);
        ++count_;
        cout << "Count: " << count_ << endl;
    }
};

int main()
{
    /**
     * Creates an Example object named example.
     * Creates three threads (t1, t2, t3) that call the increment method on the example object concurrently.
     * Joins the threads to ensure that the main thread waits for them to finish before exiting.
     */

    Example example;

    // Create a few threads to increment the count concurrently
    thread t1(&Example::increment, &example);
    thread t2(&Example::increment, &example);
    thread t3(&Example::increment, &example);

    // Join the threads
    t1.join();
    t2.join();
    t3.join();

    return 0;
}