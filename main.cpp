#include <iostream>
#include <string>
#include <cstdlib> // Random & getenv
#include <ctime>   // Time seed
#include <windows.h> // warnaa cmd

using namespace std;

// Deklarasi paling awal
class Cerita;
class Lobby;       
class LorongKanan;
class LorongKiri;
class RuangKelas;  // Lokasi Baru (Ending Lorong Kanan)

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

    // VFX Horror (Glitch) !!
void glitchEffect(string namaTarget) {
    aturWarna(BRIGHT_RED);
    cout << "\nSYSTEM FAILURE... " << namaTarget << "...";

    for(int i=0; i<15; i++) {
        cout << (char)(rand() % 90 + 33); // Karakter acak
        delay(15);
    }
    cout << endl;
    aturWarna(WHITE);
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

    void healKewarasan(int amount) {
        kewarasan += amount;
        if (kewarasan > 100) kewarasan = 100;
    }
};

class Cerita {
public:
    // Virtual Function: Ini adalah "Lubang Kunci" yang akan diisi berbeda-beda oleh anaknya.
    // Kita butuh akses ke Player biar cerita bisa mengurangi kewarasan.
    virtual Cerita* mainkan(Player* p) {
        return nullptr; // Default
    }
    
    // Virtual Destructor (Penting saat main inheritance)
    virtual ~Cerita() {} 
};

// definis class dulu tapi blum diisi
class Lobby : public Cerita {
public:
    Cerita* mainkan(Player* p) override;
    
};

class RuangKelas : public Cerita {
public:
    Cerita* mainkan(Player* p) override;
};

class LorongKiri : public Cerita {
public:
    Cerita* mainkan(Player* p) override;
    
};

class LorongKanan : public Cerita {
public:
    Cerita* mainkan(Player* p) override;
   
};

    // isi dari masing masing class
    Cerita* Lobby::mainkan(Player* p) {
        system("cls");
        aturWarna(WHITE);
        cout << "\n[LOKASI: Ruang Prodi]\n";
        cout << "Kewarasan: " << p->kewarasan << "%\n";
        cout << "1. Belok ke lorong kanan\n";
        cout << "2. Belok ke lorong kiri\n";
        cout << "3. Diam (Exit)\n";
        cout << "Pilihan > ";

        int pil;
        cin >> pil;

        if (pil == 1) {
            // ESTAFET: Kembalikan Object Lorong Kanan ke Game
            return new LorongKanan(); 
        } 
        else if (pil == 2) {
             return new LorongKiri(); // (Bikin nanti)
             
        }
        else {
            return nullptr; // Sinyal untuk keluar game
        }
    }

    Cerita* LorongKanan::mainkan(Player* p)  {
        system("cls"); // Bersihkan layar biar fresh
        aturWarna(WHITE);
        cout << "[LOKASI: LORONG KANAN]\n";
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
                    glitchEffect(p->nama);
                    slowPrint("TIDAK ADA SIAPA-SIAPA!", 20);
                    p->kewarasanDamage(10);
                } else {
                    slowPrint("Kamu mempercepat langkahmu.", 30);
                }
                break;

            case 1: 
                aturWarna(RED);
                slowPrint("Di ujung lorong... ada bayangan berdiri tegak.", 40);
                aturWarna(WHITE);
                delay(1000);
                slowPrint("Tunggu... itu cuma gantungan baju janitor.", 30);
                cout << "(Helaan napas lega... Kewarasan pulih sedikit)\n";
                p->healKewarasan(5);
                break;

            case 2: // EVENT 3: Kosong (Aman)
                slowPrint("Lorong ini sepi. Hanya ada debu beterbangan.", 30);
                cout << "Kamu merasa sedikit tenang.\n";
                break;
        }

        // --- BAGIAN KELUAR DARI LORONG ---
        // Setelah event selesai, lanjut ke narasi utama
        delay(1000);
        cout << "\n=====================\n";
        cout << "\nKamu sampai di ujung lorong. Ada pintu '2B'.\n";
        cout << "1. Masuk Ruang Kelas\n";
        cout << "2. Lari balik ke Lobby\n> ";
        
        int pil;
        cin >> pil;
        
        if (pil == 1) {
            return new RuangKelas(); // MAJU KE DEPAN
        } else {
            return new Lobby(); // MUNDUR KE BELAKANG
        }
    }

    Cerita* LorongKiri::mainkan(Player* p) {
        system("cls"); 
        cout << "[LOKASI: LORONG KIRI]\n";
        slowPrint("Lorong ini penuh dengan air menetes...", 30);
        delay(1000);
        
        slowPrint("Kamu berjalan hati-hati. Sepertinya aman.", 30);
        
        aturWarna(GREEN); 
        cout << "(Kamu merasa sedikit tenang. Kewarasan +5)\n";
        p->healKewarasan(5);
        
        aturWarna(WHITE);
        delay(1500);

        cout << "\n=====================\n";
        cout << "\nAnehnya, tiba-tiba ada tembok yang secara ajaib muncul menghalangi lorong ini?\n";
        cout << "1. Mengecek sekeliling terlebih dahulu\n";
        cout << "2. Lari balik ke Lobby\n> ";
        
        int pil;
        cin >> pil;
        
        if (pil == 1) {
            slowPrint("Kamu mengecek sebentar... tetapi tidak ada apa-apa disini", 5);
            delay(500);
            return new Lobby();
        } else {
            return new Lobby(); // MUNDUR KE BELAKANG
        }
    }

    Cerita* RuangKelas::mainkan(Player* p)  {
        system("cls");
        cout << "[LOKASI: RUANG KELAS 2B]\n";
        cout << "Kewarasan: " << p->kewarasan << "%\n";
        
        slowPrint("Pintu terbuka berderit...", 30);
        slowPrint("Di sini aman. Kamu menemukan peta.", 30);
        
        cout << "\nSekarang mau ke mana?\n";
        cout << "1. Balik ke Lobby Utama\n";
        cout << "2. Tidur di sini (End Game)\n> ";
        int pil;
        cin >> pil;
        
        if (pil == 1) return new Lobby(); // MUTER BALIK KE DEPAN
        else return nullptr; // TAMAT
    }


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
    }

    // Cari Angka (1-100)
    int rollAngka() {
        return (rand() % 100) + 1;
    }

    

    void start() {
        Cerita* lokasiSekarang = new Lobby();
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
        
     
        // --- GAME LOOP ---
        while (isRunning && !player->cekWaras()) {

            if (lokasiSekarang == nullptr) {
            isRunning = false; // Kalau gak ada lokasi, berarti game over/exit
            break;
            }
            // 1. JALANKAN LOKASI SAAT INI
            // Dan TANGKAP lokasi berikutnya yang dilempar oleh return
            Cerita* lokasiSelanjutnya = lokasiSekarang->mainkan(player);
            // 2. HAPUS LOKASI LAMA (Memory Management)
            delete lokasiSekarang;

            // 3. PINDAH KE LOKASI BARU
            lokasiSekarang = lokasiSelanjutnya;
        
            
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