#include "PosManager.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <sstream>
using namespace std;

PosManager::PosManager() {
    nextId = 1;
    namaFileDatabase = "database.txt";
}

string PosManager::getCurrentTime() {
    time_t now = time(0);
    char buffer[80];
    struct tm *timeinfo = localtime(&now);
    strftime(buffer, 80, "%d-%m-%Y %H:%M", timeinfo);
    return string(buffer);
}

bool PosManager::validasiNIU(string niu) {
    if (niu.length() != 6) return false;
    for (char c : niu) {
        if (!isdigit(c)) return false;
    }
    return true;
}

void PosManager::tambahBarang() {
    string pengirim, penitip, niu, namaBarang;
    
    cout << "\n=== REGISTRASI BARANG BARU ===" << endl;
    cout << "Nama Pengirim: ";
    cin.ignore();
    getline(cin, pengirim);
    
    cout << "Nama Barang: ";
    getline(cin, namaBarang);
    
    cout << "Untuk (Nama Penitip/Penerima): ";
    getline(cin, penitip);
    
    cout << "NIU/ID Penitip (6 digit): ";
    getline(cin, niu);
    
    if (!validasiNIU(niu)) {
        cout << "\n[ERROR] NIU/ID harus 6 digit angka!" << endl;
        return;
    }
    
    string waktu = getCurrentTime();
    
    Barang barangBaru(pengirim, waktu, penitip, niu, namaBarang, nextId);
    daftarBarang.push_back(barangBaru);
    nextId++;
    
    simpanDatabase();
    
    cout << "\n[SUKSES] Barang berhasil didaftarkan dengan ID: " << (nextId-1) << endl;
    cout << "Waktu penitipan: " << waktu << endl;
    cout << "[INFO] Data otomatis tersimpan ke database." << endl;
}

void PosManager::prosesAmbilBarang() {
    if (hitungBarangAktif() == 0) {
        cout << "\n[INFO] Tidak ada barang yang tersedia untuk diambil." << endl;
        return;
    }
    
    string nama, niu;
    int idBarang;
    
    cout << "\n=== PROSES PENGAMBILAN BARANG ===" << endl;
    cout << "ID Barang: ";
    cin >> idBarang;
    
    cout << "Nama Penitip: ";
    cin.ignore();
    getline(cin, nama);
    
    cout << "NIU/ID (6 digit): ";
    getline(cin, niu);
    
    if (!validasiNIU(niu)) {
        cout << "\n[ERROR] NIU/ID harus 6 digit angka!" << endl;
        return;
    }
    
    bool ditemukan = false;
    for (size_t i = 0; i < daftarBarang.size(); i++) {
        if (daftarBarang[i].getIdBarang() == idBarang && 
            !daftarBarang[i].getStatusDiambil()) {
            
            if (daftarBarang[i].getNamaPenitip() == nama && 
                daftarBarang[i].getNiuPenitip() == niu) {
                
                daftarBarang[i].setStatusDiambil(true);
                daftarBarang[i].setWaktuAmbil(getCurrentTime());
                
                simpanDatabase();
                
                cout << "\n[SUKSES] Barang berhasil diambil!" << endl;
                daftarBarang[i].tampilkanInfoLengkap();
                cout << "[INFO] Data otomatis tersimpan ke database." << endl;
                ditemukan = true;
                break;
            } else {
                cout << "\n[ERROR] Nama atau NIU tidak sesuai!" << endl;
                ditemukan = true;
                break;
            }
        }
    }
    
    if (!ditemukan) {
        cout << "\n[ERROR] Barang dengan ID tersebut tidak ditemukan atau sudah diambil." << endl;
    }
}

void PosManager::tampilkanBarangBelumDiambil() {
    cout << "\n=== DAFTAR BARANG BELUM DIAMBIL ===" << endl;
    cout << left << setw(5) << "ID" 
         << setw(20) << "Nama Barang" 
         << setw(20) << "Untuk" 
         << setw(15) << "NIU/ID" 
         << setw(20) << "Waktu Titip" << endl;
    cout << string(80, '-') << endl;
    
    int count = 0;
    for (const auto& barang : daftarBarang) {
        if (!barang.getStatusDiambil()) {
            barang.tampilkanInfo();
            count++;
        }
    }
    
    if (count == 0) {
        cout << "Tidak ada barang yang tersimpan." << endl;
    }
    cout << "\nTotal barang belum diambil: " << count << endl;
}

