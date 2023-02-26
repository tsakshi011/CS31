//
//  main.cpp
//  poll
//
//  Created by Sakshi Thoutireddy on 10/22/22.
//

#include <iostream>
#include <string>
#include <cctype>
#include <cassert>
using namespace std;

bool isStateCode(string stateCode){
    string upperStateCode = "";
    upperStateCode += toupper(stateCode.at(0));
    upperStateCode += toupper(stateCode.at(1));
    
    const string codes =
            "AL.AK.AZ.AR.CA.CO.CT.DE.FL.GA.HI.ID.IL.IN.IA.KS.KY."
            "LA.ME.MA.MD.MI.MN.MS.MO.MT.NE.NV.NH.NJ.NM.NY.NC.ND."
            "OH.OK.OR.PA.RI.SC.SD.TN.TX.UT.VT.VA.WA.WV.WI.WY";
    return (upperStateCode.size() == 2  &&
                upperStateCode.find('.') == string::npos  &&  // no '.' in stateCode
                codes.find(upperStateCode) != string::npos);  // match found
}


int convertToInt(string seats){
    int num = 0;
    for(int i = 0; i < seats.size(); i++){
        num = (num * 10) + (seats.at(i) - '0'); //converting character at position to integer in last digit's place
     }
    return num;
}

bool isValidStateForecast(string stateForecast){
    if(stateForecast.size() >= 2){
        string stateCode = "";
        stateCode += stateForecast.at(0);
        stateCode += stateForecast.at(1);
        if(stateForecast.size() == 2 && isStateCode(stateCode)) return true; //stateForecast - stateCode w/ no party results
        if(!isStateCode(stateCode)){
            return false;
        }
        
        for(int i = 2; i < stateForecast.size(); i++){
            if(i == stateForecast.size() - 1 && !(isalpha(stateForecast.at(i)))){
                return false; //if the last character is not a letter then pollstring not valid
            }
            
            if(!isdigit(stateForecast.at(i)) && !isalpha(stateForecast.at(i)) && stateForecast.at(i) != ','){ //if the character is not a letter, digit, or comma then not valid poll string
                return false;
            }
            if(i != stateForecast.size()-1){
                if(stateForecast.at(i) == ' '){ //if the position is not the last character and its a space then not valid forecast: "KS 4R"
                    return false;
                }
                if(isdigit(stateForecast.at(i)) && !(isdigit(stateForecast.at(i+1)) || isalpha(stateForecast.at(i+1)))){//digit followed by letter or another digit
                    return false;
                }else if(isalpha(stateForecast.at(i)) && !isdigit(stateForecast.at(i+1))){ //party code character must be followed by next party result
                    return false;
                }else if(isdigit(stateForecast.at(i)) && isdigit(stateForecast.at(i+1)) && isdigit(stateForecast.at(i-1))){ //checks to make sure party result is not more than two digits
                    return false;
                }
            }
        }
    }else{
        return false;
    }
    return true;
}

bool isValidPollString(string pollData){
    //if space after comma return false

    string stateForecast = "";
    if(pollData == ""){ // empty string is valid
        return true;
    }
    if(pollData.find(" ") != -1){ //if spaces present in the polldata string not valid
        return false;
    }
    
    for(int i = 0; i < pollData.size(); i++){
        if(pollData.at(i) != ','){
            stateForecast += pollData.at(i);
        }else if(i == 0 || i == pollData.size()-1){//if comma first position or last position return false
            return false;
        }else if(i != pollData.size() - 1 && pollData.at(i+1) == ' '){
            return false;
        }else if(!(isValidStateForecast(stateForecast))){
            return false;
        }
        if(pollData.at(i) == ','){
            stateForecast = "";
        }
    }
    return isValidStateForecast(stateForecast);
}

int countSeats(string pollData, char party, int& seatCount){
    if(!isValidPollString(pollData)){ //checking validity of the pollstring
        return 1;
    }else if(!isalpha(party)){ //if not letter party letter not valid
        return 2;
    }else{
        seatCount = 0;
        for(int i = 0; i < pollData.size(); i++){
            string numSeats = "";
            if(toupper(pollData.at(i)) == party || tolower(pollData.at(i)) == party){
                if(isdigit(pollData.at(i-1)) && isdigit(pollData.at(i-2))){ // handles two-digit numbers
                    numSeats += pollData.at(i-2);
                    numSeats += pollData.at(i-1);
                    seatCount += convertToInt(numSeats); //convert from string to int and add to seatCount
                }else if(isdigit(pollData.at(i-1))){ //handles one-digit numbers
                    numSeats += pollData.at(i-1);
                    seatCount += convertToInt(numSeats); //convert from string to int and add to seatCount
                }
            }
        }
        return 0;
    }
}

