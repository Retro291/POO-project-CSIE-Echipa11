#include "./ProdusComandat.h"
#include <iostream>

#include "./DataBase.h"

ProdusComandat::ProdusComandat() {}

ProdusComandat::ProdusComandat(const Produs& produs, int cantitate): Produs(produs) {
  this->setCantitate(cantitate);
}

ProdusComandat::ProdusComandat(const ProdusComandat& produsComandat) {
  Produs::operator=(produsComandat);

  this->cantitate = produsComandat.cantitate;
}

ProdusComandat& ProdusComandat::operator=(const ProdusComandat& produsComandat) {
  if (this == &produsComandat)
    return *this;

  Produs::operator=(produsComandat);

  this->cantitate = produsComandat.cantitate;

  return *this;
}

int ProdusComandat::getCantitate() const {
  return this->cantitate;
}

void ProdusComandat::setCantitate(int cantitateNoua) {
  if (cantitateNoua <= 0) throw "Cantitate invalida!";
  this->cantitate = cantitateNoua;
}

void ProdusComandat::scrieInBinar(fstream& bin) const {
  int id = this->getID();
  bin.write((const char*) &id, sizeof(int));
  bin.write((const char*) &this->cantitate, sizeof(int));
}

void ProdusComandat::citesteDinBinar(fstream& bin) {
  int id = 0;
  bin.read((char*) &id, sizeof(int));

  DataBase& db = DataBase::GetInstance();
  const Produs& produs = db.getProdus(id);
  Produs::operator=(produs);

  bin.read((char*) &this->cantitate, sizeof(int));
}

bool ProdusComandat::operator==(const ProdusComandat& altProdusComandat) {
  return Produs::operator==(altProdusComandat) && this->cantitate == altProdusComandat.cantitate;
}

ostream& operator<<(ostream& out, const ProdusComandat& produsComandat) {
  out << "ID produs: " << produsComandat.getID() << '\n';
  out << "Denumire: " << produsComandat.getDenumire() << '\n';
  out << "Cantitate: " << produsComandat.getCantitate() << '\n';
  out << "Stoc: " << produsComandat.getStoc() << '\n';
  return out;
}

void testProdusComandat() {
  Produs produs("qqqqqq", "wwwwwwwwwwwwww", 1, 2);

  ProdusComandat pc(produs, 1);

  cout << pc << '\n';
}
