//
//  list_test.h
//  cont
//
//  Created by mcbk on 11.05.2023.
//

#ifndef list_test_h
#define list_test_h
#include "gtest/gtest.h"
#include "../s21_list.h"
#include <list>

template <class value_type>
bool compare_func(s21::List<value_type> my_list, std::list<value_type> check_list) {
    if (my_list.size() != check_list.size())
        return false;
    auto it = check_list.begin();
    for (auto n : my_list) {
        if (n != *it)
            return false;
        ++it;
    }
    auto it1 = my_list.end();
    --it1;
    auto it2 = check_list.end();
    --it2;
    while (it1 != my_list.end()) {
        if (*it1 != *it2)
            return false;
        --it1;
        --it2;
    }
    if (it2 != check_list.end())
        return false;
    return true;
}
TEST(constructor, test1) {
    s21::List<int> d1{1, 2, 3, 4, 5};
    std::list<int> d2{1, 2, 3, 4, 5};
    auto it = d2.begin();
    for (auto n : d1) {
        EXPECT_EQ(n, *it);
        ++it;
    }
    EXPECT_EQ(d1.size(), d2.size());
}

TEST(constructor, test2) {
    s21::List<int> d1;
    std::list<int> d2;
    auto it = d2.begin();
    for (auto n : d1) {
        EXPECT_EQ(n, *it);
        ++it;
    }
    EXPECT_EQ(d1.size(), d2.size());
}

TEST(constructor, test3) {
    s21::List<int> d3{1, 2, 3, 4, 5}, d1(std::move(d3));
    std::list<int> d4{1, 2, 3, 4, 5}, d2(std::move(d4));
    auto it = d2.begin();
    for (auto n : d1) {
        EXPECT_EQ(n, *it);
        ++it;
    }
    EXPECT_EQ(d1.size(), d2.size());
    EXPECT_EQ(d3.empty(), true);
    EXPECT_EQ(d4.empty(), true);
}

TEST(constructor, test4) {
    s21::List<int> d3{1, 2, 3, 4, 5}, d1(d3);
    std::list<int> d4{1, 2, 3, 4, 5}, d2(d4);
    auto it = d2.begin();
    for (auto n : d1) {
        EXPECT_EQ(n, *it);
        ++it;
    }
    EXPECT_EQ(d1.size(), d2.size());
}

TEST(constructor, test5) {
    s21::List<int> d3, d1(std::move(d3));
    std::list<int> d4, d2(std::move(d4));
    auto it = d2.begin();
    for (auto n : d1) {
        EXPECT_EQ(n, *it);
        ++it;
    }
    EXPECT_EQ(d1.size(), d2.size());
    EXPECT_EQ(d3.empty(), true);
    EXPECT_EQ(d4.empty(), true);
}

TEST(constructor, test6) {
    try{
        s21::List<int> d3(768614336404564651);
    } catch (const std::out_of_range& ex) {
        EXPECT_STREQ(ex.what(), "size > max_size");
    }
}

TEST(oper, test1) {
    s21::List<int> d3{1, 2, 3, 4, 5}, d1;
    std::list<int> d4{1, 2, 3, 4, 5}, d2;
    d1 = std::move(d3);
    d2 = std::move(d4);
    auto it = d2.begin();
    for (auto n : d1) {
        EXPECT_EQ(n, *it);
        ++it;
    }
    EXPECT_EQ(d1.size(), d2.size());
}

TEST(oper, test2) {
    s21::List<int> d3, d1;
    std::list<int> d4, d2;
    d1 = std::move(d3);
    d2 = std::move(d4);
    auto it = d2.begin();
    for (auto n : d1) {
        EXPECT_EQ(n, *it);
        ++it;
    }
    EXPECT_EQ(d1.size(), d2.size());
}

TEST(insert, test1) {
    s21::List<int> d1{1, 2, 3, 4, 5};
    std::list<int> d2{1, 2, 3, 4, 5};
    auto pos1 = d1.begin();
    ++pos1;
    auto pos2 = d2.begin();
    ++pos2;
    auto p1 = d1.insert(pos1, 99);
    auto p2 = d2.insert(pos2, 99);
    auto it = d2.begin();
    for (auto n : d1) {
        EXPECT_EQ(n, *it);
        ++it;
    }
    EXPECT_EQ(d1.size(), d2.size());
    EXPECT_EQ(*p1, *p2);
}
TEST(insert, test2) {
    s21::List<int> d1{1};
    std::list<int> d2{1};
    auto pos1 = d1.begin();
    ++pos1;
    auto pos2 = d2.begin();
    ++pos2;
    auto p1 = d1.insert(pos1, 99);
    auto p2 = d2.insert(pos2, 99);
    auto it = d2.begin();
    for (auto n : d1) {
        EXPECT_EQ(n, *it);
        ++it;
    }
    EXPECT_EQ(d1.size(), d2.size());
    EXPECT_EQ(*p1, *p2);
}
TEST(insert, test3) {
    s21::List<int> d1;
    std::list<int> d2;
    auto pos1 = d1.begin();
    ++pos1;
    auto pos2 = d2.begin();
    ++pos2;
    auto p1 = d1.insert(pos1, 99);
    auto p2 = d2.insert(pos2, 99);
    auto it = d2.begin();
    for (auto n : d1) {
        EXPECT_EQ(n, *it);
        ++it;
    }
    EXPECT_EQ(d1.size(), d2.size());
    EXPECT_EQ(*p1, *p2);
}

