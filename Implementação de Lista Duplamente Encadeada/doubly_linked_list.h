// Copyright 2018 Arthur Machado Capaverde

#ifndef STRUCTURES_DOUBLY_LINKED_LIST_H
#define STRUCTURES_DOUBLY_LINKED_LIST_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ exceptions

namespace structures {

template<typename T>

/// Classe lista duplamente encadeada
class DoublyLinkedList {
 public:
    DoublyLinkedList();
    ~DoublyLinkedList();
    //! Funcao clear
    void clear();
    //! Insere no fim
    void push_back(const T& data);
    //! Insere no comeco
    void push_front(const T& data);
    //! insere na posição
    void insert(const T& data, std::size_t index);
    //! insere em ordem
    void insert_sorted(const T& data);
    //! retira da posicao
    T pop(std::size_t index);
    //! retira do fim
    T pop_back();
    //! retira do inicio
    T pop_front();
    //! remove específico
    void remove(const T& data);
    //! vazio
    bool empty() const;
    //! contem
    bool contains(const T& data) const;
    //! acessar um elemento
    T& at(std::size_t index);
    //! getter constante a um elemento
    const T& at(std::size_t index) const;
    //! posição de um dado
    std::size_t find(const T& data) const;
    //! tamanho
    std::size_t size() const;

 private:
    // Classe node
    class Node {
     public:
        // Construtor
        explicit Node(const T& data):
        data_{data}
        {}

        // Construtor com ponteiro
        Node(const T& data, Node* next):
        data_{data},
        next_{next}
        {}

        // Construtor Completo
        Node(const T& data, Node* prev, Node* next):
        data_{data},
        prev_{prev},
        next_{next}
        {}

        // Retorna dado.
        T& data() {
            return data_;
        }

        //! Retorna dado.
        const T& data() const {
            return data_;
        }

        // Getter node anterior.
        Node* prev() {
            return prev_;
        }

        // Getter node anterior.
        const Node* prev() const {
            return prev_;
        }

        // Setter node anterior.
        void prev(Node* node) {
            prev_ = node;
        }

        // Getter próximo node.
        Node* next() {
            return next_;
        }

        // Getter const próximo node.
        const Node* next() const {
            return next_;
        }

        // Setter próximo node.
        void next(Node* node) {
            next_ = node;
        }

     private:
        T data_;  //!< data
        Node* prev_{nullptr};
        Node* next_{nullptr};
    };

    // Caminha por todos os nodes até o último.
    Node* end() {
        auto it = head;
        for (auto i = 1u; i < size(); ++i) {
            it = it->next();
        }
        return it;
    }

    // caminha por todos os nodes até o index.
    Node* node_of_index(std::size_t index) {
        auto it = head;
        for (auto i = 1u; i <= index; ++i) {
            it = it->next();
        }
        return it;
    }

    void insert(const T& data, Node* current);

    Node* head{nullptr};
    Node* tail{nullptr};
    std::size_t size_{0u};
};

// Construtor
template<typename T>
DoublyLinkedList<T>::DoublyLinkedList() {
    size_ = 0;
    head = nullptr;
    tail = nullptr;
}

// Destrutor
template<typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
  clear();
}

// Esvazia a lista.
template<typename T>
void DoublyLinkedList<T>::clear() {
  while (!empty()) {
    pop_front();
  }
}

// Inserção no começo da lista.
template<typename T>
void DoublyLinkedList<T>::push_back(const T& data) {
  Node* nd = new Node(data);
  if (nd == nullptr) {
      throw std::out_of_range("Error creating node - push_back\n");
  }
  if (empty()) {
    printf("Empty list, pushing at head - push_back\n");
    head = nd;
  } else {
    tail->next(nd);
    nd->prev(tail);
  }
  tail = nd;
  size_++;
}

// Inserção no fim da lista.
template<typename T>
void DoublyLinkedList<T>::push_front(const T& data) {
  Node* nd = new Node(data);
  if (nd == nullptr) {
    throw std::out_of_range("Error creating node - push_front\n");
  }
  if (empty()) {
    printf("Empty list, pushing at tail - push_front\n");
    tail = nd;
  } else {
    head->prev(nd);
    nd->next(head);
  }
  head = nd;
  size_++;
}

// Inserção em qualquer lugar da lista.
template<typename T>
void DoublyLinkedList<T>::insert(const T& data, std::size_t index) {
  if (index > size()) {
    throw std::out_of_range("index cant be bigger than size - insert\n");
  } else if (index == size()) {
    push_back(data);
  } else if (index == 0) {
    push_front(data);
  } else {
    Node* nd = new Node(data);
    if (nd == nullptr) {
      throw std::out_of_range("Error creating node - insert\n");
    } else {
      if (empty()) {
        head = nd;
        tail = nd;
      } else {
        Node* aux = nullptr;
        size_t segment = size() / 2;  //  gets half of the list
        if (index <= segment) {  //  first half
          aux = head;
          for (std::size_t i = 0; i < segment; i++) {
            aux = aux ->next();
          }
        } else {  //  second half
          aux = tail;
          for (std::size_t i = 0; i < (segment - 1); i++) {
            aux = aux->prev();
          }
        }
        aux->prev()->next(nd);
        nd->next(aux);
        nd->prev(aux->prev());
        aux->prev(nd);
        size_++;
      }
    }
  }
}

