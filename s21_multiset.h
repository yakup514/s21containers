//
//  s21_multiset.h
//  cont
//
//  Created by mcbk on 26.06.2023.
//

#ifndef s21_multiset_h
#define s21_multiset_h

#include "avl_tree.h"

namespace s21 {
template <class T>
class MultiSet : public AvlTree<T>{
public:
    using value_type = T;
    using key_type = T;
    using reference = T&;
    using const_reference = const T&;
    using iterator = typename AvlTree<T>::iterator;
    using const_iterator = typename AvlTree<T>::const_iterator;
    using size_type = size_t;
    using multiset = MultiSet;
public:
    MultiSet() : AvlTree<key_type>(true){};
    MultiSet(std::initializer_list<key_type> const &items) :AvlTree<T>(items, true){};
    MultiSet(const MultiSet &s) : AvlTree<T>(s){
    };
    MultiSet(MultiSet &&s): AvlTree<T>(s){};
    ~MultiSet() = default;
    //---------------------------------Modifiers-----------
    iterator insert(const_reference key);
   
    
};

//---------------------------------Modifiers-----------
template <class key_type>
typename MultiSet<key_type>::iterator MultiSet<key_type>::insert(const_reference key) {
    if (this->size_ == 0) {
        this->begin_= this->root_ = new typename AvlTree<key_type>::node(key);
        this->begin_->parent_ = nullptr;
        this->begin_->right_ = this->end_;
        this->end_->parent_ = this->begin_;
        ++this->size_;
        return this->begin();
    } else {
        if (this->max_size() == this->size_) {
           throw std::overflow_error(
               "size > max_size");
         }
        this->root_ = this->insert_key(this->root_, nullptr, key);
        this->end_->key_ = std::max(this->end_->key_, key);
        ++this->size_;
    }

    return this->find(key);
}



}
#endif /* s21_multiset_h */
