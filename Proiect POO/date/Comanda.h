#pragma once
#include <vector>
#include <fstream>
using namespace std;

#include "./ProdusComandat.h"
#include "./IFisierBinar.h"
#include "./Client.h"

class Comanda: public IFisierBinar {
private:
  int id;
  Client client;
  vector<ProdusComandat> produse;

public:
  Comanda();

  friend ostream& operator<<(ostream& out, const Comanda& comanda);
  friend ofstream& operator<<(ofstream& out, const Comanda& comanda);

  int getID() const;
  void setID(int idNou);

  const vector<ProdusComandat>& getProduse() const;

  void preiaDateClient();

  const ProdusComandat& operator[](int index) const;
  int getNumarProduse() const;

  void citesteDinBinar();
  void scrieInBinar() const;
  void stergeFisierul() const;

  Comanda& operator+=(const ProdusComandat& produsComandat);
  Comanda& operator-=(int id);
  bool operator==(const Comanda& comanda);
};

void testComanda();
