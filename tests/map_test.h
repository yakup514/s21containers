//
//  list_test.h
//  cont
//
//  Created by mcbk on 11.05.2023.
//

#ifndef map_test_h
#define map_test_h
#include "gtest/gtest.h"
#include "../s21_map.h"
#include <map>

template <class Key, class T>
bool compare_func(s21::Map<Key, T> my_map, std::map<Key, T> check_map) {
    if (my_map.size() != check_map.size()) {
        std::cout<< "size\n";
        return false;
    }
    if (my_map.size() > 0) {
        auto it = check_map.begin();
        for (auto n : my_map) {
            if (n != (*it)) {
                std::cout << "must be: {" << ((*it)).first << ',' << (*it).second << "}, is: {" << n.first << ',' << n.second << "} \n";
                return false;
            }
            ++it;
        }
        auto it1 = my_map.end();
        --it1;
        auto it2 = check_map.end();
        --it2;
        while (it1 != my_map.begin()) {
            if (*it1 != *it2){
                std::cout << "must be: {" << (*it1).first << ',' << (*it1).second << "}, is: {" << (*it2).first << ',' << (*it2).second << "} \n";
                return false;
            }
            --it1;
            --it2;
        }
        return true;
    } else
        return true;
}
TEST(map_constructor, test1) {
    s21::Map<int, int> d1;
    std::map<int, int> d2;
    
    EXPECT_EQ(d1.size(), d2.size());
}

TEST(map_constructor, test2) {
    s21::Map<int, int> d1{{1,1},{2,2},{3,3},{4,4},{5,5}};
    std::map<int, int> d2{{1,1},{2,2},{3,3},{4,4},{5,5}};
    
    EXPECT_EQ(true, compare_func(d1, d2));
}

TEST(map_constructor, test3) {
    s21::Map<int, int> d1{{5,5}, {4,4}, {3,3}, {2,2}, {1,1}};
    std::map<int, int> d2{{5,5}, {4,4}, {3,3}, {2,2}, {1,1}};
    
    EXPECT_EQ(true, compare_func(d1, d2));
}

TEST(map_constructor, test4) {
    s21::Map<int, int> d1{{5,5}, {4,4}, {3,3}, {2,2}, {2,2}, {1,1}};
    std::map<int, int> d2{{5,5}, {4,4}, {3,3}, {2,2}, {2,2}, {1,1}};
    
    EXPECT_EQ(true, compare_func(d1, d2));
}

TEST(map_constructor, test5) {
    s21::Map<int, int> d1{{5,5}, {4,4}, {3,3}, {2,2}, {2,2}, {1,1}};
    std::map<int, int> d2{{5,5}, {4,4}, {3,3}, {2,2}, {2,2}, {1,1}};
    s21::Map<int, int> d11(d1);
    std::map<int, int> d22(d2);
    
    EXPECT_EQ(true, compare_func(d11, d22));
}

TEST(map_constructor, test6) {
    s21::Map<int, int> d1{{5,5}, {4,4}, {3,3}, {2,2}, {2,2}, {1,1}};
    std::map<int, int> d2{{5,5}, {4,4}, {3,3}, {2,2}, {2,2}, {1,1}};
    s21::Map<int, int> d11(std::move(d1));
    std::map<int, int> d22(std::move(d2));
    
    EXPECT_EQ(true, compare_func(d11, d22));
}

TEST(map_constructor, test7) {
    s21::Map<int, int> d1{};
    std::map<int, int> d2{};
    s21::Map<int, int> d11(std::move(d1));
    std::map<int, int> d22(std::move(d2));
    
    EXPECT_EQ(d11.size(), d22.size());
}

TEST(map_oper_eq, test1) {
    s21::Map<int, int> d1{{5,5}, {4,4}, {3,3}, {2,2}, {2,2}, {1,1}};
    std::map<int, int> d2{{5,5}, {4,4}, {3,3}, {2,2}, {2,2}, {1,1}};
    s21::Map<int, int> d11 = (std::move(d1));
    std::map<int, int> d22 = (std::move(d2));

    EXPECT_EQ(true, compare_func(d11, d22));
}

TEST(map_begin, test1) {
    s21::Map<int, int> d1{{5,5}, {4,4}, {3,3}, {2,2}, {2,2}, {1,1}};
    std::map<int, int> d2{{5,5}, {4,4}, {3,3}, {2,2}, {2,2}, {1,1}};

    EXPECT_EQ(*(d1.begin()), *(d2.begin()));
}

