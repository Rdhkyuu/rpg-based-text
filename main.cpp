#include <iostream>
#include <string>
#include <cstdlib> // Random & getenv
#include <ctime>   // Time seed
#include <windows.h> // warnaa cmd

using namespace std;

// --- UTILITIES ---

void delay(int ms) {
    Sleep(ms);
}

// Fungsi Warna 
void aturWarna(int colorCode) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorCode);
}

// Konstanta Warna (Biar gampang aja si ingat angkanya)
const int WHITE = 7;
const int RED = 4;
const int BRIGHT_RED = 12;
const int GREEN = 2;
const int BLUE = 1;

// Fungsi biar lambet print textnya
void slowPrint(string text, int speed = 40) {
    for (char c : text) {
        cout << c;
        delay(speed);
    }
    cout << endl;
}

void jumpScareSound() {
    // Beep(Frekuensi, Durasi milidetik)
    Beep(300, 100); 
    Beep(200, 100);
    Beep(100, 500); 
}

// --- CLASS PLAYER ---
class Player {
public:
    string nama;
    int kewarasan; 

    Player(string n) {
        nama = n;
        kewarasan = 100;
    }

    bool cekWaras() { return kewarasan <= 0; }

    void kewarasanDamage(int amount) {
        kewarasan -= amount;
        if (kewarasan < 0) kewarasan = 0;
    }
};

class Cerita {
public:
    // Virtual Function: Ini adalah "Lubang Kunci" yang akan diisi berbeda-beda oleh anaknya.
    // Kita butuh akses ke Player biar cerita bisa mengurangi kewarasan.
    virtual void mainkan(Player* p) {
        cout << "Ini cerita kosong...\n";
    }
    
    // Virtual Destructor (Penting saat main inheritance)
    virtual ~Cerita() {} 
};

class LorongKanan : public Cerita {
public:
    void mainkan(Player* p) override {
        system("cls"); // Bersihkan layar biar fresh
        aturWarna(WHITE);
        cout << "[LOKASI: LORONG SAYAP KANAN]\n";
        slowPrint("Kamu berjalan menyusuri lorong kanan yang panjang...", 30);
        delay(1000);

        // --- INI LOGIKA RNG DI BALIK LAYAR ---
        // Kita kocok dadu 0 sampai 2 (Ada 3 kemungkinan)
        int eventAcak = rand() % 3; 

        // --- Cek Hasil Kocokan ---
        switch (eventAcak) {
            
            case 0: // EVENT 1: Suara Misterius (Horror Dikit)
                slowPrint("SRRKK... SREK...", 60);
                delay(500);
                cout << "Kamu mendengar suara seretan kaki di belakangmu.\n";
                // Pilihan user merespon event ini
                cout << "1. Menoleh\n2. Jalan terus (Cuek)\n> ";
                int pil1;
                cin >> pil1;
                if (pil1 == 1) {
                    jumpScareSound();
                    slowPrint("TIDAK ADA SIAPA-SIAPA!", 20);
                    p->kewarasanDamage(10); // Kena mental dikit
                } else {
                    slowPrint("Kamu mempercepat langkahmu.", 30);
                }
                break;

            case 1: // EVENT 2: Melihat Sesuatu (Visual Horror)
                aturWarna(RED);
                slowPrint("Di ujung lorong... ada bayangan berdiri tegak.", 40);
                aturWarna(WHITE);
                delay(1000);
                slowPrint("Tunggu... itu cuma gantungan baju janitor.", 30);
                cout << "(Helaan napas lega... Kewarasan pulih sedikit)\n";
                // Bisa nambah logic heal sedikit kalau mau
                break;

            case 2: // EVENT 3: Kosong (Aman)
                slowPrint("Lorong ini sepi. Hanya ada debu beterbangan.", 30);
                cout << "Kamu merasa sedikit tenang.\n";
                break;
        }

        // --- BAGIAN KELUAR DARI LORONG ---
        // Setelah event selesai, lanjut ke narasi utama
        delay(1000);
        cout << "\nDi ujung lorong, kamu menemukan sebuah pintu kelas 2B.\n";
        // Disini nanti logika untuk pindah ke Class Cerita selanjutnya...
    }
};

// --- ANAK 1: CERITA UTAMA (Normal) ---
class CeritaUtama : public Cerita {
public:
    void mainkan(Player* p) override {
        cout << "\n[LOKASI: PERPUSTAKAAN KAMPUS]\n";
        cout << "Lampu berkedip. Kamu melihat buku tua terbuka sendiri.\n";
        cout << "1. Baca buku itu\n2. Lari keluar\n> ";
        
        int pilihan;
        cin >> pilihan;

        if (pilihan == 1) {
            cout << "Tulisan di buku itu berubah menjadi darah...\n";
            p->kewarasanDamage(10);
        } else {
            cout << "Kamu lari seperti pengecut.\n";
        }
    }
};

