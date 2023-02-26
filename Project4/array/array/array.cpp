//
//  main.cpp
//  array
//
//  Created by Sakshi Thoutireddy on 10/29/22.
//

#include <iostream>
#include <string>
#include <cassert>
using namespace std;

int appendToAll(string a[], int n, string value){
    if(n < 0){ //error checker
        return -1;
    }
    for(int i = 0; i < n; i++){
        a[i] += value; //add value to end of each element held in the parameter array
    }
    return n;
}

int lookup(const string a[], int n, string target){
    if(n < 0){ //error checker
        return -1;
    }
    for(int i = 0; i < n; i++){
        if(a[i] == target){ //check if the element is equivalent to parameter target
            return i;
        }
    }
    return -1;
}

int positionOfMax(const string a[], int n){
    if(n <= 0){ //error checker
        return -1;
    }
    string max = a[0];
    int maxIndex = 0;
    for(int i = 0; i < n; i++){
        if(a[i] > max){
            max = a[i];
            maxIndex = i;
        }
    }
    return maxIndex;
}

int rotateLeft(string a[], int n, int pos){
    if(n < 0 || pos >= n || pos < 0){ //error checker
        return -1;
    }
    string temp = a[pos];
    for(int i = 0; i < n -1; i++){
        if(i == pos){
            temp = a[pos];
            a[i] = a[i+1];
        }else if(i > pos){
            a[i] = a[i+1];
        }
    }
    a[n-1] = temp;
    return pos;
}

int countRuns(const string a[], int n){
    if(n < 0){ //error checker
        return -1;
    }
    if(n == 0){
        return 0;
    }
    int count = 1;
    for(int i = 0; i < n - 1; i++){
        if(a[i] != a[i+1]){ //if the element does not equal the next element different sequence
            count ++;
        }
    }
    return count;
}

int flip(string a[], int n){
    if(n < 0){ //error checker
        return -1;
    }
    string temp = "";
    for(int i = 0; i < n/2; i++){
        temp = a[i]; //set temp element stored not erased
        a[i] = a[n-i-1];
        a[n-i-1] = temp;
    }
    return n;
}

int differ(const string a1[], int n1, const string a2[], int n2){
    if(n1 < 0 || n2 < 0){ //error checker
        return -1;
    }
    int minLength = 0; //whichever of n1 or n2 is less
    if(n1 < n2){
        minLength = n1;
    }else if(n2 < n1){
        minLength = n2;
    }else if(n1 == n2){
        minLength = n2;
    }
    
    for(int i = 0; i < minLength; i++){
        if(a1[i] != a2[i]){ //first element in a1 that does not equal a2 return position
            return i;
        }
    }
    return minLength; //returns whichever is less of n1 or n2
}

int subsequence(const string a1[], int n1, const string a2[], int n2){
    if(n2 > n1 || n1 < 0 || n2 < 0){ //error checker
        return -1;
    }
    if(n2 == 0){ //n2 can be 0 but n1 cannot be 0 unless n2 is also 0
        return 0;
    }
    for(int i = 0; i < n1 - 1; i++){
        for(int j = 0; j < n2 -1; j++){
            if(a1[i] == a2[j] && a1[i+1] == a2[j+1]){ //if corresponding element in a1 and a2 is equal as well as at the next index then begining of sequence is detected
                return i; //smallest position of a1 returned immediately
            }
        }
    }
    
    return -1; //no sequence found returns -1
}


int lookupAny(const string a1[], int n1, const string a2[], int n2){
    if(n1 < 0 || n2 < 0){
        return -1;
    }
    for(int i = 0; i < n1; i++){
        for(int j = 0; j < n2; j++){
            if(a1[i] == a2[j]){ //first position of element in a2 in a1
                return i;
            }
        }
    }
    return -1;
}


void rotateUpper(string a[], int n){
    string temp = "";
    for(int i = 0; i < n - 1; i++){
        for(int j = i + 1; j < n; j++){
            if(a[j] < a[i]){
                temp = a[j];
                a[j] = a[i];
                a[i] = temp;
            }
        }
    }
}

int split(string a[], int n, string splitter){
    if(n < 0){ //error checker
        return -1;
    }
    int countLower = 0;
    string temp = "";
    
    rotateUpper(a, n);
    for(int i = 0; i < n; i++){
        if(a[i] < splitter){
            countLower++;
        }
    }
    return countLower;
}

