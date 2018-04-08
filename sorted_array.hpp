#ifndef sorted_array_H
#define sorted_array_H
#include <iostream>
#include <cstddef>
using namespace std;

/**
@file sorted_array.hpp
@brief Dichiarazione della classe sorted_array
**/

typedef unsigned int uint;

template <typename T, typename F>
class sorted_array {
  private:
    F _funct;
    uint _size;
    T *_array;
    T **_sorted;
    uint _elements;
    /**
    @brief selection_sort

    Ordina l'array di puntatori a puntatori di tipo T tramite selection_sort.

    N.B. Questo metodo è inutilizzato
    dato che ho implementato anche l'insertion_sort,
    ed utilizzo quest'ultimo per l'ordinamento.
    **/
    void selection_sort() {
      T *appo;
      for(uint i=0; i<_elements-1; i++) {
        for(uint j=i+1; j<=_elements-1; j++) {
          if(!_funct(*_sorted[i], *_sorted[j])) {
            appo = _sorted[i];
            _sorted[i] = _sorted[j];
            _sorted[j] = appo;
          }
        }
      }
    }
    /**
    @brief insertion_sort

    Ordina l'array di puntatori a puntatori di tipo T tramite insertion_sort.
    **/
    void insertion_sort() {
      uint jmin;
      T *appo;
      for (uint i=0; i<_elements-1; i++) {
        jmin = i;
          for (uint j=i+1; j<_elements; j++)
            if (_funct(*_sorted[j], *_sorted[jmin]))
              jmin = j;
            appo = _sorted[jmin];
            _sorted[jmin] = _sorted[i];
            _sorted[i] = appo;
      }
    }

  public:
    /**
    @brief Costruttore di default (METODO FONDAMENTALE)

    Costruttore di default per istanziare un sorted_array vuoto.
    Necessita quindi una chiamata del metodo setter della size
    **/
    sorted_array() : _size(0), _array(0), _sorted(0), _elements(0) {}
    /**
    @brief Size constructor (METODO FONDAMENTALE)

    Permette di istanziare un sorted_array con una determinata lunghezza
    @param size (la futura lunghezza dell'oggetto sorted_array)
    **/
    sorted_array(const uint size) : _elements(0) {
    set_size(size);
    }
    /**
    @brief Copy constructor (METODO FONDAMENTALE)

    Costruttore copia. Permette di istanziare un sorted_array con i valori
    presi da un altro sorted_array.
    @param other_sarr (un altro sorted array, da usare per creare la copia)
    **/
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
        _array = 0;
        _sorted = 0;
        _size = 0;
        _elements = 0;
        throw;
      }
    }

    // Setta elements a 0
    void clear() {
      _elements = 0;
    }

    /**
    @brief set_size

    Metodo setter di _size, permette di modificare la lunghezza dell'array
    CANCELLANDONE il contenuto.
    @param _size (la futura lunghezza dell'oggetto sorted_array)
    **/
    void set_size(const uint n) {
      _size = n;
      _array = new T[n];
      _sorted = new T*[n];
      clear();
    }
    uint get_size() {
      return _size;
    }

    // elements getter
    uint get_elements() {
      return _elements;
    }

    // Hakai
    /**
    @brief Distruttore (METODO FONDAMENTALE)

    Distruttore. Rimuove la memoria allocata dall'oggetto.
    **/
    ~sorted_array() {
      delete[] _array;
      delete[] _sorted;
      _array = 0;
      _sorted = 0;
      _size = 0;
      _elements = 0;
    }

    // Inserisce un elemento negli array
    void push(const T &element) {
      if(_elements >= _size)
        throw out_of_range("I'm Already full");
      _array[_elements] = element;
      _sorted[_elements] = &_array[_elements];
      _elements++;
      insertion_sort();
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

    /* ITERATORI */




};
#endif
