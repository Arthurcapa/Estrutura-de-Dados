/// Copyright [2018] <Arthur Machado Capaverde>

#include <stdexcept>

namespace structures {


template<typename T>
/// Classe LinkedQueue
class LinkedQueue {
 public:
    LinkedQueue() {
        head = nullptr;
        tail = nullptr;
        size_ = 0;
    }

    ~LinkedQueue() {
        clear();
    }

     /// limpar
    void clear() {
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
        tail = nullptr;
        size_ = 0;
    }

      /// enfilerar
    void enqueue(const T& data) {
          Node* aux;
          Node* nodoNovo = new Node(data);
          if (empty()) {
              head = nodoNovo;
              tail = nodoNovo;
            } else {
                aux = tail;
                aux->next(nodoNovo);
                tail = nodoNovo;
            }
          size_++;
    }

      /// desenfilerar
    T dequeue() {
        Node* aux;
        T retorno;
        if (empty()) {
           throw std::out_of_range("LISTA VAZIA");
        } else {
            retorno = head->data();
            aux = head->next();
            delete(head);
            head = aux;
            if (size_ == 1) {
                head = nullptr;
                tail = nullptr;
            }
            size_--;
            return retorno;
              }
    }

      /// primeiro dado
    T& front() const {
        if (empty()) {
            throw std::out_of_range("LISTA VAZIA");
        } else {
            return head->data();
        }
    }

      /// último dado
    T& back() const {
        if (empty()) {
            throw std::out_of_range("LISTA VAZIA");
        } else {
            return tail->data();
        }
    }

     /// fila vazia
    bool empty() const {
        if (size_ == 0) {
            return true;
        } else {
            return false;
        }
    }

      /// tamanho
    std::size_t size() const {
        return size_;
    }

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
    Node* head;  /// nodo-cabeça
    Node* tail;  /// nodo-fim
    std::size_t size_;  /// tamanho
};

}  /// namespace structures