TEST(map_clear, test1) {
    s21::Map<int, int> d1{{5,5}, {4,4}, {3,3}, {2,2}, {2,2}, {1,1}};
    std::map<int, int> d2{{5,5}, {4,4}, {3,3}, {2,2}, {2,2}, {1,1}};
    d1.clear();
    d2.clear();
    EXPECT_EQ(true, d1.empty());
    d1.insert({10, 10});
    d2.insert({10, 10});
    d1.insert({1,1});
    d2.insert({1,1});
    EXPECT_EQ(true, compare_func(d1, d2));
}

TEST(map_insert, test1) {
    s21::Map<int, int> d1{{5,5}, {4,4}, {3,3}, {2,2}, {2,2}, {1,1}};
    std::map<int, int> d2{{5,5}, {4,4}, {3,3}, {2,2}, {2,2}, {1,1}};
    auto p1 = d1.insert({6,6});
    auto p2 = d2.insert({6,6});
    EXPECT_EQ(p1.second, p2.second);
    EXPECT_EQ(*(p1.first), *(p2.first));
    EXPECT_EQ(true, compare_func(d1, d2));
}

TEST(map_insert, test2) {
    s21::Map<int, int> d1{{5,5}, {4,4}, {3,3}, {2,2}, {2,2}, {1,1}};
    std::map<int, int> d2{{5,5}, {4,4}, {3,3}, {2,2}, {2,2}, {1,1}};
    auto p1 = d1.insert({5,5});
    auto p2 = d2.insert({5,5});
    EXPECT_EQ(p1.second, p2.second);
    EXPECT_EQ(*(p1.first), *(p2.first));
    EXPECT_EQ(true, compare_func(d1, d2));
}

TEST(map_insert, test3) {
    s21::Map<int, int> d1;
    std::map<int, int> d2;
    auto p1 = d1.insert({5,5});
    auto p2 = d2.insert({5,5});
    EXPECT_EQ(p1.second, p2.second);
    EXPECT_EQ(*(p1.first), *(p2.first));
    EXPECT_EQ(true, compare_func(d1, d2));
}

TEST(map_insert, test4) {
    s21::Map<int, int> d11{{2,2}, {3,3}, {4,4}, {5,5}, {55,55}, {7, 7} , {77, 77}, {75,75}, {87, 87}};
    std::map<int, int> d22{{2,2}, {3,3}, {4,4}, {5,5}, {55,55}, {7, 7} , {77, 77}, {75,75}, {87, 87}};
    auto p1 = d11.insert(2,3);

    EXPECT_EQ((*(p1.first)).first, 2);
    EXPECT_EQ(p1.second, false);
}

TEST(map_insert, test5) {
    s21::Map<int, int> d1{{5,5}, {4,4}, {3,3}, {2,2}, {2,2}, {1,1}};
    std::map<int, int> d2{{5,5}, {4,4}, {3,3}, {2,2}, {2,2}, {1,1}};
    auto p1 = d1.insert({5,6});
    auto p2 = d2.insert({5,6});
    EXPECT_EQ(p1.second, p2.second);
    EXPECT_EQ(*(p1.first), *(p2.first));
    EXPECT_EQ(true, compare_func(d1, d2));
}

TEST(map_insert, test6) {
    s21::Map<int, int> d1{{5,5}, {4,4}, {3,3}, {2,2}, {2,2}, {1,1}};
    std::map<int, int> d2{{5,5}, {4,4}, {3,3}, {2,2}, {2,2}, {1,1}};
    auto p1 = d1.insert_or_assign(6, 6);
    auto p2 = d2.insert_or_assign(6, 6);
    EXPECT_EQ(p1.second, p2.second);
    EXPECT_EQ(*(p1.first), *(p2.first));
    EXPECT_EQ(true, compare_func(d1, d2));
}

TEST(map_insert, test7) {
    s21::Map<int, int> d1{{5,5}, {4,4}, {3,3}, {2,2}, {2,2}, {1,1}};
    std::map<int, int> d2{{5,5}, {4,4}, {3,3}, {2,2}, {2,2}, {1,1}};
    auto p1 = d1.insert_or_assign(5, 6);
    auto p2 = d2.insert_or_assign(5, 6);
    EXPECT_EQ(p1.second, p2.second);
    EXPECT_EQ(*(p1.first), *(p2.first));
    EXPECT_EQ(true, compare_func(d1, d2));
}

TEST(map_erase, test1) {
    s21::Map<int, int> d1{{5,5}, {4,4}, {3,3}, {2,2}, {2,2}, {1,1}};
    std::map<int, int> d2{{5,5}, {4,4}, {3,3}, {2,2}, {2,2}, {1,1}};
    auto it1 = d1.find(5);
    auto it2 = d2.find(5);;
    d1.erase(it1);
    d2.erase(it2);
    EXPECT_EQ(true, compare_func(d1, d2));
}

