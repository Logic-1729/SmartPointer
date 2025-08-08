#ifndef UNIQUE_PTR
#define UNIQUE_PTR
#include <iostream>

template <typename T>

class UniquePtr {
    private:
        // Add whatever you want to add.
    public:
        //Constructors
        UniquePtr();// Default constructor
        explicit UniquePtr(T* p);// Constructor from raw pointer
        UniquePtr(UniquePtr& other) = delete; // Copy constructor is deleted
        UniquePtr(UniquePtr&& other); // Move constructor

        //Destructor
        ~UniquePtr();

        //Assignment operators
        UniquePtr& operator= (UniquePtr & other) = delete;// Copy assignment operator is deleted
        UniquePtr& operator= (UniquePtr && other) noexcept;// Move assignment operator

        // Basic operations
        T* get() const;// Get the raw pointer
        explicit operator bool() const;// Check if the pointer is not null
        T& operator*() const;// Dereference operator
        T* operator->() const;// Arrow operator
        void reset();// Reset to empty state
        void reset(T* p);// Reset with a new raw pointer
        T* release();// Release ownership of the managed object
};

template <typename T, typename... Args>
static UniquePtr<T> make_unique(Args&&... args) {
    return UniquePtr<T>(new T(std::forward<Args>(args)...));
}


#endif //UNIQUE_PTR
