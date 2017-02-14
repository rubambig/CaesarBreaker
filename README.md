# CaesarBreaker - A project in the System Programming class(CIS 361) @ GVSU
A project for decrypting a ciphered file by using know frequencies of English letters

It reads known frequencies of letters in the English language to try and find the best
match in terms of keys used for the encryption. 
Computes the frequencies of letters in the given encrypted file. 
Using the least squares fit method, we compute the closest sum of differences between
the frequencies of the letter, the smallest difference gives the shift used in encrypting
the file, hence this also gives the key. 
