#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <math.h>

LiquidCrystal_I2C lcd(0x27,16,2);

// Keypad ayarları
const byte satir = 4;
const byte sutun = 4;
char tuslar[satir][sutun] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte satirPinleri[satir] = {A0,A1,A2,A3};
byte sutunPinleri[sutun] = {4,5,6,7};
Keypad keypad = Keypad(makeKeymap(tuslar), satirPinleri, sutunPinleri, satir, sutun);

// Durum değişkenleri
int durum = 0;    // 0=AnaMenu, 1=Bölunebilme, 2=Asal, 3=EBOB/EKOK, 4=Hesap Makinesi
int altDurum = 0; // Alt durum
String giris = "";
long sayi1 = 0;
long sayi2 = 0;
int islem = 0;    // Hesap makinesi: 1=+,2=-,3=*,4=/
const int MAX_DIGIT=16;

// ---------------- Fonksiyonlar ----------------
long enYakinKati(long n, long bolen){
  long kat = (n/bolen)*bolen;
  if(kat==n) kat-=bolen;
  return kat;
}

bool bolunurMu(long n,long bolen){
  if(bolen==0) return false;
  long kat=enYakinKati(n,bolen);
  long fark=n-kat;
  return (fark%bolen==0 && fark!=0);
}

bool asalMi(long n){
  if(n<=1) return false;
  for(long i=2;i<=sqrt(n);i++){
    if(n%i==0) return false;
  }
  return true;
}

long EBOB(long a,long b){
  while(b!=0){
    long t=b;
    b=a%b;
    a=t;
  }
  return a;
}

long EKOK(long a,long b){
  return (a*b)/EBOB(a,b);
}

void anaMenu(){
  lcd.clear();
  lcd.print("A=Bolune B=Asal");
  lcd.setCursor(0,1);
  lcd.print("C=EBOB D=Calc");
}

// ---------------- Setup ----------------
void setup(){
  lcd.init();
  lcd.backlight();
  anaMenu();
}

