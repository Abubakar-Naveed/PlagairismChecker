#pragma once
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
// Function to read input from file

/////////////Plagiarism Checker ////////////////////////////
class PlagiarismChecker
{
private:
	char* stopwords;
	int lengthofstopwords;
	char** text;
	int** wordsfrequency;
	int numberOfDocument;
	char** addressofDocument;
	int* lengthofDocument;
	int* lengthoftext;
	char** uniqueWordss;
	int** documentFrequenc;
	int uniqueCoun;
	double** similaritis;



public:


	void readInputt(const char* pathofInputFile);
	void opendocument();
	int getNumberOfDocument();
	char* getText(int documentNumber);
	void removePunctuationMarks();
	void convertUpperToLowerCase();
	void removeStopWords();
	void generateFrequencies(char**& uniqueWords, int& uniqueCount, int**& documentFrequency);
	double similarityIn(int doucmentNum1, int documentNum2);
	char* getuniqueWords(int i) 
	{
		cout << "uniqueWords[i]  exception thorwn at  " << i << endl;
		return uniqueWordss[i];
	}
	int getFrequency(int i, int j)
	{
		return documentFrequenc[i][j];
	}
	int getuniqueCount()
	{
		return uniqueCoun;
	}
	void calculateAllCosineSimilarities(double**& similarities, int** documentFrequency);

};

PlagiarismChecker plag;

double PlagiarismChecker::similarityIn(int doucmentNum1, int documentNum2)
{
	return similaritis[doucmentNum1 - 1][documentNum2 - 1];
}

double similarityIn(int doucmentNum1, int documentNum2)
{
	return plag.similarityIn(doucmentNum1, documentNum2);

}
void calculateAllCosineSimilarities(double**& similarities, int** documentFrequency)
{
	plag.calculateAllCosineSimilarities(similarities, documentFrequency);

}

void PlagiarismChecker:: calculateAllCosineSimilarities(double**& similarities, int** documentFrequency)
{
	documentFrequency = documentFrequenc;

	similarities = new double* [plag.getNumberOfDocument()];
	for (int i = 0; i < plag.getNumberOfDocument(); i++)
	{
		similarities[i] = new double[plag.getNumberOfDocument()];
		for (int j = 0; j < plag.getNumberOfDocument(); j++)
		{
			similarities[i][j] = 0.00;
		}

	}

	for (int i = 0; i < numberOfDocument; i++)
	{
		for (int j = 0; j < numberOfDocument; j++)
		{
			if (i != j)
			{
				double dotProduct = 0.00;
				double magnitude1 = 0.00;
				double magnitude2 = 0.00;

				for (int k = 0; k < plag.getuniqueCount(); k++)
				{
					dotProduct += documentFrequency[i][k] * documentFrequency[j][k];
					magnitude1 += documentFrequency[i][k] * documentFrequency[i][k];
					magnitude2 += documentFrequency[j][k] * documentFrequency[j][k];
				}

				magnitude1 = sqrt(magnitude1);
				magnitude2 = sqrt(magnitude2);

				similarities[i][j] = dotProduct / (magnitude1 * magnitude2);
				similarities[i][j] = similarities[i][j] * 100;
			}
			else
			{
				similarities[i][j] = 100;
			}
		}
	}
	
	similaritis = similarities;

	
}

int getFrequency(char* word, int documentNum) 
{
	
	int count = 0;
	int uniqueCount = plag.getuniqueCount();
	cout << "Unique Count  " << uniqueCount << endl;
	cout << "heloooooooooooooooooooooooo" << endl;
	for (int i = 0; i < uniqueCount;  i++)
	{
		cout << "word  " << word << "  plag.getuniqueWords(i)  " << plag.getuniqueWords(i) << endl;
		if (strcmp(plag.getuniqueWords(i), word) == 0)
		{
			count = plag.getFrequency(documentNum-1, i);
			cout <<" count i  " <<i<<"   " << count << endl;
			break;
		}
	}
	return count;

}

