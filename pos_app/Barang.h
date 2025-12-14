#ifndef BARANG_H
#define BARANG_H

#include <string>
using namespace std;

class Barang {
private:
    string namaPengirim;
    string waktuTitip;
    string namaPenitip;      
    string niuPenitip;       
    string namaBarang;
    bool statusDiambil;
    string waktuAmbil;
    int idBarang;            

public:
    Barang();
    Barang(string pengirim, string wktTitip, string penitip, 
           string niu, string barang, int id);
    
    void setNamaPengirim(string pengirim);
    void setWaktuTitip(string waktu);
    void setNamaPenitip(string penitip);
    void setNiuPenitip(string niu);
    void setNamaBarang(string barang);
    void setStatusDiambil(bool status);
    void setWaktuAmbil(string waktu);
    void setIdBarang(int id);
    
    string getNamaPengirim() const;
    string getWaktuTitip() const;
    string getNamaPenitip() const;
    string getNiuPenitip() const;
    string getNamaBarang() const;
    bool getStatusDiambil() const;
    string getWaktuAmbil() const;
    int getIdBarang() const;
    
    void tampilkanInfo() const;
    void tampilkanInfoLengkap() const;
};

#endif 