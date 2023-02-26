//
//  tax.cpp
//  tax
//
//  Created by Sakshi Thoutireddy on 10/7/22.
//

#include <iostream>
#include <string>
using namespace std;

int main() {
    
    string name;//declaring variables
    double taxableIncome;
    string occupation;
    int numberOfChildren;
    
    cout << "Name: "; //getting input from user
    getline(cin, name);
    cout << "Taxable income: ";
    cin >> taxableIncome;
    cin.ignore(10000, '\n');
    cout << "Occupation: ";
    getline(cin, occupation);
    cout << "Number of children: ";
    cin >> numberOfChildren;
    cin.ignore(10000, '\n');
    cout.setf(ios::fixed);
    cout.precision(2);
    cout << "---" << endl;
    
    if(name == ""){ //statements to detect incorrect input
        cout << "You must enter a name" << endl;
        return 0;
    }else if(taxableIncome < 0){
        cout << "The taxable income must not be negative" << endl;
        return 0;
    }else if(occupation == ""){
        cout << "You must enter an occupation" << endl;
        return 0;
    }else if(numberOfChildren < 0){
        cout << "The number of children must not be negative" << endl;
        return 0;
    }else{
        double tax = .04;
        double result = 0.0;
        double originalIncome = taxableIncome;
        if(taxableIncome < 55000){ //taxableIncome less than 55000
            result = taxableIncome * tax;
            taxableIncome -= 55000;
        }else{ //taxableIncome more than 55000
            result += 55000 * tax;
            taxableIncome -= 55000;
            
            if(occupation == "teacher" || occupation == "nurse"){ // conditions for next tax bracket for special occupations
                tax = .05; // tax is lowered for special occupations
            }else{
                tax = .07; // tax normal for normal occupations
            }
            
            if(taxableIncome < 70000){//if taxable income less than 125000
                result += taxableIncome * tax;
            }else{ // if taxable income more than 125000
                result += 70000 * tax;
                taxableIncome -= 70000;
                result += taxableIncome * .093;
            }

        }
        
        if(originalIncome < 125000){ // taxable income less than 125000
            result -= 200 * numberOfChildren; // reduce payment by 200 by every child
        }
        
        if(result < 0){
            result = 0; // if resulting payment less than 0; automatically set payment to 0
        }
       
        
        cout << name << " would pay $" << result << endl;;
        
    }
    
    
    return 0;
}