void PlagiarismChecker::generateFrequencies(char**& uniqueWords, int& uniqueCount, int**& documentFrequency)
{
	uniqueWords = new char* [50];    // Array to store unique words
	uniqueCount = 0;                   // Keeps track of the number of unique words
	documentFrequency = new int* [numberOfDocument];  // 2D array to store the frequency of each unique word in each document

	// Initialize the document frequency array
	for (int i = 0; i < numberOfDocument; i++)
	{
		documentFrequency[i] = new int[1000];
	}

	// Outer loop to iterate over all documents
	for (int i = 0; i < numberOfDocument; i++)
	{
		int j = 0;

		// Inner loop to go through each character in the text until the end of the document
		while (text[i][j] != '\0')    // As long as the document isn't finished
		{
			char word[20];   // Temporary array to hold the current word
			int l = 0;       // Index to build the word character by character

			// This loop will extract a single word from the text
			while (text[i][j] != ' ' && text[i][j] != '\0')   // Until we find a space or end of the document
			{
				word[l++] = text[i][j++];   // Copy the character into 'word' and move to the next character
			}

			word[l] = '\0';  // Null-terminate the word

			// Skip over any extra spaces
			if (text[i][j] == ' ') j++;

			bool flag = false;

			// Check if the word is already in uniqueWords
			for (int m = 0; m < uniqueCount; m++)
			{
				if (strcmp(uniqueWords[m], word) == 0)   // If the word already exists
				{
					flag = true;
					break;
				}
			}

			// If the word is not already in uniqueWords, add it
			if (!flag)
			{
				uniqueWords[uniqueCount] = new char[20];      // Allocate space for the new word
				strcpy(uniqueWords[uniqueCount], word);       // Copy the word into uniqueWords
				uniqueCount++;
				
			}
		}
	}

	// Initialize the document frequency array to 0 for all unique words in all documents
	for (int i = 0; i < numberOfDocument; i++)
	{
		for (int j = 0; j < uniqueCount; j++)
		{
			documentFrequency[i][j] = 0;
		}
	}

	// Populate the document frequency array with word counts
	for (int i = 0; i < numberOfDocument; i++)
	{
		int j = 0;
		while (text[i][j] != '\0')    // Iterate through the document again to count the frequencies of words
		{
			char word[20];
			int l = 0;

			// Extract each word
			while (text[i][j] != ' ' && text[i][j] != '\0')
			{
				word[l++] = text[i][j++];
			}
			word[l] = '\0';

			if (text[i][j] == ' ') j++;

			// Find the index of the word in uniqueWords and increment the corresponding frequency
			for (int m = 0; m < uniqueCount; m++)
			{
				if (strcmp(uniqueWords[m], word) == 0)
				{
					documentFrequency[i][m]++;
					//cout << "Unique Words  " << uniqueWords[m] <<"   Document " <<i<< "  Frequency  " << documentFrequency[i][m] << endl;
					break;
				}
			}
		}


	}
	
	documentFrequenc = documentFrequency;
	uniqueWordss = uniqueWords;
	uniqueCoun = uniqueCount;
}

void generateFrequencies(char**& uniqueWords, int& uniqueCount, int**& documentFrequency)
{
	plag.generateFrequencies(uniqueWords, uniqueCount, documentFrequency);
}

void removeStopWords()
{
	plag.removeStopWords();
	cout << endl;
}

void PlagiarismChecker::removeStopWords()
{
	
	
	
	char word[20];
	int lengthofword;
	lengthofstopwords = strlen(stopwords);
	cout << "number of document  " << numberOfDocument << endl;
	for (int i = 0; i < numberOfDocument; i++)
	{
		
		int j = 0;
		cout << lengthofstopwords << endl;
		while (j < lengthofstopwords)
		{
			////cout << "j  " << j << endl;
			
			for ( int k=0; k < 20; k++ )
			{
				if (stopwords[j] != '\0' && stopwords[j] != ' ')
				{
					
					word[k] = stopwords[j++];
					
				}
				else
				{
					j++;
					lengthofword = k+1;
					
					break;
				}

			}
			word[lengthofword-1] = '\0';
			int count = 0;
			bool flage = false;
			int l = 0;
			//cout << i << endl;
			//cout << lengthoftext[i] << endl;
			for (int k = 0; k < lengthoftext[i]; k++)
			{
				//cout << "word  " << word << "  text[i][k]  " << text[i][k] << endl;
				if (text[i][k] == word[0])
				{	
					
					for (l = 0; l < lengthofword - 1; l++)
					{
						if ((k != 0) && text[i][k - 1] != ' ')
						{
							cout << "break 1" << endl;
							break;
						}
						if (text[i][k + lengthofword - 1] != '\0' && text[i][k + lengthofword - 1] != ' ')
						{
							cout << "break 2" << endl;
							break;
						}
						
						if (text[i][k + l] != word[l] )
						{
							cout << "break 3" << endl;
							break;
						}

					}
					
					if (l == lengthofword-1)
					{
						count++;
						flage = true;
						cout << "word  " << word << endl;
					}
					cout << "flage  " << flage << endl;

				}
				/////// remove the word from text   /////////////////////////
				

				if (lengthoftext[i] - lengthofword == 0 )
				{
					cout << "I did it" << endl;
					text[i][0] = '\0';
					flage = false;

				}
				else
				if (flage == true)
				{
					for (int m = k; m < lengthoftext[i] - lengthofword; m++)
					{
						text[i][m] = text[i][m + lengthofword];
					}
					text[i][lengthoftext[i] - lengthofword] = '\0';
					lengthoftext[i] = lengthoftext[i] - lengthofword;
					flage = false;
				}

				
				//cout << "text[i]  " << text[i] << endl;
			}

				///////// reset word/////
			word[0] = '\0';
		}

		cout << "text[i]  " << text[i] << endl;
	}
	
}


