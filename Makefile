all: run

run: main.c
	make clean && mkdir build && gcc -g -o build/main main.c src/*.c -I/opt/homebrew/opt/openssl/include -L/opt/homebrew/opt/openssl/lib -lcrypto -pthread && chmod +x ./build/main && ./build/main $(ARGS)

clean:
	rm -rf build
