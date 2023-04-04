/// Copyright 2018 <Arthur Machado Capaverde>
#ifndef STRUCTURES_AVL_TREE_H
#define STRUCTURES_AVL_TREE_H

#include <cstdint>
#include <stdexcept>
#include <algorithm>
#include "array_list.h"

namespace structures {

/// Classe AVLTree
template<typename T>
class AVLTree {
public:
    AVLTree();
    ~AVLTree();

    void insert(const T& data);
    void remove(const T& data);

    bool contains(const T& data) const;
    bool empty() const;
    std::size_t size() const;

    ArrayList<T> pre_order() const;
    ArrayList<T> in_order() const;
    ArrayList<T> post_order() const;

private:
    struct Node {
        /// Construtor
        explicit Node(const T& data) :
        data_{data}
        {}

        /// Destrutor
        ~Node() {
            delete left_;
            delete right_;
        }

        T data_;
        std::size_t height_{0};
        Node* left_{nullptr};
        Node* right_{nullptr};

        /// Insere
        void insert(const T& data) {
            if (data < data_) {
                if (left_ == nullptr) {
                    left_ = new Node(data);
                    if (left_ == nullptr)
                        throw std::out_of_range("Full tree!");
                } else {
                    left_->insert(data);
                }
            } else {
                if (right_ == nullptr) {
                    right_ = new Node(data);
                    if (right_ == nullptr)
                        throw std::out_of_range("Full tree!");
                } else {
                    right_->insert(data);
                }
            }
        }

        /// Remove
        bool remove(const T& data) {
            bool deleted = false;
            if (data < data_ && left_ != nullptr) {
                left_ = remove(data, left_, deleted);
            } else if (data > data_ && right_ != nullptr) {
                right_ = remove(data, right_, deleted);
            } else if (data == data_) {
                if (right_ != nullptr && left_ != nullptr) {
                    Node* temp = right_->minimum();
                    data_ = temp->data_;
                    right_ = remove(data_, right_, deleted);
                } else if (right_ != nullptr) {
                    Node* temp = right_;
                    data_ = temp->data_;
                    right_ = temp->right_;
                    left_ = temp->left_;
                    temp->right_ = temp->left_ = nullptr;
                    delete temp;
                    deleted = true;
                } else if (left_ != nullptr) {
                    Node* temp = left_;
                    data_ = temp->data_;
                    right_ = temp->right_;
                    left_ = temp->left_;
                    temp->right_ = temp->left_ = nullptr;
                    delete temp;
                    deleted = true;
                }
            }
            return deleted;
        }

        /// Contains
        bool contains(const T& data) const {
            if (data < data_)
                return left_ == nullptr? false : left_->contains(data);
            else if (data > data_)
                return right_ == nullptr? false : right_->contains(data);
            else
                return true;
        }

        /// Atualiza altura
        void updateHeight() {
            int h_left, h_right;
            if (left_ == nullptr && right_ == nullptr) {
                height_ = 0;
            } else {
                if (left_ != nullptr) {
                    left_->updateHeight();
                    switch (left_->type_balance()) {
                        case 0:
                            h_left = height(left_->left_);
                            h_right = height(left_->right_);
                            left_->height_ = std::max(h_left, h_right) + 1;
                            break;
                        case 1:
                            left_ = left_->simpleLeft();
                            break;
                        case 2:
                            left_ = left_->doubleLeft();
                            break;
                        case 3:
                            left_ = left_->simpleRight();
                            break;
                        case 4:
                            left_ = left_->doubleRight();
                            break;
                        default :
                            break;
                    }
                }
                if (right_ != nullptr) {
                    right_->updateHeight();
                    switch (right_->type_balance()) {
                        case 0:
                            h_left = height(right_->left_);
                            h_right = height(right_->right_);
                            right_->height_ = std::max(h_left, h_right) + 1;
                            break;
                        case 1:
                            right_ = right_->simpleLeft();
                            break;
                        case 2:
                            right_ = right_->doubleLeft();
                            break;
                        case 3:
                            right_ = right_->simpleRight();
                            break;
                        case 4:
                            right_ = right_->doubleRight();
                            break;
                        default :
                            break;
                    }
                }
            }
        }

        /// Tipo de balanceamento
        std::size_t type_balance() {
            if (height(left_) - height(right_) > 1) {
                if (height(left_->left_) > height(left_->right_))
                    return 1;
                else
                    return 2;
            } else if (height(right_) - height(left_) > 1) {
                if (height(right_->right_) > height(right_->left_))
                    return 3;
                else
                    return 4;
            }
            return 0;
        }

        /// Altura node
        int height(Node* tnode) {
            if (tnode == nullptr)
                return -1;
            else
                return tnode->height_;
        }

        /// Rotaçao simples a esquerda
        Node* simpleLeft() {
            Node* temp = left_;
            left_ = temp->right_;
            temp->right_ = this;

            height_ = std::max(height(left_), height(right_) + 1);
            temp->height_ = std::max(height(temp->left_), height(this)) + 1;

            return temp;
        }

        /// Rotaçao dupla a esquerda
        Node* simpleRight() {
            Node* temp = right_;
            right_ = temp->left_;
            temp->left_ = this;

            height_ = std::max(height(right_), height(left_) + 1);
            temp->height_ = std::max(height(temp->right_), height(this)) + 1;

            return temp;
        }

