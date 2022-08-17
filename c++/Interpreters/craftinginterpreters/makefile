main: interpeter
	g++ fflang.cpp ./build/interpeter/*.o -std=c++20 -o fflang -Wall

interpeter:
	g++ -c ./src/*.cpp -DDebug -std=c++20 && mkdir -p ./build/interpeter && mv *.o ./build/interpeter/

clean:
	find ./build/interpeter -type f -name "*.o" -delete