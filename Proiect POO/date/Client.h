#pragma once
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Client {
private:
  string cnp;
  string nume;
  string adresa;
  string telefon;

public:
  Client();
  Client(const Client& client);
  Client& operator=(const Client& client);
  ~Client();

  friend istream& operator>>(istream& in, Client& client);
  friend ostream& operator<<(ostream& out, const Client& client);

  void scrieInFisierBinar(fstream& bin) const;
  void citesteDinFisierBinar(fstream& bin);

  string getCNP();
  string getNume();
  string getAdresa();
  string getTelefon();
};

void testClient();
