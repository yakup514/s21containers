//
//  s21_set.h
//  cont
//
//  Created by mcbk on 20.06.2023.
//

#ifndef s21_set_h
#define s21_set_h
#include "avl_tree.h"

namespace s21 {
template <class T>
class Set : public AvlTree<T>{
    using value_type = T;
    using key_type = T;
    using reference = T&;
    using const_reference = const T&;
    using iterator = typename AvlTree<T>::iterator;
    using const_iterator = typename AvlTree<T>::const_iterator;
    using size_type = size_t;
    using set = Set;
public:
    Set() : AvlTree<key_type>(){};
    Set(std::initializer_list<key_type> const &items);
    Set(const Set &s);
    Set(Set &&s);
    ~Set() = default;
    void operator=(Set &&s) noexcept;
};

template <class key_type>
Set<key_type>::Set(std::initializer_list<key_type> const &items) {
    for (auto k : items) {
        if (!(this->contains(k)))
            this->insert(k);
    }
        
}
template <class key_type>
Set<key_type>::Set(const Set &s) {
    for (auto k : s)
        this->insert(k);
}

template <class key_type>
Set<key_type>::Set(Set &&s) {
    this->root_ = s.root_;
    this-> end_ = s.end_;
    this->begin_ = s.begin_;
    this->size_ = s.size_;
    s.size_ = 0;
    s.begin_ = s.end_ = s.root_ = nullptr;
}

template <class key_type>
void Set<key_type>::operator=(Set &&s) noexcept {
    this->root_ = s.root_;
    this-> end_ = s.end_;
    this->begin_ = s.begin_;
    this->size_ = s.size_;
    s.size_ = 0;
    s.begin_ = s.end_ = s.root_ = nullptr;
}

}
#endif /* s21_set_h */

