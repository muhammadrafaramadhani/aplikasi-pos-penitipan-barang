#include "Barang.h"
#include <iostream>
#include <iomanip>
using namespace std;

Barang::Barang() {
    namaPengirim = "";
    waktuTitip = "";
    namaPenitip = "";
    niuPenitip = "";
    namaBarang = "";
    statusDiambil = false;
    waktuAmbil = "-";
    idBarang = 0;
}

Barang::Barang(string pengirim, string wktTitip, string penitip, 
               string niu, string barang, int id) {
    namaPengirim = pengirim;
    waktuTitip = wktTitip;
    namaPenitip = penitip;
    niuPenitip = niu;
    namaBarang = barang;
    statusDiambil = false;
    waktuAmbil = "-";
    idBarang = id;
}

void Barang::setNamaPengirim(string pengirim) {
    namaPengirim = pengirim;
}

void Barang::setWaktuTitip(string waktu) {
    waktuTitip = waktu;
}

void Barang::setNamaPenitip(string penitip) {
    namaPenitip = penitip;
}

void Barang::setNiuPenitip(string niu) {
    niuPenitip = niu;
}

void Barang::setNamaBarang(string barang) {
    namaBarang = barang;
}

void Barang::setStatusDiambil(bool status) {
    statusDiambil = status;
}

void Barang::setWaktuAmbil(string waktu) {
    waktuAmbil = waktu;
}

void Barang::setIdBarang(int id) {
    idBarang = id;
}

string Barang::getNamaPengirim() const {
    return namaPengirim;
}

string Barang::getWaktuTitip() const {
    return waktuTitip;
}

string Barang::getNamaPenitip() const {
    return namaPenitip;
}

string Barang::getNiuPenitip() const {
    return niuPenitip;
}

string Barang::getNamaBarang() const {
    return namaBarang;
}

bool Barang::getStatusDiambil() const {
    return statusDiambil;
}

string Barang::getWaktuAmbil() const {
    return waktuAmbil;
}

int Barang::getIdBarang() const {
    return idBarang;
}

void Barang::tampilkanInfo() const {
    cout << left << setw(5) << idBarang 
         << setw(20) << namaBarang 
         << setw(20) << namaPenitip 
         << setw(15) << niuPenitip 
         << setw(20) << waktuTitip << endl;
}

void Barang::tampilkanInfoLengkap() const {
    cout << "\n========================================" << endl;
    cout << "ID Barang       : " << idBarang << endl;
    cout << "Nama Barang     : " << namaBarang << endl;
    cout << "Pengirim        : " << namaPengirim << endl;
    cout << "Waktu Titip     : " << waktuTitip << endl;
    cout << "Untuk (Penitip) : " << namaPenitip << endl;
    cout << "NIU/ID Penitip  : " << niuPenitip << endl;
    cout << "Status          : " << (statusDiambil ? "Sudah Diambil" : "Belum Diambil") << endl;
    if (statusDiambil) {
        cout << "Waktu Diambil   : " << waktuAmbil << endl;
    }
    cout << "========================================\n" << endl;
}