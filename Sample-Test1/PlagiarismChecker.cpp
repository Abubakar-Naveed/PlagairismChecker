#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

const int MAX_WORDS = 1000;
const int MAX_LINE_LENGTH = 1000;

// Global Classes and Variables
// Use of classes is must 

// Function to read input from a file
void readInput(const char* pathofInputFile);

int getNumberOfDocument();

char* getText(int documentNumber);

// Function to remove punctuation marks from documents
void removePunctuationMarks(); 

// Function to convert all characters in documents to lowercase
void convertUpperToLowerCase();

// Function to remove stopwords from documents
void removeStopWords();

// Function to generate frequencies of each unique word in each document
void generateFrequencies(char**& uniqueWords, int& uniqueCount, int**& documentFrequency);

int getFrequency(char* word, int documentNum);   // -1 if not found

void calculateAllCosineSimilarities(double**& similarities,int** documentFrequency);

double similarityIn(int doucmentNum1, int documentNum2);


