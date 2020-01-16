CC=g++
CFLAGS= -std=c++17 -Wall 

%.o: %.cc %.h
	$(CC) $(CFLAGS) -c -o $@ $< 

%: %.o
	$(CC) $(CFLAGS) -o $@ $^ 
