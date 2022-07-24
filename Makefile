
.PHONY: all
all: pageattr

pageattr: pageattr.c
	gcc pageattr.c -o pageattr -lncurses

run: pageattr
	./pageattr