TEST(erase, test1) {
    s21::List<int> d1{1, 2, 3, 4, 5};
    std::list<int> d2{1, 2, 3, 4, 5};
    auto pos1 = d1.begin();
    ++pos1;
    auto pos2 = d2.begin();
    ++pos2;
    d1.erase(pos1);
    d2.erase(pos2);
    auto it = d2.begin();
    for (auto n : d1) {
        EXPECT_EQ(n, *it);
        ++it;
    }
    EXPECT_EQ(d1.size(), d2.size());
}
TEST(erase, test2) {
    s21::List<int> d1{1};
    std::list<int> d2{1};
    auto pos1 = d1.begin();
    auto pos2 = d2.begin();
    d1.erase(pos1);
    d2.erase(pos2);
    auto it = d2.begin();
    for (auto n : d1) {
        EXPECT_EQ(n, *it);
        ++it;
    }
    EXPECT_EQ(d1.size(), d2.size());
}

TEST(push_back, test1) {
    s21::List<int> d1{1, 2, 3, 4, 5};
    std::list<int> d2{1, 2, 3, 4, 5};
    d1.push_back(99);
    d2.push_back(99);
    EXPECT_EQ(true, compare_func(d1, d2));
}

TEST(push_back, test2) {
    s21::List<int> d1{1};
    std::list<int> d2{1};
    d1.push_back(99);
    d2.push_back(99);
    auto it = d2.begin();
    for (auto n : d1) {
        EXPECT_EQ(n, *it);
        ++it;
    }
    EXPECT_EQ(d1.size(), d2.size());
}
TEST(push_back, test3) {
    s21::List<int> d1;
    std::list<int> d2;
    d1.push_back(99);
    d2.push_back(99);
    auto it = d2.begin();
    for (auto n : d1) {
        EXPECT_EQ(n, *it);
        ++it;
    }
    EXPECT_EQ(d1.size(), d2.size());
}

TEST(pop_back, test1) {
    s21::List<int> d1{1, 2, 3, 4, 5};
    std::list<int> d2{1, 2, 3, 4, 5};
    d1.pop_back();
    d2.pop_back();
    auto it = d2.begin();
    for (auto n : d1) {
        EXPECT_EQ(n, *it);
        ++it;
    }
    EXPECT_EQ(d1.size(), d2.size());
}

TEST(pop_back, test2) {
    s21::List<int> d1{1};
    std::list<int> d2{1};
    d1.pop_back();
    d2.pop_back();
    auto it = d2.begin();
    for (auto n : d1) {
        EXPECT_EQ(n, *it);
        ++it;
    }
    EXPECT_EQ(d1.size(), d2.size());
}

TEST(pop_front, test1) {
    s21::List<int> d1{1, 2, 3, 4, 5};
    std::list<int> d2{1, 2, 3, 4, 5};
    d1.pop_front();
    d2.pop_front();
    auto it = d2.begin();
    for (auto n : d1) {
        EXPECT_EQ(n, *it);
        ++it;
    }
    EXPECT_EQ(d1.size(), d2.size());
}

TEST(pop_front, test2) {
    s21::List<int> d1{1};
    std::list<int> d2{1};
    d1.pop_front();
    d2.pop_front();
    auto it = d2.begin();
    for (auto n : d1) {
        EXPECT_EQ(n, *it);
        ++it;
    }
    EXPECT_EQ(d1.size(), d2.size());
}

TEST(push_front, test1) {
    s21::List<int> d1{1, 2, 3, 4, 5};
    std::list<int> d2{1, 2, 3, 4, 5};
    d1.push_front(99);
    d2.push_front(99);
    auto it = d2.begin();
    for (auto n : d1) {
        EXPECT_EQ(n, *it);
        ++it;
    }
    EXPECT_EQ(d1.size(), d2.size());
}

TEST(push_front, test2) {
    s21::List<int> d1{1};
    std::list<int> d2{1};
    d1.push_front(99);
    d2.push_front(99);
    EXPECT_EQ(true, compare_func(d1, d2));
}
TEST(push_front, test3) {
    s21::List<int> d1;
    std::list<int> d2;
    d1.push_front(99);
    d2.push_front(99);
    EXPECT_EQ(true, compare_func(d1, d2));
}
#endif /* list_test_h */
