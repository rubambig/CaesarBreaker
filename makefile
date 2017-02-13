CodeBreaker: CaesarBreaker.c
	gcc CaesarBreaker.c -o CodeBreaker -lm

test: test1 test2
test1:
	./cipher 1 5 Server.java Server23.java
test2:
	./cipher 2 5 Server23.java Server24.java
