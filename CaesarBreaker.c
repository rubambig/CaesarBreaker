/*********************************************************************
   A program to crack Ceasar Ciphers and produce a decrypted document
   Uses English letter frequencies in documents to approximate a key
   The key is used to decrypt the file and get the original back
   Project 1 in the System Programming class at GVSU, Allendale
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
void decrypt ( int key, FILE * datafile, FILE * fileOutput);

int main(int argc, char ** argv){
  //Check for the number of arguments
  if(argc != 3) {
    fprintf(stderr, "Usage: %s [FILEIN] [FILEOUT]\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  //Load the frequencies
  FILE *storeFreq = fopen("LetFreq.txt", "r");
  float given[26];
  readFreq(given, storeFreq);


  // Find the size of file
  struct stat st;
  stat(argv[1], &st);
  int size = st.st_size;
  printf("The file size is %d bytes\n", size);

  // Compute the frequencies in the given file
  FILE *fileFreq = fopen(argv[1], "r");
  float found[26];
  calcFreq(found, fileFreq, size);

  // Find the key based on the list of frequencies using least squares fit
  int key = findKey(given,found);

  // Decrypt the file
  FILE * encFile = fopen(argv[1], "r");
  FILE * outFile = fopen(argv[2], "w");
  decrypt(key, encFile, outFile);

  exit(EXIT_SUCCESS);
}

/* Load the array given with English letter frequencies from LetFreq.txt.
  @param given an array of floats
  @param letFreq a pointer to a file */
void readFreq (float given[], FILE * letFreq){
  float current;
  int i = 0;
  char ch;
  char dummyLine; // Captures the new line character

  if(letFreq == NULL){
    printf("file 'LetFreq.txt' could not be found!\n");
    exit(EXIT_FAILURE);
  }

  while(!feof(letFreq) && i<26){
    fscanf(letFreq, "%c %f %c", &ch, &current, &dummyLine);
    given[i] = current;
    i++;
  }

  fclose(letFreq); // Close the local file
}

/* Compute the frequencies for each letter in the document.
  @param found an array of floats
  @param datafile a pointer to a file */
void calcFreq ( float found[], FILE *datafile, int size){
  // A struct to contain a letter and its frequency
  struct Frequencies{
    char letter;
    int frequency;
  } Frequency;

  // An array of frequency structs for ease of storage and access
  struct Frequencies freqArray [26];
  int i, j=0;                   // counters for the array and letters
  for (i = 97; i<123; i++){
    freqArray[j].letter = (char)i; // Initiate the letters in the structs
    freqArray[j].frequency = 0;
    j++;
  }

  // Read the file for total letters and store them  temporarily
  char ch; // ch will get each character separately
  int k; // k will loop over the struct of letters and  their frequencies
  int total = 0; // total is the total number of letters we have seen so far
  if(datafile == NULL){ // Checking that the file was opened safely
    printf("Error opening the encrypted file!\n");
    exit(EXIT_FAILURE);
  }
  while( (ch = fgetc(datafile)) != EOF){
    if(isalpha(ch)){
      if(isupper(ch))   // Ensure they we account for uppercase letters
        ch = tolower(ch);
      for(k=0; k<26; k++){
        if(freqArray[k].letter == ch){
          freqArray[k].frequency++;
        }
      }
      total++;
    }
  }

  // Compute the frequency for each letter and store it in found array
  int l; // l will loop over the frequency structs
  for(l=0; l<26; l++){
    found[l] = (float)(freqArray[l].frequency)/(total);
  }
}

/* Rotate down the alphabet to find a corresponding character.
  @param ch the encrypted character
  @param num the key to use for decryption */
char rotate ( char ch, int num ){
  char match;
  if(isalpha(ch)){
    if(islower(ch)){  // Rotate if it's a lowercase letter
      match = (char)((ch - 'a'  + (26-num)) % 26 + 'a');
      return match;
    } else {
      match = (char)((ch - 'A'  + (26-num)) % 26 + 'A');
      return toupper(match);
    }
  }

  return ch; // return the character if it's not a letter
}

/* Find the best key for decryption based on the frequencies
  @param given an array of regular frequencies
  @param found an array of observered frequencies */
int findKey ( float given[], float found[] ){
  int i,j , wrapping, key;
  float tempSum, leastSumFound; // The sums of least squares for the given rotation

  for(i = 0; i<=26; i++){  //found
    tempSum = 0.0;
    for(j = 0; j<26; j++){ //given

      wrapping = ((j+i)%26); // Ensures we don't hit indexOfOutBounds error
      tempSum += (float) pow((double)(given[j] - found[wrapping]), 2);
      }
      if (i==0){
        leastSumFound = tempSum;
        key = i; // Catches a key for identical files
      }

      if (tempSum < leastSumFound){ // Compare the result to the lowest sum
        leastSumFound = tempSum;
        key = i;
        printf("Potential Key %d\n", key);
     }

  }
  printf("Least square of differences found : %f \n", leastSumFound);
  printf("Final key is %d\n", key);
  return key;
}

/* Decrypts the letters in an encrypted file
   Send the output to another file
   @param key is the number used for encryption
   @param datafile the file containing encrypted data */
void decrypt ( int key, FILE * datafile, FILE * fileOutput){
  char ch;
  if(datafile == NULL){ // Checking that the file was opened safely
    printf("Error opening the encrypted file!\n");
    exit(EXIT_FAILURE);
  }

  if(fileOutput == NULL){ // Checking that the file was opened safely
    printf("Error opening or writing the decrypted file!\n");
    exit(EXIT_FAILURE);
  }

  while( (ch = fgetc(datafile)) != EOF){
    fputc(rotate(ch,key), fileOutput); // Rotating the characters based on key
  }

  fclose(fileOutput); // Close the file outputs
  fclose(datafile); // Close the file inputs
}
