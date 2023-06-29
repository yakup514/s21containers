#ifndef s21_map_h
#define s21_map_h
#include "avl_tree.h"

namespace s21 {
template <class Key, class T>

class Map : public AvlTree<std::pair<const Key, T>> {
public:
    using key_type = Key;
    using mapped_type = T;
    using value_type = std::pair<const key_type,mapped_type>;
    using reference = value_type&;
    using const_reference = const value_type&;
    using iterator = typename AvlTree<value_type>::iterator;
    using node = typename AvlTree<value_type>::node;
    using const_iterator = typename AvlTree<T>::const_iterator;
    using size_type = size_t;
    
    Map() : AvlTree<value_type>(false){};
    Map(std::initializer_list<value_type> const &items) :AvlTree<value_type>(items, false){};
    Map(const Map &m) : AvlTree<value_type>(m){};
    Map(Map &&m): AvlTree<value_type>(m){};
    ~Map() = default;
    iterator find(const key_type& key);
    mapped_type& at(const key_type& key);
    mapped_type& operator[](const Key& key);
    std::pair<iterator, bool> insert(const value_type& value);
    std::pair<iterator, bool> insert(const key_type& key, const mapped_type& obj);
    std::pair<iterator, bool> insert_or_assign(const key_type& key, const mapped_type& obj);
    bool contains(const key_type& key);
private:
   node*  find_key(node* n, const Key& key) {
        if (!n)
            return nullptr;
        node* result;
        if (n->key_.first > key)
            result = find_key(n->left_, key);
        else if (n->key_.first < key)
            result = find_key(n->right_, key);
        else
            return n;
        return result;
    }
};

template <class key_type, class mapped_type>
typename Map<key_type, mapped_type>::iterator Map<key_type, mapped_type>::find(const key_type& key) {
    node* result = find_key(this->root_, key);
    if (result)
        return iterator(result);
    else
        return iterator(this->end_);
}

template <class key_type, class mapped_type>
typename Map<key_type, mapped_type>::mapped_type&
Map<key_type, mapped_type>::at(const key_type &key) {
    node* result = find_key(this->root_, key);
    if (!result || result == this->end_)
        throw std::out_of_range ("key not found");
    return result->key_.second;

}

template <class key_type, class mapped_type>
typename Map<key_type, mapped_type>::mapped_type&  Map<key_type, mapped_type>::operator[](const key_type& key) {
    return at(key);
}

template <class key_type, class mapped_type>
std::pair<typename Map<key_type, mapped_type>::iterator, bool> Map<key_type, mapped_type>::insert(const value_type& value) {
    iterator it = find(value.first);
    if ( it == this->end_)
        return AvlTree<value_type>::insert(value);
    else
        return {it, false};
}

template <class key_type, class mapped_type>
std::pair<typename Map<key_type, mapped_type>::iterator, bool> Map<key_type, mapped_type>::insert(const key_type& key, const mapped_type& obj) {
    return insert({key, obj});
}

template <class key_type, class mapped_type>
std::pair<typename Map<key_type, mapped_type>::iterator, bool> Map<key_type, mapped_type>::insert_or_assign(const key_type& key, const mapped_type& obj) {
    node* res = find_key(this->root_, key);
    if (!res)
        return insert({key, obj});
    else {
        res->key_.second = obj;
        return {iterator(res), false};
    }
}

template <class key_type, class mapped_type>
bool Map<key_type, mapped_type>::contains(const key_type& key) {
    if ( find_key(this->root_, key))
        return true;
    else
        return false;
}
}
#endif
