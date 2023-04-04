// "Copyright [2018] <Arthur Machado Capaverde>"

#ifndef STRUCTURES_ARRAY_STACK_H
#define STRUCTURES_ARRAY_STACK_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ exceptions

namespace structures {

template<typename T>
  /// Classe ArrayStack
class ArrayStack {
 public:
    ArrayStack();

    explicit ArrayStack(std::size_t max);

    ~ArrayStack();

    void push(const T& data);  // empilha

    T pop();  // desempilha

    T& top();

    void clear();  // limpa

    std::size_t size();  // tamanho

    std::size_t max_size();

    bool empty();  // vazia

    bool full();  // cheia

 private:
    T* contents;
    int top_;
    std::size_t max_size_;

    static const auto DEFAULT_SIZE = 10u;
};

}  /// namespace structures

  /// Construtor ArrayStack
template <typename T>structures:: ArrayStack<T>::ArrayStack() {
    top_ = -1;
    max_size_ = DEFAULT_SIZE;
    contents = new T[DEFAULT_SIZE];
}

  /// Construtor ArrayStack Explícito
template <typename T>structures:: ArrayStack<T>::ArrayStack(std::size_t max) {
    max_size_ = max;
    contents = new T[max_size_];
    top_ = -1;
}

  /// Destrutor ArrayStack
template <typename T> structures:: ArrayStack<T>::~ArrayStack() {
    delete []contents;
}

  /// Empilha
template <typename T>void structures:: ArrayStack<T>::push(const T& data) {
    if (full()) {
        throw std:: out_of_range("PILHA CHEIA");
    }  else {
            top_ = top_ + 1;
            contents[top_] = data;
        }
}

  /// Desempilha
template <typename T>T structures:: ArrayStack<T>::pop() {
    if (empty()) {
        throw std:: out_of_range("PILHA VAZIA");
    } else {
        top_ = top_ - 1;
        return (contents[top_ + 1]);
    }
}
  /// Topo
template <typename T>T& structures:: ArrayStack<T>::top() {
    if (empty()) {
        throw std:: out_of_range("PILHA VAZIA");
    } else {
        return (contents[top_]);
    }
}

  /// Limpa
template <typename T>void structures:: ArrayStack<T>::clear() {
    top_ = -1;
}

  /// Tamanho
template <typename T>size_t structures:: ArrayStack<T>::size() {
    return top_ + 1;
}

  /// Tamanho Máximo
template <typename T>size_t structures:: ArrayStack<T>::max_size() {
    return max_size_;
}

  /// Vazia
template <typename T>bool structures:: ArrayStack<T>::empty() {
    if (top_ == -1) {
        return (true);
    } else {
        return (false);
    }
}

  /// Cheia
template <typename T>bool structures:: ArrayStack<T>::full() {
    if ((top_ + 1) == max_size_) {
        return (true);
    } else {
        return (false);
    }
}

#endif
