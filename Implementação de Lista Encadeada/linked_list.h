//! Copyright 2018 <Arthur Machado Capaverde>
#ifndef STRUCTURES_LINKED_LIST_H
#define STRUCTURES_LINKED_LIST_H

#include <cstdint>
#include <stdexcept>

namespace structures {

//! ...
template<typename T>
class LinkedList {
 public:
    //! ...
    LinkedList();  // construtor padrão
    //! ...
    ~LinkedList();  // destrutor
    //! ...
    void clear();  // limpar lista
    //! ...
    void push_back(const T& data);  // inserir no fim
    //! ...
    void push_front(const T& data);  // inserir no início
    //! ...
    void insert(const T& data, std::size_t index);  // inserir na posição
    //! ...
    void insert_sorted(const T& data);  // inserir em ordem
    //! ...
    T& at(std::size_t index);  // acessar um elemento na posição index
    //! ...
    T pop(std::size_t index);  // retirar da posição
    //! ...
    T pop_back();  // retirar do fim
    //! ...
    T pop_front();  // retirar do início
    //! ...
    void remove(const T& data);  // remover específico
    //! ...
    bool empty() const;  // lista vazia
    //! ...
    bool contains(const T& data) const;  // contém
    //! ...
    std::size_t find(const T& data) const;  // posição do dado
    //! ...
    std::size_t size() const;  // tamanho da lista

 private:
    class Node {  // Elemento
     public:
        explicit Node(const T& data):
            data_{data}
        {}

        Node(const T& data, Node* next):
            data_{data},
            next_{next}
        {}

        T& data() {  // getter: dado
            return data_;
        }

        const T& data() const {  // getter const: dado
            return data_;
        }

        Node* next() {  // getter: próximo
            return next_;
        }

        const Node* next() const {  // getter const: próximo
            return next_;
        }

        void next(Node* node) {  // setter: próximo
            next_ = node;
        }

     private:
        T data_;
        Node* next_{nullptr};
    };

    Node* end() {  // último nodo da lista
        auto it = head;
        for (auto i = 1u; i < size(); ++i) {
            it = it->next();
        }
        return it;
    }

    Node* head{nullptr};
    std::size_t size_{0u};
};

}  // namespace structures

template<typename T>
structures::LinkedList<T>::LinkedList() {
    head = nullptr;
    size_ = 0;
}

template<typename T>
structures::LinkedList<T>::~LinkedList() {
    clear();
}

template<typename T>
void structures::LinkedList<T>::clear() {
    Node* anterior;
    Node* atual;
    atual = head;
    while (atual != nullptr) {
        anterior = atual;
        atual = anterior->next();
        // free(anterior->data());
        delete(anterior);
    }
    head = nullptr;
    size_ = 0;
}

template<typename T>
void structures::LinkedList<T>::push_back(const T& data) {
    Node* nodoNovo;
    nodoNovo = new Node(data, nullptr);
    if (nodoNovo == nullptr) {
        throw std::out_of_range("LISTA CHEIA");
    } else {
        if (empty()) {
            head = nodoNovo;
        } else {
            end()->next(nodoNovo);
        }
        size_++;
    }
}

template<typename T>
void structures::LinkedList<T>::push_front(const T& data) {
    Node* nodoNovo;
    Node* aux;
    nodoNovo = new Node(data, nullptr);
    if (nodoNovo == nullptr) {
        throw std::out_of_range("LISTA CHEIA");
    } else {
        if (empty()) {
            head = nodoNovo;
        } else {
            aux = head;
            head = nodoNovo;
            head->next(aux);
        }
        size_++;
    }
}

template<typename T>
void structures::LinkedList<T>::insert(const T& data, std::size_t index) {
    if (index < 0 || index > (size())) {
        throw std::out_of_range("POSICAO INVALIDA");
    } else {
        if (index == 0) {
            push_front(data);
        } else {
            Node* novo;
        novo = new Node(data, nullptr);
        if (novo == nullptr) {
            throw std::out_of_range("LISTA CHEIA");
        } else {
            Node* aux = head;
            size_t index_ = 1;
            while (index_ < index) {
                index_++;
                aux = aux->next();
            }
            novo->next(aux->next());
            aux->next(novo);
            size_++;
            }
        }
    }
}

template<typename T>
void structures::LinkedList<T>::insert_sorted(const T& data) {
    Node* aux = head;
    size_t index = 0;
    while (aux != nullptr && aux->data() < data) {
        aux = aux->next();
        index++;
    }
    insert(data, index);
}

template<typename T>
T& structures::LinkedList<T>::at(std::size_t index) {
    Node* aux;
    size_t index_ = 0;
    if (empty()) {
        throw std::out_of_range("LISTA VAZIA");
    } else {
            if (index < 0 || index > (size_-1)) {
                throw std::out_of_range("POSICAO INVALIDA");
            }
            aux = head;
                while (index_ < index) {
                    index_++;
                    aux = aux->next();
                }
            }
            return aux->data();
        }

template<typename T>
T structures::LinkedList<T>::pop(std::size_t index) {
    if (empty()) {
        throw std::out_of_range("LISTA VAZIA");
    } else {
        if (index < 0 || index > (size_-1)) {
            throw std::out_of_range("POSICAO INVALIDA");
        } else {
            Node* aux_atual = nullptr;
            Node* aux_del = head;
            T retorno;
            std::size_t index_ = 0;
            while (index_ < index) {
                    aux_atual = aux_del;
                    aux_del = aux_del -> next();
                    index_++;
                }
            retorno = aux_del->data();
            aux_atual->next(aux_del->next());
            delete(aux_del);
            size_--;
            return retorno;
        }
    }
}

template<typename T>
T structures::LinkedList<T>::pop_back() {
    if (empty()) {
        throw std::out_of_range("LISTA VAZIA");
    } else {
        if (size_ == 1) {
            return pop_front();
        } else {
            return pop(find(end()->data()));
        }
    }
}

template<typename T>
T structures::LinkedList<T>::pop_front() {
    Node* aux;
    T data_aux;
    if (empty()) {
        throw std::out_of_range("LISTA VAZIA");
    } else {
        aux = head;
        data_aux = aux->data();
        head = aux->next();
        size_--;
        // free(head->data());
        delete(aux);
        return data_aux;
    }
}

template<typename T>
void structures::LinkedList<T>::remove(const T& data) {
    if (empty()) {
        throw std::out_of_range("LISTA VAZIA");
    } else {
        if (contains(data)) {
            size_t index = find(data);
            pop(index);
        } else {
            throw std::out_of_range("NAO CONTEM ELEMENTO");
        }
    }
}

template<typename T>
bool structures::LinkedList<T>::empty() const {
    if (size_ == 0) {
        return true;
    } else {
        return false;
    }
}

template<typename T>
bool structures::LinkedList<T>::contains(const T& data) const {
    Node* aux;
    if (empty()) {
        throw std::out_of_range("LISTA VAZIA");
    } else {
        aux = head;
        while (aux != nullptr) {
            if (aux->data() == data) {
                return true;
            }
            aux = aux->next();
        }
        return false;
    }
}

template<typename T>
std::size_t structures::LinkedList<T>::find(const T& data) const {
    Node* aux;
    size_t index = 0;
    if (empty()) {
        throw std::out_of_range("LISTA VAZIA");
    } else {
            aux = head;
             while (aux != nullptr) {
                if (aux->data() == data) {
                    return index;
                }
            index++;
            aux = aux->next();
            }
        }
    return size_;
}

template<typename T>
std::size_t structures::LinkedList<T>::size() const {
    return size_;
}

#endif
