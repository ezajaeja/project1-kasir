#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

// 7. STRUCT: Mendefinisikan struktur data untuk menu makanan
struct MenuMakan {
    string nama;
    int harga;
};

// Variabel Global
const int MAX_MENU = 5;
const int MAX_PESANAN = 100;

// 6. ARRAY: Array of Struct untuk daftar menu dan keranjang belanja
MenuMakan daftarMenu[MAX_MENU];
MenuMakan keranjang[MAX_PESANAN];
int jumlahPesanan = 0;

// 5. FUNCTION & PROCEDURE (Void function untuk inisialisasi data)
void inisialisasiMenu() {
    daftarMenu[0] = {"Nasi Goreng", 15000};
    daftarMenu[1] = {"Ayam Bakar ", 20000};
    daftarMenu[2] = {"Mie Goreng ", 12000};
    daftarMenu[3] = {"Es Teh Manis", 5000};
    daftarMenu[4] = {"Jeruk Hangat", 6000};
}

// PROCEDURE: Menampilkan daftar menu
void tampilkanMenu() {
    cout << "\n=== DAFTAR MENU ===\n";
    // 4. LOOP (For Loop)
    for (int i = 0; i < MAX_MENU; i++) {
        cout << i + 1 << ". " << daftarMenu[i].nama << "\t: Rp " << daftarMenu[i].harga << endl;
    }
    cout << "===================\n";
}

// FUNCTION: Menghitung total harga (Return value)
int hitungTotal() {
    int total = 0;
    for (int i = 0; i < jumlahPesanan; i++) {
        total += keranjang[i].harga;
    }
    return total;
}

// PROCEDURE: Menyimpan struk ke file txt (8. FILE)
void simpanStruk(int total, int bayar, int kembalian) {
    ofstream fileStruk;
    fileStruk.open("struk_belanja.txt"); // Membuka/Membuat file

    if (fileStruk.is_open()) {
        fileStruk << "=== STRUK PEMBELIAN ===\n";
        for (int i = 0; i < jumlahPesanan; i++) {
            fileStruk << "- " << keranjang[i].nama << " : Rp " << keranjang[i].harga << endl;
        }
        fileStruk << "-----------------------\n";
        fileStruk << "Total Bayar : Rp " << total << endl;
        fileStruk << "Uang Tunai  : Rp " << bayar << endl;
        fileStruk << "Kembalian   : Rp " << kembalian << endl;
        fileStruk << "=======================\n";
        fileStruk << "Terima Kasih!\n";
        
        fileStruk.close(); // Menutup file
        cout << "[INFO] Struk berhasil disimpan ke 'struk_belanja.txt'\n";
    } else {
        cout << "[ERROR] Gagal menyimpan struk.\n";
    }
}

int main() {
    inisialisasiMenu();
    int pilihanMenuUtama;
    char lanjut;

    do { // 4. LOOP (Do-While)
        system("cls"); // Membersihkan layar (opsional, windows)
        // system("clear"); // Gunakan ini jika di Linux/Mac
        
        cout << "=== PROGRAM KASIR SEDERHANA ===\n";
        cout << "1. Tambah Pesanan\n";
        cout << "2. Lihat Keranjang & Bayar\n";
        cout << "3. Keluar\n";
        cout << "Pilihan Anda: ";
        // 1. INPUT
        cin >> pilihanMenuUtama;

        // 2. IF & SWITCH CASE
        switch (pilihanMenuUtama) {
        case 1: {
            tampilkanMenu();
            int nomorMenu;
            cout << "Pilih nomor menu (1-" << MAX_MENU << "): ";
            cin >> nomorMenu;

            // Validasi Input dengan IF
            if (nomorMenu >= 1 && nomorMenu <= MAX_MENU) {
                if (jumlahPesanan < MAX_PESANAN) {
                    // Masukkan ke array keranjang
                    keranjang[jumlahPesanan] = daftarMenu[nomorMenu - 1];
                    jumlahPesanan++;
                    cout << ">> " << daftarMenu[nomorMenu - 1].nama << " masuk keranjang.\n";
                } else {
                    cout << "Keranjang penuh!\n";
                }
            } else {
                cout << "Menu tidak valid!\n";
            }
            break;
        }
        case 2: {
            if (jumlahPesanan == 0) {
                cout << "Keranjang masih kosong.\n";
            } else {
                cout << "\n--- Rincian Pesanan ---\n";
                for (int i = 0; i < jumlahPesanan; i++) {
                    cout << i+1 << ". " << keranjang[i].nama << " - Rp " << keranjang[i].harga << endl;
                }
                
                int totalHarga = hitungTotal();
                cout << "-----------------------\n";
                cout << "Total: Rp " << totalHarga << endl;
                
                int uangBayar;
                cout << "Masukkan Uang Bayar: Rp ";
                cin >> uangBayar;

                if (uangBayar >= totalHarga) {
                    int kembalian = uangBayar - totalHarga;
                    cout << "Kembalian: Rp " << kembalian << endl;
                    cout << "Transaksi Berhasil!\n";
                    
                    // Panggil fungsi file
                    simpanStruk(totalHarga, uangBayar, kembalian);
                    
                    // Reset keranjang
                    jumlahPesanan = 0; 
                } else {
                    cout << "Uang tidak cukup! Transaksi dibatalkan.\n";
                }
            }
            break;
        }
        case 3:
            cout << "Terima kasih telah menggunakan aplikasi ini.\n";
            return 0;
        default:
            cout << "Pilihan tidak ada.\n";
        }
        
        cout << "\nTekan 'y' untuk kembali ke menu utama: ";
        cin >> lanjut;

    } while (lanjut == 'y' || lanjut == 'Y');

    return 0;
}