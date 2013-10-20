

all:test
	


test:main.o
	g++ -o $@ $< `pkg-config opencv --libs`

%.o:%.c
	g++ -c -g $< `pkg-config opencv --cflags`

clean:
	rm -rf main.o test
