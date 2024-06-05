#include "library.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>

using namespace std;

const int ARR_SIZE = 10;

int menu(){
  int option;
  cout << "Choose from the following options:" << endl;
  cout << "1. Display all crypto currencies & respective price data." << endl;
  cout << "2. Display a single crypto currency." << endl;
  cout << "3. Display stats for a single crypto currency." << endl;
  cout << "4. Display stats for a single day of the week." << endl;
  cout << "5. Show crypto currency data that is above a price." << endl;
  cout << "6. Sort by alphebetical order of crypto names." << endl;
  cout << "7. Sort by price lowest to highest." << endl;
  cout << "8. Exit the program." << endl << endl;
  do{
    cin >> option;
    if(option == 1){
      cout << "\nYou have chosen to display all crypto currency price data." << endl << endl;
      return 1;
    }
    if(option == 2){
      cout << "\nYou have chosen to display a single crypto currency." << endl << endl;
      return 2;
    }
    if(option == 3){
      cout << "\nYou have chosen to display stats of a single crypto currency." << endl << endl;
      return 3;
    }
    if(option == 4){
      cout << "\nYou have chosen to display stats for a single day of the week." << endl << endl;
      return 4;
    }
    if(option == 5){
      cout << "\nYou have chosen to filter data above a certain price." << endl << endl;
      return 5;
    }
    if(option == 6){
      cout << "\nYou have chosen to sort by alphebetical order of crypto names." << endl << endl;
      return 6;
    }
    if(option == 7){
      cout << "\nYou have chosen to sort by lowest to highest crypto price." << endl << endl;
      return 7;
    }
    if(option == 8){
      cout << "\nYou have chosen to exit the program." << endl << endl;
      return 8;
    }
  cout << "\n" << option << " is not a valid option." << endl << endl;
  }while(option < 1 || option > 8);
};

void bSortName(crypto ar[]){
  crypto temp;
  bool flag = false;
  do{
    flag = false;
    for(int i = 0; i < ARR_SIZE - 1; i++){
	    if(ar[i].name > ar[i+1].name){
        temp = ar[i];
	      ar[i] = ar[i+1];
	      ar[i+1] = temp;
	      flag = true;
	    }  
    }
  }while(flag == true);
}

double lowestPrice(crypto c){
  double lowest = 99999;
  for(int b = 0; b<7; b++){
    if(c.price[b] < lowest){
      lowest = c.price[b];
      }
  }
  return lowest;
}

void bSortPrice(crypto ar[])
{
  crypto temp;
  bool flag = false;
  do
  {
    flag = false;
    for(int i = 0; i < ARR_SIZE - 1; i++)
	  {
	    if(lowestPrice(ar[i]) > lowestPrice(ar[i+1]))
	    {
        temp = ar[i];
	      ar[i] = ar[i+1];
	      ar[i+1] = temp;
	      flag = true;
	    }  
    }
  }while(flag == true);
}

void display_SortPrice(crypto c[]){
  header();
  bSortPrice(c);
  for(int i = 0; i < 10; i++){
    cout << left << setw(10) <<  c[i].name;
    for(int j = 0; j < 7; j ++){
      cout << right << setw(10) << c[i].price[j];
    }
    cout << endl;
  }
}

void display_alphebetical(crypto c[]){
  header();
  bSortName(c);
  for(int i = 0; i < 10; i++){
    cout << left << setw(10) <<  c[i].name;
    for(int j = 0; j < 7; j ++){
      cout << right << setw(10) << c[i].price[j];
    }
    cout << endl;
  }
}



void header(){
  cout << "COIN NAME";
  cout << setw(10) << "1/1";
  cout << setw(10) << "1/2";
  cout << setw(10) << "1/3";
  cout << setw(10) << "1/4";
  cout << setw(10) << "1/5";
  cout << setw(10) << "1/6";
  cout << setw(10) << "1/7" << endl;
  cout << "================================================================================" << endl;
}

void collect(ifstream& fin, crypto c[], string& credit, string& startDate){
  getline(fin, credit);
  getline(fin, startDate);
  int row = 0;
  do{
  getline(fin, c[row].name);
  for(int i = 0; i < 7; i++)  {
    fin >> c[row].price[i];
    fin.ignore(); //discard comma
  }
  row++;
  }while(!fin.eof());
}

