# Produces the executable from the .c file
# -lm provides functionality for the power function for the math.h library
CodeBreaker: CaesarBreaker.c
	gcc CaesarBreaker.c -o CodeBreaker -lm

# test for decrypting files
# 1 is the signal for encrypting the files
# 5/17 are the keys to be used for encryption
# The input and output are compared for differences
test: test1 test2

test1:
	./cipher 1 17 SimpleParagraph.txt Enc17SimpleParagraph.txt
	./CodeBreaker Enc17SimpleParagraph.txt Dec17SimpleParagraph.txt
	diff -s SimpleParagraph.txt Dec17SimpleParagraph.txt

test2:
	./cipher 1 5 Server.java Enc5Server.java
	./CodeBreaker Enc5Server.java Dec5Server.java
	diff -s Server.java Dec5Server.java
