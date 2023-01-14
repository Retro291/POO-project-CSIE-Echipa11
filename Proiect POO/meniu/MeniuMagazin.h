#pragma once
#include "./IMeniu.h"

class MeniuMagazin: public IMeniu {
private:
  void afiseaza();
  void executa(int optiune);

  void adaugaProdus();
  void stergeProdus();
  void modificaProdus();

  void listeazaComenzi();
  void stergeComanda();
  void raportComenzi();
};