TEST(map_erase, test2) {
    s21::Map<int, int> d1{{5,5}, {4,4}, {3,3}, {2,2}, {2,2}, {1,1}};
    std::map<int, int> d2{{5,5}, {4,4}, {3,3}, {2,2}, {2,2}, {1,1}};
    auto it1 = d1.find(3);
    auto it2 = d2.find(3);
    d1.erase(it1);
    d2.erase(it2);
    EXPECT_EQ(true, compare_func(d1, d2));
}

TEST(map_erase, test3) {
    s21::Map<int, int> d1{{5,5}, {4,4}, {3,3}, {2,2}, {2,2}, {1,1}, {6, 6}, {7, 7}, {8, 8}, {9, 9}};
    std::map<int, int> d2{{5,5}, {4,4}, {3,3}, {2,2}, {2,2}, {1,1}, {6, 6}, {7, 7}, {8, 8}, {9, 9}};
    auto it1 = d1.find(7);
    auto it2 = d2.find(7);
    d1.erase(it1);
    d2.erase(it2);
    EXPECT_EQ(true, compare_func(d1, d2));
}

TEST(map_erase, test4) {
    s21::Map<int, int> d1{{2,2}, {3,3}, {4,4}, {5,5}, {55,55}, {7, 7} , {77, 77}, {75,75}, {87, 87}};
    std::map<int, int> d2{{2,2}, {3,3}, {4,4}, {5,5}, {55,55}, {7, 7} , {77, 77}, {75,75}, {87, 87}};
    auto it1 = d1.find(55);
    auto it2 = d2.find(55);
    d1.erase(it1);
    d2.erase(it2);
    EXPECT_EQ(true, compare_func(d1, d2));
}

TEST(map_swap, test1) {
    s21::Map<int, int> d1{{5,5}, {4,4}, {3,3}, {2,2}, {2,2}, {1,1}};
    std::map<int, int> d2{{5,5}, {4,4}, {3,3}, {2,2}, {2,2}, {1,1}};
    s21::Map<int, int> d11{{2,2}, {3,3}, {4,4}, {5,5}, {55,55}, {7, 7} , {77, 77}, {75,75}, {87, 87}};
    std::map<int, int> d22{{2,2}, {3,3}, {4,4}, {5,5}, {55,55}, {7, 7} , {77, 77}, {75,75}, {87, 87}};
    d1.swap(d11);
    d2.swap(d22);
    EXPECT_EQ(true, compare_func(d11, d22));
    EXPECT_EQ(true, compare_func(d1, d2));
}

TEST(map_swap, test2) {
    s21::Map<int, int> d1;
    std::map<int, int> d2;
    s21::Map<int, int> d11{{2,2}, {3,3}, {4,4}, {5,5}, {55,55}, {7, 7} , {77, 77}, {75,75}, {87, 87}};
    std::map<int, int> d22{{2,2}, {3,3}, {4,4}, {5,5}, {55,55}, {7, 7} , {77, 77}, {75,75}, {87, 87}};
    d1.swap(d11);
    d2.swap(d22);
    EXPECT_EQ(true, compare_func(d11, d22));
    EXPECT_EQ(true, compare_func(d1, d2));
}

TEST(map_swap, test3) {
    s21::Map<int, int> d1{{5,5}, {4,4}, {3,3}, {2,2}, {2,2}, {1,1}};
    std::map<int, int> d2{{5,5}, {4,4}, {3,3}, {2,2}, {2,2}, {1,1}};
    s21::Map<int, int> d11;
    std::map<int, int> d22;
    d1.swap(d11);
    d2.swap(d22);
    EXPECT_EQ(true, compare_func(d11, d22));
    EXPECT_EQ(true, compare_func(d1, d2));
}

TEST(map_swap, test4) {
    s21::Map<int, int> d1;
    std::map<int, int> d2;
    s21::Map<int, int> d11;
    std::map<int, int> d22;
    d1.swap(d11);
    d2.swap(d22);
    EXPECT_EQ(true, compare_func(d11, d22));
    EXPECT_EQ(true, compare_func(d1, d2));
}

TEST(map_merge, test1) {
    s21::Map<int, int> d1{{5,5}, {4,4}, {3,3}, {2,2}, {2,2}, {1,1}};
    std::map<int, int> d2{{5,5}, {4,4}, {3,3}, {2,2}, {2,2}, {1,1}};
    s21::Map<int, int> d11{{2,2}, {3,3}, {4,4}, {5,5}, {55,55}, {7, 7} , {77, 77}, {75,75}, {87, 87}};
    std::map<int, int> d22{{2,2}, {3,3}, {4,4}, {5,5}, {55,55}, {7, 7} , {77, 77}, {75,75}, {87, 87}};
    d1.merge(d11);
    d2.merge(d22);
    EXPECT_EQ(true, compare_func(d11, d22));
    EXPECT_EQ(true, compare_func(d1, d2));
}

