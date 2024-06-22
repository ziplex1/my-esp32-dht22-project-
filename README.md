# Proyek ESP32 DHT22 dengan HTTP POST

Proyek ini menggunakan ESP32 untuk membaca data dari sensor DHT22 dan mengirimkannya ke server lokal melalui HTTP POST.

## Rangkaian

- **ESP32** ke **DHT22**:
  - VCC ke 3.3V
  - GND ke GND
  - Data ke GPIO 15

## Kode

### ESP32

File: `ESP32.ino`

### Server

File: `server.py`

## Cara Menggunakan

1. Sambungkan ESP32 ke komputer dan unggah `ESP32.ino` menggunakan Arduino IDE.
2. Jalankan `server.py` di komputer Anda dengan Python.
3. ESP32 akan mengirimkan data suhu dan kelembapan ke server setiap 10 detik.
