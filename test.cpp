//
//  test.cpp
//  test3
//
//  Created by mcbk on 24.03.2023.
//

#include <iostream>


#include "tests/list_test.h"




int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

