/// Copyright <Arthur Machado Capaverde> 2018
#ifndef STRUCTURES_ARRAY_LIST_H
#define STRUCTURES_ARRAY_LIST_H
#include <stdexcept>  // C++ Exceptions
#include <cstdint>


namespace structures {
template<typename T>
/// Classe Arraylist
class ArrayList {
 public:
    ArrayList();
    explicit ArrayList(std::size_t max_size);
    ~ArrayList();

    void clear();
    void push_back(const T& data);
    void push_front(const T& data);
    void insert(const T& data, std::size_t index);
    void insert_sorted(const T& data);
    T pop(std::size_t index);
    T pop_back();
    T pop_front();
    void remove(const T& data);
    bool full() const;
    bool empty() const;
    bool contains(const T& data) const;
    std::size_t find(const T& data) const;
    std::size_t size() const;
    std::size_t max_size() const;
    T& at(std::size_t index);
    T& operator[](std::size_t index);
    const T& at(std::size_t index) const;
    const T& operator[](std::size_t index) const;

 private:
    T* contents;
    std::size_t size_;
    std::size_t max_size_;

    static const auto DEFAULT_MAX = 10u;
};

}  /// namespace structures

/// Construtor Arraylist
template <typename T> structures:: ArrayList<T>::ArrayList() {
    contents = new T[DEFAULT_MAX];
    max_size_ = DEFAULT_MAX;
    size_ = 0;
}

/// Construtor Arraylist Explícito
template <typename T> structures:: ArrayList<T>::ArrayList
(std::size_t max_size) {
    contents = new T[max_size];
    max_size_ = max_size;
    size_ = 0;
}

/// Destrutor ArrayList
template <typename T> structures:: ArrayList<T>::~ArrayList() {
    delete []contents;
}

/// Limpa
template <typename T>void structures:: ArrayList<T>::clear() {
    size_ = 0;
}

/// Destrutor ArrayStack
template <typename T>void structures:: ArrayList<T>::push_back(const T& data) {
     insert(data, size_);
}

/// Destrutor ArrayStack
template <typename T>void structures:: ArrayList<T>::push_front(const T& data) {
    insert(data, 0);
    }

/// Destrutor ArrayStack
template <typename T>void structures:: ArrayList<T>::insert
(const T& data, std::size_t index) {
    int atual;
    if (full()) {
         throw std:: out_of_range("LISTA CHEIA");
    } else if (index < 0 || index >= max_size_) {
            throw std:: out_of_range("POSICAO INVALIDA");
    } else {
            for (atual = size_; atual > index; atual--) {
                contents[atual] = contents[atual-1];
            }
            size_++;
            contents[index] = data;
        }
}

/// Destrutor ArrayStack
template <typename T>void structures:: ArrayList<T>::insert_sorted
(const T& data) {
    int i;
    if (full()) {
         throw std:: out_of_range("LISTA CHEIA");
    } else {
        i = 0;
        while (i < size_) {
        if (contents[i] < data) {
            i = i+1;
            } else {
                break;
            }
        }
        insert(data, i);
    }
}

/// Destrutor ArrayStack
template <typename T>T structures:: ArrayList<T>::pop(std::size_t index) {
    int atual;
    T valor;
    if (index < 0 || index > size_-1) {
        throw std:: out_of_range("POSICAO INVALIDA");
    } else {
        if (empty()) {
            throw std:: out_of_range("LISTA VAZIA");
        } else {
            valor = contents[index];
            size_ = size_-1;
            atual = index;
            while (atual < size_) {
                contents[atual] = contents[atual+1];
                atual = atual+1;
            }
            return valor;
        }
    }
}

/// Destrutor ArrayStack
template <typename T>T structures:: ArrayList<T>::pop_back() {
    if (empty()) {
        throw std:: out_of_range("LISTA VAZIA");
    } else {
        return pop(size_-1);
    }
}

/// Destrutor ArrayStack
template <typename T>T structures:: ArrayList<T>::pop_front() {
    int x;
    T value;
    if (empty()) {
        throw std:: out_of_range("LISTA VAZIA");
    } else {
        size_ = size_ - 1;
        value = contents[0];
        x = 0;
        while (x <= size_) {
            contents[x] = contents[x+1];
            x = x+1;
        }
        return value;
    }
}

/// Destrutor ArrayStack
template <typename T>void structures:: ArrayList<T>::remove(const T& data) {
    int atual;
    if (empty()) {
         throw std:: out_of_range("LISTA VAZIA");
    } else {
        atual = 0;
        while (atual <= size_) {
            if (data == contents[atual]) {
            pop(atual);
            }
            atual = atual+1;
        }
    }
}

/// Cheia
template <typename T>bool structures:: ArrayList<T>::full() const {
    if (size_ == max_size_) {
        return (true);
    } else {
        return (false);
    }
}

/// Vazia
template <typename T>bool structures:: ArrayList<T>::empty() const {
     if (size_ == 0) {
        return (true);
    } else {
        return (false);
    }
}

/// Destrutor ArrayStack

template <typename T>bool structures:: ArrayList<T>::contains
(const T& data) const {
    int atual;
    atual = 0;
    while (atual <= size_ && data != contents[atual]) {
        atual = atual+1;
    }
    if (atual > size_) {
        return false;
    } else {
        return true;
    }
}

/// Destrutor ArrayStack
template <typename T>size_t structures:: ArrayList<T>::find
(const T& data) const {
    int atual;
    int index = size_;
    atual = 0;
    while (atual <= size_) {
        if (data == contents[atual]) {
            index = atual;
        }
        atual = atual+1;
    }
    return index;
}

/// Destrutor ArrayStack
template <typename T>size_t structures:: ArrayList<T>::size() const {
    return size_;
}

/// Destrutor ArrayStack
template <typename T>size_t structures:: ArrayList<T>::max_size
() const {
    return max_size_;
}

/// Destrutor ArrayStack
template <typename T>T& structures:: ArrayList<T>::at
(std::size_t index) {
    if (empty()) {
        throw std:: out_of_range("LISTA VAZIA");
    }
    if (index >= size_ || index < 0) {
        throw std:: out_of_range("POSICAO INVALIDA");
    } else {
        return contents[index];
    }
}

/// Destrutor ArrayStack
template <typename T>T& structures:: ArrayList<T>::operator[]
(std::size_t index) {
    return contents[index];
}

/// Destrutor ArrayStack
template <typename T>const T& structures:: ArrayList<T>::at
(std::size_t index) const {
    if (empty()) {
        throw std:: out_of_range("LISTA VAZIA");
    }
    if (index >= size_ || index < 0) {
        throw std:: out_of_range("POSICAO INVALIDA");
    } else {
        return contents[index];
    }
}

/// Destrutor ArrayStack
template <typename T>const T& structures:: ArrayList<T>::operator[]
(std::size_t index) const {
    return contents[index];
}
#endif
