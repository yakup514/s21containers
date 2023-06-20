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
#include <limits>
#include <unordered_set>
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
        friend class List;
    public:
        ListConstIterator();
        ListConstIterator(ListNode&& node);
        const_reference operator*() const;
        bool operator!=(const ListConstIterator& iter) const noexcept;
        ListConstIterator operator+(size_t n);
        ListConstIterator operator-(size_t n);
        void operator++();
        void operator--();
    private:
        ListNode* data_;
    };
    class ListIterator : public ListConstIterator {
        friend class List;
    public:
        ListIterator();
        ListIterator(ListNode* node);
        //ListNode* data_;
        reference operator*();
        ListIterator operator+(size_t n);
        ListIterator operator-(size_t n);
        bool operator!=(const ListIterator& iter) const noexcept;
        void operator++();
        void operator--();
//    private:
//         ListNode* data_;
        //bool operator!=(const ListIterator& iter);
        //void operator++();
    };
    using iterator = ListIterator;
    using const_iterator = ListConstIterator;
   // const_iterator end() const;
   // const_iterator begin() const;
    iterator end() const;
    iterator begin() const;
    
    size_t distance(iterator from, iterator to);
    //size_t distance(const_iterator from, const_iterator to);
    
    bool empty();
    size_type size();
    size_type max_size();
    
    void clear();
    iterator insert(iterator pos, const_reference value);
    void erase(iterator pos);
    void push_back(const_reference value);
    void pop_back();
    void push_front(const_reference value);
    void pop_front();
    void swap(List& other);
    void merge(List& other);
    void splice(const_iterator pos, List& other);
    void reverse();
    void unique();
    void sort();
    iterator partition(iterator begin, iterator end);
    void quicksort(iterator begin, iterator end);
    template <typename... Args>
    iterator emplace(const_iterator pos, Args&&... args);
    template <typename... Args>
    void emplace_back(Args&&... args);
    template <typename... Args>
    void emplace_front(Args&&... args);
private:
    
    ListNode* head_;
    size_type size_;
    
    
};

}
//template<class value_type>
//bool operator <(typename s21::List<value_type>::const_iterator lhs, typename s21::List<value_type>::const_iterator rhs) {
//    while (lhs.data_ != head_)
//}



//------------------List Functions---------------------------
template <class value_type>
s21::List<value_type>::List() : size_(0){
   head_ = new ListNode;
   head_->next_ = head_;
   head_->prev_ = head_;
    head_->value_ = 0;
}

