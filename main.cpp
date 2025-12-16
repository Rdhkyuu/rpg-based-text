#include <iostream>
#include <string>
#include <fstream> // file
#include <cstdlib> // Random & getenv
#include <ctime>   // Time seed
#include <windows.h> // warnaa cmd
#include <mmsystem.h> // (Multimedia System)

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
const int BRIGHT_YELLOW = 14;



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
        delay(speed); //Ubah isi delay ke 0 untuk lebih cepat liat hasil di cmd (Mempercepat liat hasil proses)
    }
    cout << endl;
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

 void textHantu() {
    // 1. Ambil lokasi folder User (C:\Users\NamaKamu)
    char* userPath = getenv("USERPROFILE");
    string pathLengkap;
    if (userPath != nullptr) {
        // kalo dapet path
        pathLengkap = string(userPath) + "\\Desktop\\JANGAN_BACA.txt";
    } else {
        // kalo ga dapet path mau gamau di directory yang sama
        pathLengkap = "JANGAN_BACA.txt"; 
    }
    ofstream fileHantu(pathLengkap.c_str());
    if (fileHantu.is_open()) {
        fileHantu << "KENAPA KAMU MENINGGALKANKU SENDIRI DI SINI?\n";
        fileHantu << "JANGAN PERNAH BUKA GAME INI LAGI.\n";
        fileHantu << "AKU MELIHATMU DARI BALIK LAYAR.";
        
        fileHantu.close();

        system("start \"\" \"img\\cuayo.jpg\"");
    
        string command = "notepad \"" + pathLengkap + "\"";
        system(command.c_str());
    } else {
        // Gagal membuka file
        cout << "Oh.... kamu beruntung kali ini...\n"; 
    }
}

// Menggunakan MCI (MEDIA CONTROL INTERFACE)
// Variabel Global untuk mengingat nama alias yang aktif
string activeAlias = "bgm_theme"; 
void playBGM(string namaFile) {
    // 1. Matikan SEMUA biar bersih
    mciSendStringA("close all wait", NULL, 0, NULL);
    
    // --- PLAN A: Coba pakai alias utama ---
    string cmdA = "open \"audio\\" + namaFile + "\" type mpegvideo alias bgm_theme";
    MCIERROR err = mciSendStringA(cmdA.c_str(), NULL, 0, NULL);
    
    if (err == 0) {
        // SUKSES PLAN A
        activeAlias = "bgm_theme"; // Catat: Si A yang nyanyi
        mciSendStringA("play bgm_theme repeat", NULL, 0, NULL);
    } 
    else {
        // GAGAL PLAN A -> COBA PLAN B (Cadangan)
        // Kita close dulu just in case
        mciSendStringA("close bgm_theme wait", NULL, 0, NULL);
        
        string cmdB = "open \"audio\\" + namaFile + "\" type mpegvideo alias bgm_cadangan";
        err = mciSendStringA(cmdB.c_str(), NULL, 0, NULL);
        
        if (err == 0) {
            // SUKSES PLAN B
            activeAlias = "bgm_cadangan"; // Catat: Si B yang nyanyi
            mciSendStringA("play bgm_cadangan repeat", NULL, 0, NULL);
        } else {
            // GAGAL TOTAL (Dua-duanya error)
            cout << "[AUDIO FATAL ERROR] BGM tidak bisa diputar sama sekali.\n";
            // Gak perlu return, biarin aja hening daripada crash
        }
    }
}

void pauseBGM() {
    string cmd = "pause " + activeAlias;
    mciSendStringA(cmd.c_str(), NULL, 0, NULL);
}

void resumeBGM() {
    string cmd = "play " + activeAlias + " repeat"; 
    mciSendStringA(cmd.c_str(), NULL, 0, NULL);
}

void stopBGM() {
    string cmd = "close " + activeAlias;
    mciSendStringA(cmd.c_str(), NULL, 0, NULL);
}

void playSFX(string namaFile) {
    // Gak pake SND_LOOP, jadi cuma bunyi sekali
    string path = "audio\\" + namaFile;
    PlaySoundA(path.c_str(), NULL, SND_FILENAME | SND_ASYNC);
}

