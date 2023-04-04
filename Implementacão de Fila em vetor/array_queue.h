/// Copyright <Arthur Machado Capaverde> 2018
#ifndef STRUCTURES_ARRAY_QUEUE_H
#define STRUCTURES_ARRAY_QUEUE_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ Exceptions

namespace structures {

template<typename T>
/// Classe ArrayQueue
class ArrayQueue {
 public:
    ArrayQueue();

    explicit ArrayQueue(std::size_t max);

    ~ArrayQueue();

    void enqueue(const T& data);

    T dequeue();

    T& back();

    void clear();

    std::size_t size();

    std::size_t max_size();

    bool empty();

    bool full();

 private:
    T* contents;
    std::size_t size_;
    std::size_t max_size_;

    static const auto DEFAULT_SIZE = 10u;
};

}  /// namespace structures

  /// Construtor ArrayQueue
template <typename T>structures:: ArrayQueue<T>::ArrayQueue() {
    size_ = -1;
    max_size_ = DEFAULT_SIZE;
    contents = new T[DEFAULT_SIZE];
}
  /// Construtor ArrayQueue Explícito
template <typename T>structures:: ArrayQueue<T>::ArrayQueue(std::size_t max) {
    max_size_ = max;
    contents = new T[max_size_];
    size_ = -1;
}
  /// Destrutor ArrayQueue
template <typename T>structures:: ArrayQueue<T>::~ArrayQueue() {
    delete []contents;
}
  /// Enfila
template <typename T>void structures:: ArrayQueue<T>::enqueue(const T& data) {
      if (full()) {
        throw std:: out_of_range("FILA CHEIA");
    }  else {
            size_ = size_ + 1;
            contents[size_] = data;
        }
}
  /// Desenfila
template <typename T>T structures:: ArrayQueue<T>::dequeue() {
      if (empty()) {
        throw std:: out_of_range("FILA VAZIA");
    }
    T x = contents[0];
    for (int i = 0; i < size_; i++) {
        contents[i] = contents[i+1];
    }
    size_--;
    return x;
}
  /// Desenfila &
template <typename T>T& structures:: ArrayQueue<T>::back() {
     if (empty()) {
        throw std:: out_of_range("FILA VAZIA");
     }
     return contents[size_];
}
  /// Limpa
template <typename T>void structures:: ArrayQueue<T>::clear() {
    size_ = -1;
}
  /// Tamanho
template <typename T>size_t structures:: ArrayQueue<T>::size() {
     return size_ + 1;
}
  /// Tamanho Máximo
template <typename T>size_t structures:: ArrayQueue<T>::max_size() {
    return max_size_;
}
  /// Vazia
template <typename T>bool structures:: ArrayQueue<T>::empty() {
     if (size_ == -1) {
        return (true);
    } else {
        return (false);
    }
}
  /// Cheia
template <typename T>bool structures:: ArrayQueue<T>::full() {
    if ((size_ + 1) == max_size_) {
        return (true);
    } else {
        return (false);
    }
}
#endif
