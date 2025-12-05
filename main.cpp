#include <iostream>
#include <string>
#include <cstdlib>  // Untuk random dan getenv
#include <ctime>    // Untuk waktu (seed random)
#include <windows.h> // Untuk Sleep() dan manipulasi warna console (Windows only)

using namespace std;

// --- UTILITIES (Fungsi Bantuan) ---

// Fungsi untuk membuat jeda (dalam milidetik)
void delay(int milliseconds) {
    Sleep(milliseconds);
}

// Fungsi untuk efek mengetik lambat (Horror Vibe)
void slowPrint(string text, int speed = 50) {
    for (char c : text) {
        cout << c;
        delay(speed); // Jeda tiap karakter
    }
    cout << endl;
}

// Fungsi untuk mengganti warna teks (Merah untuk horror/darah)
void setColor(int colorCode) {
    // 7 = Default White, 4 = Red, 12 = Light Red
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorCode);
}

// --- CLASS PLAYER ---
class Player {
public:
    string name;
    int sanity; // Pengganti HP (Health Point)

    Player(string n) {
        name = n;
        sanity = 100;
    }

    bool isInsane() {
        return sanity <= 0;
    }

    void takeSanityDamage(int amount) {
        sanity -= amount;
        if (sanity < 0) sanity = 0;
    }
};

// --- CLASS GAME ---
class Game {
private:
    Player* player; // Pointer ke object player
    bool isRunning;

    // Fungsi rahasia untuk mengambil nama user PC
    string getSystemUsername() {
        char* username = getenv("USERNAME"); // Command khusus Windows
        if (username) {
            return string(username);
        }
        return "Pengguna"; // Fallback jika gagal
    }

public:
    Game() {
        // Setup Random Seed agar acak tiap kali main
        srand(time(0));
        isRunning = true;
        
        // Disini triknya: Kita ambil nama PC mereka, bukan tanya nama.
        string trueName = getSystemUsername();
        player = new Player(trueName);
    }

    // Fungsi RNG (Dadu)
    // Mengembalikan angka 1 - 100
    int rollDice() {
        return (rand() % 100) + 1;
    }

    void glitchEffect() {
        setColor(12); // Merah Terang
        cout << "\nERROR... SYSTEM FAILURE... " << player->name << " IS WATCHING...\n";
        // Cetak karakter acak
        for(int i=0; i<20; i++) {
            cout << (char)(rand() % 255); 
            delay(10);
        }
        cout << endl;
        setColor(7); // Kembalikan ke putih
    }

    void start() {
        // Intro
        setColor(7);
        slowPrint("...", 200);
        slowPrint("Sistem diinisialisasi.", 50);
        delay(1000);
        
        // Breaking the 4th Wall
        cout << "Mendeteksi User ID: ";
        delay(1500);
        
        setColor(12); // Ubah jadi merah
        slowPrint(player->name, 100); // Nama asli user PC
        setColor(7); // Balik ke putih
        
        delay(1000);
        slowPrint("\nHalo. Aku sudah menunggumu.", 60);
        
        // Contoh Gameplay Loop Sederhana
        while (isRunning && !player->isInsane()) {
            cout << "\n-----------------------------------\n";
            cout << "Sanity: " << player->sanity << "%" << endl;
            cout << "Apa yang ingin kamu lakukan?\n";
            cout << "1. Lihat sekeliling\n";
            cout << "2. Cek file sistem (Bahaya)\n";
            cout << "3. Keluar\n";
            cout << "> ";
            
            int choice;
            cin >> choice;

            if (choice == 1) {
                slowPrint("Ruangan ini gelap. Hanya ada kursor yang berkedip...", 30);
            } 
            else if (choice == 2) {
                slowPrint("Mencoba mengakses data terlarang...", 50);
                delay(1000);
                
                int luck = rollDice();
                cout << "[RNG: " << luck << "]\n"; // Tampilkan angka dadu (bisa dihide nanti)

                if (luck < 40) { // Gagal / Bad Luck
                    glitchEffect();
                    player->takeSanityDamage(20);
                    slowPrint("Kepalamu sakit mendadak!", 30);
                } else {
                    slowPrint("Tidak ada apa-apa di sini. Aman.", 30);
                }
            } 
            else if (choice == 3) {
                isRunning = false;
            }
        }

        if (player->isInsane()) {
            setColor(4);
            slowPrint("\nKEWARASANMU HABIS. GAME OVER.", 100);
        }
    }
};

// --- MAIN FUNCTION ---
int main() {
    Game myGame;
    myGame.start();
    return 0;
}