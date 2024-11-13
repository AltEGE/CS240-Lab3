addi x2 x2 -16 # Stack için yer ayır
sw x1 12(x2) # Dönüş adresini kaydet
addi x7 x0 2
addi x5 x0 0 # İlk Fibonacci sayısı, Fib(0)
addi x6 x0 1 # İkinci Fibonacci sayısı, Fib(1)
addi x11 x0 2
blt x7 x11 32 # Eğer n < 2 ise, doğrudan sonuca git
addi x11 x0 10
blt x7 x11 4 # Eğer n < 10 ise, hesaplama için devam et
add x29 x5 x6 # Bir sonraki Fibonacci sayısını hesapla
addi x5 x6 0 # Değerleri güncelle
addi x6 x29 0	
addi x7 x7 1 # Sayacı arttır								
blt x7 x11 -16 # Sayac a1'den küçükse döngüye devam et
beq x7 x0 8	 # Eğer n == 0 ise t0 doğru sonuçtur
addi x10 x6 0 # Aksi takdirde son Fibonacci sayısı t1'dedir
lw x1 12(x2) # Dönüş adresini yükle		
addi x2 x2 16	# Stack'ten ayrılan yeri serbest bırak
addi x17 x0 93 # exit sistem çağrısının numarası
addi x10 x0 0 # Çıkış durumu kodu
ecall # Sistem çağrısını gerçekleştir
