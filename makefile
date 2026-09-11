src = main.cpp args.cpp file.cpp wc.cpp output.cpp

out = wc_cpp

CXX = g++
CXXFLAGS = -g -std=c++17 -Wall -Wextra

all: $(out)

$(out): $(src) wc.hpp
	$(CXX) $(CXXFLAGS) $(src) -o $(out)

clean:
	rm -f $(out) $(out).exe