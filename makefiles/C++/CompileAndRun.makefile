%:
	g++ $@.cpp -std=c++11 -o $@
	./$@
	find . -name "$@" -delete