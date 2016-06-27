#include <string>
using namespace std;

class Hangman
{
	public:
		//METHODS
		void playGame(int ,int ,char ,char ,char);
		string getWord(); 
		string coverWord(string);
		bool wordCompare(const string&, const string&);
		bool checkLetter(char c, string word);
		
};
//#endif		