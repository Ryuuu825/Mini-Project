TESTFILE := $(wildcard *.cpp)
# suspend all the warnings
CLANG_WARNINGS_OFF := -w

all: $(TESTFILE)
	@for file in $(TESTFILE); do \
		echo "\033[31mTesting $$file \033[0m"; \
		g++ $(CLANG_WARNINGS_OFF) ../../build/interpeter/*.o ../test_script.cpp $$file ; \
		./a.out; \
		rm a.out; \
	done
	