CC=g++
CFLAGS= -std=c++17 -Wall 

repl: repl.o

%.o: %.cc %.h
	$(CC) $(CFLAGS) -c -o $@ $< 

%: %.o
	$(CC) $(CFLAGS) -o $@ $^ 
