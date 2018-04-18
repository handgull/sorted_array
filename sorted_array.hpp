#ifndef sorted_array_H
#define sorted_array_H
#include <iostream>
#include <cstddef>
#include <stdexcept>
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

    /** 
    @brief myswap

    Scambia il contenuto di due sorted_array
    @param other (l'oggetto con il quale scambiare i dati) 
    **/
    void myswap(sorted_array &other) {
      swap(other._size, this->_size);
      swap(other._elements, this->_elements);
      swap(other._array, this->_array);
      swap(other._sorted, this->_sorted);
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

    /**
    @brief clear

    Cancella il contenuto dell'array.
    N.B ho preferito un implementazione che modifica solo _elements,
    la variabile che segna la lunghezza degli array;
    in questo modo tramite altri miei controlli se si supera la nuova
    lunghezza nonostante i vecchi valori siano ancora presenti verrà lanciata
    un'eccezione.
    **/
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
    /**
    @brief get_size
    @return La _size dell'array.
    **/
    uint get_size() {
      return _size;
    }

    /**
    @brief get_elements
    @return Il numero di elementi dell'array che hanno un valore.
    **/
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

    /**
    @brief operator=

    Operatore di assegnamento che permette la copia tra sorted_array.
    @param other (l'oggetto da cui copiare)
    @return puntatore all'oggetto che lancia il metodo.
    **/
    sorted_array &operator=(const sorted_array &other) {
      if (this != &other) {
        sorted_array tmp(other);
        this->myswap(tmp);
      }
      return *this;
    }

    /**
    @brief push

    Aggiunge il nuovo elemento nella prima locazione disponibile
    (basandosi su _elements) e poi sorta immediatamente l'array
    con un sort adatto alle inserzioni continue.
    @param element (nuovo elemento dell'array)
    **/
    void push(const T &element) {
      if(_elements >= _size)
        throw out_of_range("I'm Already full");
      _array[_elements] = element;
      _sorted[_elements] = &_array[_elements];
      _elements++;
      insertion_sort();
    }

    /**
    @brief operator()

    Metodo getter per leggere il valore i-esimo dell'array non ordinato 

    @param i (indice della cella dell'array)
    @return Il valore della posizione i-esima
    **/
    const T &operator()(uint i) const {
      if(i < 0 || i >= _elements)
        throw out_of_range("Out of index");
      return _array[i];
    }
    /**
    @brief operator[]

    Metodo getter per leggere il valore i-esimo dell'array ordinato 

    @param i (indice della cella dell'array)
    @return Il valore della posizione i-esima
    **/
    const T &operator[](uint i) const {
      if(i < 0 || i >= _elements)
        throw out_of_range("Out of index");
      return *_sorted[i];
    }

    /* ITERATORI */
    class const_iterator {
      const T **p;
      public:
        typedef random_access_iterator_tag iterator_category;
        typedef T value_type;
        typedef ptrdiff_t difference_type;
        typedef const T* pointer;
        typedef const T& reference;
    
        const_iterator() : p(0) {}
      
        const_iterator(const const_iterator &other) : p(other.p){}
        
        const_iterator& operator=(const const_iterator &other) {
          p = other.p;
          return *this;
        }
      
        ~const_iterator() {}

        reference operator*() const {
          return **(p);
        }

        pointer operator->() const {
          return p;
        }

        reference operator[](uint i) {
          return **(p+i);
        }
      
        const_iterator operator++(int) {
          const_iterator tmp(*this);
          p++;
          return tmp;
        }

        const_iterator& operator++() {
          p++;
          return *this;
        }

        const_iterator operator--(int) {
          const_iterator tmp(*this);
          p--;
          return tmp;
        }

        const_iterator &operator--() {
          p--;
          return *this;
        }

        const_iterator operator+(uint i) {
          const_iterator tmp(*this);
          tmp.p += i;
          return tmp;
        }

        const_iterator operator-(uint i) {
          const_iterator tmp(*this);
          tmp.p -= i;
          return tmp;
        }

        const_iterator& operator+=(uint i) {
          p += i;
          return *this;
        }

        const_iterator& operator-=(uint i) {
          p -= i;
          return *this;
        }

        difference_type operator-(const const_iterator &other) {
          return (p > other.p ? p - other.p : other.p - p);
        }

        bool operator==(const const_iterator &other) const {
          return p == other.p;
        }

        bool operator!=(const const_iterator &other) const {
          return p != other.p;
        }

        bool operator>(const const_iterator &other) const {
          return p > other.p;
        }

        bool operator>=(const const_iterator &other) const {
          return p >= other.p;
        }

        bool operator<(const const_iterator &other) const {
          return p < other.p;
        }

        bool operator<=(const const_iterator &other) const {
          return p <= other.p;
        }

      private:
        friend class sorted_array;

        const_iterator(const T** ptr) : p(ptr){}
    };
    /**
    @brief begin

    @return iteratore alla fine dell'array ordinato
    */
    const_iterator begin() const {
      return const_iterator(const_cast<const T**>(_sorted));
    }
    /**
    @brief end

    @return iteratore alla fine dell'array ordinato
    */
    const_iterator end() const {
      return const_iterator(const_cast<const T**>(_sorted + _elements));
    }

    class unsorted_const_iterator {
      const T *p;
      public:
        typedef random_access_iterator_tag iterator_category;
        typedef T value_type;
        typedef ptrdiff_t difference_type;
        typedef const T* pointer;
        typedef const T& reference;

        unsorted_const_iterator() : p(0) {}
      
        unsorted_const_iterator(const unsorted_const_iterator &other): p(other.p){}
        
        unsorted_const_iterator& operator=(const unsorted_const_iterator &other) {
          p = other.p;
          return *this;
        }

        ~unsorted_const_iterator() {}

        reference operator*() const {
          return *p;
        }

        pointer operator->() const {
          return p;
        }

        reference operator[](uint i) {
          return *(p + i);
        }

        unsorted_const_iterator operator++(int) {
          unsorted_const_iterator tmp(*this);
          p++;
          return tmp;
        }

        unsorted_const_iterator& operator++() {
          p++;
          return *this;
        }

        unsorted_const_iterator operator--(int) {
          unsorted_const_iterator tmp(*this);
          p--;
          return tmp;
        }

        unsorted_const_iterator &operator--() {
          p--;
          return *this;
        }

        unsorted_const_iterator operator+(uint i) {
          unsorted_const_iterator tmp(*this);
          tmp.p += i;
          return tmp;
        }

        unsorted_const_iterator operator-(uint i) {
          unsorted_const_iterator tmp(*this);
          tmp.p -= i;
          return tmp;
        }

        unsorted_const_iterator& operator+=(uint i) {
          p += i;
          return *this;
        }

        unsorted_const_iterator& operator-=(uint i) {
          p -= i;
          return *this;
        }

        difference_type operator-(const unsorted_const_iterator &other) {
          return (p > other.p ? p - other.p : other.p - p);
        }

        bool operator==(const unsorted_const_iterator &other) const {
          return p == other.p;
        }

        bool operator!=(const unsorted_const_iterator &other) const {
          return p != other.p;
        }

        bool operator>(const unsorted_const_iterator &other) const {
          return p > other.p;
        }

        bool operator>=(const unsorted_const_iterator &other) const {
          return p >= other.p;
        }

        bool operator<(const unsorted_const_iterator &other) const {
          return p < other.p;
        }
      
        bool operator<=(const unsorted_const_iterator &other) const {
          return p <= other.p;
        }

      private:
        friend class sorted_array;

        unsorted_const_iterator(const T* ptr): p(ptr){}
        
    };
    /**
    @brief end

    @return iteratore alla fine dell'array non ordinato
    */
    unsorted_const_iterator begin_u() const {
      return unsorted_const_iterator(_array);
    }
    /**
    @brief end

    @return iteratore alla fine dell'array non ordinato
    */
    unsorted_const_iterator end_u() const {
      return unsorted_const_iterator(_array + _elements);
    }
};

/**
@brief find_count

dato un generico sorted_array che contiene dati di tipo T,
un valore target di tipo T, e un predicato binario,
stampa a schermo il numero di valori contenuti nel sorted_array
uguali al target secondo il criterio definito dal predicato binario.
@param sorted_array (array in cui cercare)
@param target (valore target)
@param funct (predicato da soddisfare)
**/
template <typename T, typename F, typename P>
void find_count(const sorted_array<T,F> &sarr,const T &target,const P &func) {
  for(typename sorted_array<T,F>::uint i = 0; i < sarr.get_elements(); i++)
    if(func(sarr[i], target))
      cout<<sarr[i]<<" ";
}

/**
@brief opeartor<<

Operatore di stream, permette di spedire su uno stream
di output il contenuto dell'array.
@param os (lo stream target)
@param sarr (sorted_array da utilizzare)
@return Il riferimento allo stream di output
**/
template <typename T, typename F>
ostream &operator<<(ostream &os, const sorted_array<T,F> &sarr) {
  for(typename sorted_array<T,F>::uint i = 0; i < sarr.get_elements(); ++i)
    os << sarr[i] << " ";
  return os;
}
#endif
