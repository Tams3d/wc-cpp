src = main.cpp args.cpp

out = wc_cpp

all: $(out)

$(out): $(src) wc.hpp
	g++ -g $(src) -o $(out)

clean:
	rm -f $(out)