import random

def generate_random_bits(length):
    """Belirtilen uzunlukta rastgele 0 ve 1'lerden oluşan bit dizisi üretir"""
    return ''.join(str(random.randint(0, 1)) for _ in range(length))

# Kaç tane dizi üretileceği ve her bir dizinin uzunluğu
num_sequences = 5  # 5 adet dizi
sequence_length = 100  # Her bir dizinin uzunluğu 100 bit

# Rastgele bit dizilerini üret ve ekrana yazdır
random_bit_sequences = [generate_random_bits(sequence_length) for _ in range(num_sequences)]

# Dosyaya yazma işlemi
with open("random_bit_sequences.txt", "w") as f:
    for i, bit_sequence in enumerate(random_bit_sequences):
        f.write(bit_sequence + "\n")
        print(f"Üretilen {i+1}. bit dizisi: {bit_sequence}")

print("\nTüm rastgele bit dizileri 'random_bit_sequences.txt' dosyasına kaydedildi.")
