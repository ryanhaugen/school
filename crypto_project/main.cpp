#include <iostream>
#include <fstream>
#include "library.h"
#include <iomanip>
#include <cstring>

using namespace std;

int main() {
crypto c[10];
ifstream fin;
fin.open("input.dat");
  if (!fin.is_open()){
    cout << "can't open the file\n";
    return 1;
  }
int option;
string cryptoName;
int day = 0;
string credit;
string startDate;
double price = 0;
do {
  collect(fin, c, credit, startDate);
  option = menu();
  if(option == 1){
    display_all(c);
  }
  if(option == 2){
    cout << endl << "Which crypto currency would you like to display? Please input in all caps. (Ex: BITCOIN)"<< endl << endl;
    cin.ignore();
    getline(cin, cryptoName);
    cout << endl;
    for(int i = 0; i < 10; i++){
      if(cryptoName == c[i].name){
          display(c, cryptoName);
      }
    }
    cout << endl; 
  }
  if(option == 3){
    cout << endl << "Which crypto currency would you like to display stats for? Please input in all caps. (Ex: BITCOIN)"<< endl << endl;
    cin.ignore();
    getline(cin, cryptoName);
    cout << endl;
    for(int i = 0; i < 10; i++){
      if(cryptoName == c[i].name){
          coin_change(c, cryptoName);
      }
    }
    cout << endl; 
  }
  if(option == 4){
    cout << endl << "Which day would you like to display stats for? Please pick between (1-7)." << endl << endl;
    cin >> day;
    if(day <= 7 && day >= 1){
      cout << endl;
      day_change(c, day);
    }
  }
  if(option == 5){
    cout << endl << "At what price would you like to filter crypto currencies?" << endl << endl;
    cin >> price;
    if(price <= 20000 && price >= 0){
      cout << endl;
      price_above(c, price);
    }
  }
  if(option == 6){
    cout << endl;
    display_alphebetical(c);
    cout << endl;
  }
  if(option == 7){
    cout << endl;
    display_SortPrice(c);
    cout << endl;
  }
  if(option == 8){
    return 0;
  }
}while(option != 8);

//collect(fin, c, credit, startDate);
//display_SortPrice(c);
//display_alphebetical(c);
//price_above(c, price);
//display_all(c);
//cout << endl;
//coin_change(c, cryptoName);
//cout << endl;
//display(c, cryptoName);
//cout << endl;
//day_change(c, day);
//cout << endl;
//
  fin.close();
  return 0;
}