template<class value_type>
s21::List<value_type>::List(size_type n) : s21::List<value_type>::List() {
    if (n > max_size())
        throw std::out_of_range("size > max_size");
   ListNode* node;
   ListNode* prev_node = head_;
   for (size_t i = 0; i < n; ++i) {
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
    if (l.head_->next_ != l.head_) {
        head_->next_ = l.head_->next_;
        l.head_->prev_->next_= head_;
        size_ = l.size_;
        l.head_->next_ = l.head_;
        l.head_->prev_ = l.head_;
        l.size_ = 0;
    }
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
    if (l.head_->next_ != l.head_) {
        clear();
        head_->next_ = l.head_->next_;
        l.head_->prev_->next_= head_;
        size_ = l.size_;
        delete l.head_;
        l.head_ = nullptr;
        l.size_ = 0;
    }
}

//--------------------------List Element access
template<class value_type>
typename s21::List<value_type>::const_reference s21::List<value_type>::back() {
    return head_->prev_->value_;
}

template<class value_type>
typename s21::List<value_type>::const_reference s21::List<value_type>::front() {
    return head_->next_->value_;
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

//template <class value_type>
//s21::List<value_type>::const_iterator::ListConstIterator(ListNode&& node) : data_(nullptr) {
//}

template <class value_type>
bool s21::List<value_type>::const_iterator::operator!=(const typename s21::List<value_type>::const_iterator& iter) const noexcept{
    return data_ != iter.data_;
}

template <class value_type>
void s21::List<value_type>::const_iterator::operator++() {
   data_ = data_->next_;
}

template <class value_type>
void s21::List<value_type>::const_iterator::operator--() {
   data_ = data_->prev_;
}

template <class value_type>
typename s21::List<value_type>::const_reference s21::List<value_type>::const_iterator::operator*() const{
    return data_->value_;
}

template <class value_type>
typename s21::List<value_type>::ListConstIterator s21::List<value_type>::const_iterator::operator+(size_t n){
    const_iterator tmp = *this;
    for (size_t i = 0; i < n; ++i)
        ++tmp;
    return tmp;
}

template <class value_type>
typename s21::List<value_type>::ListConstIterator s21::List<value_type>::const_iterator::operator-(size_t n){
    const_iterator tmp = *this;
    for (size_t i = 0; i < n; ++i)
        ++tmp;
    return tmp;
}


//------------------iterator------------------------------------
template <class value_type>
s21::List<value_type>::iterator::ListIterator() : ListConstIterator() {
}

template <class value_type>
s21::List<value_type>::iterator::ListIterator(ListNode* node) : ListConstIterator() {
    this->data_ = node;
}

template <class value_type>
typename s21::List<value_type>::reference s21::List<value_type>::iterator::operator*() {
    return this->data_->value_;
}

template <class value_type>
typename s21::List<value_type>::iterator s21::List<value_type>::iterator::operator+(size_t n){
    iterator tmp = *this;
    for (size_t i = 0; i < n; ++i)
        ++(tmp);
    return tmp;
}

template <class value_type>
typename s21::List<value_type>::iterator s21::List<value_type>::iterator::operator-(size_t n){
    for (size_t i = 0; i < n; ++i)
        --(*this);
    return *this;
}

template <class value_type>
bool s21::List<value_type>::iterator::operator!=(const ListIterator& iter) const noexcept {
    return this->data_ != iter.data_;
}

template <class value_type>
void s21::List<value_type>::iterator::operator++() {
   this->data_ = this->data_->next_;
}

template <class value_type>
void s21::List<value_type>::iterator::operator--() {
   this->data_ = this->data_->prev_;
}

//---------------------------------------------------------------
//template <class value_type>
//typename s21::List<value_type>::const_iterator s21::List<value_type>::begin() const{
//   typename s21::List<value_type>::const_iterator result;
//   result.data_ = head_->next_;
//   return result;
//}

//template <class value_type>
//typename s21::List<value_type>::const_iterator s21::List<value_type>::end() const{
//   typename s21::List<value_type>::const_iterator result;
//   result.data_ = head_;
//   return result;
//}

template <class value_type>
typename s21::List<value_type>::iterator s21::List<value_type>::begin() const{
   typename s21::List<value_type>::iterator result;
   result.data_ = head_->next_;
   return result;
}

template <class value_type>
typename s21::List<value_type>::iterator s21::List<value_type>::end() const{
   typename s21::List<value_type>::iterator result;
   result.data_ = head_;
   return result;
}

//template <class value_type>
//size_t s21::List<value_type>::distance(const_iterator from, const_iterator to) {
//    size_t res = 0;
//    while (from != to) {
//        ++from;
//        ++res;
//    }
//    return res;
//}

template <class value_type>
size_t s21::List<value_type>::distance(iterator from, iterator to) {
    size_t res = 0;
    while (from != to) {
        ++from;
        ++res;
    }
    return res;
}

//-----------------------List Capacity
template <class value_type>
bool s21::List<value_type>::empty() {
    return size_ == 0;
}

template <class value_type>
typename s21::List<value_type>::size_type s21::List<value_type>::size() {
    return size_;
}
template <class value_type>
typename s21::List<value_type>::size_type s21::List<value_type>::max_size() {
    return std::numeric_limits<size_type>::max()/sizeof(ListNode);
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

template <class value_type>
typename s21::List<value_type>::iterator s21::List<value_type>::insert(iterator pos, const_reference value) {
    if (size_ >= max_size())
        throw std::out_of_range("size > max_size");
ListNode* new_node = new ListNode(value);
    pos.data_->prev_->next_ = new_node;
    new_node->prev_ = pos.data_->prev_;
    new_node->next_ = pos.data_;
    pos.data_->prev_ = new_node;
    size_ += 1;
    --pos;
    return pos;
}

template <class value_type>
void s21::List<value_type>::erase(iterator pos) {
    pos.data_->prev_->next_ = pos.data_->next_;
    pos.data_->next_->prev_ = pos.data_->prev_;
    delete pos.data_;
    size_ -= 1;
}

template <class value_type>
void s21::List<value_type>::push_back(const_reference value) {
    if (size_ >= max_size())
        throw std::out_of_range("size > max_size");
    ListNode* new_node = new ListNode(value);
    head_->prev_->next_ = new_node;
    new_node->prev_ = head_->prev_;
    new_node->next_ = head_;
    head_->prev_ = new_node;
    ++size_;
}

template <class value_type>
void s21::List<value_type>::pop_back(){
    ListNode* tmp = head_->prev_;
    tmp->prev_->next_ = head_;
    head_->prev_ = tmp->prev_;
    delete  tmp;
    --size_;
}

template <class value_type>
void s21::List<value_type>::push_front(const_reference value){
    if (size_ >= max_size())
        throw std::out_of_range("size > max_size");
    ListNode* new_node = new ListNode(value);
    head_->next_->prev_ = new_node;
    new_node->next_ = head_->next_;
    new_node->prev_ = head_;
    head_->next_ = new_node;
    ++size_;
}

template <class value_type>
void s21::List<value_type>::pop_front(){
    ListNode* tmp = head_->next_;
    tmp->next_->prev_ = head_;
    head_->next_ = tmp->next_;
    delete  tmp;
    --size_;
}

template <class value_type>
void s21::List<value_type>::swap(List& other) {
    std::swap(size_, other.size_);
    std::swap(head_, other.head_);
}

template <class value_type>
void s21::List<value_type>::merge(List& other){
    iterator other_it = other.begin();
    iterator this_it = begin();
    while (other_it != other.end()) {
        if (this_it != end() && *this_it < *other_it) {
            ++this_it;
        } else {
            ListNode* tmp = other_it.data_->next_;
            this_it.data_->prev_->next_ = other_it.data_;
            other_it.data_->prev_ = this_it.data_->prev_;
            other_it.data_->next_ = this_it.data_;
            this_it.data_->prev_ = other_it.data_;
            other_it.data_ = tmp;
        }
    }
    other.head_->prev_ = other.head_;
    other.head_->next_ = other.head_;
    size_ += other.size_;
    other.size_ = 0;
}

template <class value_type>
void s21::List<value_type>::splice(const_iterator pos, List& other) {
    const_iterator it = other.begin();
    pos.data_->prev_->next_ = it.data_;
    it.data_->prev_ = pos.data_->prev_;
    other.head_->prev_->next_ = pos.data_;
    pos.data_->prev_ = other.head_->prev_;
    other.head_->next_ = other.head_;
    other.head_->prev_ = other.head_;
    size_ += other.size_;
    other.size_ = 0;
    
}

template <class value_type>
void s21::List<value_type>::reverse() {
    auto left = begin();
    auto right = end();
    --right;
    size_t iterations = 0;
    while (iterations < size_/2) {
        std::swap(*left, *right);
        ++left;
        --right;
        ++iterations;
    }
}

template <class value_type>
void s21::List<value_type>::unique() {
    std::unordered_set<value_type> data;
    auto it = begin();
    for(auto d : *this) {
        if (data.find(d) != data.end()) {
            auto tmp = it;
            ++it;
            erase(tmp);
        } else {
            data.insert(*it);
        }
    }
}

template <class value_type>
typename s21::List<value_type>::iterator s21::List<value_type>::partition(iterator begin, iterator end) {
    iterator pivot = end;
    iterator p_ind = begin;
    auto end_list = this->end();
    for (iterator it = begin; distance(it, end_list) > distance(end, end_list); ++it) {
        if (*it <= *pivot) {
            std::swap(*it, *p_ind);
            ++p_ind;
        }
    }
    std::swap(*p_ind, *end);
    return p_ind;
}
template <class value_type>
void s21::List<value_type>::quicksort(iterator begin, iterator end) {
    iterator end_list = this->end();
    if (distance(begin, end_list) <= distance(end, end_list))
        return;
    iterator pivot = partition(begin, end);
    quicksort(begin, pivot != this->begin() ? pivot - 1 : pivot);
    quicksort(pivot != this->end() ? pivot + 1 : pivot, end);
}

template <class value_type>
void s21::List<value_type>::sort() {
    quicksort(begin(), end() - 1);
}

template <class value_type>
template <typename... Args>
typename s21::List<value_type>::iterator s21::List<value_type>::emplace(const_iterator pos, Args&&... args) {
    s21::List<value_type> tmp_list({args...});
    if (tmp_list.size() > 0) {
        if (size_ + tmp_list.size() > max_size())
            throw std::out_of_range("size > max_size");
        else
            size_ += tmp_list.size();
        const_iterator pos_next = pos + 1;
        tmp_list.head_->prev_->next_ = head_->next_;
        pos.data_->next_ = tmp_list.head_->next_;
        tmp_list.head_->next_->prev_ = pos.data_;
        pos_next.data_->prev_ = tmp_list.head_->prev_;
        tmp_list.head_->prev_->next_ = pos_next.data_;
        tmp_list.head_->next_ = tmp_list.head_;
        tmp_list.head_->prev_ = tmp_list.head_;
        ++pos;
        iterator result(pos.data_);
        return result;
    }
    return begin();
}

template <class value_type>
template <typename... Args>
void s21::List<value_type>::emplace_back(Args&&... args) {
    emplace(end() - 1, args...);
}

template <class value_type>
template <typename... Args>
void s21::List<value_type>::emplace_front(Args&&... args) {
    emplace(end(), args...);
}
//template <typename... Args>
//void emplace_front(Args&&... args);
#endif /* list_h */
