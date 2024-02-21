build: src/backtickc.c
	cc src/*.c -o backtickc -I./include

debug: src/backtickc.c
	cc src/*.c -o backtickc -I./include -g
