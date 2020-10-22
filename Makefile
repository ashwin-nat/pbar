CFLAGS_RELEASE:=	-O2 \
					-Wall \
					-Werror
CFLAGS_DEBUG:=		-O0 \
					-ggdb3 \
					-Wall

all: main
debug: main_dbg

main:
	$(CC) $(CFLAGS_RELEASE) pbar.c example.c -o pbar_example

main_dbg:
	$(CC) $(CFLAGS_DEBUG) pbar.c example.c -o pbar_example

clean:
	@rm -f pbar_example