TEST(map_merge, test2) {
    s21::Map<int, int> d1;
    std::map<int, int> d2;
    s21::Map<int, int> d11{{2,2}, {3,3}, {4,4}, {5,5}, {55,55}, {7, 7} , {77, 77}, {75,75}, {87, 87}};
    std::map<int, int> d22{{2,2}, {3,3}, {4,4}, {5,5}, {55,55}, {7, 7} , {77, 77}, {75,75}, {87, 87}};
    d1.merge(d11);
    d2.merge(d22);
    EXPECT_EQ(true, compare_func(d11, d22));
    EXPECT_EQ(true, compare_func(d1, d2));
}

TEST(map_merge, test3) {
    s21::Map<int, int> d1{{5,5}, {4,4}, {3,3}, {2,2}, {2,2}, {1,1}};
    std::map<int, int> d2{{5,5}, {4,4}, {3,3}, {2,2}, {2,2}, {1,1}};
    s21::Map<int, int> d11;
    std::map<int, int> d22;
    d1.merge(d11);
    d2.merge(d22);
    EXPECT_EQ(true, compare_func(d11, d22));
    EXPECT_EQ(true, compare_func(d1, d2));
}

TEST(map_merge, test4) {
    s21::Map<int, int> d1;
    std::map<int, int> d2;
    s21::Map<int, int> d11;
    std::map<int, int> d22;
    d1.merge(d11);
    d2.merge(d22);
    EXPECT_EQ(true, compare_func(d11, d22));
    EXPECT_EQ(true, compare_func(d1, d2));
}

TEST(map_at, test1) {
    s21::Map<int, int> d11{{2,2}, {3,3}, {4,4}, {5,5}, {55,55}, {7, 7} , {77, 77}, {75,75}, {87, 87}};
    std::map<int, int> d22{{2,2}, {3,3}, {4,4}, {5,5}, {55,55}, {7, 7} , {77, 77}, {75,75}, {87, 87}};
    EXPECT_EQ(d11[2], d22[2]);
}

TEST(map_at, test2) {
    s21::Map<int, int> d11{{2,2}, {3,3}, {4,4}, {5,5}, {55,55}, {7, 7} , {77, 77}, {75,75}, {87, 87}};
    std::map<int, int> d22{{2,2}, {3,3}, {4,4}, {5,5}, {55,55}, {7, 7} , {77, 77}, {75,75}, {87, 87}};
    EXPECT_EQ(d11[55], d22[55]);
}

TEST(map_at, test3) {
    s21::Map<int, int> d11{{2,2}, {3,3}, {4,4}, {5,5}, {55,55}, {7, 7} , {77, 77}, {75,75}, {87, 87}};
    std::map<int, int> d22{{2,2}, {3,3}, {4,4}, {5,5}, {55,55}, {7, 7} , {77, 77}, {75,75}, {87, 87}};
    EXPECT_EQ(d11[87], d22[87]);
}

TEST(map_at, test4) {
    s21::Map<int, int> d11{{2,2}, {3,3}, {4,4}, {5,5}, {55,55}, {7, 7} , {77, 77}, {75,75}, {87, 87}};
    try {
        d11.at(-1);
        FAIL();
    } catch (std::out_of_range& ex) {
        EXPECT_STREQ("key not found", ex.what());
    }
}

TEST(map_at, test5) {
    s21::Map<int, int> d11{{2,2}, {3,3}, {4,4}, {5,5}, {55,55}, {7, 7} , {77, 77}, {75,75}, {87, 87}};
    try {
        d11[-1];
        FAIL();
    } catch (std::out_of_range& ex) {
        EXPECT_STREQ("key not found", ex.what());
    }
}

TEST(map_contains, test1) {
    s21::Map<int, int> d11{{2,2}, {3,3}, {4,4}, {5,5}, {55,55}, {7, 7} , {77, 77}, {75,75}, {87, 87}};
    EXPECT_EQ(d11.contains(55), true);
}

TEST(map_contains, test2) {
    s21::Map<int, int> d11{{2,2}, {3,3}, {4,4}, {5,5}, {55,55}, {7, 7} , {77, 77}, {75,75}, {87, 87}};
    EXPECT_EQ(d11.contains(56), false);
}



//TEST(map_emplace, test1) {
//    s21::Map<int, int> d1;
//    auto vec = d1.emplace( {1,1}, {2,2},{2,2}, {1,1}, {4,4}, {5,5});
//    std::map<int, int> d2{ {1,1}, {2,2}, {2,2}, {1,1}, {4,4}, {5,5}};
//    EXPECT_EQ(true, compare_func(d1, d2));
//}

#endif /* map_test_h */
