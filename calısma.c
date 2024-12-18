#include <stdio.h>
#include <stdlib.h>

// Bağlı liste düğümü yapısı
typedef struct Node {
    int data; // Düğümdeki veri
    struct Node *next; // Bir sonraki düğümün işaretçisi
} tpye;

// Push fonksiyonu: Yeni bir düğüm ekler
void push(tpye **top, int value) {
    tpye *newNode = (tpye *)malloc(sizeof(tpye)); // Yeni düğüm için bellek ayırma
    newNode->data = value; // Yeni düğümün verisini ayarla
    newNode->next = *top; // Yeni düğümün 'next' işaretçisini mevcut 'top' işaretçisine yönlendir
    *top = newNode; // 'top' işaretçisini yeni düğüme yönlendir
}


void pushToEnd(tpye **head, int value) {
    tpye *newNode = (tpye *)malloc(sizeof(tpye));  // Yeni düğüm oluşturuluyor
    newNode->data = value;  // Düğümün verisi ayarlanıyor
    newNode->next = NULL;  // Yeni düğümün 'next' işaretçisi NULL olmalı, çünkü bu son düğüm

    // Eğer liste boşsa, yeni düğüm listenin başı olur
    if (*head == NULL) {
        *head = newNode;
    } else {
        // Eğer liste boş değilse, son düğüme kadar gidip, son düğümün 'next' işaretçisini yeni düğüme yönlendiriyoruz
        tpye *current = *head;
        while (current->next != NULL) {
            current = current->next;  // Sonraki düğüme geç
        }
        current->next = newNode;  // Son düğümün 'next' işaretçisini yeni düğüme yönlendiriyoruz
    }
}

int main() {
    tpye *head = NULL; // Başlangıçta baş düğüm 'NULL'
    
    // Push fonksiyonunu kullanarak verileri ekleyelim
    push(&head, 10); // 10 değerini ekle
    push(&head, 20); // 20 değerini ekle
    push(&head, 30); // 30 değerini ekle

    // Listeyi yazdıralım
    tpye *current = head;
    while (current != NULL) {
        printf("Düğümün verisi: %d\n", current->data);
        current = current->next;
    }

    // Belleği serbest bırakma
    while (head != NULL) {
        tpye *temp = head;
        head = head->next;
        free(temp); // Düğümü serbest bırak
    }

    return 0;
}

