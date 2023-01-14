#include "./Comanda.h"

#include <string>
#include <fstream>
#include <filesystem>
using namespace std;

#include "./DataBase.h"

int genereazaIdComanda() {
  string fisier = "db/comenzi/id.txt";
  int id;

  ifstream in(fisier);
  if (!in.is_open()) id = 0;
  else {
    in >> id;
    in.close();
  }

  id++;

  ofstream out(fisier);
  out << id;
  out.close();

  return id;
}

const ProdusComandat& Comanda::operator[](int index) const {
  if (index < 0 || index >= this->produse.size()) throw "Index in afara limitelor";

  return this->produse[index];
}

int Comanda::getNumarProduse() const {
  return this->produse.size();
}

void Comanda::citesteDinBinar() {
  string locatie = "./db/comenzi/" + to_string(this->id) + ".bin";
  fstream in;
  in.open(locatie, ios::in | ios::binary);

  this->client.citesteDinFisierBinar(in);

  int numarProduse = 0;
  in.read((char*) &numarProduse, sizeof(int));
  this->produse.resize(numarProduse);

  for (int i = 0; i < numarProduse; i++)
    this->produse[i].citesteDinBinar(in);

  in.close();
}

void Comanda::scrieInBinar() const {
  string locatie = "./db/comenzi/" + to_string(this->id) + ".bin";
  fstream out;
  out.open(locatie, ios::out | ios::binary);

  this->client.scrieInFisierBinar(out);

  int numarProduse = this->produse.size();
  out.write((const char*) &numarProduse, sizeof(int));

  for (int i = 0; i < numarProduse;i++)
    this->produse[i].scrieInBinar(out);

  out.close();
}

void Comanda::stergeFisierul() const {
  string locatie = "./db/comenzi/" + to_string(this->id) + ".bin";
  try {
    filesystem::remove(locatie);
  } catch (const filesystem::filesystem_error& err) {
  }
}

const vector<ProdusComandat>& Comanda::getProduse() const {
  return this->produse;
}

int Comanda::getID() const {
  return this->id;
}

void Comanda::setID(int idNou) {
  this->id = idNou;
}

void Comanda::preiaDateClient() {
  cin >> this->client;
}

Comanda::Comanda(): id(genereazaIdComanda()) {}

Comanda& Comanda::operator+=(const ProdusComandat& produsComandat) {
  for (int i = 0; i < this->produse.size(); i++) {
    if (this->produse[i].getID() == produsComandat.getID()) {
      int cantitateNoua = this->produse[i].getCantitate() + produsComandat.getCantitate();
      if (cantitateNoua > this->produse[i].getStoc())
        throw "Nu sunt suficiente produse in stoc";
      this->produse[i].setCantitate(cantitateNoua);
      return *this;
    }
  }

  this->produse.push_back(produsComandat);

  return *this;
}

Comanda& Comanda::operator-=(int id) {
  int index = -1;

  for (int i = 0; i < this->produse.size(); i++)
    if (this->produse[i].getID() == id) {
      index = i;
      break;
    }

  if (index != -1)
    this->produse.erase(produse.begin() + index);
  else throw "Nu exista produsul";

  return *this;
}

bool Comanda::operator==(const Comanda& comanda) {
  return this->id == comanda.id;
}

ostream& operator<<(ostream& out, const Comanda& comanda) {
  out << '\n' << "ID Comanda: " << comanda.id << '\n';
  out << "Client: " << '\n' << comanda.client << '\n';
  out << "Produsele comenzii " << '\n';
  for (int i = 0; i < comanda.produse.size(); i++)
    out << comanda.produse[i] << '\n';
  out << '\n';
  return out;
}

ofstream& operator<<(ofstream& out, const Comanda& comanda) {
  out << '\n' << "ID Comanda: " << comanda.id << '\n';
  out << "Client: " << '\n' << comanda.client << '\n';
  out << "Produsele comenzii " << '\n';
  for (int i = 0; i < comanda.produse.size(); i++)
    out << comanda.produse[i] << '\n';
  out << '\n';
  return out;
}

void testComanda() {
  Produs produs1("qqqqqq", "dwqdwew", 1, 2);
  Produs produs2("aaaaaa", "rgtrtrgtr", 3, 4);
  Produs produs3("bbbbbb", "gtrhty", 5, 6);

  DataBase& db = DataBase::GetInstance();
  db.adaugaProdus(produs1);
  db.adaugaProdus(produs2);
  db.adaugaProdus(produs3);

  ProdusComandat pc1(produs1, 1);
  ProdusComandat pc2(produs2, 1);
  ProdusComandat pc3(produs3, 1);

  Comanda comanda;

  // comanda.preiaDateClient();
  comanda += pc1;
  comanda += pc1;
  comanda += pc1;
  comanda += pc2;

  cout << comanda << '\n';

  comanda.scrieInBinar();
  Comanda comanda2;
  comanda2.setID(comanda.getID());

  comanda2.citesteDinBinar();

  cout << '\n' << '\n' << '\n' << comanda2 << '\n';
}
