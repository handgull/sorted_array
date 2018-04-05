#ifndef sorted_array_H
#define sorted_array_H
#include <iostream>
#include <cstddef>
using namespace std;

template <typename T, typename F>

class sorted_array {
  private:
    F _funct;
    unsigned int _size;
    T *_array;
    T **_sorted;
    unsigned int _elements;
  public:
    sorted_array() : _size(0), _array(0), _sorted(0), _elements(0) {}
};
#endif
