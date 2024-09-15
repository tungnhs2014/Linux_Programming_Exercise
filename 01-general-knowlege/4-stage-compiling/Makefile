.PHONY: stage1 stage2 stage3 stage4


stage1:
	gcc -E hello.c -o hello.i
stage2:
	gcc -S hello.i -o hello.s
stage3:
	gcc -c hello.s -o hello.o
stage4:
	gcc -o hello hello.o

all:
	gcc -o hello hello.c

clean:
	rm -rf hello hello.o hello.i hello.s
