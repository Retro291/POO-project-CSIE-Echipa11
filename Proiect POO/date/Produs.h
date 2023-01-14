#pragma once

#include "string"
using namespace std;

#include "./IFisierBinar.h"

class Produs: public IFisierBinar {
private:
  int id;
  char* denumire;
  string descriere;
  float pret;
  int stoc;

public:
  Produs();
  Produs(const Produs& produs);
  Produs(const char* denumire, string descriere, float pret, int stoc);
  ~Produs();
  Produs& operator=(const Produs& produs);

  friend istream& operator>>(istream& in, Produs& produs);
  friend ostream& operator<<(ostream& out, const Produs& produs);

  void citesteDinBinar();
  void scrieInBinar() const;
  void stergeFisierul() const;

  void genereazaID();

  int getID() const;
  const char* getDenumire() const;
  string getDescriere() const;
  float getPret() const;
  int getStoc() const;

  void setDenumire(const char* denumireNoua);
  void setDescriere(string descriereNoua);
  void setPret(float pretNou);
  void setStoc(int stocNou);
  void setID(int idNou);

  bool operator==(const Produs& altProdus);
};

void testProdus();
