# Arduino Math Tool (LCD + Keypad)

Bu proje **Arduino UNO**, **16x2 I2C LCD** ve **4x4 Keypad** kullanarak yapılmış çok fonksiyonlu bir matematik aracıdır.

Projede şu özellikler bulunmaktadır:

* Bölünebilme kontrolü (çıkarmalı kural)
* Asal sayı kontrolü
* EBOB / EKOK hesaplama
* Hesap makinesi (+, -, *, /)

Sistem tamamen **menü tabanlıdır** ve keypad ile kontrol edilir.

---

# Donanım

Gerekli parçalar:

* Arduino UNO
* 16x2 I2C LCD
* 4x4 Keypad
* Jumper kablolar

---

# Bağlantılar

## I2C LCD

| LCD | Arduino |
| --- | ------- |
| VCC | 5V      |
| GND | GND     |
| SDA | A4      |
| SCL | A5      |

## Keypad

| Keypad Pin | Arduino |
| ---------- | ------- |
| 1          | A0      |
| 2          | A1      |
| 3          | A2      |
| 4          | A3      |
| 5          | 4       |
| 6          | 5       |
| 7          | 6       |
| 8          | 7       |

---

# Tuş Dizilimi

```
1 2 3 A
4 5 6 B
7 8 9 C
* 0 # D
```

---

# Menü Sistemi

## Ana Menü

| Tuş | Fonksiyon      |
| --- | -------------- |
| A   | Bölünebilme    |
| B   | Asal Sayı      |
| C   | EBOB / EKOK    |
| D   | Hesap Makinesi |

---

# Bölünebilme

Kullanıcı iki sayı girer:

1. Sayı
2. Bölen

Program **çıkarmalı kuralı** kullanarak:

* En yakın katı bulur
* Farkı hesaplar
* Sonucu gösterir

LCD'de işlem adımları gösterilir.

---

# Asal Sayı

Kullanıcı bir sayı girer.

Program sayının:

* **Asal**
* **Asal Degil**

olduğunu gösterir.

---

# EBOB / EKOK

C tuşuna basınca iki seçenek çıkar:

| Tuş | İşlem |
| --- | ----- |
| A   | EKOK  |
| B   | EBOB  |

Kullanıcı iki sayı girer ve sonuç hesaplanır.

---

# Hesap Makinesi

D tuşuna basınca hesap makinesi açılır.

| Tuş | İşlem |
| --- | ----- |
| A   | +     |
| B   | -     |
| C   | *     |
| D   | /     |

Kullanım:

1. İlk sayıyı gir
2. `#` ile onayla
3. İkinci sayıyı gir
4. `#` ile sonucu hesapla

---

# Özel Tuşlar

| Tuş | İşlev |
| --- | ----- |
| *   | Sil   |
| #   | Onay  |

---

# Özellikler

* 16 basamak sayı girişi
* Menü tabanlı sistem
* LCD'de işlem gösterimi
* Sıfıra bölme kontrolü
* LCD uyumlu karakterler (Türkçe karakter kullanılmaz)

---

# Kullanılan Kütüphaneler

* Wire
* LiquidCrystal_I2C
* Keypad

---

# Amaç

Bu proje:

* Arduino öğrenmek
* Matematik algoritmalarını uygulamak
* LCD ve Keypad kullanımını öğrenmek

amacıyla yapılmıştır.

---

# Lisans

Bu proje eğitim amaçlıdır.
