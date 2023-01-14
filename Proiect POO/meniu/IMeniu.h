#pragma once

#include "../date/DataBase.h"

class IMeniu {
private:
  virtual void afiseaza() = 0;
  virtual void executa(int optiune) = 0;

protected:
  void listeazaProduse();

public:
  IMeniu();

  void loop();

  virtual ~IMeniu();
};
