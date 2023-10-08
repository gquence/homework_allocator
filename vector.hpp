#pragma once

#include "allocator.hpp"

#include <cstring>
#include <functional>

template<class T, class _alloc = std::allocator<T>> 
class my_vector
{
private:
    _alloc _Allocator;
    T *_data = nullptr;
    size_t _size = 0;
    size_t _capacity = 0;
public:
    my_vector(/* args */) {};
    ~my_vector()
    {
        if (_data)
            _Allocator.deallocate(_data, _capacity);
    };
    T &push_back(const T &elem) {
        if (!_data) {
            _capacity = 10;
            _data = _Allocator.allocate(_capacity);
        }
        if (_size == _capacity) {
            _capacity *= 2;
            T * tmp_data = _Allocator.allocate(_capacity);
            memcpy(tmp_data, _data, sizeof(T) * _size);
        }
        _data[_size] = elem;
        _size++;
        return *_data;
    };
    void foreach(std::function<void(const T &)> func) {
        for (size_t i = 0; i < _size; i++ ){
            func(_data[i]);
        }
    };
};
