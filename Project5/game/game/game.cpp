//
//  main.cpp
//  game
//
//  Created by Sakshi Thoutireddy on 11/7/22.
//

#include "utilities.h"
#include <iostream>
#include <cstring>
using namespace std;

const char WORDFILENAME[] = "/Users/Sakshi/Desktop/Project5/words.txt";
        // Windows users:  Use / instead of \ for pathname separators.

bool isInDictionary(const char dictionary[][7], char word[], int nWords){
    for(int i = 0; i < nWords; i++){
        if(strcmp(word, dictionary[i]) == 0){//checks in the text file passed in whether word is present
            return true;
        }
    }
    return false;
}

bool validGuess(char guess[]){ //unknown guess words or lengths not between 4 and 6 --> 4 & 6 are not valid
    if(strlen(guess) < 4 || strlen(guess) > 6){
        return false;
    }
    for(int i = 0; i < strlen(guess); i++){
        if(!islower(guess[i])){ //each element of the cstring has to be lowercase
            return false;
        }
    }
    return true;
}

int numGolds(char targetWord[], char guess[]){ //checks the number of golds in two words
    int gold = 0;
    int len = strlen(guess); //avoid out of bounds error
    if(strlen(targetWord) < strlen(guess)){
        len = strlen(targetWord);
    }
    for(int i = 0; i < len; i++){
        if(targetWord[i] == guess[i]){ //gold: equal letters have to be at the same position from the probe word and target word
            gold ++;
        }
    }
    return gold;
}

int numSilvers(char targetWord[], char guess[]){//checks the number of silvers in two words
    int silver = 0;
    char duplicateTarget[7] = {'\0'};
    char duplicateGuess[7] = {'\0'};
   
    strcpy(duplicateTarget, targetWord); //copies targetWord over into duplicateTarget b/c char array
    strcpy(duplicateGuess, guess);
    
    for(int i = 0; i < strlen(duplicateTarget); i++){
        for(int j = 0; j < strlen(duplicateGuess); j++){
            if(isalpha(duplicateGuess[j]) && duplicateGuess[j] == duplicateTarget[i]){ //checks if element is a letter and if any elements equal from duplicateTarget and duplicateGuess
                silver ++;
                duplicateTarget[i] = '#'; //avoids duplicate silvers being counted more than once
                duplicateGuess[j] = '#';
                break;
            }
        }
    }
    return (silver - numGolds(targetWord, guess)); // true number of silvers removes silvers that are considered to be golds
}


int playOneRound(const char words[][7], int nWords, int wordnum){
    char targetWord[7] = {'\0'};
    strcpy(targetWord, words[wordnum]); //copies the cstring at the random index as the hidden/target word
    char probe[101] = {'\0'};
    int tries = 0;
    
    if(nWords <= 0 || wordnum < 0 || wordnum >= nWords){ //checking the validity of parameters
        return -1;
    }
    
    //cout << "TARGET WORD: " << targetWord << endl;
    for(;;){ //infinite for loop
        cout << "Probe word: ";
        cin.getline(probe, 101);
        if(!validGuess(probe)){//calling to check validity of the probe word
            cout << "Your probe word must be a word of 4 to 6 lower case letters." << endl;
            continue;
        }
        if(!isInDictionary(words, probe, nWords)){ //calling to check if the word is in the dictionary
            cout << "I don't know that word." << endl;
            continue;
        }
        if(strcmp(targetWord,probe) == 0){ //when the targetWord is equal to guess break out of the infinite loop
            tries ++;
            break;
        }else{
            tries ++;
            cout << "Golds: " << numGolds(targetWord, probe) << ", Silvers: " << numSilvers(targetWord, probe) << endl;
        }
    }
    return tries;
}

int main(){
    const int MAXWORDS = 9002;//Initializes all variables; declared number of cstrings in the array is at least 9000
    const int MAXWORDLEN = 6;
    char wordList[MAXWORDS][MAXWORDLEN +1];
    int nWords = getWords(wordList, MAXWORDS, WORDFILENAME);
    int RANDINT = 0;
    if(nWords < 1){
        cout << "No words were loaded, so I can't play the game." << endl;
        return 0;
    }
    
    
    int rounds = 0; //Segment for Rounds portion of the game
    cout << "How many rounds do you want to play? ";
    cin >> rounds;
    cin.ignore(1000,'\n');
    if(rounds <= 0){
        cout << "The number of rounds must be positive." << endl;
        return 0;
    }
    
    int maxTries = 0;
    int minTries = 0;
    double average = 0.0;
    for(int i = 1; i <= rounds; i++){ //loops for the number of rounds
        
        RANDINT = randInt(0,nWords-1); //Random integer generated here
        
        cout << endl;
        cout << "Round " << i << endl;
        cout << "The hidden word is " << strlen(wordList[RANDINT]) <<" letters long." << endl; //program tells user the hidden word's length
        int tries = playOneRound(wordList, nWords, RANDINT); //calls playOneRound for each round played
        
        if(i == 1){ //sets maximum tries and minimum tries
            maxTries = tries;
            minTries = tries;
        }else{
            if(tries < minTries){
                minTries = tries;
            }else if(tries > maxTries){
                maxTries = tries;
            }
        }
        average += tries;
        if(tries == 1){ //Printing out the tries differ between 1 or more than 1
            cout << "You got it in " << tries << " try." << endl;
        }else{
            cout << "You got it in " << tries << " tries." << endl;
        }
        cout.setf(ios::fixed);
        cout.precision(2); //two decimal points when returning the average
        cout << "Average: " << average/i <<", minimum: " << minTries << ", maximum: " << maxTries << endl;
    }
    
    
}
