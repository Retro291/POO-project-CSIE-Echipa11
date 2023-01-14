#include "./DataBase.h"

#include <filesystem>
#include <algorithm>
#include <vector>
using namespace std;

DataBase::DataBase() {}

vector<int> getIDs(string directory) {
  vector<int> ids;
  for (const auto& entry : filesystem::directory_iterator(directory)) {
    if (entry.path().extension() == ".bin") {
      ids.push_back(stoi(entry.path().filename().string()));
    }
  }
  sort(ids.begin(), ids.end());
  return ids;
}

void DataBase::incarcaDatele() {
  vector<int> idProduse = getIDs("db/produse");
  this->produse.clear();
  this->produse.reserve(idProduse.size());
  for (int i = 0; i < idProduse.size();i++) {
    Produs& produs = this->produse.emplace_back();
    produs.setID(idProduse[i]);
    produs.citesteDinBinar();
  }

  vector<int> idComenzi = getIDs("db/comenzi");
  this->comenzi.clear();
  this->comenzi.reserve(idComenzi.size());
  for (int i = 0; i < idComenzi.size();i++) {
    Comanda& comanda = this->comenzi.emplace_back();
    comanda.setID(idComenzi[i]);
    comanda.citesteDinBinar();
  }
}

void DataBase::salveazaDatele() {
  for (int i = 0; i < this->produse.size();i++)
    this->produse[i].scrieInBinar();

  for (int i = 0; i < this->comenzi.size();i++)
    this->comenzi[i].scrieInBinar();
}

const vector<Produs>& DataBase::getProduse() {
  return this->produse;
}

const vector<Comanda>& DataBase::getComenzi() {
  return this->comenzi;
}

void DataBase::adaugaProdus(const Produs& produs) {
  this->produse.push_back(produs);
  produs.scrieInBinar();
}

bool DataBase::modificaProdus(int idProdusVechi, Produs& produsNou) {
  for (int i = 0; i < this->produse.size(); i++)
    if (this->produse[i].getID() == idProdusVechi) {
      this->produse[i] = produsNou;
      produsNou.setID(this->produse[i].getID());
      produsNou.scrieInBinar();
      return true;
    }
  return false;
}

bool DataBase::stergeProdus(int id) {
  for (int i = 0; i < this->produse.size();i++)
    if (this->produse[i].getID() == id) {
      this->produse[i].stergeFisierul();
      this->incarcaDatele();
      return true;
    }
  return false;
}

void DataBase::adaugaComanda(const Comanda& comanda) {
  this->comenzi.push_back(comanda);
  comanda.scrieInBinar();

  for (int i = 0; i < comanda.getNumarProduse(); i++) {
    int idProdusComandat = comanda[i].getID();
    int stocNou = comanda[i].getStoc() - comanda[i].getCantitate();

    Produs& produs = getProdus(idProdusComandat);
    produs.setStoc(stocNou);
    produs.scrieInBinar();
  }
}

void DataBase::modificaComanda(const Comanda& comandaVeche, const Comanda& comandaNoua) {
  for (int i = 0; i < this->comenzi.size(); i++)
    if (this->comenzi[i] == comandaVeche) {
      this->comenzi[i] = comandaNoua;
      comandaNoua.scrieInBinar();
      break;
    }
}

bool DataBase::stergeComanda(int id) {
  for (int i = 0; i < this->comenzi.size();i++)
    if (this->comenzi[i].getID() == id) {
      this->comenzi[i].stergeFisierul();
      this->incarcaDatele();
      return true;
    }
  return false;
}

Produs& DataBase::getProdus(int id) {
  for (int i = 0; i < this->produse.size(); i++)
    if (this->produse[i].getID() == id)
      return this->produse[i];

  throw "Nu exista produsul";
}

DataBase::~DataBase() {}

DataBase DataBase::instance = DataBase();
DataBase& DataBase::GetInstance() {
  return DataBase::instance;
}

void dataBaseTest() {
  Produs prod1("qqqqq", "qwertyui", 1, 2);
  Produs prod2("aaaaa", "dknea", 3, 4);
  Produs prod3("bbbbb", "efoireho8", 5, 6);

  DataBase& db = DataBase::GetInstance();

  db.adaugaProdus(prod1);
  db.adaugaProdus(prod2);
  db.adaugaProdus(prod3);
}
