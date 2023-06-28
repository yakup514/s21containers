//
//  list_test.h
//  cont
//
//  Created by mcbk on 11.05.2023.
//

#ifndef set_test_h
#define set_test_h
#include "gtest/gtest.h"
#include "../s21_set.h"
#include <set>

template <class value_type>
bool compare_func(s21::Set<value_type> my_set, std::set<value_type> check_set) {
    if (my_set.size() != check_set.size()) {
        std::cout<< "size\n";
        return false;
    }
    if (my_set.size() > 0) {
        auto it = check_set.begin();
        for (auto n : my_set) {
            if (n != *it) {
                std::cout << "must be: " << *it << ", is: " << n << '\n';
                return false;
            }
            ++it;
        }
        auto it1 = my_set.end();
        --it1;
        auto it2 = check_set.end();
        --it2;
        while (it1 != my_set.begin()) {
            if (*it1 != *it2){
                std::cout << "must be: " << *it2 << ", is: " << *it1 << '\n';
                return false;
            }
            --it1;
            --it2;
        }
        return true;
    } else
        return true;
}
TEST(set_constructor, test1) {
    s21::Set<int> d1;
    std::set<int> d2;
    
    EXPECT_EQ(d1.size(), d2.size());
}

TEST(set_constructor, test2) {
    s21::Set<int> d1{1,2,3,4,5};
    std::set<int> d2{1,2,3,4,5};
    
    EXPECT_EQ(true, compare_func(d1, d2));
}

TEST(set_constructor, test3) {
    s21::Set<int> d1{5, 4, 3, 2, 1};
    std::set<int> d2{5, 4, 3, 2, 1};
    
    EXPECT_EQ(true, compare_func(d1, d2));
}

TEST(set_constructor, test4) {
    s21::Set<int> d1{5, 4, 3, 2, 2, 1};
    std::set<int> d2{5, 4, 3, 2, 2, 1};
    
    EXPECT_EQ(true, compare_func(d1, d2));
}

TEST(set_constructor, test5) {
    s21::Set<int> d1{5, 4, 3, 2, 2, 1};
    std::set<int> d2{5, 4, 3, 2, 2, 1};
    s21::Set<int> d11(d1);
    std::set<int> d22(d2);
    
    EXPECT_EQ(true, compare_func(d11, d22));
}

TEST(set_constructor, test6) {
    s21::Set<int> d1{5, 4, 3, 2, 2, 1};
    std::set<int> d2{5, 4, 3, 2, 2, 1};
    s21::Set<int> d11(std::move(d1));
    std::set<int> d22(std::move(d2));
    
    EXPECT_EQ(true, compare_func(d11, d22));
}

TEST(set_constructor, test7) {
    s21::Set<int> d1{};
    std::set<int> d2{};
    s21::Set<int> d11(std::move(d1));
    std::set<int> d22(std::move(d2));
    
    EXPECT_EQ(d11.size(), d22.size());
}

TEST(set_oper_eq, test1) {
    s21::Set<int> d1{5, 4, 3, 2, 2, 1};
    std::set<int> d2{5, 4, 3, 2, 2, 1};
    s21::Set<int> d11 = (std::move(d1));
    std::set<int> d22 = (std::move(d2));
    
    EXPECT_EQ(true, compare_func(d11, d22));
}

TEST(set_begin, test1) {
    s21::Set<int> d1{5, 4, 3, 2, 2, 1};
    std::set<int> d2{5, 4, 3, 2, 2, 1};
    
    EXPECT_EQ(*(d1.begin()), *(d2.begin()));
}

TEST(set_clear, test1) {
    s21::Set<int> d1{5, 4, 3, 2, 2, 1};
    std::set<int> d2{5, 4, 3, 2, 2, 1};
    d1.clear();
    d2.clear();
    EXPECT_EQ(true, d1.empty());
    d1.insert(10);
    d2.insert(10);
    d1.insert(1);
    d2.insert(1);
    EXPECT_EQ(true, compare_func(d1, d2));
}

TEST(set_insert, test1) {
    s21::Set<int> d1{5, 4, 3, 2, 2, 1};
    std::set<int> d2{5, 4, 3, 2, 2, 1};
    auto p1 = d1.insert(6);
    auto p2 = d2.insert(6);
    EXPECT_EQ(p1.second, p2.second);
    EXPECT_EQ(*(p1.first), *(p2.first));
    EXPECT_EQ(true, compare_func(d1, d2));
}

TEST(set_insert, test2) {
    s21::Set<int> d1{5, 4, 3, 2, 2, 1};
    std::set<int> d2{5, 4, 3, 2, 2, 1};
    auto p1 = d1.insert(5);
    auto p2 = d2.insert(5);
    EXPECT_EQ(p1.second, p2.second);
    EXPECT_EQ(*(p1.first), *(p2.first));
    EXPECT_EQ(true, compare_func(d1, d2));
}

TEST(set_insert, test3) {
    s21::Set<int> d1;
    std::set<int> d2;
    auto p1 = d1.insert(5);
    auto p2 = d2.insert(5);
    EXPECT_EQ(p1.second, p2.second);
    EXPECT_EQ(*(p1.first), *(p2.first));
    EXPECT_EQ(true, compare_func(d1, d2));
}

