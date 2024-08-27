all: run

run: main.c
	make clean && mkdir build && gcc -g -o build/main main.c src/*.c -I/opt/homebrew/opt/openssl/include -L/opt/homebrew/opt/openssl/lib -lcrypto -pthread && make format && chmod +x ./build/main && ./build/main "example.com http"

format:
	clang-format -i src/*.c && clang-format -i include/*.h

clean:
	rm -rf build
