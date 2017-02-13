/*********************************************************************
   A program to crack Ceasar Ciphers and produce a decrypted document
   Uses English letter frequencies in documents to approximate a key
   @Author Gloire Rubambiza
   @version 01/31/2017
**********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <math.h>
#include <ctype.h>

/* Definition of fuctions signatures */
void readFreq(float given[], FILE * letFreq);
void calcFreq ( float found[], FILE * datafile, int size);
char rotate ( char ch, int num );
int findKey ( float given[], float found[] );

int main(int argc, char ** argv){

  //Check for the number of arguments
  if(argc != 2) {
    fprintf(stderr, "Usage: %s [FILEIN]\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  /* Load the frequencies */
  FILE *storeFreq;
  float given[26];
  readFreq(given, storeFreq);


  /* Find the size of file */
  struct stat st;
  stat(argv[1], &st);
  int size = st.st_size;
  printf("The file size is %d bytes", size);

  /* Compute the frequencies in the given file */
  FILE *fileFreq = fopen(argv[1], "r");
  float found[26];
  calcFreq(found, fileFreq, size);

  /* Try and find the key */
  findKey(given,found);

  exit(EXIT_SUCCESS);
}

/* Load the array given with English letter frequencies from LetFreq.txt. */
/* @param given an array of floats */
/* @param letFreq a pointer to a file */
void readFreq (float given[], FILE * letFreq){
  letFreq = fopen("LetFreq.txt", "r");
  float current;
  int i = 0;
  char ch;
  char dummyLine; /* Captures the new line character */

  if(letFreq == NULL){
    printf("file 'LetFreq.txt' could not be found!\n");
    exit(EXIT_FAILURE);
  }

  while(!feof(letFreq) && i<26){
    fscanf(letFreq, "%c %f %c", &ch, &current, &dummyLine);
    printf("Given Frequency letter:%c number: %f\n", ch, current);
    given[i] = current;
    i++;
  }

  /* Close the file */
  fclose(letFreq);
}

/* Compute the frequencies for each letter in the document. */
/* @param found an array of floats */
/* @param datafile a pointer to a file */
void calcFreq ( float found[], FILE *datafile, int size){
  // A struct to contain a letter and its frequency
  struct Frequencies{
    char letter;
    int frequency;
  } Frequency;

  /* An array of frequency structs for ease of storage and access */
  struct Frequencies freqArray [26];
  int i, j=0;                   /* counters for the array and letters */
  for (i = 97; i<123; i++){
    freqArray[j].letter = (char)i; /* Initiate the letters in the structs */
    freqArray[j].frequency = 0;
    j++;
  }

  /* Read the file for total letters and store them  temporarily */
  char ch; /* ch will get each character separately */
  int k; /* k will loop over the struct of letters and  their frequencies */
  int total = 0; /* total is the total number of letters we have seen so far */
  while( (ch = fgetc(datafile)) != EOF){
    if(isalpha(ch)){
      if(isupper(ch))   /*Ensure they we account for uppercase letters*/
        ch = tolower(ch);
      for(k=0; k<26; k++){
        if(freqArray[k].letter == ch){
          freqArray[k].frequency++;
        }
      }
      total++;
    }
  }

  /* Compute the frequency for each letter and store it in found array */
  int l; /* l will loop over the frequency structs*/
  for(l=0; l<26; l++){
    found[l] = (float)(freqArray[l].frequency)/(total);
    printf("frequency for letter: %c is %f \n", freqArray[l].letter, found[l]);
  }
}

/* Rotate down the alphabet to find a corresponding character. */
/* @param ch the encrypted character */
/* @param num the key to use for decryption */
char rotate ( char ch, int num ){
  char match;
  if(islower(ch)){  // Rotate if it's a lowercase letter
    match = (char)((ch - 'a'  + (26-num)) % 26 + 'a');
    return match;
  } else {
    match = (char)((ch - 'A'  + (26-num)) % 26 + 'A');
    return toupper(match);
  }
  return ch;
}

/* Find the best key for decryption based on the frequencies */
/* @param given an array of regular frequencies */
/* @param found an array of observered frequencies */
int findKey ( float given[], float found[] ){
  int key, shift; // The sum of least squares
  float tempSum, leastSumFound; // The sum of least squares for the given rotation
  int i, j, k, wrapping; // The numbers we will be rotating with

  for(i = 0; i<26; i++){  //found
    shift = (i%26);
    printf("Shift is %d \n", shift);
    for(j = 0; j<26; j++){ //given
      tempSum = 0.0;
      wrapping = ((j+shift)%26);
      printf("wrapping is %d\n", wrapping);
      tempSum += (float) pow((double)(found[j] - given[wrapping]), 2.0);
      printf("Looking at %f, Matching %d to %f, temp is %f\n", found[j], i, given[wrapping], tempSum);
      }
      if (i==0){
        //printf("tempSum Beginning %f\n", tempSum);
        leastSumFound = tempSum;
      }

      if (tempSum < leastSumFound){
        leastSumFound = tempSum;
        key = j - shift;
        //printf("Smallest so far %f", leastSumFound);
        printf("Key %d\n", key);
     }
    //printf("Current temp sum: %f\n", tempSum);

  }
  //printf("Least found : %f \n", leastSumFound);
  return key;
}