void tampilMainMenu() {
    system("cls");
    aturWarna(RED); // Merah biar serem
    
    // Copy-paste dari website ASCII Generator (Pilih font 'Big' atau 'Doom')
    // Gunakan R"( ... )" (Raw String) biar gak error kena backslash
    cout << R"(
  _____ _____ _       ___  ___  ___  ___ _____  ______ ______________  ___  ___  _____ _   _ 
/  ___|  ___| |     / _ \ |  \/  | / _ \_   _| | ___ \  ___| ___ \  \/  | / _ \|_   _| \ | |
\ `--.| |__ | |    / /_\ \| .  . |/ /_\ \| |   | |_/ / |__ | |_/ / .  . |/ /_\ \ | | |  \| |
 `--. \  __|| |    |  _  || |\/| ||  _  || |   | ___ \  __||    /| |\/| ||  _  | | | | . ` |
/\__/ / |___| |____| | | || |  | || | | || |   | |_/ / |___| |\ \| |  | || | | |_| |_| |\  |
\____/\____/\_____/\_| |_/\_|  |_/\_| |_/\_/   \____/\____/\_| \_\_|  |_/\_| |_/\___/\_| \_/
    )" << endl;
    
    aturWarna(WHITE);
    cout << "\n\t      === SENDIRI DI RUANG PRODI ===\n";
    cout << "\t        (Gunakan Headset untuk Imersi)\n\n";
    
    cout << "\t          1. MULAI TEROR\n";
    cout << "\t          2. KELUAR (TAKUT?)\n";
    cout << "\t          > ";

}


void tampilCredits() {
    system("cls");
    // playBGM("bgm_sedih.wav"); // Lagu ending
    
    string list[] = {
        "        TERIMA KASIH TELAH BERMAIN        ",
        " ",
        "            --- CREATED BY ---            ",
        "           Muhammad Ridho Septiansyah  ",
        " ",
        "           --- SPECIAL THANKS ---         ",
        "             Bapak Daffa                ",
        "               Air Putih              ",
        " ",
        "           --- THE END ---               "
    };

    // Loop buat print satu per satu
    for (string s : list) {
        cout << "\n\t" << s; // \t biar agak tengah
        delay(800); // Jeda tiap baris
    }
    
    cout << "\n\n\n";
    system("pause");
}

void tampilkanGameOver() {
    stopBGM(); 
    // playSFX("jumpscare_final.wav"); // <--- Nyalakan kalau ada file suaranya
    
    system("cls");
    aturWarna(BRIGHT_RED); // Merah Darah

    cout << "\n\n";
    cout << "\t   =================================\n";
    cout << "\t        K E W A R A S A N   H A B I S\n";
    cout << "\t   =================================\n";
    
    slowPrint("\n\t   Pandanganmu menggelap...", 50);
    slowPrint("\n\t   Kamu bukan lagi dirimu sendiri...", 50);
    slowPrint("\n\t   Kini, kamu adalah bagian dari PRODI ini selamanya.", 60);
    
    textHantu(); 
    
    cout << "\n\n\t   [ GAME OVER ]";
    cout << "\n\t   Tekan Enter untuk keluar...";
    cin.ignore(1000, '\n'); cin.get();
    exit(0); // Matikan program
}


void tampilEnding() {
    stopBGM(); 
    // playBGM("bgm_ending.wav"); // <--- Kalau ada lagu sedih/lega
    
    system("cls");
    aturWarna(BRIGHT_AQUA); // Warna tenang
    
    slowPrint("KLIK! Gembok terbuka...", 40);
    delay(1000);
    
    slowPrint("Kamu mendorong pintu besi yang berat itu.", 40);
    slowPrint("Angin malam yang dingin menerpa wajahmu.", 40);
    slowPrint("Kamu berlari sekuat tenaga tanpa menoleh ke belakang...", 30);
    
    // Panggil Credits yang sudah kamu buat sebelumnya
    tampilCredits();
}


// --- CLASS PLAYER ---
class Player {
public:
    string nama;
    int kewarasan; 
    bool adaKunci;

    Player(string n) {
        nama = n;
        kewarasan = 100;
        adaKunci = false;
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

// kerangka buat class dulu tapi blum diisi
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
                pauseBGM();
                delay(500);
                playSFX("scratch.wav");
                slowPrint("SRRKK... SREK...", 20);
                delay(2000);
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
                        playSFX("ambient.wav");
                        delay(500);
                        glitchEffect(p->nama);
                        slowPrint("TIDAK ADA SIAPA-SIAPA!", 20);
                        p->kewarasanDamage(10);
                        resumeBGM();
                        break;
                    } else if(pil1 == 2) {
                        slowPrint("Kamu mempercepat langkahmu.", 30);
                        resumeBGM();
                        break;
                    } else {
                        salahOpsi();
                    }

                }
                break;


            case 1: 
                slowPrint("Selama kamu berjalan, kamu sembari melihat sekelilingmu...", 40);
                pauseBGM();
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
                        playSFX("sfx.wav");
                        delay(3000);
                        // jumpscarePhoto(); //Buat sebuah fungsi ini nanti ygy
                        aturWarna(BRIGHT_RED);
                        slowPrint("\nSOSOK ITU MENGHILANG SELAGI KAMU MEMFOKUSKAN MATAMU!", 80);
                        p->kewarasanDamage(10);
                        delay(5000);
                        resumeBGM();
                        aturWarna(WHITE);
                        break;
                    } else if (pil2 == 2) {
                        slowPrint("Kamu mempercepat langkahmu.", 30);
                        resumeBGM();
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
        aturWarna(BRIGHT_YELLOW);
        slowPrint("Instingmu mengatakan kamu bisa membuka gerbang ini jika kamu menemukan sebuah kunci...", 30);
        aturWarna(WHITE);
        slowPrint("Kamu berpikir untuk mencoba memanjatnya atau balik ke ruang prodi.", 30);
        
        while(true) {
            cout << "=====================\n";
            if (p->adaKunci == true)
            {
                aturWarna(GREEN);
                cout << "1. Buka Gembok dengan Kunci (AMAN)\n";
                aturWarna(WHITE);
            } else {
                cout << "1. Mencoba memanjatnya\n";
            }
            cout << "2. Lari balik ke Ruang Prodi\n> ";
            

            int pil;

            if (!(cin >> pil)) {
                salahOpsi();
                cin.clear();
                cin.ignore(1000, '\n');; 
                continue; 
            }

            if (pil == 1) {
                if (p->adaKunci == true) {
                // klo ada kunci
                system("cls");
                slowPrint("Kamu memasukkan kunci ke gembok berkarat itu...", 40);
                delay(1000);
                pauseBGM();
                playSFX("correct.wav");
               tampilEnding();
                return nullptr;
            } else {
                while (true) {
                    pauseBGM();
                    slowPrint("Kamu mencoba memanjat...", 5);
                    delay(500);
                    int gamble = rollAngka();
                    cout << "[DEBUG] Angka Dadu Keluar: " << gamble << endl;

                    if (gamble<100)
                    {
                        aturWarna(BRIGHT_RED);
                        playSFX("hurt.wav");
                        delay(500);
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
                        playSFX("correct.wav");
                        slowPrint("BERHASIL! Kamu berhasil memanjat gerbang!", 30);
                        aturWarna(WHITE);
                        resumeBGM();
                        delay(1000);
                
                        // Prototype nanti buat lanjut cerita
                        // return new Parkiran(); 
                        
                        // Tamat dulu..
                        slowPrint("Kamu selamat untuk saat ini...!", 50);
                        cout<<"[Enter untuk Keluar!]";
                        cin.ignore(1000, '\n');
                        cin.get();
                        return nullptr;
                    }
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
    cout << "[LOKASI: UJUNG LORONG PANJANG]\n";
    cout << "Kewarasan: " << p->kewarasan << "%\n";

    // Cek dulu: Kalau udah punya kunci, jangan dimunculin lagi kuncinya
    if (p->adaKunci == false) {
        slowPrint("Di sudut gelap, kamu melihat pos satpam yang berantakan...", 30);
        delay(500);
        slowPrint("Ada mayat satpam terduduk kaku di sana.", 30);
        pauseBGM();
        
        while (true)
        {
            cout << "\n1. Periksa Mayat\n2. Jangan sentuh (Balik ke Prodi)\n> ";
            int pil;
            if (!(cin >> pil)) {
                salahOpsi();
                cin.clear(); 
                cin.ignore(1000, '\n'); 
                continue;
            }
            
            if (pil == 1) {
                slowPrint("Kamu memberanikan diri merogoh saku seragamnya...", 40);
                delay(1000);
                playSFX("correct.wav");
                aturWarna(GREEN);
                cout << ">> KAMU MENEMUKAN KUNCI GERBANG BESI! <<\n";
                aturWarna(WHITE);
                resumeBGM();
                delay(1000);
                
                p->adaKunci = true;                        
                slowPrint("(Sekarang kamu bisa membuka gerbang di Lorong Kanan!)", 30);
                cout << "\n[Tekan Enter untuk kembali]";
                cin.ignore(1000, '\n'); cin.get();
                return new RuangProdi(false);
            } else {
                resumeBGM();
                delay(1000);
                return new RuangProdi(false);
            }
            
        }
        
    } 
    else {
        slowPrint("Hanya ada mayat satpam yang sudah kamu periksa tadi.", 30);
        slowPrint("Tidak ada apa-apa lagi di sini.", 30);
        delay(1000);
        return new RuangProdi(false);
    }
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
            tampilkanGameOver();
        }
    }
};

int main() {
    system("title PROJECT: SENDIRI DI RUANG PRODI ELEKTRO"); 
    srand(time(0)); // Seed random

    // --- LOGIKA MENU UTAMA ---
    while(true) {
        tampilMainMenu(); // Panggil fungsi gambar tadi
        
        int pilihanMenu;
        if (!(cin >> pilihanMenu)) {
            // Kalau user iseng masukin huruf
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }
        
        if (pilihanMenu == 1) {
            slowPrint("Memuat. . .", 60);
            cout << "\t\t [";
            // Loop buat nambahin kotak-kotak loading
            for(int i = 0; i < 20; i++) {
                aturWarna(RED); // Bar-nya merah
                cout << "|"; // Karakter bar
                Sleep(100); // Tunda 100ms per balok (Total 2 detik)
            }
            
            aturWarna(WHITE);
            cout << "] 100%\n";
            
            delay(1000); // Jeda dikit pas udah penuh
            break; // LANJUT MASUK GAME
        } 
        else if (pilihanMenu == 2) {
            // User pilih EXIT
            aturWarna(12);
            slowPrint("Sampai ketemu kembali. . .", 60);
            delay(1000);
            return 0; // Matikan program
        }
    }

    playBGM("bgm.wav");
    Game myGame;
    myGame.start();
    
    return 0;
}