int main() {
    //cases from spec
    string h[7] = { "rishi", "margaret", "gordon", "tony", "", "john", "liz" };
    assert(lookup(h, 7, "john") == 5);
    assert(lookup(h, 7, "gordon") == 2);
    assert(lookup(h, 2, "gordon") == -1); //gordon not found in the array given
    assert(positionOfMax(h, 7) == 3);

    string g[4] = { "rishi", "margaret", "liz", "theresa" };
    assert(differ(h, 4, g, 4) == 2);
    assert(appendToAll(g, 4, "?") == 4 && g[0] == "rishi?" && g[3] == "theresa?");
    assert(rotateLeft(g, 4, 1) == 1 && g[1] == "liz?" && g[3] == "margaret?");

    string e[4] = { "gordon", "tony", "", "john" };
    assert(subsequence(h, 7, e, 4) == 2);

    string d[5] = { "margaret", "margaret", "margaret", "tony", "tony" };
    assert(countRuns(d, 5) == 2);
        
    string f[3] = { "liz", "gordon", "tony" };
    assert(lookupAny(h, 7, f, 3) == 2);
    assert(flip(f, 3) == 3 && f[0] == "tony" && f[2] == "liz");
        
    assert(split(h, 7, "liz") == 3);
    
    //appendToAll() test cases
    string s[3] = { "borris", "rishi", "borris"};
    string q[2] = {"", ""};
    string w[3] = {"borris", "liz", "rishi"};
    assert(appendToAll(s, -9, "borris") == -1 && s[0] == "borris"); // n is negative therefore must return -1 & array is unchanged
    assert(appendToAll(s, 0, "2") == 0 && s[0] == "borris"); //n is 0 therefore must return 0 & array is unchanged
    assert(appendToAll(s, 3, "") == 3 && s[2] == "borris"); //returns n && adds empty string
    assert(appendToAll(q, 2, "?") == 2 && q[1] == "?"); //returns n && appends string to an empty string
    assert(appendToAll(w, 2, "!") == 2 && w[0] == "borris!" && w[2] == "rishi"); //changes only number of elements passed does not changed rest of elements in the array
    
    
    //lookup() test cases
    string r[6] = {"borris", "rishi", "liz", "gordon", "", "gordon"};
    assert(lookup(r, -9, "borris") == -1 && r[3] == "gordon"); //n is negative must return -1 & array is unchanged
    assert(lookup(r, 4, "liz") == 2 && r[3] == "gordon");// returns 2 position of liz & array is unchanged
    assert(lookup(r, 4, "sam") == -1); //returns -1 because element not found
    assert(lookup(r, 4, "sam") == -1); //returns -1 because element not found
    assert(lookup(r, 5, "") == 4);//returns 3 - lookup empty string
    assert(lookup(r, 0, "borris") == -1); //returns -1 if you pass length of 0
    assert(lookup(r, 6,  "gordon") == 3); //returns the smallest position of where element appears
    assert(lookup(r, 6, "Rishi") == -1); //returns -1 bc capitalization matters
    
    //positionOfMax test cases
    string t[4] = {"david", "liz", "tony", "tony"};
    string p[5] = {"zia", "david", "liz", "tony", "tony"};
    assert(positionOfMax(t, 4) == 2 && t[0] == "david"); //returns 2 - smallest element if max element has a duplicate & array unchanged
    assert(positionOfMax(t,0) == -1); //n is 0 returns -1
    assert(positionOfMax(p, 5) == 0); //max located at position 0
    assert(positionOfMax(t,1) == 0); //max of length 1 returns first element
    
    //rotateLeft test cases
    string u[3] = {"david", "liz", "rishi"};
    string l[4] = {"david", "liz", "rishi", "amara"};
    assert(rotateLeft(u, 0, 1) == -1);// if n is 0 return -1
    assert(rotateLeft(u, 3, 0) == 0 && u[0] == "liz" && u[2] == "david"); //rotate element at the first position
    assert(rotateLeft(l, 4, 3) == 3 && l[0] == "david" && l[3] == "amara"); //rotate element at the last position which leaves the array unchanged
    assert(rotateLeft(l, -3, 2) == -1); //negative n returns -1
    assert(rotateLeft(l, 3, -2) == -1); //negative position returns -1
    assert(rotateLeft(l, 2, 3) == -1); //position is greater than length given(n) therefore return -1
    
    //countRuns test cases
    string b[9] = {"tony", "boris", "rishi", "rishi", "gordon", "gordon", "gordon", "rishi", "rishi"};
    string m[3] = {"tony", "tony", "tony"};
    assert(countRuns(b,0) == 0); //if n is 0 returns 0 because no runs
    assert(countRuns(b,-5) == -1); //if negative n return -1
    assert(countRuns(b,9) == 5); // 5 different subsequences
    assert(countRuns(b,5) == 4); // checking if does not duplicate run
    assert(countRuns(m,3) == 1); //only one run all strings equal
    
    //flip test cases
    string leader[6] = { "boris", "rishi", "", "tony", "theresa", "david" };
    assert(flip(leader, 0) == 0); // if n is 0 returns 0
    assert(flip(leader, -4) == -1); //n1 is negative therefore return -1
    assert(flip(leader, 1) == 1 && leader[0] == "boris" && leader[1] == "rishi");
    assert(flip(leader, 2) == 2 && leader[0] == "rishi" && leader[1] == "boris");
    assert(flip(leader, 3) == 3 && leader[0] == "" && leader[1]=="boris" && leader[2]=="rishi");//checking if flip works - normal case
    
    //differ test cases
    string first[6] = { "boris", "rishi", "", "tony", "theresa", "david" };
    string second[5] = { "boris", "rishi", "david", "", "tony" };
    assert(differ(first, 6, second, 5) == 2); //elements stopped being equal at index 2 of first
    assert(differ(first, 2, second, 1) == 1); //returns 1 beacuse n2 < n1 equal uptil n2 running out
    assert(differ(first, 0, second, 5) == 0); //return 0
    assert(differ(first, 6, second, 0) == 0); //return 0
    assert(differ(first, 2, second, 6) == 2); //return 2 because n1 < n2 equal uptil n1 ran out
    assert(differ(first, 3, second, 4) == 2); //corresponding elements stopped being equal at index 2 wiht "" and "david"
    
    //subsequence test cases
    string names[10] = { "john", "margaret", "theresa", "rishi", "boris", "liz" };
    string names1[10] = { "margaret", "theresa", "rishi" };
    //assert(subsequence(names, 0, names1, 0) == 0); //return 0
    assert(subsequence(names, 0, names1, 4) == -1); // returns -1
    assert(subsequence(names, 4, names1, 0) == 0); // returns 0
    assert(subsequence(names, 3, names1, 2) == 1); //returns 0 where subsequence begins
    assert(subsequence(names, 2, names1, 2) == -1); //no subsquence found
    
    //lookupAny test cases
    string names2[10] = { "john", "margaret", "theresa", "rishi", "rishi", "boris", "liz" };
    string set1[10] = { "david", "boris", "rishi", "margaret" };
    assert(lookupAny(names2, 0, set1, 0) == -1); //n1 and n2 is 0 return -1
    assert(lookupAny(names2, 3, set1, 0) == -1); //no element found return -1
    assert(lookupAny(names2, 0, set1, 3) == -1); //no element found return -1
    assert(lookupAny(names2, 3, set1, 2) == -1); //no element from bounds in a1 equal to any in a2
    assert(lookupAny(names2, -9, set1, 2) == -1); //n1 is negative therefore returns -1
    assert(lookupAny(names2, 3, set1, -2) == -1); //n2 is negative therefore returns -1
    assert(lookupAny(names2, 5, set1, 3) == 3); //position of element in a1 that is found in a3 --> smallest position
    assert(lookupAny(names2, 3, set1, 4) == 1); //when n1 is greater than n2 element can still be found
    
    //split test cases
    string pmnorm[6] = { "david", "liz", "margaret", "tony", "gordon", "boris" };
    string pm[7] = { "david", "liz", "liz", "margaret", "tony", "gordon", "boris" };
    string pm2[4] = { "margaret", "theresa", "liz", "rishi" };
    assert(split(pm2, 4, "rishi") == 2 && pm2[2] == "rishi" && pm2[3] == "theresa"); //splitter present in the array
    assert(split(pmnorm, 6, "john") == 3 && pmnorm[3] == "liz"); //normal case
    assert(split(pm, 0, "liz") == 0); //if n is 0 returns 0
    assert(split(pm, 7, "david") == 1 && pm[0] == "boris" && pm[1] == "david");
    assert(split(pm, 7, "liz") == 3 && pm[3] == "liz");
    string ex[4] ={"zita", "ari", "ari", "caya"};
    assert(split(ex, 4, "ari") == 0 && ex[0] == "ari" && ex[3] == "zita"); //two cases of splitter located in the array and they are less than all the other elements
    string ex2[5] = {"borris", "ari", "caya", "davis", "bina"};
    assert(split(ex2,5,"davis") == 4 && ex2[0] == "ari" && ex2[4] == "davis"); //splitter is greater than all the other elements
    cerr << "All tests succeeded" << endl;
    

}
