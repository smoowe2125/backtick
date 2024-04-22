build: src/stellar-clang.c include/stellarc_utils.h include/tokenizer.h
	cc src/*.c -o stellar-clang -I./include

debug: src/stellar-clang.c include/stellarc_utils.h include/tokenizer.h
	cc src/*.c -o stellar-clang -I./include -g
