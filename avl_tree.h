//
//  avl_tree.h
//  cont
//
//  Created by mcbk on 14.06.2023.
//

#ifndef avl_tree_h
#define avl_tree_h
#include <iostream>
#include <limits>
#include <vector>
namespace s21 {
template <class T>

class AvlTree {
protected:
    struct TreeNode;
    using node = TreeNode;
public:
    class TreeIterator;
    class TreeConstIterator;
    using value_type = T;
    using key_type = T;
    using reference = T&;
    using const_reference = const T&;
    using iterator = TreeIterator;
    using const_iterator = TreeConstIterator;
    using size_type = size_t;
    
    
public:
    AvlTree(bool multi);
    AvlTree(value_type key, bool multi);
    AvlTree(std::initializer_list<value_type> const &items, bool multi);
    AvlTree(const AvlTree& other);
    AvlTree(AvlTree&& other);
    void operator=(AvlTree &&other) noexcept;
    virtual ~AvlTree();
protected:
    struct TreeNode {
        friend AvlTree;
    public:
        TreeNode(T val) : key_(val), height_(1) {};
        TreeNode() : height_(1) {};
        T key_{};
        TreeNode* left_{};
        TreeNode* right_{};
        TreeNode* parent_{};
        int height_;
    };
public:
    class TreeConstIterator {
        friend AvlTree;
    public:
        //---------------------member functions--------------------------
        TreeConstIterator() : data_(nullptr){};
        TreeConstIterator(node* n) : data_(n){};
        TreeConstIterator(const TreeConstIterator& it) : TreeConstIterator(it.data_){};
        const_reference operator*() const;
        bool operator!=(const TreeConstIterator& iter) const noexcept;
        void operator++() noexcept;
        void operator--() noexcept;
    protected:
        node* data_;
    };
    
    class TreeIterator : public TreeConstIterator{
        friend AvlTree;
    public:
        TreeIterator() : TreeConstIterator() {};
        TreeIterator(node* n) {this->data_ = n;}
        TreeIterator(const TreeIterator& it) : TreeIterator(it.data_){};
        reference operator*() noexcept;
        bool operator!=(const TreeIterator& iter) const noexcept;
        bool operator==(const TreeIterator& iter) const noexcept;
        void operator++() noexcept;
        void operator--() noexcept;
    };
public:
    //------------------------------iterators access---------------------------
    iterator begin() const noexcept;
    iterator end() const noexcept;
    
    //------------------------------capacity------------------------------------
    bool empty() const noexcept;
    size_type size() const noexcept;
    size_type max_size() const noexcept;
    
    //------------------------------Modifiers-----------------------------------
    void clear() noexcept;
    void erase(iterator pos);
    void swap(AvlTree& other) noexcept;
    void merge(AvlTree& other);
    
    //------------------------------Lookup-----------------------------------
    iterator find(const_reference key);
    bool contains(const_reference key) ;
    std::pair<iterator, bool> insert(const_reference key);
    size_type count(const_reference key) ;
    std::pair<iterator,iterator> equal_range(const_reference key);
    iterator lower_bound(const_reference key);
    iterator upper_bound(const_reference key);
    //----------------------------emplace------------------------------------
    template <typename... Args>
    std::vector<std::pair<iterator,bool>> emplace(Args&&... args);
    void print() {print_tree(root_);};
protected:
    //----------------------tree service func-----------------------------------
    void destruct_node(node* n);
    int get_height(node* n) {return n ? n->height_ : 0;}
    int get_bfactor(node* n) {return get_height(n->right_) - get_height(n->left_);}
    void fix_height(node* n) {
        n->height_ = std::max(get_height(n->right_),get_height(n->left_)) + 1;
    }
    node* rotate_right(node* n);
    node* rotate_left(node* n);
    node* balance(node* n);
    
    node* find_min(node* n);
    node* delete_min(node* n);
    
