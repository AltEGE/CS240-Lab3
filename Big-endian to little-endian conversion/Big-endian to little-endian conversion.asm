lui x8, 703710 # t0 = 0x300, using addi to set the base address of the data
addi x8, x8, 291
sw x8, 0(x0)

lui x5 0 # t0'a üst 20 bit olarak 0x0 yükler
addi x5 x5 768 # t0'a 0x300 ekler, böylece t0 şimdi 0x300 adresini gösterir
addi x6 x0 8
lbu x7 0(x5)  # İlk byte
lbu x28 1(x5) # İkinci byte
lbu x29 2(x5) # Üçüncü byte
lbu x30 3(x5) # Dördüncü byte
sb x30 0(x5) # Dördüncü byte'ı ilk byte pozisyonuna sakla
sb x29 1(x5) # Üçüncü byte'ı ikinci byte pozisyonuna sakla
sb x28 2(x5) # İkinci byte'ı üçüncü byte pozisyonuna sakla
sb x7 3(x5) # İlk byte'ı dördüncü byte pozisyonuna sakla
addi x17 x0 93 # exit sistem çağrısının numarası
addi x10 x0 0 # Çıkış kodu olarak 0 kullan
ecall # Sistem çağrısını yap