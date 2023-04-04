///  Copyright [2018] <Arthur Machado Capaverde>
#ifndef STRUCTURES_DOUBLY_CIRCULAR_LIST_H
#define STRUCTURES_DOUBLY_CIRCULAR_LIST_H

#include <cstdint>
#include <stdexcept>

namespace structures {

//! Classe Lista Circular Dupla
template<typename T>
class DoublyCircularList {
 public:
    DoublyCircularList();
    ~DoublyCircularList();

    void clear();

    void push_back(const T& data);
    void push_front(const T& data);
    void insert(const T& data, std::size_t index);
    void insert_sorted(const T& data);

    T pop(std::size_t index);
    T pop_back();
    T pop_front();
    void remove(const T& data);

    bool empty() const;
    bool contains(const T& data) const;

    T& at(std::size_t index);
    const T& at(std::size_t index) const;

    std::size_t find(const T& data) const;
    std::size_t size() const;

 private:
    /// Subclasse Node
    class Node {
     public:
        /// Construtor Padrão
        explicit Node(const T& data):
        data_{data}
        {}

        /// Construtor
        Node(const T& data, Node* next):
        data_{data},
        next_{next}
        {}

        /// Construtor
        Node(const T& data, Node* prev, Node* next):
        data_{data},
        next_{next},
        prev_{prev}
        {}

        /// Retorna dado
        T& data() {
            return data_;
        }

        /// Retorna dado
        const T& data() const {
            return data_;
        }

        /// Node anterior
        Node* prev() {
            return prev_;
        }

        /// Node anterior
        const Node* prev() const {
            return prev_;
        }

        /// Set node anterior.
        void prev(Node* node) {
            prev_ = node;
        }

        /// Próximo node.
        Node* next() {
            return next_;
        }

        /// Próximo node.
        const Node* next() const {
            return next_;
        }

        /// Set próximo node.
        void next(Node* node) {
            next_ = node;
        }

     private:
        T data_;
        Node* prev_;
        Node* next_;
    };

    /// Retorna nodo no index
    Node* node_of_index(std::size_t index) {
        auto it = head;
        if (index <= size_/2) {
            for (auto i = 1u; i <= index; ++i)
                it = it->next();
        } else {
            for (auto i = 1u; i <= (size_-index); ++i)
                it = it->prev();
        }
        return it;
    }

    void insert(const T& data, Node* current);

    Node* head{nullptr};
    std::size_t size_{0u};
};

/// Construtor
template<typename T>
DoublyCircularList<T>::DoublyCircularList() {}

/// Destrutor
template<typename T>
DoublyCircularList<T>::~DoublyCircularList() {
    clear();
}

/// Limpa lista
template<typename T>
void DoublyCircularList<T>::clear() {
    while (!empty())
        pop_front();
}

/// Insere no fim
template<typename T>
void DoublyCircularList<T>::push_back(const T& data) {
      insert(data, size_);
}

/// Insere no começo
template<typename T>
void DoublyCircularList<T>::push_front(const T& data) {
    Node* new_node = new Node(data);
    if (new_node == nullptr)
        throw std::out_of_range("Full list!");

    if (empty()) {
      head = new_node;
      head->next(head);
      head->prev(head);
    } else {
      new_node->next(head);
      new_node->prev(head->prev());
      head->prev()->next(new_node);
      head->prev(new_node);
      head = new_node;
    }
    size_++;
}

/// Insere no index
template<typename T>
void DoublyCircularList<T>::insert(const T& data, std::size_t index) {
    if (index > size_)
        throw std::out_of_range("Invalid index!");

    if (index == 0) {
        push_front(data);
    } else {
        Node* new_node = new Node(data);
        if (new_node == nullptr)
            throw std::out_of_range("Full list!");

        Node* current = node_of_index(index);
        new_node->next(current);
        new_node->prev(current->prev());
        current->prev()->next(new_node);
        current->prev(new_node);
        size_++;
    }
}

/// Insere apos um node
template<typename T>
void DoublyCircularList<T>::insert(const T& data, Node* previous) {
    Node* new_node = new Node(data);
    if (new_node == nullptr)
        throw std::out_of_range("Full list!");

    if (empty()) {
        head = new_node;
        head->next(head);
        head->prev(head);
    } else {
        previous->next()->prev(new_node);
        new_node->next(previous->next());
        previous->next(new_node);
        new_node->prev(previous);
    }
    size_++;
}

/// Insere sorted
template<typename T>
void DoublyCircularList<T>::insert_sorted(const T& data) {
    if (empty()) {
        push_front(data);
    } else {
        auto current = head;
        std::size_t position = 0u;
        while (data > current->data()) {
            if (++position == size_)
                break;
            current = current->next();
        }
        position == 0? push_front(data) :
        position == size_?  push_back(data) :
                            insert(data, current->prev());
    }
}

/// Retira o dado na index
template<typename T>
T DoublyCircularList<T>::pop(std::size_t index) {
    if (empty())
        throw std::out_of_range("Empty list");
    if (index >= size())
        throw std::out_of_range("Invalid index!");

    if (index == 0)
        return pop_front();

    auto out = node_of_index(index);
    T data = out->data();
    out->prev()->next(out->next());
    out->next()->prev(out->prev());
    size_--;
    delete out;
    return data;
}

/// Retira dado no fim
template<typename T>
T DoublyCircularList<T>::pop_back() {
    return pop(size_-1);
}

/// Retira dado no inicio
template<typename T>
T DoublyCircularList<T>::pop_front() {
      if (empty())
          throw std::out_of_range("Empty list");

      auto out = head;
      T data = head->data();
      head->prev()->next(head->next());
      head->next()->prev(head->prev());
      head = head->next();
      size_--;
      delete out;

      if (empty())
        head = nullptr;
      return data;
}

/// Remove dado
template<typename T>
void DoublyCircularList<T>::remove(const T& data) {
    pop(find(data));
}

/// Testa lista vazia
template<typename T>
bool DoublyCircularList<T>::empty() const {
    return size() == 0u;
}

/// Metodo Contains
template<typename T>
bool DoublyCircularList<T>::contains(const T& data) const {
    return find(data) != size();
}

/// Retorna dado do nodo no index
template<typename T>
T& DoublyCircularList<T>::at(std::size_t index) {
    if (index >= size())
        throw std::out_of_range("Invalid index or empty list!");

    Node* current = node_of_index(index);
    return current->data();
}

/// Retorna dado do nodo no index
template<typename T>
const T& DoublyCircularList<T>::at(std::size_t index) const {
    if (index >= size())
        throw std::out_of_range("Invalid index or empty list!");

    Node* current = node_of_index(index);
    return current->data();
}

/// Retorna index do dado
template<typename T>
std::size_t DoublyCircularList<T>::find(const T& data) const {
    std::size_t index = 0u;
    auto current = head;
    while (index < size()) {
        if (current->data() == data)
            break;
        current = current->next();
        index++;
    }
    return index;
}

/// Tamanho
template<typename T>
std::size_t DoublyCircularList<T>::size() const {
    return size_;
}

}  // namespace structures

#endif
