# Profile
- Nama: Veronica Ivana Dewani
- NIM: 26/583110/PT/11281

# Description
Sistem pengendali lengan/keseimbangan robot menggunakan ESP32 yang merespons orientasi spasial. Sistem mengambil data posisi dari sensor IMU BNO055 (melalui protokol komunikasi I2C) dan data gerakan dari sensor PIR. ESP32 kemudian mengirimkan sinyal PWM 50Hz (1000-2000 µs) ke 5 motor servo untuk memproyeksikan ulang pergerakan pada sumbu Roll, Pitch, dan Yaw secara real-time, ditambah override posisi saat mendeteksi gerakan luar.

# Feature Table
| Fitur | Input (Sensor) | Output (Aktuator) | Perilaku |
| :--- | :--- | :--- | :--- |
| Roll | BNO055 (X-Axis) | Servo 1 & 2 | Berputar berlawanan arah dari kemiringan bidang. |
| Pitch | BNO055 (Y-Axis) | Servo 3 & 4 | Berputar searah dengan kemiringan bidang. |
| Yaw | BNO055 (Z-Axis) | Servo 5 | Mengikuti arah rotasi. Kembali ke tengah (0°) setelah jeda 1 detik (Non-blocking millis). |
| PIR | PIR Sensor | Semua Servo | Semua servo bergerak serentak ke 45° lalu kembali normal saat tidak ada gerakan. |

# How to Run
1. Buka (https://wokwi.com/projects/480770732830413825)
2. Library yang dibutuhkan adalah `ESP32Servo`.
3. Klik "Start the simulation".
4. Cara memicu input uji:
   - Uji 1 (Roll & Pitch): Ubah nilai variabel `roll_deg` menjadi 30.0 dan `pitch_deg` menjadi -20.0 pada kode, jalankan simulasi, lalu pantau nilai PWM di Serial Monitor.
   - Uji 2 (Yaw Berhenti): Ubah nilai variabel `yaw_deg` pada kode menjadi sudut tertentu (misalnya 45.0) dan jalankan simulasi. Perhatikan Servo 5 yang akan berputar ke arah 45°, lalu karena nilai sudutnya tidak berubah lagi (berhenti), motor akan menahan posisinya selama 1 detik sebelum otomatis berputar kembali ke tengah (0°).
   - Gerakan Eksternal: Klik modul sensor PIR pada layar simulasi, lalu klik tombol "Simulate Motion".