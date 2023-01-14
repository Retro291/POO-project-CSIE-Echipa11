#include "./MeniuMagazin.h"

#include "../date/DataBase.h"

#include <iostream>

using namespace std;

void MeniuMagazin::afiseaza() {
  cout << '\n' << "------- Meniu Magazin -------" << '\n';
  cout << "0) afiseaza meniul" << '\n';
  cout << "1) listeaza produsele" << '\n';
  cout << "2) listeaza comenzile" << '\n';
  cout << "3) adauga produs" << '\n';
  cout << "4) sterge produs" << '\n';
  cout << "5) modifica produs" << '\n';
  cout << "6) sterge comanda" << '\n';
  cout << "7) raport comenzi" << '\n';
  cout << "8) exit" << '\n';
}

void MeniuMagazin::executa(int optiune) {
  switch (optiune) {
  case 0:
    this->afiseaza();
    break;
  case 1:
    this->listeazaProduse();
    break;
  case 2:
    this->listeazaComenzi();
    break;
  case 3:
    this->adaugaProdus();
    break;
  case 4:
    this->stergeProdus();
    break;
  case 5:
    this->modificaProdus();
    break;
  case 6:
    this->stergeComanda();
    break;
  case 7:
    this->raportComenzi();
    break;
  case 8:
    cout << "> Exit..." << '\n';
    exit(0);
    break;
  default:
    cout << "> Optiune invalida!" << '\n';
    break;
  }
}

void MeniuMagazin::listeazaComenzi() {
  DataBase& db = DataBase::GetInstance();

  if (db.getComenzi().size() == 0)
    cout << "> Nu exista comenzi!" << '\n';
  else
    for (int i = 0; i < db.getComenzi().size(); i++)
      cout << '\n' << "-----------------------" << '\n' << db.getComenzi()[i] << '\n';
}

void MeniuMagazin::adaugaProdus() {
  cin.get();

  Produs produs;
  produs.genereazaID();
  cout << "> Introduceti datele produsului: " << '\n';
  cin >> produs;

  DataBase& db = DataBase::GetInstance();
  db.adaugaProdus(produs);
  cout << "> Produsul a fost adaugat!" << '\n';
}

void MeniuMagazin::stergeProdus() {
  cout << "> Introduceti ID-ul produsului pe care doriti sa il stergeti: ";
  int id;
  cin >> id;

  DataBase& db = DataBase::GetInstance();
  if (db.stergeProdus(id))
    cout << "> Produsul a fost sters!" << '\n';
  else
    cout << "> Nu exista produse cu ID " << id << "." << '\n';
}

void MeniuMagazin::modificaProdus() {
  cout << "> Introduceti ID-ul produsului pe care doriti sa il modificati: ";
  int id;
  cin >> id;

  DataBase& db = DataBase::GetInstance();
  try {
    Produs produs = db.getProdus(id);

    cout << "> Datele vechi ale produsului: " << produs << '\n';
    cout << "> Introduceti noile date ale produsului: ";
    cin.get();
    cin >> produs;

    if (db.modificaProdus(id, produs))
      cout << "> Produsul a fost modificat!" << '\n';
    else
      cout << "> Nu exista produs cu ID " << id << "." << '\n';
  } catch (const char* err) {
    cout << "> Nu exista produse cu ID " << id << "." << '\n';
  }
}

void MeniuMagazin::stergeComanda() {
  cout << "> Introduceti ID-ul comenzii pe care doriti sa o stergeti: ";
  int id;
  cin >> id;

  DataBase& db = DataBase::GetInstance();
  if (db.stergeComanda(id))
    cout << "> Comanda a fost stearsa!" << '\n';
  else
    cout << "> Nu exista comanda cu ID " << id << "." << '\n';
}

void MeniuMagazin::raportComenzi() {
  ofstream raport("raport.txt");

  DataBase& db = DataBase::GetInstance();
  for (int i = 0; i < db.getComenzi().size(); i++)
    raport << db.getComenzi()[i] << '\n';

  cout << "> Raportul a fost realizat! (raport.txt)" << '\n';
}