// ---------------- Loop ----------------
void loop(){
  char tus = keypad.getKey();
  if(!tus) return;

  // Silme tuşu
  if(tus=='*'){
    if(giris.length()>0){
      giris.remove(giris.length()-1);
      lcd.setCursor(0,1);
      lcd.print("                "); // temizle
      lcd.setCursor(0,1);
      lcd.print(giris);
    }
    return;
  }

  // ---------------- Ana Menü ----------------
  if(durum==0){
    if(tus=='A'){ durum=1; altDurum=0; giris=""; lcd.clear(); lcd.print("Sayi Gir:"); return; }
    if(tus=='B'){ durum=2; altDurum=0; giris=""; lcd.clear(); lcd.print("Sayi Gir:"); return; }
    if(tus=='C'){ durum=3; altDurum=0; giris=""; lcd.clear(); lcd.print("A=EKOK B=EBOB"); return; }
    if(tus=='D'){ durum=4; altDurum=0; giris=""; lcd.clear(); lcd.print("A=+ B=-"); lcd.setCursor(0,1); lcd.print("C=* D=/"); return; }
  }

  // ---------------- Bölünebilme ----------------
  if(durum==1){
    if(isdigit(tus)){
      if(giris.length()<MAX_DIGIT){ giris+=tus; lcd.setCursor(0,1); lcd.print("                "); lcd.setCursor(0,1); lcd.print(giris); }
      else { lcd.clear(); lcd.print("Hata!"); lcd.setCursor(0,1); lcd.print("Cok Buyuk Sayi!"); delay(1500); giris=""; lcd.clear(); lcd.print("Sayi Gir:"); }
      return;
    }
    if(tus=='#'){
      if(altDurum==0){ sayi1=giris.toInt(); giris=""; altDurum=1; lcd.clear(); lcd.print("Bolunecek Sayi:"); return; }
      else{ sayi2=giris.toInt(); lcd.clear(); long kat=enYakinKati(sayi1,sayi2); long fark=sayi1-kat; bool bolun=(fark%sayi2==0 && fark!=0); lcd.print("Kat:"); lcd.print(kat); lcd.setCursor(0,1); lcd.print("Fark:"); lcd.print(fark); delay(2000); lcd.clear(); lcd.print(bolun?"Bolunur":"Bolunmez"); delay(2000); durum=0; anaMenu(); return; }
    }
  }

  // ---------------- Asal Sayı ----------------
  if(durum==2){
    if(isdigit(tus)){
      if(giris.length()<MAX_DIGIT){ giris+=tus; lcd.setCursor(0,1); lcd.print("                "); lcd.setCursor(0,1); lcd.print(giris); }
      else{ lcd.clear(); lcd.print("Hata!"); lcd.setCursor(0,1); lcd.print("Cok Buyuk Sayi!"); delay(1500); giris=""; lcd.clear(); lcd.print("Sayi Gir:"); }
      return;
    }
    if(tus=='#'){ sayi1=giris.toInt(); lcd.clear(); lcd.print(asalMi(sayi1)?"Asal":"Asal Degil"); delay(2000); durum=0; anaMenu(); return; }
  }

  // ---------------- EBOB / EKOK ----------------
  if(durum==3){
    if(altDurum==0){
      if(tus=='A'){ islem=1; altDurum=1; giris=""; lcd.clear(); lcd.print("Sayi1 Gir:"); return; } // EKOK
      if(tus=='B'){ islem=2; altDurum=1; giris=""; lcd.clear(); lcd.print("Sayi1 Gir:"); return; } // EBOB
    } else{
      if(isdigit(tus)){
        if(giris.length()<MAX_DIGIT){ lcd.setCursor(0,1); lcd.print("                "); giris+=tus; lcd.setCursor(0,1); lcd.print(giris); }
        else{ lcd.clear(); lcd.print("Hata!"); lcd.setCursor(0,1); lcd.print("Cok Buyuk Sayi!"); delay(1500); giris=""; lcd.clear(); lcd.print(altDurum==1?"Sayi1 Gir:":"Sayi2 Gir:"); }
        return;
      }
      if(tus=='#'){
        if(altDurum==1){ sayi1=giris.toInt(); giris=""; altDurum=2; lcd.clear(); lcd.print("Sayi2 Gir:"); return; }
        if(altDurum==2){ sayi2=giris.toInt(); lcd.clear(); long sonuc=(islem==1)?EKOK(sayi1,sayi2):EBOB(sayi1,sayi2); lcd.print((islem==1)?"EKOK=":"EBOB="); lcd.print(sonuc); delay(2000); durum=0; anaMenu(); altDurum=0; return; }
      }
    }
  }

  // ---------------- Hesap Makinesi ----------------
  if(durum==4){
    if(altDurum==0){ // İşlem seçimi
      if(tus=='A'){ islem=1; altDurum=1; giris=""; lcd.clear(); lcd.print("Sayi1 Gir:"); return; }
      if(tus=='B'){ islem=2; altDurum=1; giris=""; lcd.clear(); lcd.print("Sayi1 Gir:"); return; }
      if(tus=='C'){ islem=3; altDurum=1; giris=""; lcd.clear(); lcd.print("Sayi1 Gir:"); return; }
      if(tus=='D'){ islem=4; altDurum=1; giris=""; lcd.clear(); lcd.print("Sayi1 Gir:"); return; }
    } 
    else if(altDurum==1){ // Sayi1 girisi
      if(isdigit(tus)){ if(giris.length()<MAX_DIGIT){ giris+=tus; lcd.setCursor(0,1); lcd.print("                "); lcd.setCursor(0,1); lcd.print(giris); } return; }
      if(tus=='#'){ sayi1=giris.toInt(); giris=""; altDurum=2; lcd.clear(); lcd.print("Sayi2 Gir:"); return; }
    }
    else if(altDurum==2){ // Sayi2 girisi
      if(isdigit(tus)){ if(giris.length()<MAX_DIGIT){ giris+=tus; lcd.setCursor(0,1); lcd.print("                "); lcd.setCursor(0,1); lcd.print(giris); } return; }
      if(tus=='#'){ sayi2=giris.toInt(); lcd.clear(); 
        float sonuc=0;
        if(islem==1) sonuc=sayi1+sayi2;
        else if(islem==2) sonuc=sayi1-sayi2;
        else if(islem==3) sonuc=(long)sayi1*sayi2;
        else if(islem==4){ if(sayi2!=0) sonuc=(float)sayi1/sayi2; else { lcd.print("Sifira Bolme"); delay(2000); durum=0; anaMenu(); return; } }
        lcd.print("Sonuc:"); lcd.print(sonuc); delay(3000); durum=0; altDurum=0; giris=""; anaMenu(); return;
      }
    }
  }
}
