fixdump : Makefile src/main.cpp src/*.h
	clang++ -g -std=c++14 \
	-Wall -Wextra -Wpedantic \
	src/main.cpp -o fixdump


run : 
	chmod 755 fixdump
	./fixdump

format :
	clang-format -i -style=file src/main.cpp
	clang-format -i -style=file src/*.h

line_endings :
	dos2unix src/*.cpp src/*.h

clean :
	\rm -f fixdump

strip :
	strip fixdump
