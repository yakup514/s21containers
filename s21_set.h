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
public:
    using value_type = T;
    using key_type = T;
    using reference = T&;
    using const_reference = const T&;
    using iterator = typename AvlTree<T>::iterator;
    using const_iterator = typename AvlTree<T>::const_iterator;
    using size_type = size_t;
    using set = Set;
public:
    Set() : AvlTree<key_type>(false){};
    Set(std::initializer_list<key_type> const &items) :AvlTree<T>(items, false){};
    Set(const Set &s) : AvlTree<T>(s){};
    Set(Set &&s): AvlTree<T>(s){};
    ~Set() = default;
   
};


}
#endif /* s21_set_h */

