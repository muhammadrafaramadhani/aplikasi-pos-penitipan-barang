#ifndef POSMANAGER_H
#define POSMANAGER_H

#include "Barang.h"
#include <vector>
#include <string>
using namespace std;

class PosManager {
private:
    vector<Barang> daftarBarang;
    int nextId;  
    
    bool validasiNIU(string niu);
    string getCurrentTime();

public:
    PosManager();
    
    void tambahBarang();                    
    void prosesAmbilBarang();               
    void tampilkanBarangBelumDiambil();     
    void tampilkanHistoryBarang();          
    void cariBarangByPenitip();             
    
    void loadDatabase();                    
    void simpanDatabase();                  
    string namaFileDatabase;                
    
    int hitungBarangAktif();
    int hitungTotalBarang();
    void tampilkanMenu();
};

#endif 