TEST(set_erase, test1) {
    s21::Set<int> d1{5, 4, 3, 2, 2, 1};
    std::set<int> d2{5, 4, 3, 2, 2, 1};
    auto it1 = d1.find(5);
    auto it2 = d2.find(5);
    d1.erase(it1);
    d2.erase(it2);
    EXPECT_EQ(true, compare_func(d1, d2));
}

TEST(set_erase, test2) {
    s21::Set<int> d1{5, 4, 3, 2, 2, 1};
    std::set<int> d2{5, 4, 3, 2, 2, 1};
    auto it1 = d1.find(3);
    auto it2 = d2.find(3);
    d1.erase(it1);
    d2.erase(it2);
    EXPECT_EQ(true, compare_func(d1, d2));
}

TEST(set_erase, test3) {
    s21::Set<int> d1{5, 4, 3, 2, 2, 1, 6, 7, 8, 9};
    std::set<int> d2{5, 4, 3, 2, 2, 1, 6, 7, 8, 9};
    auto it1 = d1.find(7);
    auto it2 = d2.find(7);
    d1.erase(it1);
    d2.erase(it2);
    EXPECT_EQ(true, compare_func(d1, d2));
}

TEST(set_erase, test4) {
    s21::Set<int> d1{2, 3, 4, 5, 55, 7, 77, 75, 87};
    std::set<int> d2{2, 3, 4, 5, 55, 7, 77, 75, 87};
    auto it1 = d1.find(55);
    auto it2 = d2.find(55);
    d1.erase(it1);
    d2.erase(it2);
    EXPECT_EQ(true, compare_func(d1, d2));
}

TEST(set_swap, test1) {
    s21::Set<int> d1{5, 4, 3, 2, 2, 1};
    std::set<int> d2{5, 4, 3, 2, 2, 1};
    s21::Set<int> d11{2, 3, 4, 5, 55, 7, 77, 75, 87};
    std::set<int> d22{2, 3, 4, 5, 55, 7, 77, 75, 87};
    d1.swap(d11);
    d2.swap(d22);
    EXPECT_EQ(true, compare_func(d11, d22));
    EXPECT_EQ(true, compare_func(d1, d2));
}

TEST(set_swap, test2) {
    s21::Set<int> d1;
    std::set<int> d2;
    s21::Set<int> d11{2, 3, 4, 5, 55, 7, 77, 75, 87};
    std::set<int> d22{2, 3, 4, 5, 55, 7, 77, 75, 87};
    d1.swap(d11);
    d2.swap(d22);
    EXPECT_EQ(true, compare_func(d11, d22));
    EXPECT_EQ(true, compare_func(d1, d2));
}

TEST(set_swap, test3) {
    s21::Set<int> d1{5, 4, 3, 2, 2, 1};
    std::set<int> d2{5, 4, 3, 2, 2, 1};
    s21::Set<int> d11;
    std::set<int> d22;
    d1.swap(d11);
    d2.swap(d22);
    EXPECT_EQ(true, compare_func(d11, d22));
    EXPECT_EQ(true, compare_func(d1, d2));
}

TEST(set_swap, test4) {
    s21::Set<int> d1;
    std::set<int> d2;
    s21::Set<int> d11;
    std::set<int> d22;
    d1.swap(d11);
    d2.swap(d22);
    EXPECT_EQ(true, compare_func(d11, d22));
    EXPECT_EQ(true, compare_func(d1, d2));
}

TEST(set_merge, test1) {
    s21::Set<int> d1{5, 4, 3, 2, 2, 1};
    std::set<int> d2{5, 4, 3, 2, 2, 1};
    s21::Set<int> d11{2, 3, 4, 5, 55, 7, 77, 75, 87};
    std::set<int> d22{2, 3, 4, 5, 55, 7, 77, 75, 87};
    d1.merge(d11);
    d2.merge(d22);
    EXPECT_EQ(true, compare_func(d11, d22));
    EXPECT_EQ(true, compare_func(d1, d2));
}

TEST(set_merge, test2) {
    s21::Set<int> d1;
    std::set<int> d2;
    s21::Set<int> d11{2, 3, 4, 5, 55, 7, 77, 75, 87};
    std::set<int> d22{2, 3, 4, 5, 55, 7, 77, 75, 87};
    d1.merge(d11);
    d2.merge(d22);
    EXPECT_EQ(true, compare_func(d11, d22));
    EXPECT_EQ(true, compare_func(d1, d2));
}

TEST(set_merge, test3) {
    s21::Set<int> d1{5, 4, 3, 2, 2, 1};
    std::set<int> d2{5, 4, 3, 2, 2, 1};
    s21::Set<int> d11;
    std::set<int> d22;
    d1.merge(d11);
    d2.merge(d22);
    EXPECT_EQ(true, compare_func(d11, d22));
    EXPECT_EQ(true, compare_func(d1, d2));
}

TEST(set_merge, test4) {
    s21::Set<int> d1;
    std::set<int> d2;
    s21::Set<int> d11;
    std::set<int> d22;
    d1.merge(d11);
    d2.merge(d22);
    EXPECT_EQ(true, compare_func(d11, d22));
    EXPECT_EQ(true, compare_func(d1, d2));
}

TEST(set_emplace, test1) {
    s21::Set<int> d1;
    auto vec = d1.emplace( 1, 2,2, 1, 4, 5);
    std::set<int> d2{ 1, 2, 2, 1, 4, 5};
    EXPECT_EQ(true, compare_func(d1, d2));
}

#endif /* set_test_h */