int main() {
    
    assert(!isValidPollString("+"));//not a digit, letter, or comma
    assert(!isValidPollString("ct5d,ny9r17+1i"));//contains character not valid
    assert(isValidPollString("CT5D,NY9R16D1I,VT,ne3r00D"));//valid 00
    assert(!isValidPollString("ZT5D,NY9R16D1I,VT,ne3r00D"));//not valid state code ZT
    assert(!isValidPollString("CT 5D,NY9R16D1I,VT,ne3r00D"));//not valid
    assert(!isValidPollString("CT5 D,NY9R16D1I,VT,ne3r00D"));//not valid space in between the party result
    assert(!isValidPollString("CT5D, NY9R16D1I,VT,ne3r00D"));//not valid - cannot have space after comma
    assert(!isValidPollString("CT5D,NY9R16D1I,VT,ne3r00D "));//not valid - cannot end with a space
    assert(!isValidPollString("CT5D#,NY9R16D1I,VT,ne3r00D"));//not valid - cannot have hashtag - not a letter or a digit
    assert(!isValidPollString("CIL5D,NY9R16D1I,VT,ne3r00D"));//not valid - cannot have three letter state code
    assert(!isValidPollString("CT505D,NY9R16D1I,VT,ne3r00D"));//not valid - three digit party result
    assert(isValidPollString("Ct5D,nY0R16d1I,VT,ne3r00D"));//valid - different punctuations of party code & party codes
    assert(!isValidPollString("CT5DR,NY0R16D1I,VT,ne3r00D")); //not valid -party code could not be more than one letter
    assert(!isValidPollString("CT505D,NY9R16D1I,VT,3r00D"));//not valid - do not have a party code
    assert(!isValidPollString(",CT505D,NY9R16D1I,VT,CA3r00D"));//not valid - cannot start with comma
    assert(!isValidPollString("CT505D,NY9R16D1I,VT,CA3r00D,"));//not valid - cannot end with comma
    assert(!isValidPollString("CAR5D,NY9R16D1I,VT,3r00D")); //not valid - three letter party code
    assert(isValidPollString("VT")); //valid - only one state code
    assert(isValidPollString("VT5D")); //valid - only one state forecast
    assert(!isValidPollString(",CT5D,NY9R16D1I,VT,ne3r00D"));//cannot begin with a comma
    assert(!isValidPollString("CT5D,NY9R16D1I,VT,ne3r00D,")); //cannot end with a comma
    assert(isValidPollString("CT5D,NY9R16D1I,VT,ne3r00D"));
    assert(!isValidPollString("CT5D,NY9R16D1I,VT,,ne3r00D")); //not valid - double comma
    assert(!isValidPollString(","));//not valid - comma not valid
    assert(isValidPollString(""));//valid - empty string is valid
    assert(!isValidPollString(" "));//not valid - string with space is not valid
    int seats;
    seats = -999;    // so we can detect whether countSeats sets seats
    assert(countSeats("CT5D,NY9R16D1I,VT,ne3r00D", 'd', seats) == 0  &&  seats == 21);
    seats = -999;    // invalid poll string, seats should remain the same and function should return 1
    assert(countSeats("CT5D,NY9R16D1I,VT,,ne3r00D", 'd', seats) == 1  &&  seats == -999);
    seats = -999;    // invalid poll string & party letter
    assert(countSeats("CT5D,NY9R16D1I,VT,,ne3r00D", '2', seats) == 1  &&  seats == -999);
    seats = -999;    //not a valid party letter
    assert(countSeats("CT5D,NY9R16D1I,VT,ne3r00D", '%', seats) == 2  &&  seats == -999);
    seats = -999;    //not a valid party letter
    assert(countSeats("CT5D,NY9R16D1I,VT,ne3r00D", '1', seats) == 2  &&  seats == -999);
    seats = -999;
    assert(countSeats("CT5D,NY9R16D1I,VT,ne3r00D,cA9R18D1i,NY9r", 'r', seats) == 0  &&  seats == 30);
    seats = -999; //only state code poll string
    assert(countSeats("VT", 'r', seats) == 0 && seats == 0);
    seats = -999; //uppercase party letter
    assert(countSeats("VT9r", 'R', seats) == 0 && seats == 9);
    seats = -999; //two of same party's results in same state forecast
    assert(countSeats("VT9r,CA94R5d4d", 'd', seats) == 0 && seats == 9);
    seats = -999; //party results starts with 0
    assert(countSeats("VT9r0l,CA94R5d4d", 'l', seats) == 0 && seats == 0);
    seats = -999;
    assert(countSeats("", 'D', seats) == 0 && seats == 0);
    seats = -999;
    assert(countSeats("CT5D,NY9R16D1I,VT,ne3r00D", '%',seats) == 2 &&seats == -999);
    cerr << "All tests succeeded" << endl;
}
