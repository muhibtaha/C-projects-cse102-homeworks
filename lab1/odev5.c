#include <stdio.h>
#include <stdlib.h>

// Bağlı liste için düğüm yapısı
struct Node {
    int data;
    struct Node *next;
};

// Listeyi normal sırada görüntüleme fonksiyonu
void displayList(struct Node *head) {
    struct Node *temp = head;
    int count = 0;
    printf("Data entered in the list are:\n");
    while (temp != NULL) {
        printf("Data = %d\n", temp->data);
        temp = temp->next;
        count++;
    }
    printf("\nTotal number of nodes = %d\n", count);
}

// Listeyi ters sırada görüntüleme fonksiyonu (rekürsif)
void displayReverse(struct Node *node) {
    if (node == NULL) return;  // Liste sonuna ulaşınca geri dön
    displayReverse(node->next);  // Bir sonraki düğüme geç
    printf("Data = %d\n", node->data);
}

int main() {
    int n, i, data;
    struct Node *head = NULL, *temp, *newNode;

    printf("Input the number of nodes: ");
    scanf("%d", &n);

    // Listeyi oluştur
    for (i = 1; i <= n; i++) {
        printf("Input data for node %d: ", i);
        scanf("%d", &data);

        newNode = (struct Node *)malloc(sizeof(struct Node));  // Yeni düğüm oluştur
        newNode->data = data;
        newNode->next = NULL;

        if (head == NULL) {
            head = newNode;  // İlk düğüm için head belirle
        } else {
            temp->next = newNode;  // Önceki düğümü yeni düğüme bağla
        }
        temp = newNode;  // Son düğümü güncelle
    }

    // Listeyi normal sırada yazdır
    displayList(head);

    // Listeyi ters sırada yazdır
    printf("\nThe list in reverse are:\n");
    displayReverse(head);

    return 0;
}

