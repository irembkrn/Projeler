#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <random>
using namespace std;

string karistir(string kelime) {
    shuffle(kelime.begin(), kelime.end(), default_random_engine());
    return kelime;
}


void yeniKelimeEkle(const string& dosyaYolu, const string& yeniKelime) {
    ofstream dosya(dosyaYolu, ios::app);

    if (!dosya.is_open()) {
        cerr << "Dosya acilamadi: " << dosyaYolu << endl;
        return;
    }

    dosya << yeniKelime << ",";
    dosya.close();
}

void dosyadanKelimeleriOku(const string& dosyaYolu, vector<string>& kelimeler) {
    ifstream dosya(dosyaYolu);

    if (!dosya.is_open()) {
        cerr << "Dosya acilamadi: " << dosyaYolu << endl;
        return;
    }

    string kelime;
    while (getline(dosya, kelime, ',')) {
        kelimeler.push_back(kelime);
    }

    dosya.close();
}

void tekOyunculuMod(const string& dilDosyaYolu) {
    string oyuncu;
    int puan = 50;
    string yeniDosyaYolu = "C:\\Kelime\\Yenikelimeler.txt";
    vector<string> kelimeler;
    dosyadanKelimeleriOku(dilDosyaYolu, kelimeler);

    cout << "Oyuncu ismini girin: ";
    cin >> oyuncu;

    while (puan < 80 && puan >= 0) {
        srand(static_cast<unsigned int>(time(0)));
        int rastgeleIndex = rand() % kelimeler.size();
        string secilenKelime = kelimeler[rastgeleIndex];
        string karisikKelime = karistir(secilenKelime);

        cout << "Harfleri karistirilmis kelime: " << karisikKelime << endl;
        cout << oyuncu << ", dogru kelimeyi tahmin et: ";

        string kullaniciTahmini;
        cin >> kullaniciTahmini;

        if (kullaniciTahmini == secilenKelime) {
            cout << "Dogru tahmin! 10 puan kazandiniz." << endl;
            puan += 10;
        } else {
            cout << "Yanlis tahmin. 10 puan kaybettiniz. Dogru kelime: " << secilenKelime << endl;
            puan -= 10;
            yeniKelimeEkle(yeniDosyaYolu, kullaniciTahmini);
        }

        if (puan < 0) {
            cout << "Oyunu kaybettiniz! Puaniniz sifirin altina dustu." << endl;
            break;
        }

        if (puan >= 80) {
            cout << oyuncu << " kazandi! Toplam puan: " << puan << endl;
            break;
        }
    }
}

void cokOyunculuMod(const string& dilDosyaYolu) {
    string oyuncu1, oyuncu2;
    int puan1 = 50, puan2 = 50;
    string yeniDosyaYolu = "C:\\Kelime\\Yenikelimeler.txt";
    vector<string> kelimeler;
    dosyadanKelimeleriOku(dilDosyaYolu, kelimeler);

    cout << "Oyuncu 1 ismini girin: ";
    cin >> oyuncu1;

    cout << "Oyuncu 2 ismini girin: ";
    cin >> oyuncu2;

    while (puan1 < 80 && puan2 < 80 && puan1 >= 0 && puan2 >= 0) {
        srand(static_cast<unsigned int>(time(0)));
        int rastgeleIndex = rand() % kelimeler.size();
        string secilenKelime = kelimeler[rastgeleIndex];
        string karisikKelime = karistir(secilenKelime);

        cout << oyuncu1 << ", harfleri karistirilmis kelime: " << karisikKelime << endl;
        cout << "Dogru kelimeyi tahmin et: ";

        string kullaniciTahmini;
        cin >> kullaniciTahmini;

        if (kullaniciTahmini == secilenKelime) {
            cout << "Dogru tahmin! 10 puan kazandiniz." << endl;
            puan1 += 10;
        } else {
            cout << "Yanlis tahmin. 10 puan kaybettiniz. Dogru kelime: " << secilenKelime << endl;
            puan1 -= 10;
            yeniKelimeEkle(yeniDosyaYolu, kullaniciTahmini);
        }

        if (puan1 < 0) {
            cout << oyuncu1 << ", oyunu kaybetti! Puaniniz sifirin altina dustu." << endl;
            break;
        }

        if (puan1 >= 80) {
            cout << oyuncu1 << " kazandi! Toplam puan: " << puan1 << endl;
            break;
        }

        rastgeleIndex = rand() % kelimeler.size();
        secilenKelime = kelimeler[rastgeleIndex];
        karisikKelime = karistir(secilenKelime);

        cout << oyuncu2 << ", harfleri karistirilmis kelime: " << karisikKelime << endl;
        cout << "Dogru kelimeyi tahmin et: ";
        cin >> kullaniciTahmini;

        if (kullaniciTahmini == secilenKelime) {
            cout << "Dogru tahmin! 10 puan kazandiniz." << endl;
            puan2 += 10;
        } else {
            cout << "Yanlis tahmin. 10 puan kaybettiniz. Dogru kelime: " << secilenKelime << endl;
            puan2 -= 10;
            yeniKelimeEkle(yeniDosyaYolu, kullaniciTahmini);
        }

        if (puan2 < 0) {
            cout << oyuncu2 << ", oyunu kaybetti! Puaniniz sifirin altina dustu." << endl;
            break;
        }

        if (puan2 >= 80) {
            cout << oyuncu2 << " kazandi! Toplam puan: " << puan2 << endl;
            break;
        }
    }
}

int main() {
    do {
        string dilSecimi;
        cout << "Hangi dilde oynamak istersiniz? (T: Turkce, E: English): ";
        cin >> dilSecimi;

        string dilDosyaYolu;
        if (dilSecimi == "T" || dilSecimi == "t") {
            dilDosyaYolu = "C:\\Kelime\\kelimelerturkce.txt";
        } else if (dilSecimi == "E" || dilSecimi == "e") {
            dilDosyaYolu = "C:\\Kelime\\wordlistenglish.txt";
        } else {
            cerr << "Hatali dil secimi. Programdan cikiliyor." << endl;
            return 1;
        }

        int mod;
        cout << "Oyun modunu secin (1: Tek Oyunculu, 2: Cok Oyunculu): ";
        cin >> mod;

        if (mod == 1) {
            tekOyunculuMod(dilDosyaYolu);
        } else if (mod == 2) {
            cokOyunculuMod(dilDosyaYolu);
        } else {
            cout << "Hatali mod secimi. Lutfen tekrar deneyin." << endl;
        }

        char devam;
        cout << "Yeni bir oyun oynamak istiyor musunuz? (E/H): ";
        cin >> devam;
        if (devam != 'E' && devam != 'e') {
            cout << "Programdan cikiliyor." << endl;
            break;
        }
    } while (true);

    return 0;
}