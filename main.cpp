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

// --- CLASS GAME ---
class Game {
private:
    Player* player;
    bool isRunning;

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

    void start() {
        // --- INTRO ---
        system("cls");
        
        aturWarna(WHITE);
        slowPrint("...", 300);
        slowPrint("Menghubungkan ke terminal...", 60);
        delay(1000);

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