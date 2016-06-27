#include "Hangman.h"
#include <iostream>
#include <string>
#include <fstream> //for using files
#include <vector> // can grow dynamically
#include <cstdlib> // to access random
#include <cTime> //for getting random numbers
#include <stdio.h>
#include <string.h>

using namespace std;

	
	void Hangman::playGame(int lives,int count,char choice,char guess,char playAgain)
	{	
		do
		{
			string lettersUsed = "";
			string word = getWord(); //get the random word
			cout << word << endl;
			string otherWord = coverWord(word); // cover the word up
			cout << otherWord;
			
			cout << "\n	    -----------WELCOME TO HANGMAN----------		" << endl;
			cout << "\n	 	   THE LENGTH OF YOUR WORD IS: " << word.length() << endl;
			
			cout << "\n	 	   DO YOU WANT TO PLAY? Y or N: ";
			cin >> choice;
			
			//if we want to end program
			if(choice == 'n' || choice == 'N')
			{
				break;
			}	
			cout << endl << endl; //to neaten things up
			do
			{
				here:
				if(count != 0) 
				{
					cout << "	\nUSED LETTERS: ";
					cout << lettersUsed << " ";
					cout << endl;
				}
				
				cout << "\n	       HERE IS WHAT YOU HAVE SO FAR:   " << otherWord << endl;
				cout << "\n	       YOU HAVE " << lives << " LIVES, MAKE A GUESS: ";
				cin >> guess;
				
				//check if character has been read b4
				if(checkLetter(guess, lettersUsed))
				{
					cout << "\n\n\n              YOU ALREADY USED THAT !!!!\n\n\n";
					goto here;
				}
				
				
				//lettersUsed[count] = guess; count++;
				lettersUsed = lettersUsed + " " + guess + ","; 
				count++;
				int backUp = lives + 1;//for use with same letter occurance
				for(int i = 0; i <= word.length(); i++)
				{
					if (word[i] == guess || word[i] == guess+32 || word[i] == guess-32) //to accomadate capitals 
					{	
						otherWord[i] = guess;
						lives++;//you don't lose a life
						if(lives == backUp +1) //needed incase same letter occurance
						{
							lives--;
						}	
						
					}
				}
				if (wordCompare(otherWord,word) != 0) 
				{
					cout << "\n\t\t\t      " << word << endl << "\n\t\t\tYOU WIN!!!  \n";
					if(lives > 6)//check that lives doesnt go over 6
					{	
						lives = 6;
					}	
					break;
				}
				lives--;
				if(lives > 6)
				{
					lives = 6;
				}	
			}
			while(wordCompare(otherWord,word) != 0 || lives > 0);//while the words are not equal or you have lives left,
			
			if (wordCompare(word,otherWord) == 0) //if the words are not equal
			{	
				cout<<"\n\n\n\n			YOU LOSE.\n\n			THE WORD WAS: " << word << endl;
			}
				
			cout << "\n\n WOULD YOU LIKE TO PLAY ANOTHER GAME? : y OR n: ";
			lives = 6;
			//clear the used letters string
			cin >> playAgain;
			//if(playAgain == 'y'){
			//	for(int i = 0; i < lettersUsed.size();i++)
			//	{
			//		lettersUsed = lettersUsed +" ";
			//	}
			//}

			count = 0;//reset the count
				
		}while(playAgain == 'y' ||playAgain == 'Y');	
	}
//function to get a random word from a text file
string Hangman::getWord()
{		
		vector<string> myWords;
		string word;
		ifstream myFile("words.txt");
		
		//add all the words into the vector myWords
		
		
		while(myFile >> word) // while words.txt has words left
		{
			myWords.push_back(word); //push_back adds a new element at the end of the vector
		}
		
		myFile.close();
		
		//now randomly select a word from the vector and return it
		
		int vecSize = myWords.size();
		
		srand(time(0)); //changes rand algorithm, accesses clock(seconds elapsed since a certain date) => very random
		return myWords.at(rand()%vecSize);
		
} 
//function to cover the word in *s
string Hangman::coverWord(string coverMe)
{
	string theCover = coverMe;
	
	for(int i=0; i <= coverMe.length();i++)//to run through the word
    {
		if(coverMe[i] != ' ')
		{
			theCover[i]='*'; //cover Letter with '*'
		}	
	}
	return theCover;
}
//compares strings ignoring case sensitivity
bool Hangman::wordCompare(const string& x, const string& y)
{
    unsigned int size = x.size();
    if (x.size() != size)
	{
        return false;
	}
    for(unsigned int i = 0; i < size; ++i)
	{
        if (tolower(x[i]) != tolower(y[i]))
        { 
			return false;
		}
	}	
    return true;
}
bool Hangman::checkLetter(char c, string word){

    for(int i=0;i<word.length();i++)
	{
        if(c==word[i])
		{
            return true;
        }
    }
    return false;
}