//
//  m_test.cpp
//  cont
//
//  Created by mcbk on 15.06.2023.
//

//
//  main.cpp
//  cont
//
//  Created by mcbk on 30.05.2023.
//

#include <iostream>
#include <list>
#include <vector>
#include "s21_list.h"

#include <set>
#include "s21_set.h"
int main(int argc, const char * argv[]) {
    s21::AvlTree<int> tree, tt(10), ttt;
   s21::Set<int> ss;
   ss.insert(111);
//    std::cout << "set = " << *(ss.begin());
//    for (int i = 2; i < 10; ++i) {
//        tree.insert(i);
//    }
// tree.root_ = tree.delete_key(tree.root_, 2);
//    tree.print_tree(tree.root_);
//  //  tree.root_ = tree.delete_key(tree.root_, 8);
//    //   tree.print_tree(tree.root_);
//    //s21::AvlTree<int>::const_iterator it(tree.root_);
//    std::cout<< '\n' << tree.size_ << " root: " << tree.root_->key_<<'\n';
//    std::cout<< "begin: " << tree.begin_->key_ << ", end: " << tree.end_->key_ << '\n';
////    auto  it = tree.begin();
////    for (int i = 0; i < 8; ++i) {
////        std::cout << *it << ' ';
////        ++it;
////    }
//    //std::cout << '\n' << tree.root_->height_ << ", bfact = " << tree.get_bfactor(tree.root_);
//    std::set<int> data ;
//    //(--data.begin()) == (data.end()) ?  std::cout <<"da" << '\n':std::cout <<"net" << '\n';
//    //std::cout << *data.begin();
//    if (tree.begin() != tree.end())
//        std::cout <<"da";
//    std::cout<< '\n';
//    for (auto it = tree.begin(); it != tree.end(); ++it)
//        std::cout << *it << ' ';
//    for (auto t : tree)
//        std::cout << t << 'q';
//    std::cout<< '\n';
//    auto itt = tree.end();
//    --itt;
//   for (; itt != tree.begin(); --itt)
//        std::cout << *itt << ' ';
//    std::cout << '\n' << "set  max: " << data.max_size();
//    std::cout << '\n' << "tree max: " << tree.max_size() << "node size: " << sizeof(s21::AvlTree<int>::node);
//    tree.clear();
    for (int i = 2; i < 10; ++i) {
        tree.insert(i);
    }
    
    for (auto it = tree.begin(); it != tree.end(); ++it) {
        std::cout << "erase: " << *it << '\n' ;
        tree.erase(it);
        tree.print_tree(tree.root_);
        
    }
        
//    tree.print_tree(tree.root_);
//    auto itf = tree.find(77);
//    std::cout << '\n' << *itf;
    return 0;
}
