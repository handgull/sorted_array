#ifndef sorted_array_H
#define sorted_array_H
#include <iostream>
#include <cstddef>
using namespace std;

typedef unsigned int uint;

template <typename T, typename F>
class sorted_array {
  private:
    F _funct;
    uint _size;
    T *_array;
    T **_sorted;
    uint _elements;
  public:
    // Costruttore di default
    sorted_array() : _size(0), _array(0), _sorted(0), _elements(0) {}
    // Costruttore che inizializza la lunghezza dell'array
    sorted_array(const uint size) : _elements(0) {
    set_size(size);
    }
    // Costruttore copia
    sorted_array(const sorted_array &other_sarr) {
      set_size(other_sarr._size);
      _elements = other_sarr._elements;
      try {
        for(uint i=0; i<_size; i++) {
          _array[i] = other_sarr._array[i];
          _sorted[i] = other_sarr._sorted[i];
        }
      } catch(...) {
        delete[] _array;
        delete[] _sorted;
        _size = 0;
        _array = 0;
        _sorted = 0;
        _elements = 0;
        throw;
      }
    }

    // _size setter e getter
    void set_size(const uint n) {
      _size = n;
      _array = new T[n];
      _sorted = new T*[n];
    }
    uint get_size() {
      return _size;
    }

    // elements getter
    uint get_elements() {
      return _elements;
    }

    // Hakai
    ~sorted_array() {
      delete[] _array;
      delete[] _sorted;
      _array = 0;
      _sorted = 0;
      _size = 0;
      _elements = 0;
    }

    // Setta tutti gli elementi a 0
    void clear() {
      for(uint i=0; i<_size; i++) {
        _array[i] = 0;
        //_sorted[i] = 0;
      }
      _elements = 0;
    }

    // Inserisce un elemento negli array
    void push(const T &element) {
      if(_elements >= _size)
        throw out_of_range("I'm Already full");
      _array[_elements] = element;
      //_sorted[i] = &_array[_elements];
      _elements++;
      //sort();
    }    

    // Metodo getter per l'i-esimo elemento di _array
    const T &operator()(uint i) const {
      if(i < 0 || i >= _elements)
        throw out_of_range("Out of index");
      return _array[i];
    }

    // Metodo getter per l'i-esimo elemento di _sorted
    const T &operator[](uint i) const {
      if(i < 0 || i >= _elements)
        throw out_of_range("Out of index");
      return *_sorted[i];
    }
};
#endif
