CXX = g++
OBJ = $(CC) -c $< -o $@ $(CXXFLAGS)
CXXFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
GFLAGS = -g -Wall -Wextra -pthread
GTEST_DIR = thirdparty/googletest/googletest
USER_DIR = test
CPPFLAGS += -isystem $(GTEST_DIR)/include
TESTS = bin/asteroids-test
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
                $(GTEST_DIR)/include/gtest/internal/*.h
GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

all: bin/asteroids $(TESTS)

bin/asteroids: build/src/main.o build/src/funcs.o build/src/menu.o build/src/interface.o
	mkdir -p bin
	$(CXX) $^ -o $@ $(CXXFLAGS) 

build/src/main.o: src/main.cpp
	mkdir -p build build/src
	 $(OBJ) -std=c++11

build/src/menu.o: src/menu.cpp
	$(OBJ) -std=c++11

build/src/funcs.o: src/funcs.cpp
	$(OBJ) -std=c++11

build/src/interface.o: src/interface.cpp
	$(OBJ) -std=c++11

bin/asteroids-test : build/src/funcs.o build/test/main.o gtest_main.a
	$(CXX) $^ -o $@ $(CPPFLAGS) $(CXXFLAGS) $(GFLAGS) -lpthread

build/test/main.o : $(USER_DIR)/main.cc
	mkdir -p build/test
	$(OBJ) -std=c++11 $(CPPFLAGS)

gtest-all.o: $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(GFLAGS) -c \
            $(GTEST_DIR)/src/gtest-all.cc

gtest_main.o: $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(GFLAGS) -c \
            $(GTEST_DIR)/src/gtest_main.cc

gtest.a: gtest-all.o
	$(AR) $(ARFLAGS) $@ $^

gtest_main.a: gtest-all.o gtest_main.o
	$(AR) $(ARFLAGS) $@ $^

clean:
	rm -f *.o *.a build/src/*.o build/test/*.o bin/*
	rmdir build/src build/test build bin
