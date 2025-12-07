#include <iostream>
#include <string>
#include <cstdlib> // Random & getenv
#include <ctime>   // Time seed
#include <windows.h> // warnaa cmd

using namespace std;

// Deklarasi paling awal
class Cerita;
class RuangProdi;       
class LorongKiri;
class LorongKanan;
class LorongPanjang; 
class Parkiran;

// --- UTILITIES ---

void delay(int ms) {
    Sleep(ms);
}

// Fungsi Warna 
void aturWarna(int colorCode) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorCode);
}

// Konstanta Warna (biar lebih gampang ngatur warna daripada nulis angkanya)
const int WHITE = 7;
const int RED = 4;
const int BRIGHT_RED = 12;
const int GREEN = 2;
const int BRIGHT_AQUA = 11;
const int BLUE = 1;



int rollAngka() {
    return (rand() % 100) + 1;
}

void salahOpsi() {
    aturWarna(BRIGHT_AQUA);
    cout << "\nKamu salah opsi... liat lagi pilihannya...\n";
    aturWarna(WHITE);
}


// Fungsi biar lambet print textnya
void slowPrint(string text, int speed = 40) {

    for (char c : text) {
        cout << c;
        delay(0); //Ubah isi delay ke 0 untuk lebih cepat liat hasil di cmd (Mempercepat liat hasil proses)
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
        aturWarna(BRIGHT_RED);
        cout<<"(Menerima damage sebesar: "<<amount<<" )"<<endl;
        aturWarna(WHITE);
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
class RuangProdi : public Cerita {
    public:
    bool cekStatusAlur;
    Cerita* mainkan(Player* p) override;

    RuangProdi(bool statusPertama) {
        cekStatusAlur = statusPertama;
    }
    
};

class LorongPanjang : public Cerita {
    public:
    Cerita* mainkan(Player* p) override;
};

class LorongKanan : public Cerita {
    public:
    Cerita* mainkan(Player* p) override;
    
};

class LorongKiri : public Cerita {
    public:
    Cerita* mainkan(Player* p) override;
   
};

class Parkiran : public Cerita {
    public:
    Cerita* mainkan(Player* p) override;
};

    // isi dari masing masing class
    Cerita* RuangProdi::mainkan(Player* p) {
        system("cls"); 
        aturWarna(WHITE);
        if (cekStatusAlur)
        {
            slowPrint("Setelah kamu mengetahui kamu sendirian di ruang prodi, kamu bergegas untuk keluar dari kelas...", 20);
            slowPrint("Wah, ajaib sekali pintunya masih terbuka di jam seperti ini...", 20);
            delay(100);
            slowPrint("\nKamu menengok ke kiri dan ke kanan, memandangi lorong yang gelap...", 10);
            slowPrint("Entah kenapa... hari ini fakultas teknik keliatannya... kosong?", 10);
            slowPrint("Terlintas dalam pikiranmu hanya satu, yaitu pergi dari sini atau setidaknya pulang.", 10);
            slowPrint("Tujuanmu saat ini adalah mencapai sepeda motor yang biasa kamu pakai.", 10);
            delay(100);
            slowPrint("\nDi lorong sebelah kanan, itu adalah jalan yang tercepat untuk mencapai parkiran... tapi entah kenapa kamu yakin bahwa gerbang di lorong itu terkunci...", 10);
            slowPrint("Sedangkan di lorong sebelah kiri, itu adalah lorong yang biasanya masih dibuka hingga larut malam walaupun sedikit agak jauh...", 10);
        } else {
            slowPrint("Kamu kembali lagi ke ruang prodi...", 5);
        }
        
        while (true) {
            cout << "\n[LOKASI: Ruang Prodi]\n";
            cout << "Kewarasan: " << p->kewarasan << "%\n";
            cout << "1. Belok ke lorong kiri\n";
            cout << "2. Belok ke lorong Kanan\n";
            cout << "3. Diam (Exit)\n";
            cout << "Pilihan > ";

            int pil;
            if (!(cin >> pil)) {
                salahOpsi();
                cin.clear();
                cin.ignore(1000, '\n');
                continue;
            }

            if (pil == 1) {
                return new LorongKiri(); 
            } 
            else if (pil == 2) {
                 return new LorongKanan(); 
                 
            }
            else if (pil == 3) {
                return nullptr; 
            } else {
                salahOpsi();
            }
        }

    }

    Cerita* LorongKiri::mainkan(Player* p)  {
        system("cls"); 
        aturWarna(WHITE);
        cout << "[LOKASI: LORONG KIRI]\n";
        slowPrint("Kamu berjalan menyusuri lorong kiri yang panjang...", 30);
        delay(1000);

        int eventAcak = rand() % 3; 

        switch (eventAcak) {
            
            case 0:
                slowPrint("SRRKK... SREK...", 60);
                delay(500);
                while (true) {
                    cout << "Kamu mendengar suara seretan kaki di belakangmu.\n";
                    cout << "1. Menoleh\n2. Jalan terus (Cuek)\n> ";
                    int pil1;
                    
                    if (!(cin >> pil1)) {
                        salahOpsi();
                        cin.clear();
                        cin.ignore(1000, '\n');
                        continue;
                    }
                    
                    if (pil1 == 1) {
                        jumpScareSound();
                        glitchEffect(p->nama);
                        slowPrint("TIDAK ADA SIAPA-SIAPA!", 20);
                        p->kewarasanDamage(10);
                        break;
                    } else if(pil1 == 2) {
                        slowPrint("Kamu mempercepat langkahmu.", 30);
                        break;
                    } else {
                        salahOpsi();
                    }

                }
                break;


            case 1: 
                slowPrint("Selama kamu berjalan, kamu sembari melihat sekelilingmu...", 40);
                delay(1000);
                aturWarna(BRIGHT_RED);
                slowPrint("ADA SESUATU DARI KEJAUHAN DI LAPANGAN BASKET YANG TERLIHAT MENGHADAPMU", 80);
                aturWarna(WHITE);
                
                while (true) {
                    cout<<"=========================\n";
                    cout<< "1. Fokuskan matamu untuk melihat sosok itu lebih jelas lagi\n2. Jalan terus dengan pura-pura cuek\n> ";
                    int pil2;

                    if (!(cin >> pil2)) {
                        salahOpsi();
                        cin.clear(); 
                        cin.ignore(1000, '\n');
                        continue;
                    }
                    if (pil2 == 1) {
                        delay(500);
                        // jumpscarePhoto(); //Buat sebuah fungsi ini nanti ygy
                        jumpScareSound();
                        aturWarna(BRIGHT_RED);
                        slowPrint("\nSOSOK ITU MENGHILANG SELAGI KAMU MEMFOKUSKAN MATAMU!", 70);
                        p->kewarasanDamage(10);
                        aturWarna(WHITE);
                        break;
                    } else if (pil2 == 2) {
                        slowPrint("Kamu mempercepat langkahmu.", 30);
                        break; 
                    } else {
                        salahOpsi();
                    }
                    delay(1000);
                }
                break;
                

            case 2:
                slowPrint("...Lorong ini sangat-sangat hening dan sepi.", 30);
                break;
        }

        delay(1000);
        slowPrint("Kamu berhenti di ujung lorong...");
        slowPrint("Di sebelah kirimu adalah musholla untuk perempuan dengan gerbang terkunci,");
        slowPrint("dan di sebelah kananmu adalah lorong panjang yang menunggumu...");

        while(true) {
            cout << "\n=====================\n";
            cout << "1. Lanjut ke kanan\n";
            cout << "2. Lari balik ke Ruang Prodi\n> ";
        
            int pil3;
            if (!(cin >> pil3)) {
                salahOpsi();
                cin.clear();
                cin.ignore(1000, '\n');
                continue;
            }
            if (pil3 == 1) {
                return new LorongPanjang();
            } else if (pil3 == 2) {
                return new RuangProdi(false);
            } else {
            salahOpsi();
           }
        }
        
        
    }

    Cerita* LorongKanan::mainkan(Player* p) {
        system("cls"); 
        cout << "[LOKASI: LORONG KANAN]\n";
        cout << "Kewarasan: " << p->kewarasan << "%\n";
        slowPrint("Terbiasa melewati lorong ini, tapi entah kenapa kamu waspada saat berjalan...", 30);
        slowPrint("Dan benar saja, gerbang tangga untuk menuju kebawah terkunci...", 30);
        delay(500);
        slowPrint("Kamu berpikir untuk mencoba memanjatnya atau balik ke ruang prodi.", 30);
        
        while(true) {
            cout << "=====================\n";
            cout << "1. Mencoba memanjatnya\n";
            cout << "2. Lari balik ke Ruang Prodi\n> ";

            int pil;

            if (!(cin >> pil)) {
                salahOpsi();
                cin.clear();
                cin.ignore(1000, '\n');; 
                continue; 
            }

            if (pil == 1) {
                while (true) {
                    slowPrint("Kamu mencoba memanjat...", 5);
                    delay(500);
                    int gamble = rollAngka();
                    cout << "[DEBUG] Angka Dadu Keluar: " << gamble << endl;

                    if (gamble<70)
                    {
                        aturWarna(BRIGHT_RED);
                        slowPrint("Kamu terpleset saat mencoba memanjat!", 30);
                        p->kewarasanDamage(50);
                        aturWarna(WHITE);

                        if (p->kewarasan <= 0) return nullptr; // MATI AWKAKWKAKW

                        cout << "\n=====================\n";
                        cout << "Kewarasan: " << p->kewarasan << "%\n";
                        cout << "1. Mencoba memanjatnya lagi...?\n";
                        cout << "2. Nyerah...\n> ";
            
                        int pil2;
                        if (!(cin >> pil2)) {
                            cin.clear();
                            cin.ignore(1000, '\n');; 
                            continue; 
                        }

                        if (pil2 == 1)
                        {
                            system("cls");
                            cout << "[Mencoba lagi...]\n";
                            continue;
                        } else if (pil2 == 2) {
                            break;
                        } else {
                            salahOpsi();
                        }
                    } else {
                        aturWarna(GREEN);
                        slowPrint("BERHASIL! Kamu berhasil melewati gerbang!", 30);
                        aturWarna(WHITE);
                        delay(1000);
                
                        // CONTOH: Lanjut ke area baru (misal Lantai 1)
                        // return new Parkiran(); 
                        
                        // Atau kalau belum ada class-nya, tamatin aja dulu:
                        slowPrint("Kamu selamat untuk saat ini...!", 50);
                        cout<<"[Enter untuk Keluar!]";
                        cin.ignore(1000, '\n');
                        cin.get();
                        return nullptr;
                    }
                    
                }
            
        } else if (pil == 2) {
            return new RuangProdi(false); 
        } else {
            salahOpsi();
        }
        }
      
    }

    Cerita* LorongPanjang::mainkan(Player* p)  {
        system("cls");
        cout << "[LOKASI: Lorong Panjang]\n";
        cout << "Kewarasan: " << p->kewarasan << "%\n";

        slowPrint("Pintu terbuka berderit...", 30);
        slowPrint("Di sini aman. Kamu menemukan peta.", 30);
        
        cout << "\nSekarang mau ke mana?\n";
        cout << "1. Balik ke Ruang Prodi Utama\n";
        cout << "2. Tidur di sini (End Game)\n> ";
        int pil;
        cin >> pil;
        
        if (pil == 1) return new RuangProdi(false); // MUTER BALIK KE DEPAN
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
        isRunning = true;
        string trueName = getSystemUsername();
        player = new Player(trueName);
    }

    // Tambahkan ini (Destructor)
    ~Game() {
        delete player; // Hapus Player saat game ditutup
    }

    

    void start() {
        Cerita* lokasiSekarang = new RuangProdi(true);
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
        slowPrint("Kamu melihat sekelilingmu, tidak ada siapapun kecuali dirimu.", 50);
        slowPrint("Berpikir dalam hati, apakah aku ditinggalkan begitu saja?", 50);
        delay(2000);
        cout << "\n[Tekan Enter untuk lanjut...]";
        cin.get();

        // Nanti buat breaking 4th wall, nge print nama system bukan nama inputan
        // cout << "User terdeteksi: ";
        // delay(800);
        // aturWarna(BRIGHT_RED); 
        // slowPrint(player->nama, 150); // MENCETAK NAMA PC ASLI
        // aturWarna(WHITE);
        
     
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
            cout << "CUUUPUU BANGET JIRRR.\n";
            cout << "Game Over.\n";
            aturWarna(WHITE);
            delay(2000);
            cout<<"[Enter untuk Keluar!]";
            cin.ignore(1000, '\n');
            cin.get();
        }
    }
};

int main() {
    system("title PROJECT: SENDIRI DI RUANG PRODI ELEKTRO"); 
    srand(time(0)); // Seed random
    
    Game myGame;
    myGame.start();
    
    return 0;
}