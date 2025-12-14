#include "PosManager.h"
#include <iostream>
using namespace std;

int main() {
    PosManager pos;
    int pilihan;
    
    pos.loadDatabase();
    
    do {
        pos.tampilkanMenu();
        cin >> pilihan;
        
        switch(pilihan) {
            case 1:
                pos.tambahBarang();
                break;
                
            case 2:
                pos.prosesAmbilBarang();
                break;
                
            case 3:
                pos.tampilkanBarangBelumDiambil();
                break;
                
            case 4:
                pos.tampilkanHistoryBarang();
                break;
                
            case 5:
                pos.cariBarangByPenitip();
                break;
                
            case 6:
                cout << "\n========================================" << endl;
                cout << "[INFO] Terima kasih telah menggunakan aplikasi!" << endl;
                cout << "[INFO] Semua data tersimpan di database.txt" << endl;
                cout << "========================================\n" << endl;
                break;
                
            default:
                cout << "\n[ERROR] Pilihan tidak valid! Silakan pilih 1-6." << endl;
                break;
        }
        
        if (pilihan != 6) {
            cout << "\nTekan Enter untuk melanjutkan...";
            cin.ignore();
            cin.get();
        }
        
    } while(pilihan != 6);
    
    return 0;
}