//
//  main_t.cpp
//  cont
//
//  Created by mcbk on 22.06.2023.
//

#include <stdio.h>
#include "s21_set.h"
#include <set>
//#include "avl_tree.h"
template <class value_type>
bool compare_func(s21::Set<value_type> my_set, std::set<value_type> check_set) {
    if (my_set.size() != check_set.size())
        return false;
//    auto it = check_set.begin();
//    for (auto n : my_set) {
//        if (n != *it)
//            return false;
//        ++it;
//    }
//    auto it1 = my_set.end();
//    --it1;
//    auto it2 = check_set.end();
//    --it2;
//    while (it1 != my_set.begin()) {
//        if (*it1 != *it2)
//            return false;
//        --it1;
//        --it2;
//    }
    return true;
}

void ttt(s21::AvlTree<int> tree) {
    
}

int main() {
    s21::Set<int> d1{5, 4, 3, 2, 2, 1};
    std::set<int> d2{5, 4, 3, 2, 2, 1};
    s21::Set<int> d11{2, 3, 4, 5, 55, 7, 77, 75, 87} , emp_m{1};
    std::set<int> d22{2, 3, 4, 5, 55, 7, 77, 75, 87}, emp;
    emp_m.erase(emp_m.find(1));
    for (auto e : emp_m)
        std::cout << "123aSSasa";
    d1.merge(d11);
    d2.merge(d22);
    for (auto d : d2)
        std:: cout << d << ' ';
    std::cout << '\n';
    std::cout << " d2 s= " << d2.size() <<  "   d1 s= " << d1.size() << '\n';
    std::cout << "d22 s= " << d22.size() <<  " d11 s= " << d11.size() << '\n';
    return 0;
}
