main: vm
	g++ main.cpp ./build/vm/*.o -std=c++11 && ./a.out ./test/2048.obj

test: ./test/add.cpp vm
	g++ ./test/add.cpp ./build/vm/*.o  && ./a.out

vm:  
	g++ -c ./core/*.cpp -DDebug && mkdir -p ./build/vm && mv *.o ./build/vm/

clean:
	find ./build/vm -type f -name "*.o" -delete