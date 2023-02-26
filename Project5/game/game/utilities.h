//
//  utilities.h
//  game
//
//  Created by Sakshi Thoutireddy on 11/7/22.
//

// utilities.h

const int MINWORDLEN = 4;
const int MAXWORDLEN = 6;

int getWords(char words[][MAXWORDLEN+1], int maxWords, const char wordfilename[]);
int randInt(int min, int max);
