CC:=g++
CFLAGS:=-Wall -Wextra -Werror -std=c++17 -O2 -g -I./includes -DDebug
cppfiles:=./src/*.cpp
builddir:=./build/interpeter
objfiles:=$(builddir)/*.o
app:=fflang
main:=./$(app).cpp

main:  interpeter
	$(CC) $(CFLAGS) $(main) $(objfiles)  -o fflang

interpeter: ./src/*.cpp
	$(CC) $(CFLAGS) -c $(cppfiles) 
	mkdir -p $(builddir)
	mv *.o $(builddir)

clean:
	find $(builddir) -type f -name "*.o" -delete
	find ./$(app).dSYM -type f -delete
	find . -type f -name $(app) -delete