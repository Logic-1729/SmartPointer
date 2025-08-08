#ifndef WEAK_PTR
#define WEAK_PTR

#include "Shared_ptr.h" // Include SharedPtr definition
// When submitting to damn ACMOJ, please replace this with the content inside shared_ptr.h

template <typename T>
class WeakPtr {
    private:
        // Add whatever you want to add.
    public:
        // Constructors
        WeakPtr();// Default constructor
        WeakPtr(const SharedPtr<T>& temp);// Constructor from SharedPtr
        WeakPtr(const WeakPtr& temp);// Copy constructor
        WeakPtr(WeakPtr&& temp);// Move constructor

        // Destructor
        ~WeakPtr();
        
        // Assignment operators
        WeakPtr& operator=(const WeakPtr& temp);// Copy assignment operator
        WeakPtr& operator=(const SharedPtr<T>& temp);// Assignment from SharedPtr
        WeakPtr& operator=(WeakPtr&& temp);// Move assignment operator

        // Basic operations
        int use_count();// Get the number of shared owners
        SharedPtr<T> lock();// Get a SharedPtr to the managed object
        bool expired();// Check if the managed object was deleted
        void reset();// Reset to empty state

        // Utility functions
        void swap(WeakPtr& other) noexcept;  // Swap with another WeakPtr
};


#endif //WEAK_PTR