// Inserção ordenada na lista.
template<typename T>
void DoublyLinkedList<T>::insert_sorted(const T& data) {
  if (empty()) {
    push_front(data);
  } else {
    Node* aux = head;
    std::size_t index = 0;
    while (index < size() && aux != nullptr && data > aux->data()) {
      index++;
      aux = aux->next();
    }
    insert(data, index);
  }
  //  size++ is already made inside 'insert'
}

// Retira o dado de uma específica posição da lista.
template<typename T>
T DoublyLinkedList<T>::pop(std::size_t index) {
    Node *anterior, *eliminar;
    T data;
  if (index >= size()) {
    throw std::out_of_range("Erro posição");
  } else if (index == 0) {
    return pop_front();
  } else {
      anterior = head;
    for (int i = 0; i < index - 1; i++) {
        anterior = anterior->next();
    }
    eliminar = anterior->next();
    data = eliminar->data();
    anterior->next(eliminar->next());
    if (eliminar->next() != (nullptr)) {
        eliminar->next()->prev(anterior);
    } else {
        tail = anterior;
    }
    size_--;
    delete(eliminar);
    return data;
  }
}

// Retira o dado do final da lista
template<typename T>
T DoublyLinkedList<T>::pop_back() {
  if (empty()) {
    throw std::out_of_range("Empty list - pop_back\n");
  } else {
    Node* nd = tail;
    T data = nd->data();
    if (size() == 1) {
      tail = nullptr;
      head = nullptr;
    } else {
      nd->prev()->next(nullptr);
      tail = nd->prev();
    }
    size_--;
    delete(nd);
    return data;
  }
}

// Coleta o dado do início da lista.
template<typename T>
T DoublyLinkedList<T>::pop_front() {
  if (empty()) {
    throw std::out_of_range("Empty list - pop_front\n");
  } else {
    Node* nd = head;
    T data = nd->data();
    if (size() == 1) {
      head = nullptr;
      tail = nullptr;
    } else {
      nd->next()->prev(nullptr);
      head = nd->next();
    }
    size_--;
    delete(nd);
    return data;
  }
}

// Remoção de um dado da lista.
template<typename T>
void DoublyLinkedList<T>::remove(const T& data) {
  if (empty()) {
    throw std::out_of_range("Empty list - remove\n");
  } else {
    if (contains(data)) {
      std::size_t index = find(data);
      pop(index);
    } else {
      throw std::out_of_range("The element doesnt exist - remove");
    }
  }
}

// lista vazia
template<typename T>
bool DoublyLinkedList<T>::empty() const {
  if (size() == 0) {
      return true;
  } else {
      return false;
  }
}

// Contém um dado
template<typename T>
bool DoublyLinkedList<T>::contains(const T& data) const {
  if (empty()) {
    throw std::out_of_range("Empty list - contains\n");
  } else {
    Node* aux = head;
    for (std::size_t i = 0; i < size(); i++) {
      if (aux->data() == data) {
        return true;
      }
      aux = aux->next();
    }
    return false;  //  if data is not found or the list is empty
  }
}

// Referencia o dado na posição da lista.
template<typename T>
T& DoublyLinkedList<T>::at(std::size_t index) {
  if (empty()) {
      throw std::out_of_range("Empty list - at\n");
  } else if (index >= size()) {
      throw std::out_of_range("Index cant be bigger than size - at\n");
  }
  Node* aux = nullptr;
  size_t interval = (size())/ 2;
  if (index <= interval) {
      aux = head;
      for (size_t i = 0; i < index; i++) {
          aux = aux->next();
      }
  } else {
      aux = tail;
      for (size_t i = 0; i < (size() - index - 1); i++) {
          aux = aux->prev();
      }
  }
  return aux->data();
}

// Referencia o dado na posição da lista / CONSTANTE.
template<typename T>
const T& DoublyLinkedList<T>::at(std::size_t index) const {
  if (empty()) {
      throw std::out_of_range("Empty list - at\n");
  } else if (index >= size()) {
      throw std::out_of_range("Index cant be bigger than size - at\n");
  }
  Node* aux = nullptr;
  size_t interval = (size())/ 2;
  if (index <= interval) {
      aux = head;
      for (size_t i = 0; i < index; i++) {
          aux = aux->next();
      }
  } else {
      aux = tail;
      for (size_t i = 0; i < (size() - index - 1); i++) {
          aux = aux->prev();
      }
  }
  return aux->data();
}

// Procura dado.
template<typename T>
std::size_t DoublyLinkedList<T>::find(const T& data) const {
  if (empty()) {
    throw std::out_of_range("Empty list - find\n");
  } else {
    Node* aux = head;
    std::size_t index = 0;
    while (index < size()) {
      if (aux->data() == data) {
        return index;
      }
      aux = aux->next();
      index++;
    }
    return size();  //  if not found, returns size
  }
}

// Tamanho da lista.
template<typename T>
std::size_t DoublyLinkedList<T>::size() const {
  return size_;
}

}  // namespace structures

#endif
