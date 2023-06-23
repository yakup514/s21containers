 //
//  list.cpp
//  cont
//
//  Created by mcbk on 11.05.2023.
//

#include "s21_list.h"
template <class T>
s21::List<T>::List() {
    head_ = new ListNode;
    head_->next_ = head_;
    head_->prev = head_;
}

template<class T>
s21::List<T>::List(size_t n) : s21::List<T>::List() {
    ListNode* node;
    ListNode* prev_node = head_;

    for (int i = 0; i < n; ++i) {
        node = new ListNode;
        prev_node->next = node;
        node->prev_ = prev_node;
        prev_node = node;
    }
    prev_node->next_ = head_;
    head_->prev_ = prev_node;
}

template <class T>
s21::List<T>::ListNode::ListNode() : value_(), next_(nullptr), prev_(nullptr){
}

template <class T>
s21::List<T>::ListNode::ListNode(const T& val) : value_(val), next_(nullptr), prev_(nullptr){
}

template <class T>
s21::List<T>::Iterator::Iterator() : data_(nullptr) {
}

//template <class T>
//bool s21::List<T>::Iterator::operator!=(const typename s21::List<T>::Iterator& iter) {
//    return *this != *iter;
//}

template <class T>
void s21::List<T>::Iterator::operator++() {
    data_ = data_->next_;
}

//template <class T>
//typename s21::List<T>::ListNode s21::List<T>::Iterator::operator*() {
//    return *data_;
//}

template <class T>
typename s21::List<T>::Iterator s21::List<T>::begin() {
    typename s21::List<T>::Iterator result;
    result.data_ = head_->next_;
    return result;
}

template <class T>
typename s21::List<T>::Iterator s21::List<T>::end() {
    typename s21::List<T>::Iterator result;
    result.data_ = head_;
    return result;
}