void convertUpperToLowerCase()
{
	plag.convertUpperToLowerCase();
}
void PlagiarismChecker::convertUpperToLowerCase()
{
	for (int i = 0; i < numberOfDocument; i++)
	{
		for (int j = 0; j < lengthoftext[i]; j++)
		{
			if (text[i][j] >= 'A' && text[i][j] <= 'Z')
			{
				text[i][j] = text[i][j] + 32;
			}
		}
	}
	///////// print text array
	for (int i = 0; i < numberOfDocument; i++)
	{
		cout << text[i] << endl;
	}

}


void removePunctuationMarks()
{
	plag.removePunctuationMarks();
	cout << endl;
	
}
void PlagiarismChecker::removePunctuationMarks()
{
	for (int i = 0; i < numberOfDocument; i++) {
		int length = lengthofDocument[i]; 
		for (int j = 0; j < length; j++) {
			
			if (text[i][j] == '.' || text[i][j] == ',' || text[i][j] == ':' || text[i][j] == ';' ||
				text[i][j] == '!' || text[i][j] == '?' || text[i][j] == '-' || text[i][j] == '(' ||
				text[i][j] == ')' || text[i][j] == '[' || text[i][j] == ']' || text[i][j] == '{' ||
				text[i][j] == '}' || text[i][j] == '\'' || text[i][j] == '\"' || text[i][j] == '/' ||
				text[i][j] == '\\' || text[i][j] == '@' || text[i][j] == '#' || text[i][j] == '$' ||
				text[i][j] == '%' || text[i][j] == '^' || text[i][j] == '&' || text[i][j] == '*' ||
				text[i][j] == '_' || text[i][j] == '+' || text[i][j] == '=' || text[i][j] == '|' ||
				text[i][j] == '<' || text[i][j] == '>' || text[i][j] == '`' || text[i][j] == '~' || (text[i][j-1] == ' ' && text[i][j] == ' '))
			{
				
				for (int k = j; k < length - 1; k++) 
				{
					text[i][k] = text[i][k + 1];
				}
				text[i][length - 1] = '\0';  
				length--;  
				j--;  
			}
		}
		lengthoftext[i] = length;

	}
}
	


void readInput(const char* pathofInputFile)
{
		
	plag.readInputt(pathofInputFile);

}

void PlagiarismChecker::opendocument()
{
	for (int i = 0; i < numberOfDocument; i++)
	{
		ifstream is(addressofDocument[i], std::ifstream::in);
		if (!is.is_open())
		{
			cout << "File not found";
		}
		else
		{
			is.getline(text[i], 1000);
		}
		is.close();
	}
}



void PlagiarismChecker::readInputt(const char* pathofInputFile)
{
	stopwords = new char[1000];
	
	
	
	
	ifstream is(pathofInputFile, std::ifstream::in);
	if (!is.is_open())
	{
		cout << "File not found";
	}
	else
	{
			
		
		
		if (is.peek() == std::ifstream::traits_type::eof())
		{
			cout << "File is empty" << endl;
			numberOfDocument = 0;  // Set numberOfDocument to 0
			is.close();
			return;
		}
		
			is.getline(stopwords, 1000);
			is >> numberOfDocument;
			cout << "number of document  " << numberOfDocument << endl;

			

			/////////////initialize address of document array/////////////////////	

			addressofDocument = new char* [numberOfDocument];
			char temp[20];
			is.getline(temp, 20);
			for (int i = 0; i < numberOfDocument; i++)
			{
				addressofDocument[i] = new char[20];
				is.getline(addressofDocument[i], 20);
				cout << "index " << i << "   " << addressofDocument[i] << endl;
			}
			


	}
	// next line of doucment is about the number of documents
	
	///// ////////initialize text array/////////////////////
	text = new char* [numberOfDocument];
	for (int i = 0; i < numberOfDocument; i++)
	{
		text[i] = new char[1000];
	}

	lengthofDocument = new int[numberOfDocument];
	is.close();




	/////////////open document and read text///  ///and save text of document///////////////
	for (int i = 0; i < numberOfDocument; i++)
	{
		ifstream is(addressofDocument[i], std::ifstream::in);
		if (!is.is_open())
		{
			cout << "File not found";
		}
		else
		{
			is.getline(text[i], 1000);
			lengthofDocument[i] = strlen(text[i]);
		}
		is.close();
	}
	

	/////////// lenght of text array/////////////////////
	lengthoftext = new int[numberOfDocument];
	for (int i = 0; i < numberOfDocument; i++)
	{
		lengthoftext[i] = lengthofDocument[i];
	}

	//plag.removePunctuationMarks();
}

int PlagiarismChecker::getNumberOfDocument()
{
	return numberOfDocument;
}

int getNumberOfDocument()
{
	return plag.getNumberOfDocument();
}

char* PlagiarismChecker::getText(int documentNumber)
{
	cout << "text[documentNumber-1]  " << text[documentNumber - 1] << endl;
	return text[documentNumber-1];
}

char* getText(int documentNumber)
{
	return plag.getText(documentNumber);	
}

