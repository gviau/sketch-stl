#ifndef SKETCH_STL_VECTOR_H
#define SKETCH_STL_VECTOR_H

#include <type_traits>

namespace SketchStl {
/**
 * @class vector
 * This class represents a dynamic contiguous array
 */
template <typename T>
class vector {
    public:
        /**
         * Default constructor
         * Initializes everything to 0
         */
        vector();

        /**
         * Fill constructor
         * Constructs a container with n elements. Each element is a copy of val
         * @param n The number of elements
         * @param val The value to fill the vector with
         */
        vector(size_t n, const T& val=T());

        /**
         * Copy constructor
         * @param src The vector to copy
         */
        vector(const vector<T>& src);

        /**
         * Destructor
         * Frees the vector
         */
        ~vector();

        /**
         * Assignment operator
         * @param rhs The vector to assign to this one
         */
        vector<T>& operator=(const vector& rhs);

        size_t size() const { return length_; }
        size_t capacity() const { return capacity_; }
        bool empty() const { return length_ == 0; }

        /**
         * Resize the vector. This reallocates memory to the array only if the requested size is greater than the vector's
         * current capacity.
         * @param n The new size of the vector
         * @param val The value to copy at the end of the vector, in case the new size is larger than our array's
         */
        void resize(size_t n, T val=T());

        /**
         * Reserve memory for the vector. This reallocates memory to the array only if the requested capacity is greater than
         * the current one. This function does not modify the vector's elements
         * @param n The new capacity the we want for this vector
         */
        void reserve(size_t n);

        /**
         * Access element
         * @param n The position at which we want to access the element
         */
        T& operator[](size_t n);
        const T& operator[](size_t n) const;

        /**
         * Returns a reference to the element at position n in the vector
         * @param n The position at which we want to access the element
         */
        T& at(size_t n);
        const T& at(size_t n) const;

        /**
         * Fill the vector with a value
         * @param n The new size for the vector
         * @param val Value to fill the vector with
         */
        void assign(size_t n, const T& val);

        /**
         * Add an element at the end of the vector
         * @param val The value to add at the end
         */
        void push_back(const T& val);

        /**
         * Remove the last element of the vector
         */
        void pop_back();

        /**
         * Clear the vector. This frees the allocated memory
         */
        void clear();

    private:
        T*      data_;      /**< The contiguous dynamic array */
        size_t  length_;    /**< The length of the array */
        size_t  capacity_;  /**< The capacity of the array */
};

template <typename T>
vector<T>::vector() : data_(nullptr), length_(0), capacity_(4) {
    data_ = (T*)malloc(sizeof(T) * capacity_);
}

template <typename T>
vector<T>::vector(size_t n, const T& val) : length_(n), capacity_(n * 2) {
    data_ = (T*)malloc(sizeof(T) * capacity_);
    for (size_t i = 0; i < length_; i++) {
        data_[i] = val;
    }
}

template <typename T>
vector<T>::vector(const vector<T>& src) {
    length_ = src.length_;
    capacity_ = src.capacity_;
    data_ = (T*)malloc(sizeof(T) * capacity_);

    for (size_t i = 0; i < length_; i++) {
        data_[i] = src.data_[i];
    }
}

template <typename T>
vector<T>::~vector() {
    clear();
}

template <typename T>
vector<T>& vector<T>::operator=(const vector& rhs) {
    if (this != &rhs) {
        clear();

        length_ = rhs.length_;
        capacity_ = rhs.capacity_;
        data_ = (T*)malloc(sizeof(T) * capacity_);

        for (size_t i = 0; i < length_; i++) {
            data_[i] = rhs.data_[i];
        }
    }

    return *this;
}

template <typename T>
void vector<T>::resize(size_t n, T val) {
    if (n < length_) {
        capacity_ = n * 2;

        T* newData = (T*)malloc(sizeof(T) * capacity_);
        for (size_t i = 0; i < n; i++) {
            newData[i] = data_[i];
        }

        for (size_t i = n; i < length_; i++) {
            data_[i].~T();
        }

        free(data_);
        data_ = newData;
    } else if (n > length_) {
        if (n > capacity_) {
            capacity_ = n * 2;

            T* newData = (T*)malloc(sizeof(T) * capacity_);
            for (size_t i = 0; i < length_; i++) {
                newData[i] = data_[i];
            }

            free(data_);
            data_ = newData;
        }

        for (size_t i = length_; i < n; i++) {
            data_[i] = val;
        }
    }

    length_ = n;
}

template <typename T>
void vector<T>::reserve(size_t n) {
    if (n > capacity_) {
        capacity_ = n;

        T* newData = (T*)malloc(sizeof(T) * capacity_);
        for (size_t i = 0; i < length_; i++) {
            newData[i] = data_[i];
        }

        free(data_);
        data_ = newData;
    }
}

template <typename T>
T& vector<T>::operator[](size_t n) {
    assert(n < length_);
    return data_[n];
}

template <typename T>
const T& vector<T>::operator[](size_t n) const {
    assert(n < length_);
    return data_[n];
}

template <typename T>
T& vector<T>::at(size_t n) {
    assert(n < length_);
    return data_[n];
}

template <typename T>
const T& vector<T>::at(size_t n) const {
    assert(n < length_);
    return data_[n];
}

template <typename T>
void vector<T>::assign(size_t n, const T& val) {
    clear();
    reserve(n * 2);

    for (size_t i = 0; i < n; i++) {
        data_[i] = val;
    }

    length_ = n;
}

template <typename T>
void vector<T>::push_back(const T& val) {
    if (length_ + 1 >= capacity_) {
        capacity_ *= 2;

        T* newData = (T*)malloc(sizeof(T) * capacity_);
        for (size_t i = 0; i < length_; i++) {
            newData[i] = data_[i];
        }

        free(data_);
        data_ = newData;
    }

    data_[length_++] = val;
}

template <typename T>
void vector<T>::pop_back() {
    data_[length_-1].~T();
    length_ -= 1;
}

template <typename T>
void vector<T>::clear() {
    for (size_t i = 0; i < length_; i++) {
        data_[i].~T();
    }

    free(data_);
    data_ = nullptr;
    length_ = 0;
    capacity_ = 0;
}

}

#endif