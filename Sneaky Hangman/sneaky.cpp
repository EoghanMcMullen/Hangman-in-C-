#include <iostream>
#include <list>
#include <fstream>
#include <string>
#include "sneaky.h"
#include <cTime>
#include <cstdlib> // to access random
using namespace std;

// print words in allwords, Used for testing
void sneaky::printWords(int wordCount) // must pass in the count of words read in
{
	for(int i = 0; i < wordCount;i++)
	{
		cout << allWords2[i] << " ";
	}

}
//returns word to display
string sneaky::getCurrentWord()
{
	string aWord = theWord;
	int i = 0;
	
	while(i < aWord.length())
	{
		if(!letterInString(lettersUsed,aWord[i]))
		{
			aWord[i] = '*';
		}	
		i++;
	}
	return aWord;
}
//print theWord
void sneaky::printTheWord()
{
	string thisWord = theWord;
	int i = 0;
	
	while(i < thisWord.length())
	{
		if(letterInString(lettersUsed,thisWord[i]) == false)
		{
			thisWord[i] = '*';
		}	
		i++;
	}
	cout <<"\n			" << thisWord << endl;
	cout << "\n";
}

//return number of lives user wants
int sneaky::getLives()
{
	int temp;
	cout << "\n\n			HOW MANY LIVES DO YOU WANT:";
	cin >> temp;
	return temp;
	
}
int sneaky::getWordLength()
{
	int wordLength;
	cout << "\n\n			WHAT LENGTH WORD DO YOU WANT? : ";
	cin >> wordLength;
	return wordLength;

}

void sneaky::printString(string s)
{
	int i = 0;
	while(i < s.length())
	{
		if(s[i] != '*')
		{
			cout << s[i] + " ,";
		}	
		i++;
	}
}

bool sneaky::debugMode() //decide to play in debug mode
{
	char dMode;
	cout << "\n\n			WOULD YOU LIKE TO USE DEBUG MODE? y or n:";
	cin >> dMode;
	
	if(dMode == 'y'||dMode == 'Y')
	{
		return true;
	}
	else return false;
}

void sneaky::play()	//Method to play the game.
{

	cout << "\n			  -----------WELCOME TO HANGMAN----------		" << endl;
	
	srand(time(0)); //changes rand algorithm, accesses clock(seconds elapsed since a certain date) => very random
	allWords = new string[200000]; // can hold up to 200000
	updatedAllWords = new string[200000];
	allWords2 = new string[2000000];
	char hasWon = 'n';
	char playAgain;
	bool toPlay;
	bool debug = debugMode();
	
	if(debug)
	{
		cout << "\n\n   *******************WELCOME TO DEBUG MODE*************************" << endl;
 	}

	do
	{
	 	int lives = getLives();		//gets number of lives
		wordCount = 0;				//empties myWords array saying has no words
		lettersUsed = "";			//Clear guessed letters.
		char guess;
		int wordLength = getWordLength();
		char playAgain = 'y';
		
		getWords(wordLength); // read the words into the array
		printTheWord();
		
		//continue while lives > 0
		do 		
		{
			string checkWin = getCurrentWord();
			//if you have no *s left in the word you have won
			if(letterInString(checkWin, '*') == false)
			{									
				hasWon = 'y';
				
			}	
			//If you have got the word break out of the while loop
			if(hasWon == 'y')
			{						
				break;
			}	
			char charOk = 'n';
			
			//use to make sure words in the file fit the pattern
			fitPattern(); 
			
			//output parts needed for the debug part
			if(debug)
			{	
				cout << "\nTHE NUMBER OF WORDS IN THE ARRAY IS: ";
				cout << updatedSize << "\n\n\n";
				cout << "THE WORD WE ARE CURRENTLY LOOKING AT IS: ";
				cout << theWord << "\n\n\n";
				
			}
			
			//continue getting a letter until it is one that has not been used 
			do
			{
				cout << "			ENTER A GUESS:";
				cin >> guess;
				cout << endl;
				
				if(checkLetter(guess, lettersUsed))
				{
					cout << "\n\n			YOU ALREADY USED " << "'" << guess << "'";
					cout << "\n\n";
				}
				
				//if the letter is not in lettersUsed then change charOk to y to continue
				if(letterInString(lettersUsed,guess) == false)	//if guess is not in lettersUsed
				{
					charOk = 'y';
					lettersUsed.push_back(guess);	//put guess in lettersUsed
					lives--;					//Used up a guess.
				}	
			}while(charOk == 'n');
			
			//get rid of the words with the letter you guessed
			removeWordsWithLetter(guess);
			
			if(letterInString(getCurrentWord(),guess))
			{											//if word contains guess
				lives++; //you keep your life
				cout << "\n			YOU GOT A LETTER!!!!\n\n";
			}
			
			if (lives > 1)
			{	
				cout << "			YOU HAVE " << lives << " LIVES LEFT." << endl << endl;
				printTheWord();
			}
			if(lives == 1)
			{	
				cout << "			YOU HAVE " << lives << " LIFE LEFT, CHOOSE WISELY" << endl << endl;
				printTheWord();
			}	
		}while (lives > 0);
		if(lives == 0)	//If you use up the guesses without revealing the full word, you lost.
		{
			cout << "		*****YOU LOSE*****		" << endl << endl;
			cout << "			THE WORD WAS: " << theWord;
		}
		else cout << "\n			WELL DONE, YOU WIN." << endl;

		cout << "\n\n\n			WOULD YOU LIKE TO PLAY AGAIN? y or n: ";
		cin >> playAgain;
		
		if(playAgain == 'y'||playAgain == 'Y')
		{
			toPlay = true;
		}
		else
		{
			toPlay = false;
		}
	
	} while (toPlay);
}
//removes the words containing the guessed letter
void sneaky::removeWordsWithLetter(char c)
{
	int i = 0;
	int allWords2Size = 0;
	
	while(i < updatedSize)
	{
		//if char c is not in word at loc i
		if(letterInString(updatedAllWords[i], c) == false)
		{
			//put that word into a diff array
			allWords2[allWords2Size] = updatedAllWords[i];
			allWords2Size++;
		}
		i++;
	}
	int j = 0;
	if(allWords2Size > 0)
	{
		while(j < allWords2Size)
		{
			updatedAllWords[j] = allWords2[j];
			j++;
		}
		updatedSize = allWords2Size;
	}
	//pick a random word in current wordbank
	theWord = updatedAllWords[rand()%updatedSize];
}
// use to check if a letter is in a string

