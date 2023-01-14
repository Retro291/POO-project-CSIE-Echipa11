#include "IMeniu.h"

#include "../date/DataBase.h"
#include <iostream>
using namespace std;

IMeniu::IMeniu() {}

void IMeniu::loop() {
  this->afiseaza();
  while (true) {
    cout << "> Introduceti optiunea: ";
    int optiune;
    cin >> optiune;
    this->executa(optiune);
  }
}

void IMeniu::listeazaProduse() {
  DataBase& db = DataBase::GetInstance();

  if (db.getProduse().size() == 0)
    cout << "> Nu exista produse!" << '\n';
  else
    for (int i = 0; i < db.getProduse().size(); i++)
      cout << "-----------------------" << '\n' << db.getProduse()[i] << '\n';
}

IMeniu::~IMeniu() {}
