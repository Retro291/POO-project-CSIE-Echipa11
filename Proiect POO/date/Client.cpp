#include "./Client.h"

#include <iostream>

Client::Client(): cnp(""), nume(""), adresa(""), telefon("") {}

Client::Client(const Client& client) {
  this->cnp = client.cnp;
  this->nume = client.nume;
  this->adresa = client.adresa;
  this->telefon = client.telefon;
}

Client& Client::operator=(const Client& client) {
  if (this == &client)
    return *this;

  this->cnp = client.cnp;
  this->nume = client.nume;
  this->adresa = client.adresa;
  this->telefon = client.telefon;

  return *this;
}

Client::~Client() {}

bool contineDoarCifre(string str) {
  for (int i = 0; i < str.length();i++)
    if (str[i] < '0' || str[i] > '9')
      return false;
  return true;
}

istream& operator>>(istream& in, Client& client) {
  string cnp;
  bool cnpOK = false;
  do {
    cout << "CNP: ";
    getline(in, cnp);

    if (cnp.length() != 13) {
      cout << "Lungime CNP incorecta!" << '\n';
    } else {
      if (!contineDoarCifre(cnp)) {
        cout << "CNP-ul poate contine doar cifre!" << '\n';
      } else cnpOK = true;
    }
  } while (!cnpOK);
  client.cnp = cnp;

  cout << "Nume: ";
  getline(in, client.nume);

  cout << "Adresa: ";
  getline(in, client.adresa);

  string telefon;
  bool telefonOK = false;
  do {
    cout << "Telefon: ";
    getline(in, telefon);

    if (telefon.length() != 10) {
      cout << "Lungime telefon incorecta!" << '\n';
    } else {
      if (!contineDoarCifre(telefon)) {
        cout << "Telefonul poate contine doar cifre!" << '\n';
      } else telefonOK = true;
    }
  } while (!telefonOK);
  client.telefon = telefon;

  return in;
}

ostream& operator<<(ostream& out, const Client& client) {
  out << "CNP client: " << client.cnp << '\n';
  out << "Nume client: " << client.nume << '\n';
  out << "Adresa client: " << client.adresa << '\n';
  out << "Telefon client: " << client.telefon << '\n';

  return out;
}

void Client::scrieInFisierBinar(fstream& bin) const {
  int lungime = 0;

  lungime = this->cnp.length() + 1;
  bin.write((const char*) &lungime, sizeof(int));
  bin.write(this->cnp.c_str(), lungime * sizeof(char));

  lungime = this->nume.length() + 1;
  bin.write((const char*) &lungime, sizeof(int));
  bin.write(this->nume.c_str(), lungime * sizeof(char));

  lungime = this->adresa.length() + 1;
  bin.write((const char*) &lungime, sizeof(int));
  bin.write(this->adresa.c_str(), lungime * sizeof(char));

  lungime = this->telefon.length() + 1;
  bin.write((const char*) &lungime, sizeof(int));
  bin.write(this->telefon.c_str(), lungime * sizeof(char));
}

void Client::citesteDinFisierBinar(fstream& bin) {
  int lungime = 0;

  bin.read((char*) &lungime, sizeof(int));
  this->cnp.resize(lungime);
  bin.read((char*) this->cnp.c_str(), lungime * sizeof(char));

  bin.read((char*) &lungime, sizeof(int));
  this->nume.resize(lungime);
  bin.read((char*) this->nume.c_str(), lungime * sizeof(char));

  bin.read((char*) &lungime, sizeof(int));
  this->adresa.resize(lungime);
  bin.read((char*) this->adresa.c_str(), lungime * sizeof(char));

  bin.read((char*) &lungime, sizeof(int));
  this->telefon.resize(lungime);
  bin.read((char*) this->telefon.c_str(), lungime * sizeof(char));
}

string Client::getCNP() {
  return this->cnp;
}

string Client::getNume() {
  return this->nume;
}

string Client::getAdresa() {
  return this->adresa;
}

string Client::getTelefon() {
  return this->telefon;
}

void testClient() {
  Client client;

  cout << "Introduceti datele clientului: " << '\n';
  cin >> client;
  cout << '\n' << "Ati introdus clientul " << '\n' << client << '\n';


  std::fstream fisierClient;
  fisierClient.open("test-client.bin", ios::out | ios::binary);
  client.scrieInFisierBinar(fisierClient);
  fisierClient.close();
  cout << '\n' << "Clientul a fost scris in fisier binar!" << '\n';

  Client client2;
  fisierClient.open("test-client.bin", ios::in | ios::binary);
  client2.citesteDinFisierBinar(fisierClient);
  fisierClient.close();
  cout << '\n' << "Am citit clientul" << '\n' << client2 << '\n';

  Client client3(client);
  cout << client3 << '\n';

  Client client4;
  client4 = client;
  cout << client4 << '\n';
}
