# Hangman-in-C-

The goal of this project was to create a command line version of hanging in C++. After successful creation of the regular game the sneaky game had to be implemented which is described below.

Sneaky Hangman - Description
In a normal game of hangman there are two players, one, the server, thinks of a word and the other, the player, tries to guess the word by choosing letters. The server usually does not change the word after play has begun. This would be very sneaky.

You are to write a sneaky version of the game of hangman. As far as the player is concerned it is just like a normal game of hangman except that the player nearly always loses. Here is an example of the sneakiness. The player has just reached this position:

	D_NCE
The secret word could be DANCE or DUNCE. Let's say the the player chooses 'U' for DUNCE, then the server says, "Tough" it was DANCE. However, if the player had chosen 'A', then the server would have said that it was DUNCE. So at every stage, the server chooses a word which will make it harder for the player.

Note that this process happens at every guess, not just the last letter. Let's assume that there are 5 letters in the word and on the first go, the player guesses 'e'. For this example, let's assume that no word contains more than one 'e'. So there are 6 possibilities that the server needs to consider: the first possibility is that there is no 'e' in the word and the remaining five possibilities are that the 'e' occurs in one of the five other positions.

Each of these possibilities has a number of words associated with it, e.g. there might be 100 words with no 'e' in it and 10 words with 'e' in the first position. When the server is deciding on a letter, it should choose the possibility with most words associated with it.

It will not be possible to win against such a game unless you get a large number of guesses.

Note: this assignment idea came from the Nifty Assignment series and was developed by Keith Schwarz.