        /// Rotaçao simples a direita
        Node* doubleLeft() {
            left_ = left_->simpleRight();
            return this->simpleLeft();
        }

        /// Rotaçao dupla a direita
        Node* doubleRight() {
            right_ = right_->simpleLeft();
            return this->simpleRight();
        }

        /// Pre-ordem
        void pre_order(ArrayList<T>& v) const {
            v.push_back(data_);
            if (left_ != nullptr)
                left_->pre_order(v);
            if (right_ != nullptr)
                right_->pre_order(v);
        }

        /// Em ordem
        void in_order(ArrayList<T>& v) const {
            if (left_ != nullptr)
                left_->in_order(v);
            v.push_back(data_);
            if (right_ != nullptr)
                right_->in_order(v);
        }

        /// Pos-ordem
        void post_order(ArrayList<T>& v) const {
            if (left_ != nullptr)
                left_->post_order(v);
            if (right_ != nullptr)
                right_->post_order(v);
            v.push_back(data_);
        }

     private:
        /// Remove
        Node* remove(const T& data, Node* arv, bool& deleted) {
            deleted = false;
            if (arv == nullptr)
                return arv;
            if (data < arv->data_) {
                arv->left_ = remove(data, arv->left_, deleted);
                return arv;
            }
            if (data > arv->data_) {
                arv->right_ = remove(data, arv->right_, deleted);
                return arv;
            }
            if (arv->right_ != nullptr && arv->left_ != nullptr) {
                Node* temp = arv->right_->minimum();
                arv->data_ = temp->data_;
                arv->right_ = remove(data, arv->right_, deleted);
                return arv;
            }
            Node* temp = nullptr;
            if (arv->right_ != nullptr)
                temp = arv->right_;
            else
                temp = arv->left_;

            arv->right_ = arv->left_ = nullptr;
            delete arv;
            deleted = true;
            return temp;
        }

        /// Encontra node menor
        Node* minimum() {
            if (left_ == nullptr)
                return this;
            return left_->minimum();
        }
    };

    Node* root_{nullptr};
    std::size_t size_{0u};
};

/// Construtor
template<typename T>
AVLTree<T>::AVLTree()
{}

/// Destrutor
template<typename T>
AVLTree<T>::~AVLTree() {
    delete root_;
}

/// Insere
template<typename T>
void AVLTree<T>::insert(const T& data) {
    if (empty()) {
        root_ = new Node(data);
        if (root_ == nullptr)
            throw std::out_of_range("Full tree!");
    } else {
        root_->insert(data);
    }
    ++size_;

    int h_left, h_right;
    root_->updateHeight();
    switch (root_->type_balance()) {
        case 0:
            h_left = root_->height(root_->left_);
            h_right = root_->height(root_->right_);
            root_->height_ = std::max(h_left, h_right) + 1;
            break;
        case 1:
            root_ = root_->simpleLeft();
            break;
        case 2:
            root_ = root_->doubleLeft();
            break;
        case 3:
            root_ = root_->simpleRight();
            break;
        case 4:
            root_ = root_->doubleRight();
            break;
        default :
            break;
    }
}

/// Remove
template<typename T>
void AVLTree<T>::remove(const T& data) {
    if (empty())
        throw std::out_of_range("Empty tree!");

    if (size() != 1u) {
        if (root_->remove(data)) {
            --size_;
            int h_left, h_right;
            root_->updateHeight();
            switch (root_->type_balance()) {
                case 0:
                    h_left = root_->height(root_->left_);
                    h_right = root_->height(root_->right_);
                    root_->height_ = std::max(h_left, h_right) + 1;
                    break;
                case 1:
                    root_ = root_->simpleLeft();
                    break;
                case 2:
                    root_ = root_->doubleLeft();
                    break;
                case 3:
                    root_ = root_->simpleRight();
                    break;
                case 4:
                    root_ = root_->doubleRight();
                    break;
                default :
                    break;
            }
        }
    } else {
        if (root_->data_ == data) {
            delete root_;
            root_ = nullptr;
            --size_;
        }
    }
}

/// Contains
template<typename T>
bool AVLTree<T>::contains(const T& data) const {
    return empty()? false : root_->contains(data);
}

/// Testa arvore vazia
template<typename T>
bool AVLTree<T>::empty() const {
    return size_ == 0u;
}

/// Tamanho
template<typename T>
std::size_t AVLTree<T>::size() const {
    return size_;
}

/// Pre-ordem
template<typename T>
ArrayList<T> AVLTree<T>::pre_order() const {
    ArrayList<T> v{size()};
    if (!empty())
        root_->pre_order(v);
    return v;
}

/// Em ordem
template<typename T>
ArrayList<T> AVLTree<T>::in_order() const {
    ArrayList<T> v{size_};
    if (!empty())
        root_->in_order(v);
    return v;
}

/// Pps-ordem
template<typename T>
ArrayList<T> AVLTree<T>::post_order() const {
    ArrayList<T> v{size_};
    if (!empty())
        root_->post_order(v);
    return v;
}

}  //  namespace structures

#endif
