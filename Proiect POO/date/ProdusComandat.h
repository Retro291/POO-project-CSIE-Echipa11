#pragma once
#include "./Produs.h"
#include <fstream>
using namespace std;

class ProdusComandat: public Produs {
private:
  int cantitate;

public:
  ProdusComandat();
  ProdusComandat(const Produs& produs, int cantitate);
  ProdusComandat(const ProdusComandat& produsComandat);
  ProdusComandat& operator=(const ProdusComandat& produsComandat);

  int getCantitate() const;
  void setCantitate(int cantitateNoua);

  void scrieInBinar(fstream& bin) const;
  void citesteDinBinar(fstream& bin);

  friend ostream& operator<<(ostream& out, const ProdusComandat& produs);

  bool operator==(const ProdusComandat& altProdusComandat);
};

void testProdusComandat();