bool sneaky::checkLetter(char c, string word){

    for(int i=0;i<word.length();i++)
	{
        if(c==word[i])
		{
            return true;
        }
    }
    return false;
}
//removes words that don't fit pattern we already have
void sneaky::fitPattern()	
{
	char containUnderscore = 'n';
 	int allWords2Size = 0;
	string revealed = getCurrentWord();
	int checkStar = 0;
	int wordLoc = 0;
	int letterLoc = 0;
	
	while(checkStar < revealed.length())	//any letters revealed that are not *s
	{
		if(revealed[checkStar] != '*')
		{
			containUnderscore = 'y';
		}	
		checkStar++;
	}								//If word we are looking at only contains '*s', no need to filter
	if(containUnderscore == 'y')//if any letters revealed, get rid of the ones that don't fit the pattern
	{
		while(wordLoc < updatedSize)
		{
			char canBeAdded = 'y';
			
			//if char is'*' check if there is a letter being shown already
			while(letterLoc < updatedAllWords[wordLoc].length())
			{
				if(revealed[letterLoc] == '*')
				{
					if(letterInString(lettersUsed,theWord[letterLoc]))	//If the character is '*', check if the updatedWord
					{									//has char being shown there
						canBeAdded = 'n';					//if it does it shouldn't be added to out current word list
					}
				}
				else									
				{
					//if chars not equal it can't be added
					if(updatedAllWords[wordLoc][letterLoc] != revealed[letterLoc])
					{
						canBeAdded = 'n';
					}						
				}
				letterLoc++;
			}
			if(canBeAdded == 'y')										//If canBeAdded is still true, then the word has passed all of the tests and can be canBeAddeded to the
			{
				allWords2[allWords2Size] = updatedAllWords[wordLoc];
				allWords2Size++;
			}
			wordLoc++;
		}
		if(allWords2Size > 0)
		{
			for(int i = 0; i < allWords2Size; i++)
			{
				updatedAllWords[i] = allWords2[i];
			}
			updatedSize = allWords2Size;
		}
		//pick a random word in current wordbank
		theWord = updatedAllWords[rand()%updatedSize];
	}
}
//checks if char c is in a given string
bool sneaky::letterInString(string s, char c)
{
	int i = 0;
	while(i < s.length())
	{
		if(s[i] == c)
		{
			return true;
		}	
		i++;
	}
	return false;
}
//Function to read words in from text file
//reads words into first array then checks length of words
//and only adds the words of desired length into second array
void sneaky::getWords(int wLength)
{
	string word;
	fstream myFile;
	myFile.open("words.txt");
	while(myFile >> word)
	{
		allWords[wordCount] = word;
		wordCount++;
	}
	myFile.close();
	
	updatedSize = 0;
	int i = 0;
	while(i < wordCount)
	{
		if(allWords[i].length() == wLength)
		{
			updatedAllWords[updatedSize] = allWords[i];
			updatedSize++;
		}
		i++;
	}
	//pick a random word in current wordbank
	theWord = updatedAllWords[rand()%updatedSize];
}