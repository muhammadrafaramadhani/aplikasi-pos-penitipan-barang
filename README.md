# aplikasi-pos-penitipan-barang
Aplikasi Pos Penitipan Barang - Project Pemrograman Dasar 
# Aplikasi Pos Penitipan Barang

Aplikasi manajemen penitipan barang berbasis console untuk Pos Satpam Fakultas Teknik UGM.

Aplikasi ini dikembangkan sebagai project mata kuliah Pemrograman Dasar  Semester Gasal 2025/2026. Aplikasi ini membantu petugas pos satpam dalam mengelola penitipan barang dengan fitur registrasi, pengambilan, pencarian, dan database terintegrasi.

Fitur Utama
- Registrasi Barang Baru - Daftarkan barang titipan dengan validasi NIU 6 digit
- Proses Pengambilan Barang - Verifikasi ganda (nama + NIU) untuk keamanan
- Lihat Barang Aktif - Monitoring barang yang masih tersimpan
- History Barang - Riwayat barang yang sudah diambil
- Pencarian Barang - Cari berdasarkan nama penitip
- Database Auto-Save - Data tersimpan otomatis setiap perubahan

Teknologi
- Bahasa: C++ (Standard C++17)
- Paradigma: Object-Oriented Programming (OOP)
- Database: Text-based file storage (database.txt)
- Compiler: GNU G++

Cara Compile 
- Jalankan : pos_app.exe
- Compile :
cd pos_app
g++ -std=c++17 -Wall -O2 main.cpp Barang.cpp PosManager.cpp -o pos_app.exe
pos_app.exe

Pengembang
- Muhammad Rafa Ramadhani
- 25/562068/TK/63534

Project ini dibuat untuk keperluan akademik mata kuliah Pemrograman Dasar UGM.
