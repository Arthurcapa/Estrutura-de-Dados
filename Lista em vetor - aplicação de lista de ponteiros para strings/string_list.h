/// Copyright <Arthur Machado Capaverde> 2018

#ifndef STRUCTURES_STRING_LIST_H
#define STRUCTURES_STRING_LIST_H

#include <cstdint>
#include <stdexcept>  // C++ exceptions
#include <cstring>

namespace structures {

//! ...
template<typename T>
class ArrayList {
 public:
    //! ...
    ArrayList();
    //! ...
    explicit ArrayList(std::size_t max_size);
    //! ...
    ~ArrayList();

    //! ...
    void clear();
    //! ...
    void push_back(const T& data);
    //! ...
    void push_front(const T& data);
    //! ...
    void insert(const T& data, std::size_t index);
    //! ...
    void insert_sorted(const T& data);
    //! ...
    T pop(std::size_t index);
    //! ...
    T pop_back();
    //! ...
    T pop_front();
    //! ...
    void remove(const T& data);
    //! ...
    bool full() const;
    //! ...
    bool empty() const;
    //! ...
    bool contains(const T& data) const;
    //! ...
    std::size_t find(const T& data) const;
    //! ...
    std::size_t size() const;
    //! ...
    std::size_t max_size() const;
    //! ...
    T& at(std::size_t index);
    //! ...
    T& operator[](std::size_t index);
    //! ...
    const T& at(std::size_t index) const;
    //! ...
    const T& operator[](std::size_t index) const;

 protected:
    //! ...
    T* contents;

    //! ...
    std::size_t size_;

    //! ...
    std::size_t max_size_;

    //! ...
    static const auto DEFAULT_MAX = 10u;
};


template<typename T>
structures::ArrayList<T>::ArrayList() {
  size_ = 0;
  max_size_ = DEFAULT_MAX;
  contents = new T[DEFAULT_MAX];
}

template<typename T>
structures::ArrayList<T>::ArrayList(std::size_t max_size) {
  size_ = 0;
  max_size_ = max_size;
  contents = new T[max_size_];
}

template<typename T>
structures::ArrayList<T>::~ArrayList() {
  delete[] contents;
}

template<typename T>
void structures::ArrayList<T>::clear() {
    size_ = 0;
}

template<typename T>
void structures::ArrayList<T>::push_back(const T& data) {
  if (full()) {
    throw std::out_of_range("A lista esta cheia.");
  } else {
      contents[size_] = data;
      size_ += 1;
  }
}

template<typename T>
void structures::ArrayList<T>::push_front(const T& data) {
  int i = size_;
  if (full()) {
    throw std::out_of_range("A lista esta cheia.");
  } else {
    while (i > 0) {
      contents[i] = contents[i - 1];
      i--;
    }
    contents[0] = data;
    size_++;
  }
}

template<typename T>
void structures::ArrayList<T>::insert(const T& data, std::size_t index) {
    if (full()) {
        throw std::out_of_range("A lista esta cheia");
    } else if (index < 0 || index > size_) {
        throw std::out_of_range("O index está fora do escopo");
    } else if (index == size_) {
        contents[size_] = data;
        size_ += 1;
    } else {
        int i = size_;
        while (i > index) {
            contents[i] = contents[i-1];
            i -= 1;
        }
        contents[index] = data;
        size_ += 1;
    }
}

template<typename T>
void structures::ArrayList<T>::insert_sorted(const T& data) {
  int i = 0;
  if (full()) {
    throw std::out_of_range("A lista esta cheia.");
  } else {
    while (i < size_ && data > contents[i]) {
      i++;
    }
    insert(data, i);
  }
}

template<typename T>
T structures::ArrayList<T>::pop(std::size_t index) {
  if (index >= size_) {
    throw std::out_of_range("O index esta fora do escopo.");
  } else {
      std::size_t i = index;
      T value = contents[index];
      while (i < size_-1) {
          contents[i] = contents[i+1];
          i++;
      }
      size_--;
      return value;
  }
}

template<typename T>
T structures::ArrayList<T>::pop_back() {
  if (empty()) {
    throw std::out_of_range("A lista esta vazia.");
  } else {
      size_ -= 1;
      return contents[size_];
  }
}


template<typename T>
T structures::ArrayList<T>::pop_front() {
  if (empty()) {
    throw std::out_of_range("A lista esta vazia.");
  } else {
    T aux = contents[0];
    int i = 0;
    while (i < size_ - 1) {
        contents[i] = contents[i+1];
        i++;
    }
    size_--;
    return aux;
  }
}

template<typename T>
void structures::ArrayList<T>::remove(const T& data) {
    std::size_t index = find(data);
    if (index < size_) {
        pop(index);
    }
}

template<typename T>
bool structures::ArrayList<T>::full() const {
  if (size_ == max_size_) {
    return true;
  }  else {
    return false;
  }
}

template<typename T>
bool structures::ArrayList<T>::empty() const {
  if (size_ == 0) {
    return true;
  } else {
    return false;
  }
}

template<typename T>
bool structures::ArrayList<T>::contains(const T& data) const {
  int i = 0;
  int con = false;
  if (empty()) {
    throw std::out_of_range("A lista esta vazia.");
    return false;
  } else {
    while (i < size_) {
      if (contents[i] == data) {
        con = true;
      }
      i++;
    }
  }
  return con;
}

template<typename T>
std::size_t structures::ArrayList<T>::find(const T& data) const {
  int i = 0;
  if (empty()) {
    throw std::out_of_range("A lista esta vazia.");
  } else {
    while (i < size_) {
      if (contents[i] == data) {
        return i;
      }
      i++;
    }
  }
  // se nao achar, retorna o tamanho da lista
  return size_;
}

template<typename T>
std::size_t structures::ArrayList<T>::size() const {
  return size_;
}

template<typename T>
std::size_t structures::ArrayList<T>::max_size() const {
  return max_size_;
}

template<typename T>
T& structures::ArrayList<T>::at(std::size_t index) {
  if (index < 0 || index >= size_) {
      throw std::out_of_range("O index esta fora dos limites");
  } else {
      return contents[index];
  }
}

template<typename T>
T& structures::ArrayList<T>::operator[](std::size_t index) {
  return contents[index];
}

template<typename T>
const T& structures::ArrayList<T>::at(std::size_t index) const {
  if (index < 0 || index >= size_) {
      throw std::out_of_range("O index esta fora dos limites");
  } else {
      return contents[index];
  }
}

template<typename T>
const T& structures::ArrayList<T>::operator[](std::size_t index) const {
  return contents[index];
}



//-------------------------------------



//! ...
//! ArrayListString e' uma especializacao da classe ArrayList
class ArrayListString : public ArrayList<char *> {
 public:
    //! ...
    ArrayListString() : ArrayList() {}
    //! ...
    explicit ArrayListString(std::size_t max_size) : ArrayList(max_size) {}
    //! ...
    ~ArrayListString();

