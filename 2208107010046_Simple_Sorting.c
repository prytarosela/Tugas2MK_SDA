#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Bubble Sort
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Pertukaran nilai
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Selection Sort
void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        // Pertukaran nilai
        int temp = arr[i];
        arr[i] = arr[minIndex];
        arr[minIndex] = temp;
    }
}

// Insertion Sort
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// Menyimpan array ke dalam file teks
void saveToFile(int arr[], int n, const char *filename, const char *message) {
    FILE *file = fopen(filename, "a"); // Menggunakan mode "a" untuk menambahkan data ke file yang sudah ada
    if (file != NULL) {
        fprintf(file, "%s\n", message);
        for (int i = 0; i < n; i++) {
            fprintf(file, "%d\n", arr[i]);
        }
        fclose(file);
    } else {
        printf("Gagal membuka file untuk disimpan.\n");
    }
}

int main() {
    // Mengatur seed untuk fungsi rand()
    srand(time(NULL));

    // Jumlah iterasi dan penambahan bilangan setiap iterasi
    int iterations = 10;
    int increment = 100000;

    printf("|--------------------------------------------------------------|\n");
    printf("|Jenis Algoritma      Jumlah Bilangan       Waktu Eksekusi (ms)|\n");
    printf("|--------------------------------------------------------------|\n");

    for (int i = 1; i <= iterations; i++) {
        // Mengalokasikan memori untuk array bilangan
        int maxNumbers = i * increment;
        int *numbers = (int *)malloc(maxNumbers * sizeof(int));

        // Mengisi array dengan bilangan acak
        for (int j = 0; j < maxNumbers; j++) {
            numbers[j] = rand();
        }

        // Salin array sebelum diurutkan untuk disimpan ke file
        int *numbersUnsorted = (int *)malloc(maxNumbers * sizeof(int));
        for (int j = 0; j < maxNumbers; j++) {
            numbersUnsorted[j] = numbers[j];
        }

        // Memulai penghitungan waktu untuk bubble sort
        clock_t startBubble = clock();
        bubbleSort(numbers, maxNumbers);
        clock_t endBubble = clock();
        double bubbleTime = ((double)(endBubble - startBubble)) * 1000 / CLOCKS_PER_SEC;

        // Memulai penghitungan waktu untuk selection sort
        clock_t startSelection = clock();
        selectionSort(numbersUnsorted, maxNumbers); // Menggunakan array yang belum diurutkan
        clock_t endSelection = clock();
        double selectionTime = ((double)(endSelection - startSelection)) * 1000 / CLOCKS_PER_SEC;

        // Memulai penghitungan waktu untuk insertion sort
        clock_t startInsertion = clock();
        insertionSort(numbersUnsorted, maxNumbers); // Menggunakan array yang belum diurutkan
        clock_t endInsertion = clock();
        double insertionTime = ((double)(endInsertion - startInsertion)) * 1000 / CLOCKS_PER_SEC;

        // Menyimpan array yang belum diurutkan dan yang sudah diurutkan ke dalam file
        char filename[100];
        sprintf(filename, "results_%d.txt", maxNumbers);
        saveToFile(numbers, maxNumbers, filename, "Array yang sudah diurutkan (Bubble Sort):");
        saveToFile(numbersUnsorted, maxNumbers, filename, "Array yang belum diurutkan:");

        // Menampilkan hasil evaluasi dalam bentuk tabel
        printf("| Bubble Sort       | %-18d | %13.3f       |\n", maxNumbers, bubbleTime);
        printf("| Selection Sort    | %-18d | %13.3f       |\n", maxNumbers, selectionTime);
        printf("| Insertion Sort    | %-18d | %13.3f       |\n", maxNumbers, insertionTime);
        printf("|--------------------------------------------------------------|\n");

        // Membebaskan memori yang dialokasikan untuk array
        free(numbers); 
        free(numbersUnsorted);
    }

    return 0;
}
