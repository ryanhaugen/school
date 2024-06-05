#include <strings.h>
#include <iostream>
using namespace std;

struct crypto  {
  string name;
  double price[7];
  double rateChange;
  double percentage;
};

int menu();

double lowestPrice(crypto c);

void bSortName(crypto ar[]);

void bSortPrice(crypto ar[]);

void display_SortPrice(crypto c[]);

void display_alphebetical(crypto c[]);

void header();

void collect(ifstream& fin, crypto c[], string& credit, string& startDate);

void display_all(crypto c[]);

void display(crypto c[], string coin);

void coin_change(crypto c[], string coin);

void day_change(crypto c[], int day);

void price_above(crypto c[], double price);