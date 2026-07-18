all:
	gcc -Wall main.c apc.c add.c sub.c mul.c div.c mod.c pow.c -o a.out

clean:
	rm -f a.out