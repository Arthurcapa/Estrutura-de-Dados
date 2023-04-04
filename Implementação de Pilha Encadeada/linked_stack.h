/// Copyright [2018] <Arthur Machado Capaverde>

#include <stdexcept>

namespace structures {

template<typename T>
/// Classe LinkedStack
class LinkedStack {
 public:
    LinkedStack() {
        top_ = nullptr;
        size_ = 0;
    }

    ~LinkedStack() {
        clear();
    }
    /// classe clear
    void clear() {
         Node* anterior;
       Node* atual;
       atual = top_;
       while (atual != nullptr) {
           anterior = atual;
           atual = anterior->next();
           // free(anterior->data());
           delete(anterior);
       }
       top_ = nullptr;
       size_ = 0;
    }  /// limpa pilha

    void push(const T& data) {
        Node* aux;
        Node* nodoNovo = new Node(data);
        aux = top_;
        top_ = nodoNovo;
        nodoNovo->next(aux);
        size_++;
    }  /// empilha

    T pop() {
        Node* aux;
        T retorno;
         if (empty()) {
         throw std::out_of_range("LISTA VAZIA");
            } else {
                retorno = top_->data();
                   aux = top_->next();
                   delete(top_);
                   size_--;
                   top_ = aux;
                   return retorno;
            }
    }  /// desempilha

    T& top() const {
        if (empty()) {
            throw std::out_of_range("LISTA VAZIA");
        } else {
            return top_->data();
        }
    }  /// dado no topo

    bool empty() const {
        if (size_ == 0) {
            return true;
        } else {
            return false;
        }
    }  /// pilha vazia

    std::size_t size() const {
        return size_;
    }  /// tamanho da pilha

 private:
    class Node {
     public:
        explicit Node(const T& data) {
            data_= data;
            next_ = nullptr;
        }

        Node(const T& data, Node* next) {
            data_ = data;
            next_ = next;
        }

        T& data() {
            return data_;
        }  // getter: info

        const T& data() const {
            return data_;
        }  // getter-constante: info

        Node* next() {
            return next_;
        }  // getter: próximo

        const Node* next() const {
            return next_;
        }  // getter-constante: próximo

        void next(Node* next) {
            next_ = next;
        }  // setter: próximo

     private:
        T data_;
        Node* next_;
    };

    Node* top_;  // nodo-topo
    std::size_t size_;  // tamanho
};

}  // namespace structures