// --- ANAK 2: CERITA RAHASIA (Horror/Glitch) ---
class CeritaRahasia : public Cerita {
public:
    void mainkan(Player* p) override {
        aturWarna(BRIGHT_RED); // Merah
        cout << "\n[LOKASI: ???_ERROR_???]\n";
        cout << "KENAPA KAMU DATANG KE SINI, " << p->nama << "?\n";
        
        // Logika Horror
        p->kewarasanDamage(50); // Damage besar!
        cout << "Pikiranmu terasa terbakar!\n";
        
        aturWarna(WHITE); // Balikin warna
        delay(2000);
    }
};

// --- CLASS GAME ---
class Game {
private:
    Player* player;
    bool isRunning;
    Cerita* lokasiAktif;

    string getSystemUsername() {
        // Mencoba mengambil nama user Windows (breaking 4th wall!!)
        char* username = getenv("USERNAME"); 
        if (username) return string(username);
        return "Tamu tak dikenal"; 
    }

public:
    Game() {
        srand(time(0)); // Seed random
        isRunning = true;
        string trueName = getSystemUsername();
        player = new Player(trueName);
        lokasiAktif = new CeritaUtama();
    }

    // Cari Angka (1-100)
    int rollAngka() {
        return (rand() % 100) + 1;
    }

    // VFX Horror (Glitch) !!
    void glitchEffect() {
        aturWarna(BRIGHT_RED);
        cout << "\nSYSTEM FAILURE... " << player->nama << "...";
        for(int i=0; i<15; i++) {
            cout << (char)(rand() % 90 + 33); // Karakter acak
            delay(15);
        }
        cout << endl;
        aturWarna(WHITE);
    }

    void gantiLokasi(int tipe) {
        // Hapus lokasi lama dari memori dulu (PENTING biar RAM gak bocor)
        delete lokasiAktif; 

        // Ganti dengan lokasi baru sesuai tipe
        if (tipe == 1) {
            lokasiAktif = new CeritaUtama();
        } 
        else if (tipe == 2) {
            lokasiAktif = new LorongKanan(); 
        }
    }
    

    void start() {
        // --- INTRO ---
        system("cls");
        
        aturWarna(WHITE);
        slowPrint("Senin, 12 Desember 2025...", 20);
        delay(1000);
        slowPrint("Pada saat itu, sedang dalam pelajaran kalkulus...", 5);
        delay(1000);
        slowPrint("Dan entah kenapa pada saat itu, aku tertidur...", 5);
        delay(1000);

        cout << "\n[Tekan Enter untuk lanjut...]";
        cin.get();

        system("cls");
        slowPrint("Terbangun, ruangan telah sepi... dengan kondisi di luar yang sudah gelap gulita.", 50);
        delay(2000);

        cout << "User terdeteksi: ";
        delay(800);
        
        aturWarna(BRIGHT_RED); 
        slowPrint(player->nama, 150); // MENCETAK NAMA PC ASLI
        aturWarna(WHITE);
        
        delay(1000);
        slowPrint("\nJangan melihat ke belakang.", 80);
        delay(1000);

        // --- GAME LOOP ---
        while (isRunning && !player->cekWaras()) {
        
        
            cout << "\n===================================\n";
            cout << "Kewarasan: " << player->kewarasan << "%\n";
            cout << "1. Masuk ke lorong gelap\n";
            cout << "2. Diam di tempat\n";
            cout << "3. Akhiri sesi (Keluar)\n";
            cout << "Pilihan > ";
            
            int pilihan;
            // Validasi input agar tidak error kalau user ketik huruf
            if (!(cin >> pilihan)) {
                cin.clear();
                cin.ignore(1000, '\n'); 
                continue;
            }

            if (pilihan == 1) {
                slowPrint("Kamu melangkah masuk...", 40);
                delay(500);
                
                // RNG 
                int hoki = rollAngka();
                // cout<<hoki; // Debug untuk menjelaskan seed
                
                if (hoki < 100) { // 40% kemungkinan buruk
                    jumpScareSound();
                    glitchEffect();
                    player->kewarasanDamage(25);
                    slowPrint("Sesuatu menyentuh kakimu!", 30);
                    delay(500);
                    system("cls");
                } else {
                    aturWarna(GREEN);
                    slowPrint("Lorong ini kosong. Kamu aman untuk saat ini.", 30);
                    aturWarna(WHITE);
                    delay(500);
                    system("cls");
                }
            }
            else if (pilihan == 2) {
                slowPrint("Kamu menunggu...", 50);
                player->kewarasanDamage(5); // Diam pun mengurangi mental sedikit
                delay(500);
                system("cls");
            }
            else if (pilihan == 3) {
                slowPrint("Mencabut koneksi...", 50);
                delay(500);
                isRunning = false;
            }
            else {
                slowPrint("ASTAGA, KAMU BODOH ATAU GIMANA?! ITU KAN ADA OPSI PILIHANNYA!?", 20);
                delay(500);
                system("cls");
            }
        }

        // --- GAME OVER ---
        if (player->cekWaras()) {
            aturWarna(RED);
            cout << "\n\n=== PIKIRANMU HANCUR ===\n";
            cout << "Game Over.\n";
            aturWarna(WHITE);
            delay(2000);
        }
    }
};

int main() {
    system("title PROJECT: SENDIRI DI RUANG PRODI"); 
    
    Game myGame;
    myGame.start();
    
    return 0;
}