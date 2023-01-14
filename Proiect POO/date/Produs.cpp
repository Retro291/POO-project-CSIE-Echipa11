#include "./Produs.h"

#include <iostream>
#include "cstring"
#include <vector>

#include <string>
#include <fstream>
#include <filesystem>
using namespace std;

int genereazaIdProdus() {
    string fisier = "db/produse/id.txt";
    int id;

    ifstream in(fisier);
    if (!in.is_open()) id = 0;
    else {
        in >> id;
        in.close();
    }

    id++;

    ofstream out(fisier);
    out << id;
    out.close();

    return id;
}

Produs::Produs(): id(-1), denumire(nullptr), descriere(""), pret(-1), stoc(-1) {}

Produs::Produs(const char* denumire, string descriere, float pret, int stoc) {
    this->id = genereazaIdProdus();
    setDenumire(denumire);
    setDescriere(descriere);
    setPret(pret);
    setStoc(stoc);
}

Produs::Produs(const Produs& produs):
    id(produs.id), descriere(produs.descriere), pret(produs.pret), stoc(produs.stoc) {

    this->denumire = new char[strlen(produs.denumire) + 1];
    strcpy(this->denumire, produs.denumire);
}

Produs& Produs::operator=(const Produs& produs) {
    if (this == &produs)
        return *this;

    this->id = produs.id;
    setDenumire(produs.denumire);
    this->descriere = produs.descriere;
    this->pret = produs.pret;
    this->stoc = produs.stoc;

    return *this;
}

Produs::~Produs() {
    if (this->denumire != nullptr) {
        delete[] this->denumire;
    }
}

void Produs::citesteDinBinar() {
    string locatie = "./db/produse/" + to_string(this->id) + ".bin";
    fstream in;
    in.open(locatie, ios::in | ios::binary);

    int lungime = 0;

    in.read((char*) &lungime, sizeof(int));
    if (this->denumire != nullptr)delete[] this->denumire;
    this->denumire = new char[lungime];
    in.read(this->denumire, lungime * sizeof(char));

    in.read((char*) &lungime, sizeof(int));
    this->descriere.resize(lungime);
    in.read((char*) this->descriere.c_str(), lungime * sizeof(char));

    in.read((char*) &this->pret, sizeof(float));
    in.read((char*) &this->stoc, sizeof(int));

    in.close();
}

void Produs::scrieInBinar() const {
    string locatie = "./db/produse/" + to_string(this->id) + ".bin";
    fstream out;
    out.open(locatie, ios::out | ios::binary);

    int lungime = 0;

    lungime = strlen(this->denumire) + 1;
    out.write((const char*) &lungime, sizeof(int));
    out.write((const char*) this->denumire, lungime * sizeof(char));

    lungime = this->descriere.length() + 1;
    out.write((const char*) &lungime, sizeof(int));
    out.write((const char*) this->descriere.c_str(), lungime * sizeof(char));

    out.write((const char*) &this->pret, sizeof(float));
    out.write((const char*) &this->stoc, sizeof(int));

    out.close();
}

void Produs::stergeFisierul() const {
    string locatie = "./db/produse/" + to_string(this->id) + ".bin";
    try {
        filesystem::remove(locatie);
    } catch (const filesystem::filesystem_error& err) {
    }
}

int Produs::getID() const {
    return this->id;
}

const char* Produs::getDenumire() const {
    return this->denumire;
}

string Produs::getDescriere() const {
    return this->descriere;
}

float Produs::getPret() const {
    return this->pret;
}

int Produs::getStoc() const {
    return this->stoc;
}

void Produs::setDenumire(const char* denumireNoua) {
    if (denumireNoua == nullptr) throw "Denumirea nu poate avea valoarea nula!";

    if (this->denumire != nullptr)
        delete[] this->denumire;

    int lungime = strlen(denumireNoua) + 1;

    if (lungime < 3) throw "Denumirea nu poate contine mai putin de 3 caractere!";

    this->denumire = new char[lungime];
    strcpy(this->denumire, denumireNoua);
}

void Produs::setDescriere(string descriereNoua) {
    if (descriereNoua.length() < 5) throw "Descrierea nu poate contine mai putin de 5 caractere!";

    this->descriere = descriereNoua;
}

void Produs::setPret(float pretNou) {
    if (pretNou <= 0) throw "Valoare incorecta pentru pret!";

    this->pret = pretNou;
}

void Produs::setStoc(int stocNou) {
    if (stocNou < 0) throw "Valoare incorecta pentru pret!";

    this->stoc = stocNou;
}

void Produs::setID(int idNou) {
    this->id = idNou;
}

bool Produs::operator==(const Produs& altProdus) {
    return this->id == altProdus.id;
}

void Produs::genereazaID() {
    this->id = genereazaIdProdus();
}

istream& operator>>(istream& in, Produs& produs) {
    string denumire;
    bool denumireOK = false;
    do {
        cout << "Denumire: ";
        getline(in, denumire);
        try {
            produs.setDenumire(denumire.c_str());
            denumireOK = true;
        } catch (const char* mesajEroare) {
            cout << mesajEroare << '\n';
        }
    } while (!denumireOK);

    string descriere;
    bool descriereOK = false;
    do {
        cout << "Descriere: ";
        getline(in, descriere);
        try {
            produs.setDescriere(descriere.c_str());
            descriereOK = true;
        } catch (const char* mesajEroare) {
            cout << mesajEroare << '\n';
        }
    } while (!descriereOK);

    float pret;
    bool pretOK = false;
    do {
        cout << "Pret: ";
        in >> pret;
        try {
            produs.setPret(pret);
            pretOK = true;
        } catch (const char* mesajEroare) {
            cout << mesajEroare << '\n';
        }
    } while (!pretOK);

    float stoc;
    bool stocOK = false;
    do {
        cout << "Cantitate: ";
        in >> stoc;
        try {
            produs.setStoc(stoc);
            stocOK = true;
        } catch (const char* mesajEroare) {
            cout << mesajEroare << '\n';
        }
    } while (!stocOK);

    return in;
}

ostream& operator<<(ostream& out, const Produs& produs) {
    out << "ID: " << produs.id << '\n';
    out << "Denumire: " << produs.denumire << '\n';
    out << "Descriere: " << produs.descriere << '\n';
    out << "Pret: " << produs.pret << " RON\n";
    out << "Stoc: " << produs.stoc << " BUC\n";
    return out;
}

void testProdus() {
    Produs produs;

    cout << "Introduceti datele produsului" << '\n';
    cin >> produs;
    cout << '\n' << "Ati introdus produsul " << '\n' << produs << '\n';

    Produs produs2(produs);
    cout << '\n' << produs2 << '\n';

    Produs produs3;
    produs3 = produs;
    cout << '\n' << produs3 << '\n';

    produs.scrieInBinar();
    Produs produs4;
    produs4.setID(produs.getID());
    produs4.citesteDinBinar();
    cout << '\n' << produs4 << '\n';
}
