#ifndef SMARTARRAY_H
#define SMARTARRAY_H
#include <iostream>
#include <stdexcept>
#include <utility>

template <typename T>
class SmartArray {
private:
    T* data_;
    unsigned size_;
    unsigned capacity_;

    void reallocate(unsigned newCapacity) {
        T* newData = new T[newCapacity];
        for (unsigned i = 0; i < size_; ++i) {
            newData[i] = std::move(data_[i]);
        }
        delete[] data_;
        data_ = newData;
        capacity_ = newCapacity;
    }

public:
    SmartArray() : size_(0), capacity_(1) {
        data_ = new T[capacity_];
    }

    SmartArray(unsigned size) : size_(size), capacity_(size) {
        data_ = new T[capacity_];
    }

    SmartArray(const SmartArray& other) {
        capacity_ = other.capacity_;
        size_ = other.size_;
        data_ = new T[capacity_];
        for (int i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }
    }

    SmartArray(unsigned size, T elem) : size_(size), capacity_(size) {
        data_ = new T[capacity_];
        for (unsigned i = 0; i < size_; ++i) {
            data_[i] = elem;
        }
    }

    ~SmartArray() {
        delete[] data_;
    }

    T at(unsigned index) {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return data_[index];
    }

    bool isEmpty() const {
        return size_ == 0;
    }

    unsigned size() const {
        return size_;
    }

    unsigned capacity() const {
        return capacity_;
    }

    void reserve(unsigned size) {
        if (size > capacity_) {
            reallocate(size);
        }
    }

    void resize(unsigned size) {
        if (size > capacity_) {
            reallocate(size);   
        }
        size_ = size;
    }

    void resize(unsigned size, T elem) {
        if (size > capacity_) {
            reallocate(size);
        }
        for (unsigned i = size_; i < size; ++i) {
            data_[i] = elem;
        }
        size_ = size;
    }

    void clear() {
        size_ = 0;
    }

    void insert(unsigned index, T elem) {
        if (index > size_) {
            throw std::out_of_range("Index out of range");
        }
        if (size_ == capacity_) {
            reallocate(capacity_ * 2);
        }
        for (unsigned i = size_; i > index; --i) {
            data_[i] = std::move(data_[i - 1]);
        }
        data_[index] = elem;
        ++size_;
    }

    void erase(unsigned index) {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        for (unsigned i = index; i < size_ - 1; ++i) {
            data_[i] = std::move(data_[i + 1]);
        }
        --size_;
    }

    void erase(unsigned index, unsigned amount) {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        if (index + amount > size_) {
            amount = size_ - index;
        }
        for (unsigned i = index; i < size_ - amount; ++i) {
            data_[i] = std::move(data_[i + amount]);
        }
        size_ -= amount;
    }

    void pushBack(T elem) {
        if (size_ == capacity_) {
            reallocate(capacity_ * 2);
        }
        data_[size_++] = elem;
    }

    void popBack() {
        --size_;
    }

    bool operator==(const SmartArray& other) const {
        if (size_ != other.size_) {
            return false;
        }
        for (unsigned i = 0; i < size_; ++i) {
            if (data_[i] != other.data_[i]) {
                return false;
            }
        }
        return true;
    }

    T& operator[](unsigned index) {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return data_[index];
    }

    const T& operator[](unsigned index) const {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return data_[index];
    }

    template <typename T>
    void saveToFile(const SmartArray<T>& arr, const std::string& filename) {
        std::ofstream out(filename, std::ios::binary);
        if (!out) throw std::runtime_error("Could not open file for writing");

        unsigned size = arr.size();
        out.write(reinterpret_cast<const char*>(&size), sizeof(size));

        for (unsigned i = 0; i < size; ++i) {
            serialize(out, arr[i]);
        }

        out.close();
    }

    template <typename T>
    void loadFromFile(SmartArray<T>& arr, const std::string& filename) {
        std::ifstream in(filename, std::ios::binary);
        if (!in) throw std::runtime_error("Could not open file for reading");

        unsigned size;
        in.read(reinterpret_cast<char*>(&size), sizeof(size));

        arr.clear();
        arr.reserve(size);

        for (unsigned i = 0; i < size; ++i) {
            T value;
            deserialize(in, value);
            arr.pushBack(value);
        }

        in.close();
    }
};

#endif //SMARTARRAY_H
