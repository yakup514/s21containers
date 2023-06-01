//
//  list.h
//  cont
//
//  Created by mcbk on 11.05.2023.
//

#ifndef list_h
#define list_h
#include <cstddef>
#include <initializer_list>
namespace s21 {
template <class T>
class List  {
public:
    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using size_type = size_t;
    List();
    List(size_type n);
    List(const std::initializer_list<value_type> &items);
    List(const List& l);
    List(List&& l);
    ~List();
    void operator=(List &&l) noexcept;
    const_reference front();
    const_reference back();
    struct ListNode {
    public:
        ListNode();
        ListNode(const value_type& val);
        value_type value_;
        ListNode* next_;
        ListNode* prev_;
    };
    class ListConstIterator {
    public:
        ListConstIterator();
        ListNode* data_;
        const_reference operator*() const;
        bool operator!=(const ListConstIterator& iter) const noexcept;
        void operator++();
    };
    class ListIterator : public ListConstIterator {
    public:
        ListIterator();
        //ListNode* data_;
        reference operator*();
        //bool operator!=(const ListIterator& iter);
        //void operator++();
    };
    using iterator = ListIterator;
    using const_iterator = ListConstIterator;
    const_iterator end() const;
    const_iterator begin() const;
    iterator end();
    iterator begin();
    
    void clear();
private:
    ListNode* head_;
    size_type size_;
    
};
}

//------------------List Functions---------------------------
template <class value_type>
s21::List<value_type>::List() : size_(0){
   head_ = new ListNode;
   head_->next_ = head_;
   head_->prev_ = head_;
}

template<class value_type>
s21::List<value_type>::List(size_type n) : s21::List<value_type>::List() {
   ListNode* node;
   ListNode* prev_node = head_;
   for (int i = 0; i < n; ++i) {
       node = new ListNode;
       prev_node->next_ = node;
       node->prev_ = prev_node;
       prev_node = node;
   }
   prev_node->next_ = head_;
   head_->prev_ = prev_node;
    size_ = n;
}

template<class value_type>
s21::List<value_type>::List(const std::initializer_list<value_type> &items) : s21::List<value_type>::List(items.size()) {
    auto it = begin();
    for (auto item : items) {
        *it = item;
        ++it;
    }
}

template<class value_type>
s21::List<value_type>::List(const List& l) : s21::List<value_type>::List(l.size_) {
    auto it = begin();
    for (auto l_node : l) {
        *it = l_node;
        ++it;
    }
}

template<class value_type>
s21::List<value_type>::List(List&& l) : s21::List<value_type>::List(){
    head_->next_ = l.head_->next_;
    l.head_->prev_->next_= head_;
    size_ = l.size_;
    delete l.head_;
    l.head_ = nullptr;
}

template<class value_type>
s21::List<value_type>::~List() {
    clear();
    if (head_) {
        delete head_;
    }
}

template <class value_type>
void s21::List<value_type>::operator=(List &&l) noexcept{
    clear();
    head_->next_ = l.head_->next_;
    l.head_->prev_->next_= head_;
    size_ = l.size_;
    delete l.head_;
    l.head_ = nullptr;
}

//--------------------------List Element access
template<class value_type>
typename s21::List<value_type>::const_reference s21::List<value_type>::back() {
    return head_->prev_;
}

//-----------------------------------------------------------------

template <class value_type>
s21::List<value_type>::ListNode::ListNode() : value_(), next_(nullptr), prev_(nullptr){
}

template <class value_type>
s21::List<value_type>::ListNode::ListNode(const value_type& val) : value_(val), next_(nullptr), prev_(nullptr){
}


//------------------const-iterator------------------------------------

template <class value_type>
s21::List<value_type>::const_iterator::ListConstIterator() : data_(nullptr) {
}

template <class value_type>
bool s21::List<value_type>::const_iterator::operator!=(const typename s21::List<value_type>::const_iterator& iter) const noexcept{
    return data_ != iter.data_;
}

template <class value_type>
void s21::List<value_type>::const_iterator::operator++() {
   data_ = data_->next_;
}

template <class value_type>
typename s21::List<value_type>::const_reference s21::List<value_type>::const_iterator::operator*() const{
    return data_->value_;
}

//------------------iterator------------------------------------
template <class value_type>
s21::List<value_type>::iterator::ListIterator() : ListConstIterator() {
}

template <class value_type>
typename s21::List<value_type>::reference s21::List<value_type>::iterator::operator*() {
    return this->data_->value_;
}




//---------------------------------------------------------------
template <class value_type>
typename s21::List<value_type>::const_iterator s21::List<value_type>::begin() const{
   typename s21::List<value_type>::const_iterator result;
   result.data_ = head_->next_;
   return result;
}

template <class value_type>
typename s21::List<value_type>::const_iterator s21::List<value_type>::end() const{
   typename s21::List<value_type>::const_iterator result;
   result.data_ = head_;
   return result;
}

template <class value_type>
typename s21::List<value_type>::iterator s21::List<value_type>::begin() {
   typename s21::List<value_type>::iterator result;
   result.data_ = head_->next_;
   return result;
}

template <class value_type>
typename s21::List<value_type>::iterator s21::List<value_type>::end() {
   typename s21::List<value_type>::iterator result;
   result.data_ = head_;
   return result;
}



//-------------------------List Modifiers----------------
template <class value_type>
void s21::List<value_type>::clear() {
    if (head_) {
        ListNode* next = head_->next_;
        while (next != head_) {
            ListNode* tmp = next;
            next = next->next_;
            delete tmp;
        }
    }
    size_ = 0;
}




#endif /* list_h */
