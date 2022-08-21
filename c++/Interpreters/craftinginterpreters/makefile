main:  interpeter
	g++ -DDebug fflang.cpp ./build/interpeter/*.o -std=c++20 -o fflang  

interpeter: clean ./src/*.cpp
	g++ -DDebug -c ./src/*.cpp  -std=c++20 && mkdir -p ./build/interpeter && mv *.o ./build/interpeter/

clean:
	find ./build/interpeter -type f -name "*.o" -delete