void PosManager::tampilkanHistoryBarang() {
    cout << "\n=== HISTORY BARANG YANG SUDAH DIAMBIL ===" << endl;
    cout << left << setw(5) << "ID" 
         << setw(20) << "Nama Barang" 
         << setw(20) << "Penitip" 
         << setw(20) << "Waktu Titip"
         << setw(20) << "Waktu Ambil" << endl;
    cout << string(85, '-') << endl;
    
    int count = 0;
    for (const auto& barang : daftarBarang) {
        if (barang.getStatusDiambil()) {
            cout << left << setw(5) << barang.getIdBarang()
                 << setw(20) << barang.getNamaBarang()
                 << setw(20) << barang.getNamaPenitip()
                 << setw(20) << barang.getWaktuTitip()
                 << setw(20) << barang.getWaktuAmbil() << endl;
            count++;
        }
    }
    
    if (count == 0) {
        cout << "Belum ada barang yang diambil." << endl;
    }
    cout << "\nTotal barang sudah diambil: " << count << endl;
}

void PosManager::cariBarangByPenitip() {
    string nama;
    cout << "\n=== CARI BARANG ===" << endl;
    cout << "Masukkan nama penitip: ";
    cin.ignore();
    getline(cin, nama);
    
    cout << "\nHasil pencarian untuk: " << nama << endl;
    cout << string(80, '-') << endl;
    
    int count = 0;
    for (const auto& barang : daftarBarang) {
        if (barang.getNamaPenitip().find(nama) != string::npos) {
            barang.tampilkanInfoLengkap();
            count++;
        }
    }
    
    if (count == 0) {
        cout << "Tidak ada barang untuk nama tersebut." << endl;
    }
}

void PosManager::loadDatabase() {
    ifstream file(namaFileDatabase);
    if (!file.is_open()) {
        cout << "[INFO] File database.txt tidak ditemukan." << endl;
        cout << "[INFO] Memulai dengan database kosong." << endl;
        cout << "[INFO] Database akan dibuat otomatis saat ada data baru." << endl;
        return;
    }
    
    daftarBarang.clear();
    string line;
    
    while (getline(file, line)) {
        stringstream ss(line);
        string pengirim, waktuTitip, penitip, niu, namaBarang, waktuAmbil;
        int id, status;
        
        getline(ss, pengirim, '|');
        getline(ss, waktuTitip, '|');
        getline(ss, penitip, '|');
        getline(ss, niu, '|');
        getline(ss, namaBarang, '|');
        ss >> id;
        ss.ignore();
        ss >> status;
        ss.ignore();
        getline(ss, waktuAmbil, '|');
        
        Barang b(pengirim, waktuTitip, penitip, niu, namaBarang, id);
        b.setStatusDiambil(status == 1);
        if (status == 1) {
            b.setWaktuAmbil(waktuAmbil);
        }
        
        daftarBarang.push_back(b);
        if (id >= nextId) nextId = id + 1;
    }
    
    file.close();
    cout << "\n========================================" << endl;
    cout << "[SUKSES] Database berhasil dimuat!" << endl;
    cout << "Total barang dalam database: " << daftarBarang.size() << endl;
    cout << "Barang aktif (belum diambil): " << hitungBarangAktif() << endl;
    cout << "========================================\n" << endl;
}

void PosManager::simpanDatabase() {
    ofstream file(namaFileDatabase);
    if (!file.is_open()) {
        cout << "[ERROR] Tidak dapat menyimpan ke database!" << endl;
        return;
    }
    
    for (const auto& barang : daftarBarang) {
        file << barang.getNamaPengirim() << "|"
             << barang.getWaktuTitip() << "|"
             << barang.getNamaPenitip() << "|"
             << barang.getNiuPenitip() << "|"
             << barang.getNamaBarang() << "|"
             << barang.getIdBarang() << "|"
             << (barang.getStatusDiambil() ? 1 : 0) << "|"
             << barang.getWaktuAmbil() << "|" << endl;
    }
    
    file.close();
}

int PosManager::hitungBarangAktif() {
    int count = 0;
    for (const auto& barang : daftarBarang) {
        if (!barang.getStatusDiambil()) count++;
    }
    return count;
}

int PosManager::hitungTotalBarang() {
    return daftarBarang.size();
}

void PosManager::tampilkanMenu() {
    cout << "\n========================================" << endl;
    cout << "   APLIKASI POS PENITIPAN BARANG" << endl;
    cout << "   Fakultas Teknik - UGM" << endl;
    cout << "========================================" << endl;
    cout << "1. Daftar Barang Baru" << endl;
    cout << "2. Proses Pengambilan Barang" << endl;
    cout << "3. Lihat Barang Belum Diambil" << endl;
    cout << "4. Lihat History Barang Diambil" << endl;
    cout << "5. Cari Barang" << endl;
    cout << "6. Keluar" << endl;
    cout << "========================================" << endl;
    cout << "Barang Aktif: " << hitungBarangAktif() 
         << " | Total: " << hitungTotalBarang() << endl;
    cout << "Database: " << namaFileDatabase << endl;
    cout << "Pilih menu (1-6): ";
}