#Makefile variables
CXX			 = g++
CXXFLAGS	 = -std=c++14 -Wall -Werror -Wextra -pedantic -Wconversion
SRC_DIR  	 = src
SOURCES 	 = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS		 = $(SOURCES:%.cpp=%.o)
EXECUTABLE   = lmb

#Normal compile
all: $(EXECUTABLE)

# make debug
#complies with debug flags and allows "#ifdef DEBUG /*..*/ #endif" for debug output
debug: CXXFLAGS += -g3 -DDEBUG
debug: clean all

# make release
# compiles without asserts and most efficient code
release: CXXFLAGS += -O3 -DNDEBUG
release: clean all


$(EXECUTABLE): $(OBJECTS)
		$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(EXECUTABLE)

clean:
	rm -rf $(SRC_DIR)/*.o $(EXECUTABLE)