    node* insert_key(node* n, node* prev_node, value_type key);
    node* delete_key(node* n, value_type key);
    node* find_key(node* n, const value_type& key);
    void print_tree(node* n);
    //-------------------------tree func-----------------------------------------
    
protected:
    node* root_, *end_, *begin_;
    size_type size_{};
    bool multi_;

};
//---------------------member functions--------------------------
template <class value_type>
AvlTree<value_type>::AvlTree(bool multi) {
    root_ = begin_ = end_= new TreeNode();
    begin_->height_ = 0;
    multi_ = multi;
    
}

template <class value_type>
AvlTree<value_type>::AvlTree(value_type key, bool multi) : AvlTree(multi){
    insert(key);
}

template <class value_type>
AvlTree<value_type>::AvlTree(std::initializer_list<value_type> const &items, bool multi) : AvlTree(multi){
    for (auto item : items) {
        insert(item);
    }

   
}

template <class value_type>
AvlTree<value_type>::AvlTree(const AvlTree& other) : AvlTree(other.multi_) {
  //  multi_ = other.multi_;
 
    for (auto t : other) {
      
        insert(t);
     
    }
    
}

template <class value_type>
AvlTree<value_type>::AvlTree(AvlTree&& other) {
    
    multi_ = other.multi_;
    root_ = other.root_;
    end_ = other.end_;
    begin_ = other.begin_;
    size_ = other.size_;
    other.size_ = 0;
    other.begin_ = other.end_ = other.root_ = nullptr;
}

template <class value_type>
void AvlTree<value_type>::operator=(AvlTree &&other) noexcept {
   
    multi_ = other.multi_;
    root_ = other.root_;
    end_ = other.end_;
    begin_ = other.begin_;
    size_ = other.size_;
    other.size_ = 0;
    other.begin_ = other.end_ = other.root_ = nullptr;
}

template <class value_type>
void AvlTree<value_type>::destruct_node(node* n) {
    
    if (n) {
        destruct_node(n->left_);
        destruct_node(n->right_);
        delete n;
    }
}

template <class value_type>
AvlTree<value_type>::~AvlTree(){
    destruct_node(root_);
    
}

//----------------------tree service func-----------------------------------

template <class value_type>
typename AvlTree<value_type>::node* AvlTree<value_type>::rotate_right(node* n){
    node* tmp = n->left_;
    n->left_ = tmp->right_;
    if (tmp->right_)
        tmp->right_->parent_ = n;
    tmp->right_ = n;
    tmp->parent_ = n->parent_;
    n->parent_ = tmp;
    fix_height(n);
    fix_height(tmp);
    return tmp;
}
template <class value_type>
typename AvlTree<value_type>::node* AvlTree<value_type>:: rotate_left(node* n) {
    node* tmp = n->right_;
    n->right_ = tmp->left_;
    if (tmp->left_)
        tmp->left_->parent_ = n;
    tmp->left_ = n;
    tmp->parent_ = n->parent_;
    n->parent_ = tmp;
    fix_height(n);
    fix_height(tmp);
    return tmp;
}

template <class value_type>
typename AvlTree<value_type>::node* AvlTree<value_type>::balance(node* n){
    fix_height(n);
    if (get_bfactor(n) == 2) {
        //std::cout << "bfactor = 2";
        if (get_bfactor(n->right_) < 0) {
            n->right_ = rotate_right(n->right_);
        }
        return rotate_left(n);
        
    }
    if (get_bfactor(n) == -2) {
        // std::cout << "bfactor = 2";
        if (get_bfactor(n->left_) > 0) {
            n->left_ = rotate_left(n->left_);
        }
        return rotate_right(n);
    }
    return n;
}

template <class value_type>
typename AvlTree<value_type>::node* AvlTree<value_type>::insert_key(node* n, node* prev_node, value_type key) {
    if (!n) {
        node* tmp = new node(key);
        tmp->parent_ = prev_node;
        return tmp;
    }
    if (key < n->key_) {
        n->left_ = insert_key(n->left_, n, key);
        if (n == begin_ && n->left_) {
            begin_ = n->left_;
        }
    } else {
        if (n->right_ == end_) {
            n->right_ = end_->parent_ = new node(key);
            n->right_->parent_ = n;
            n->right_->right_ = end_;
        } else {
            n->right_ = insert_key(n->right_, n, key);
        }
    }
    return balance(n);
}


template <class value_type>
typename AvlTree<value_type>::node* AvlTree<value_type>::find_min(node* n){
    return n->left_? find_min(n->left_) : n;
}
template <class value_type>
typename AvlTree<value_type>::node* AvlTree<value_type>::delete_min(node* n) {
    if (!n->left_) {
        return n->right_;
    }
    n->left_ = delete_min(n->left_);
    return balance(n);
}

template <class value_type>
typename AvlTree<value_type>::node* AvlTree<value_type>::delete_key(node* n, value_type key) {
    if (!n || n == end_)
        return nullptr;
    if (key < n->key_) {
        n->left_ = delete_key(n->left_, key);
    } else if (key > n->key_) {
        n->right_ = delete_key(n->right_, key);
    } else {
        if (!n->right_ || n->right_ == end_) {
            if (n == begin_) {
                begin_ = n->right_ ? n->right_ : n->parent_;
            }
            if (n->right_ == end_) {
                if (!n->left_) {
                    end_->parent_ = n->parent_;
                    delete n;
                    return end_;
                } else {
                    n->left_->right_ = end_;
                    end_->parent_ = n->left_;
                    node* tmp = n->left_;
                    delete n;
                    return tmp;
                }
            }
            node* tmp = n->left_;
            delete n;
            return tmp;
        }
        if (n == begin_) {
            begin_ = n->right_ ? n->right_ : n->parent_;
        }
        node* min = find_min(n->right_);
        node* left = n->left_;
        node* right = n->right_;
        min->right_ = delete_min(right);
        min->left_ = left;
        min->parent_ = n->parent_;
        if (min->left_)
            min->left_->parent_ = min;
        if (min->right_)
            min->right_->parent_ = min;
        
//        if (n->right_ == end_) {
//            n->parent_->right_ = end_;
//            end_->parent_ = n->parent_;
//        }
        delete n;
        return balance(min);
    }
    return balance(n);
}

template <class value_type>
typename AvlTree<value_type>::node* AvlTree<value_type>::find_key(node* n, const value_type& key) {
    if (!n)
        return nullptr;
    node* result;
    if (n->key_ > key)
        result = find_key(n->left_, key);
    else if (n->key_ < key)
        result = find_key(n->right_, key);
    else
        return n;
    return result;
}



template <class value_type>
void AvlTree<value_type>::print_tree(node* n) {
    if (!n) {
        return;
    }
    std::cout << "parr ";
    n->parent_? std::cout<< n->parent_->key_ << ' ' : std::cout << "NULL ";
    std::cout <<"{"<< n->key_ << ',';
    n->left_ ? std::cout << n->left_->key_<< "," : std::cout<< "NULL,";
    //    //std::cout << ',';
    n->right_ ? std::cout << n->right_->key_ << "}\n" :std::cout<< "NULL}\n";
    print_tree(n->left_);
    print_tree(n->right_);
}



//-------------------------------iterators-------------------------------------
template <class key_type>
typename s21::AvlTree<key_type>::const_reference  AvlTree<key_type>::const_iterator::operator*() const {
    return data_->key_;
}

template <class key_type>
bool AvlTree<key_type>::const_iterator::operator!=(const TreeConstIterator& iter) const noexcept {
    return data_!= iter.data_;
}

template <class key_type>
void AvlTree<key_type>::const_iterator::operator++() noexcept{
    if (this->data_->right_) {
        this->data_ = this->data_->right_;
        while (this->data_->left_)
            this->data_ = this->data_->left_;
    } else {
        node* tmp = this->data_->parent_;
        if (tmp->left_ == this->data_ && tmp->key_ == this->data_->key_) {
            this->data_ = tmp;;
        } else {
            node* curr = tmp;
            while (tmp && tmp->parent_ && tmp->key_ <= this->data_->key_) {
                if (tmp->left_ == curr && tmp->key_ == curr->key_) {
                    break;
                }
                curr = tmp;
                tmp = tmp->parent_;
            }
            
            this->data_ = tmp;
        }
    }
}
template <class key_type>
void AvlTree<key_type>::const_iterator::operator--() noexcept{
    if (this->data_->parent_ && this->data_->parent_->right_ == this->data_ && this->data_->key_ < this->data_->parent_->key_) {
        this->data_ = this->data_->parent_;
    } else {
        if (this->data_->left_) {
            this->data_ = this->data_->left_;
            while(this->data_->right_)
                this->data_=this->data_->right_;
        } else {
            node* tmp = this->data_->parent_;
            if (tmp->right_ == this->data_ && tmp->key_ == this->data_->key_) {
                this->data_ = tmp;;
            } else {
                node* curr = tmp;
                while (tmp && tmp->parent_ && tmp->key_ >= this->data_->key_) {
                    if (tmp->right_ == curr && tmp->key_ == curr->key_) {
                        break;
                    }
                    curr = tmp;
                    tmp = tmp->parent_;
                }
                
                this->data_ = tmp;
            }
            
        }
    }
}




template <class key_type>
typename s21::AvlTree<key_type>::reference  AvlTree<key_type>::iterator::operator*() noexcept {
    return this->data_->key_;
}

template <class key_type>
bool AvlTree<key_type>::iterator::operator!=(const TreeIterator& iter) const noexcept {
    return this->data_ != iter.data_;
}
template <class key_type>
bool AvlTree<key_type>::iterator::operator==(const TreeIterator& iter) const noexcept {
    return this->data_ == iter.data_;
}

template <class key_type>
void AvlTree<key_type>::iterator::operator++() noexcept{
  
    if (this->data_->right_) {
        this->data_ = this->data_->right_;
        while (this->data_->left_)
            this->data_ = this->data_->left_;
    } else {
        node* tmp = this->data_->parent_;
        if (tmp->left_ == this->data_ && tmp->key_ == this->data_->key_) {
            this->data_ = tmp;;
        } else {
            node* curr = tmp;
            while (tmp && tmp->parent_ && tmp->key_ <= this->data_->key_) {
                if (tmp->left_ == curr && tmp->key_ == curr->key_) {
                    break;
                }
                curr = tmp;
                tmp = tmp->parent_;
            }
            
            this->data_ = tmp;
        }
    }
}

template <class key_type>
void AvlTree<key_type>::iterator::operator--() noexcept{
    if (this->data_->parent_ && this->data_->parent_->right_ == this->data_ && this->data_->key_ < this->data_->parent_->key_) {
        this->data_ = this->data_->parent_;
    } else {
        if (this->data_->left_) {
            this->data_ = this->data_->left_;
            while(this->data_->right_)
                this->data_=this->data_->right_;
        } else {
            node* tmp = this->data_->parent_;
            if (tmp->right_ == this->data_ && tmp->key_ == this->data_->key_) {
                this->data_ = tmp;;
            } else {
                node* curr = tmp;
                while (tmp && tmp->parent_ && tmp->key_ >= this->data_->key_) {
                    if (tmp->right_ == curr && tmp->key_ == curr->key_) {
                        break;
                    }
                    curr = tmp;
                    tmp = tmp->parent_;
                }
                
                this->data_ = tmp;
            }
            
        }
    }
}
//--------------------------iterators access---------------------------------
template <class key_type>
typename AvlTree<key_type>::iterator AvlTree<key_type>::begin() const noexcept{
    return iterator(begin_);
}
template <class key_type>
typename AvlTree<key_type>::iterator AvlTree<key_type>::end() const noexcept{
    return iterator(end_);
}

//------------------------------capacity------------------------------------
template <class key_type>
bool AvlTree<key_type>::empty() const noexcept{
    return size_ == 0;
}

template <class key_type>
typename AvlTree<key_type>::size_type AvlTree<key_type>::size() const noexcept {
    return size_;
}

template <class key_type>
typename AvlTree<key_type>::size_type AvlTree<key_type>::max_size() const noexcept{
    return std::numeric_limits<size_type>::max()/sizeof(node);
}

//------------------------------Modifiers-----------------------------------
template <class key_type>
void  AvlTree<key_type>::clear()  noexcept{
    destruct_node(root_);
    root_ = begin_ = end_ = new node;
    size_ = 0;
    begin_->height_ = 0;
}
template <class key_type>
void  AvlTree<key_type>::erase(iterator pos) {
    if (pos != end_ && contains(pos.data_->key_)) {
        root_ = delete_key(root_, pos.data_->key_);
    --size_;
}
}
template <class key_type>
void  AvlTree<key_type>::swap(AvlTree& other) noexcept{
    std::swap(root_, other.root_);
    std::swap(end_, other.end_);
    std::swap(begin_, other.begin_);
}
template <class key_type>
void  AvlTree<key_type>::merge(AvlTree& other) {
    for (auto key : other){
        if (!contains(key) || multi_) {
            insert(key);
            other.erase(find(key));
            //--other.size_;
        }
    }
}


//------------------------------Lookup-----------------------------------
template <class key_type>
typename AvlTree<key_type>::iterator AvlTree<key_type>::find(const_reference key){
    node* tmp = find_key(root_, key);
    if (tmp)
        return iterator(tmp);
    else
        return end();
}


template <class key_type>
bool AvlTree<key_type>::contains(const_reference key) {
   if( find(key) != end())
       return true;
    else
        return false;
}

template <class key_type>
typename AvlTree<key_type>::size_type AvlTree<key_type>::count(const_reference key) {
    node *n1 = find_key(root_, key);
    node *n2 = n1;
    if (n1 == nullptr)
        return 0;
    size_type result = 1;
    while (n1->left_ && n1->left_->key_ == key) {
        n1 = n1->left_;
        ++result;
    }
    while (n2->right_ && n2->right_->key_ == key && n2->right_ != end_) {
        n2 = n2->right_;
        ++result;
    }
    return result;
}

template <class key_type>
typename AvlTree<key_type>::iterator AvlTree<key_type>::lower_bound(const_reference key) {
    node* tmp = root_;
    while (tmp->key_ < key && tmp->right_) {
        tmp = tmp->right_;
    }
    while (tmp->left_ && tmp->left_->key_ >= key)
        tmp = tmp->left_;
    return iterator(tmp);
        
}

template <class key_type>
typename AvlTree<key_type>::iterator AvlTree<key_type>::upper_bound(const_reference key) {
    node* tmp = root_;
    while (tmp->left_ && tmp->left_->key_ >= key)
        tmp = tmp->left_;
    while (!tmp->right_ && tmp->parent_)
        tmp = tmp->parent_;
    while (tmp->key_ <= key && tmp->right_) {
        tmp = tmp->right_;
    }
    while (tmp->left_ && tmp->left_->key_ > key)
        tmp = tmp->left_;
   
    return iterator(tmp);
        
}

template <class key_type>
typename std::pair<typename AvlTree<key_type>::iterator, typename AvlTree<key_type>::iterator> AvlTree<key_type>::equal_range(const_reference key) {
    return {lower_bound(key), upper_bound(key)};
}

//-------------------------tree func-----------------------------------------
template <class key_type>
std::pair<typename AvlTree<key_type>::iterator, bool> AvlTree<key_type>::insert(const_reference key) {
    bool result = false;
    if (size_ == 0) {
        begin_= root_ = new node(key);
        begin_->parent_ = nullptr;
        begin_->right_ = end_;
        end_->parent_ = begin_;
       // end_->key_ = key;
        ++size_;
        return {begin(), true};
    } else if (multi_ || find(key) == end()){
        if (max_size() == size_) {
           throw std::overflow_error(
               "size > max_size");
         }
        root_ = insert_key(root_, nullptr, key);
      //  end_->key_ = std::max(end_->key_, key);
        ++size_;
        result = true;
    }
    
    return {find(key), result};
}



//----------------------------emplace------------------------------------
template <class key_type>
template <typename... Args>
std::vector<std::pair<typename AvlTree<key_type>::iterator,bool>> AvlTree<key_type>::emplace(Args&&... args) {
    std::vector<std::pair<iterator, bool>> res;
    for (auto arg : {args...}) {
        auto p = insert(arg);
        res.push_back(p);
    }
    return res;
}
}

#endif /* avl_tree_h */
