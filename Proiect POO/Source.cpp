#include <iostream>

#include "string"

#include "./meniu/IMeniu.h"
#include "./meniu/MeniuClient.h"
#include "./meniu/MeniuMagazin.h"

using namespace std;

int main() {
  DataBase::GetInstance().incarcaDatele();

  IMeniu* meniu = nullptr;

  string utilizator;
  string parola;

  cout << "Introduceti utilizatorul: (client/magazin) ";
  getline(cin, utilizator);

  cout << "Introduceti parola: ";
  getline(cin, parola);

  if (utilizator == "client") {
    if (parola != "parolaclient") {
      cout << "Parola incorecta!" << '\n';
      return 1;
    } else meniu = new MeniuClient();
  } else {
    if (parola != "parolamagazin") {
      cout << "Parola incorecta!" << '\n';
      return 1;
    } else meniu = new MeniuMagazin();
  }

  meniu->loop();

  delete meniu;

  DataBase::GetInstance().salveazaDatele();
  return 0;
}
