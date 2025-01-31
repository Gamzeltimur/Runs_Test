#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// --- EXTERNS.H İÇERİĞİ BURAYA EKLENDİ ---
#ifndef EXTERNS_H
#define EXTERNS_H

typedef unsigned char BitSequence;

#define ALPHA 0.01
#define TEST_RUNS 3
#define NUMOFTESTS 15
#define NUMOFGENERATORS 10

typedef struct {
    int param;
} TP;

BitSequence	*epsilon;
TP tp;

#endif
// --- EXTERNS.H İÇERİĞİ BURADA BİTTİ ---

// --- CEPHES FONKSİYONLARI ---
double erfc(double x) {
    return 1.0 - erf(x);
}

int isNegative(double p_value) {
    return (p_value < 0.0);
}

int isGreaterThanOne(double p_value) {
    return (p_value > 1.0);
}

// --- RUNS TEST ---
void Runs(int n)
{
    int		S, k;
    double	pi, V, erfc_arg, p_value;

    S = 0;
    for ( k=0; k<n; k++ )
        if ( epsilon[k] )
            S++;
    pi = (double)S / (double)n;

    if ( fabs(pi - 0.5) > (2.0 / sqrt(n)) ) {
        printf("\nRUNS TEST\n");
        printf("------------------------------------------\n");
        printf("PI ESTIMATOR CRITERIA NOT MET! PI = %f\n", pi);
        p_value = 0.0;
    }
    else {
        V = 1;
        for ( k=1; k<n; k++ )
            if ( epsilon[k] != epsilon[k-1] )
                V++;

        erfc_arg = fabs(V - 2.0 * n * pi * (1-pi)) / (2.0 * pi * (1-pi) * sqrt(2*n));
        p_value = erfc(erfc_arg);

        printf("\nRUNS TEST\n");
        printf("------------------------------------------\n");
        printf("COMPUTATIONAL INFORMATION:\n");
        printf("------------------------------------------\n");
        printf("(a) Pi                        = %f\n", pi);
        printf("(b) V_n_obs (Total # of runs) = %d\n", (int)V);
        printf("(c) V_n_obs - 2 n pi (1-pi)\n");
        printf("    -----------------------   = %f\n", erfc_arg);
        printf("      2 sqrt(2n) pi (1-pi)\n");
        printf("------------------------------------------\n");
        if ( isNegative(p_value) || isGreaterThanOne(p_value) )
            printf("WARNING:  P_VALUE IS OUT OF RANGE.\n");

        printf("%s\t\tp_value = %f\n\n", p_value < ALPHA ? "FAILURE" : "SUCCESS", p_value);
    }
}

// --- ANA PROGRAM: SENİN 5 ADET 100 BİTLİK DİZİN İLE ---
int main() {
    // Senin verdiğin 5 adet 100 bitlik diziler
    char *bitStrings[] = {
        "0001100110011010000001110011001011101100101101110011111111110001100010010111100010100111100101001101",
        "1101100111111110010011110101011011101000110000011001111111100010110010000000000000101001000000011010",
        "0111001000100101000011111011100100100100010010100001111110101100000011001001111011010111000001110010",
        "1111011000011011110010100011110010100010110100100000110001000110011010001011010110010111010111000010",
        "0010110010001000101111000100000010010010001110001100111010100100011101000000000011101101101011110000"
    };

    for (int numLines = 0; numLines < 5; numLines++) {
        char *bitString = bitStrings[numLines];
        int n = strlen(bitString);

        epsilon = (BitSequence*)malloc(n * sizeof(BitSequence));
        if (epsilon == NULL) {
            printf("Hata: Bellek tahsis edilemedi!\n");
            return 1;
        }

        for (int i = 0; i < n; i++) {
            if (bitString[i] == '0' || bitString[i] == '1') {
                epsilon[i] = bitString[i] - '0';
            } else {
                printf("Hata: Satır %d geçersiz karakter içeriyor!\n", numLines + 1);
                free(epsilon); // Bellek serbest bırakılıyor
                epsilon = NULL;
                continue;
            }
        }

        printf("\nSatır %d: %s\n", numLines + 1, bitString);
        Runs(n);

        free(epsilon); // Belleği serbest bırak
        epsilon = NULL; // İşaretçiyi NULL yaparak hataları önle
    }

    return 0;
}
