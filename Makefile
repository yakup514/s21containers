CFLAGS = -Wall -Werror -Wextra
ARCH = $(shell arch)
ifeq "$(ARCH)" "i386"
MYFLAGS = -lm --coverage -lgtest
endif
ifeq "$(ARCH)" "x86_64"
MYFLAGS =-L/usr/lib -lm --coverage -lgtest
endif

all: clean test gcov_report

test: test.cpp
	g++ -std=c++17 $(CFLAGS) test.cpp $(MYFLAGS) -o  test
	./test
	
s21_matrix_oop.a: s21_matrix_oop.cpp
		g++ -std=c++17 -c $(CFLAGS) s21_matrix_oop.cpp -o s21_matrix_oop.o
		ar rc s21_matrix_oop.a s21_matrix_oop.o
		ranlib s21_matrix_oop.a

gcov_report: test
	./test
	gcovr --html-details rep.html
	open rep.html
	
clean:
	rm -rf *.o *.gcda *.a *.html *.gcno *.css
	rm -f test

style:
	cp ../materials/linters/.clang-format .clang-format
	clang-format -n *.cpp
	clang-format -n *.h
	
git:
	git add *.cpp *.h
	git add Makefile
	