void coin_change(crypto c[], string coin){
  int target = -1;
  double priceTotal = 0;
  double avgPrice;
  string change;
  double highestPrice = 0;
  double lowestPrice = 999999;
  int highestPos = -1;
  int lowestPos = -1;
  for(int i=0; i<10; i++){
    if(c[i].name == coin){
      target = i;
    }
  }
  for(int i=0; i <7; i++){
    priceTotal += c[target].price[i];
    avgPrice = priceTotal / 7;
    if(c[target].price[i] > highestPrice){
      highestPrice = c[target].price[i];
      highestPos = i+1;
    }
    if(c[target].price[i] < lowestPrice){
      lowestPrice = c[target].price[i];
      lowestPos = i+1;
    }
  }
  if((((c[target].price[6] / c[target].price[0]) -1) * 100) > 0){
    change = "increase";
  } else{
    change = "decrease";
  }
  cout << "The average price of " << c[target].name << " is $" << fixed << setprecision(4) << avgPrice <<  " as of 1/7/23." << endl << endl;
  cout << fixed << setprecision(4) << "The lowest price of the week for " << c[target].name << " was $" << lowestPrice << " on 1/" << lowestPos << "/2023." << endl << endl;
  cout << fixed << setprecision(4) << "The highest price of the week for " << c[target].name << " was $" << highestPrice << " on 1/" << highestPos << "/2023." << endl << endl;
  cout << fixed << setprecision(2) << c[target].name << " has had a " << abs(((c[target].price[6] / c[target].price[0]) -1) * 100) << "% " << change << " since the beginning of the week." << endl << endl;
}

void day_change(crypto c[], int day){
  double dayTotal = 0;
  double dayAvg = 0;
  double highestPrice = 0;
  double lowestPrice = 999999;
  string highestName;
  string lowestName;
  int target = day - 1;
  for(int i = 0; i < 10; i++){
    dayTotal += c[i].price[target];
    dayAvg = dayTotal / 10;
    if(c[i].price[target] > highestPrice){
      highestPrice = c[i].price[target];
      highestName = c[i].name;
    }
    if(c[i].price[target] < lowestPrice){
      lowestPrice = c[i].price[target];
      lowestName = c[i].name;
    }
  }
  cout << "The average price of all crypto currency was $" << fixed << setprecision(2) << dayAvg <<  " on 1/" << day << "/2023." << endl << endl;
  cout << fixed << setprecision(4) << "The lowest price on 1/" << day << "/2023 was " << lowestName << " with the price of $" << lowestPrice << endl << endl;
  cout << fixed << setprecision(2) << "The highest price on 1/" << day << "/2023 was " << highestName << " with the price of $" << highestPrice << endl << endl;
  cout << fixed << setprecision(2) << "The difference between the lowest price and the highest price is $" << highestPrice - lowestPrice << endl << endl;
}

void price_above(crypto c[], double price){
  header();
  double lowest;
  int counter = 0;
  for(int i = 0; i<10; i++){
    lowest = 99999;
    for(int b = 0; b<7; b++){
      if(c[i].price[b] < lowest){
        lowest = c[i].price[b];
      }
    }
    if(lowest > price){
      cout << left << setw(10) << c[i].name;
      counter++;
      for(int j = 0; j<7; j++){
        cout << right << setw(10) << c[i].price[j];
      }
      cout << endl;
    }
  }
  cout << endl << "There are " << counter << " crypto currencies that are above $" << fixed << setprecision(2) << price << endl << endl;
}

void display(crypto c[], string coin){
  int target = -1;
  header();
  for(int i=0; i<10; i++){
    if(c[i].name == coin){
      target = i;
    }
  }
  cout << left << setw(10) << c[target].name;
  for (int j = 0; j < 7; j++){
    cout << right << setw(10) << c[target].price[j];
  }
  cout << endl;
}


void display_all(crypto c[]){
  header();
  for (int i=0; i<10; i++){
    cout << left << setw(10) <<  c[i].name;
    //setw(13 - c[i].name.length());
    for (int j = 0; j < 7; j++){
    cout << right << setw(10) << c[i].price[j];
    }
  cout << endl;
  }
  cout << endl;
}
  