    //! ...
    void clear();
    //! ...
    void push_back(const char *data);
    //! ...
    void push_front(const char *data);
    //! ...
    void insert(const char *data, std::size_t index);
    //! ...
    void insert_sorted(const char *data);
    //! ...
    char *pop(std::size_t index);
    //! ...
    char *pop_back();
    //! ...
    char *pop_front();
    //! ...
    void remove(const char *data);
    //! ...
    bool contains(const char *data);
    //! ...
    std::size_t find(const char *data);
};


structures::ArrayListString::~ArrayListString() {
}

void structures::ArrayListString::clear() {
  size_ = 0;
}


void structures::ArrayListString::push_back(const char *data) {
    insert(data, size_);
}


void structures::ArrayListString::push_front(const char *data) {
  insert(data, 0);
}


void structures::ArrayListString::insert(const char *data, std::size_t index) {
    char* aux = new char[strlen(data)+1];
    snprintf(aux, strlen(data)+1, "%s", data);
    ArrayList::insert(aux, index);
}


void structures::ArrayListString::insert_sorted(const char *data) {
  std::size_t index = size_;
  if (full()) {
    throw std::out_of_range("Full");
  } else {
    for (std::size_t i = 0; i < size_; i ++) {
      if (strcmp(contents[i], data) > 0) {
        index = i;
        break;
      }
    }
    char* aux = new char[strlen(data)+1];
    snprintf(aux, strlen(data)+1, "%s", data);
    insert(aux, index);
  }
}


char* structures::ArrayListString::pop(std::size_t index) {
  return ArrayList::pop(index);
}


char* structures::ArrayListString::pop_back() {
  if (empty()) {
    throw std::out_of_range("Empty");
  } else {
    size_--;
    return contents[size_];
  }
  return 0;
}


char* structures::ArrayListString::pop_front() {
  if (empty()) {
    throw std::out_of_range("Empty");
  } else {
    char* aux = contents[0];
    for (std::size_t i = 1; i < size_; i++) {
      contents[i-1] = contents[i];
    }
    size_--;
    return aux;
  }
  return 0;
}


void structures::ArrayListString::remove(const char *data) {
  if (empty()) {
    throw std::out_of_range("Empty");
  } else {
      if (contains(data)) {
        std::size_t index = find(data);
        pop(index);
      }
  }
}


bool structures::ArrayListString::contains(const char *data) {
  bool cont = false;
  if (empty()) {
    throw std::out_of_range("Empty");
  } else {
    for (std::size_t i = 0; i < size_; i++) {
    char* aux = new char[strlen(data)+1];
    snprintf(aux, strlen(data)+1, "%s", data);
      if (strcmp(contents[i], data) == 0) {
        cont = true;
        break;
      }
    }
  }
  return cont;
}


std::size_t structures::ArrayListString::find(const char *data) {
  std::size_t index = size_;
  for (std::size_t i = 0; i < size_; i++) {
    char* aux = new char[strlen(data)+1];
    snprintf(aux, strlen(data)+1, "%s", data);
    char* aux2 = new char[strlen(contents[i])+1];
    snprintf(aux2, strlen(contents[i])+1, "%s", contents[i]);
    if (strcmp(aux2, aux) == 0) {
      return i;
    }
  }
  return index;
}


}  // namespace structures

#endif

