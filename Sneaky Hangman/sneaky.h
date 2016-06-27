#include <string>
using namespace std;

class sneaky
{
	public:
		//ALL METHODS USED IN sneaky.cpp
		int getLives();
		int getWordLength();
		void printString(string);
		void play();
		bool debugMode();
		bool checkLetter(char, string);
		void getWords(int);
		void printWords(int);
		void removeWordsWithLetter(char );
		bool letterInString(string, char);
		string getCurrentWord();
		void fitPattern();	
		void printTheWord();
		
		
	private:
		//VARIABLES THAT CAN BE ACCEESED THROUGHOUT CODE
		string lettersUsed;
		long wordCount;
		string *allWords;//so can use as array throughout program
		string *allWords2;
		string *updatedAllWords;
		string theWord; // current word we are looking at
		int updatedSize;
		
};