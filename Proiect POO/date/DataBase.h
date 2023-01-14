#pragma once

#include <vector>
using namespace std;

#include "./Produs.h"
#include "./Comanda.h"

class DataBase {
private:
  vector<Produs> produse;
  vector<Comanda> comenzi;

  DataBase();
  static DataBase instance;
public:
  static DataBase& GetInstance();

  void incarcaDatele();
  void salveazaDatele();


  const vector<Produs>& getProduse();
  Produs& getProdus(int id);
  const vector<Comanda>& getComenzi();

  void adaugaProdus(const Produs& produs);
  bool modificaProdus(int idProdusVechi, Produs& produsNou);
  bool stergeProdus(int id);

  void adaugaComanda(const Comanda& comanda);
  void modificaComanda(const Comanda& comandaVeche, const Comanda& comandaNoua);
  bool stergeComanda(int id);

  ~DataBase();
};

void dataBaseTest();
