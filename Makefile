all: run

run: main.c
	gcc -g -o build/main main.c src/*.c && chmod +x ./build/main && ./build/main

clean:
	rm build/main
