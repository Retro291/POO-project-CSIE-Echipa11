#pragma once

#include <fstream>
using namespace std;


class IFisierBinar {
public:
  virtual void scrieInBinar() const = 0;
  virtual void citesteDinBinar() = 0;
  virtual void stergeFisierul() const = 0;
};
