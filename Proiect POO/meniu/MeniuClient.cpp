#include "./MeniuClient.h"

#include <iostream>

#include "../date/DataBase.h"

using namespace std;

void MeniuClient::afiseaza() {
  cout << '\n' << "------- Meniu Client -------" << '\n';
  cout << "0) afiseaza meniul" << '\n';
  cout << "1) listeaza produsele" << '\n';
  cout << "2) adauga produs la comanda" << '\n';
  cout << "3) sterge produs din comanda" << '\n';
  cout << "4) vizualizeaza comanda" << '\n';
  cout << "5) trimite comanda" << '\n';
  cout << "6) exit" << '\n';
}

void MeniuClient::executa(int optiune) {
  switch (optiune) {
  case 0:
    this->afiseaza();
    break;
  case 1:
    this->listeazaProduse();
    break;
  case 2:
    this->adaugaLaComanda();
    break;
  case 3:
    this->stergeDinComanda();
    break;
  case 4:
    this->vizualizeazaComanda();
    break;
  case 5:
    this->trimiteComanda();
    break;
  case 6:
    cout << "> Exit..." << '\n';
    exit(0);
    break;
  default:
    cout << "> Optiune invalida!" << '\n';
  }
}

void MeniuClient::adaugaLaComanda() {
  cout << "> Introduceti ID-ul produsului pe care doriti sa il adaugati la comanda: ";

  int id;
  cin >> id;
  try {
    DataBase& db = DataBase::GetInstance();
    const Produs& produs = db.getProdus(id);

    int cantitate = 0;
    bool cantitateOK = false;
    do {
      cout << "> Introduceti cantitatea: ";
      cin >> cantitate;
      if (cantitate <= 0) {
        cout << "> Cantitate invalida!" << '\n';
        continue;
      }

      if (cantitate > produs.getStoc()) {
        cout << "> In stoc avem doar" << produs.getStoc() << " BUC." << '\n';
        continue;
      }

      try {
        ProdusComandat pc(produs, cantitate);
        comanda += pc;
        cantitateOK = true;
      } catch (const char* err) {
        cout << "> Nu sunt suficiente produse pe stoc!" << '\n';
        continue;
      }
    } while (!cantitateOK);

    cout << "> Produsul a fost adaugat la comanda!" << '\n';
  } catch (const char* err) {
    cout << "> Nu exista produse cu ID " << id << '\n';
    return;
  }

}

void MeniuClient::stergeDinComanda() {
  cout << "> Introduceti ID-ul produsului pe care doriti sa il stergeti din comanda: ";

  int id;
  cin >> id;
  try {
    this->comanda -= id;
    cout << "> Produsul a fost sters din comanda!" << '\n';
  } catch (const char* err) {
    cout << "> Comanda nu contine produsul cu ID " << id << '\n';
  }
}

void MeniuClient::vizualizeazaComanda() {
  if (this->comanda.getProduse().size() == 0)
    cout << "> Nu aveti produse in comanda." << '\n';
  else
    cout << '\n' << "> Comanda: " << '\n' << this->comanda << '\n';
}

void MeniuClient::trimiteComanda() {
  cout << "> Pentru a finaliza comanda intreoduceti datele de livrare: " << '\n';
  cin.get();
  this->comanda.preiaDateClient();

  DataBase& db = DataBase::GetInstance();
  db.adaugaComanda(this->comanda);
  this->comanda = Comanda();

  cout << "> Comanda a fost trimisa!" << '\n';
}
