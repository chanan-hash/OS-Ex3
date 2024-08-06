#include <iostream>
#include <mutex>

using namespace std;

class Singleton
{
private:
    static mutex mutex_;         // A static mutex to ensure thread-safe access to the singleton instance.
    static Singleton *instance_; // A static pointer to hold the singleton instance.
protected:
    // Protected constructor to prevent direct instantiation
    Singleton() {}

public:
    // Delete the copy constructor and assignment operator to prevent copying
    Singleton(const Singleton &) = delete;
    Singleton &operator=(const Singleton &) = delete;

    // Provide a static method to get the instance of the singleton
    static Singleton *getInstance();

    // Pure virtual function to be implemented by derived classes
    virtual void showMessage() = 0;
};

// Define the static mutex and instance pointer
mutex Singleton::mutex_;
Singleton *Singleton::instance_ = nullptr;

// Example derived class from Singleton
class MySingleton : public Singleton
{
public:
    void showMessage() override
    {
        cout << "Hello, I am a Singleton!" << endl;
    }
};

// Define the getInstance method outside the class definition
/**
 * The method checks if instance_ is nullptr.
 * If it is, it locks the mutex using lock_guard to ensure thread safety.
 * It checks again if instance_ is nullptr (double-checked locking) and then creates an instance of MySingleton.
 * Finally, it returns the singleton instance.
 */

Singleton *Singleton::getInstance()
{
    // Use a local static variable to ensure thread-safe initialization in C++11 and later
    if (instance_ == nullptr)
    {
        lock_guard<mutex> guard(mutex_);
        if (instance_ == nullptr)
        {
            instance_ = new MySingleton(); // Creating an instance of the derived class
        }
    }
    return instance_;
}

int main()
{
    // Get the singleton instance and use it
    Singleton *singletonInstance = Singleton::getInstance();
    singletonInstance->showMessage();

    return 0;
}