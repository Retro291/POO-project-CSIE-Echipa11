#pragma once
#include "./IMeniu.h"
#include "../date/Comanda.h"

class MeniuClient: public IMeniu {
private:
  Comanda comanda;
private:
  void afiseaza();
  void executa(int optiune);

  void adaugaLaComanda();
  void stergeDinComanda();
  void vizualizeazaComanda();
  void trimiteComanda();
};
