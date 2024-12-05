#include <stdio.h>
#include <stdlib.h>

// Tek yönlü bağlı liste düğümü
struct Node {
    int data;
    struct Node *next;
};

// Listeyi oluştur
struct Node *createList(int n) {
    struct Node *head = NULL, *temp = NULL, *newNode = NULL;
    int data, i;

    for (i = 1; i <= n; i++) {
        printf("Enter data for node %d: ", i);
        scanf("%d", &data);

        newNode = (struct Node *)malloc(sizeof(struct Node));
        newNode->data = data;
        newNode->next = NULL;

        if (head == NULL) {
            head = newNode;
        } else {
            temp->next = newNode;
        }
        temp = newNode;
    }
    return head;
}

// Listeye yeni düğüm ekle
void append(struct Node **head, int data) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    struct Node *temp = *head;

    newNode->data = data;
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
        return;
    }

    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

// Belirtilen değeri sil
void deleteValue(struct Node **head, int value) {
    struct Node *temp = *head, *prev = NULL;

    while (temp != NULL && temp->data != value) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Value %d not found in the list.\n", value);
        return;
    }

    if (prev == NULL) {
        *head = temp->next;
    } else {
        prev->next = temp->next;
    }

    free(temp);
}

// Liste başına yeni düğüm ekle
void prepend(struct Node **head, int data) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = *head;
    *head = newNode;
}

// Listeyi yazdır
void displayList(struct Node *head) {
    struct Node *temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

int main() {
    struct Node *head = NULL;

    head = createList(3);
    displayList(head);

    append(&head, 50);
    displayList(head);

    prepend(&head, 25);
    displayList(head);

    deleteValue(&head, 50);
    displayList(head);

    return 0;
}


#include <stdio.h>
#include <stdlib.h>

// Çift yönlü bağlı liste düğümü
struct Node {
    int data;
    struct Node *next;
    struct Node *prev;
};

// Listeyi oluştur
struct Node *createList(int n) {
    struct Node *head = NULL, *temp = NULL, *newNode = NULL;
    int data, i;

    for (i = 1; i <= n; i++) {
        printf("Enter data for node %d: ", i);
        scanf("%d", &data);

        newNode = (struct Node *)malloc(sizeof(struct Node));
        newNode->data = data;
        newNode->next = NULL;
        newNode->prev = temp;

        if (head == NULL) {
            head = newNode;
        } else {
            temp->next = newNode;
        }
        temp = newNode;
    }
    return head;
}

// Liste başına yeni düğüm ekle
void prepend(struct Node **head, int data) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = *head;
    newNode->prev = NULL;

    if (*head != NULL) {
        (*head)->prev = newNode;
    }
    *head = newNode;
}

// Liste sonuna yeni düğüm ekle
void append(struct Node **head, int data) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    struct Node *temp = *head;

    newNode->data = data;
    newNode->next = NULL;

    if (*head == NULL) {
        newNode->prev = NULL;
        *head = newNode;
        return;
    }

    while (temp->next != NULL) {
        temp = temp->next;
    }

    temp->next = newNode;
    newNode->prev = temp;
}

// Belirtilen değeri sil
void deleteValue(struct Node **head, int value) {
    struct Node *temp = *head;

    while (temp != NULL && temp->data != value) {
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Value %d not found.\n", value);
        return;
    }

    if (temp->prev != NULL) {
        temp->prev->next = temp->next;
    } else {
        *head = temp->next;
    }

    if (temp->next != NULL) {
        temp->next->prev = temp->prev;
    }

    free(temp);
}

// Listeyi yazdır
void displayList(struct Node *head) {
    struct Node *temp = head;
    while (temp != NULL) {
        printf("%d <-> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

int main() {
    struct Node *head = NULL;

    head = createList(3);
    displayList(head);

    append(&head, 50);
    displayList(head);

    prepend(&head, 25);
    displayList(head);

    deleteValue(&head, 50);
    displayList(head);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>

// Döngüsel bağlı liste düğümü
struct Node {
    int data;
    struct Node *next;
};

// Listeyi oluştur
struct Node *createList(int n) {
    struct Node *head = NULL, *temp = NULL, *newNode = NULL;
    int data, i;

    for (i = 1; i <= n; i++) {
        printf("Enter data for node %d: ", i);
        scanf("%d", &data);

        newNode = (struct Node *)malloc(sizeof(struct Node));
        newNode->data = data;

        if (head == NULL) {
            head = newNode;
            newNode->next = head;
        } else {
            temp->next = newNode;
            newNode->next = head;
        }
        temp = newNode;
    }
    return head;
}

// Listeyi yazdır
void displayList(struct Node *head) {
    struct Node *temp = head;

    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }

    do {
        printf("%d -> ", temp->data);
        temp = temp->next;
    } while (temp != head);

    printf("(HEAD)\n");
}

int main() {
    struct Node *head = NULL;

    head = createList(3);
    displayList(head);

    return 0;
}


#include <stdio.h>
#include <string.h>

// Bir kişiyi temsil eden struct
struct Person {
    int id;
    char name[50];
    int age;
};

// Kişileri listelemek için fonksiyon
void displayPersons(struct Person persons[], int size) {
    printf("Remaining Persons:\n");
    for (int i = 0; i < size; i++) {
        printf("ID: %d, Name: %s, Age: %d\n", persons[i].id, persons[i].name, persons[i].age);
    }
}



int main() {
    // Struct dizisiyle kişiler oluştur
    struct Person persons[3] = {
        {1, "Alice", 25},
        {2, "Bob", 30},
        {3, "Charlie", 35}
    };

    int size = 3; // Mevcut kişi sayısı
    int deleteId = 2; // Silinecek kişinin ID'si

    printf("Before Deletion:\n");
    displayPersons(persons, size);

    // ID'si 2 olan kişiyi sil
    for (int i = 0; i < size; i++) {
        if (persons[i].id == deleteId) {
            // Kalan elemanları sola kaydır
            for (int j = i; j < size - 1; j++) {
                persons[j] = persons[j + 1];
            }
            size--; // Boyutu bir azalt
            break;
        }
    }

    printf("\nAfter Deletion:\n");
    displayPersons(persons, size);

    return 0;
}

//son node eyi silmek
void deleteLastNode(struct Node **head) {
    // Eğer liste boşsa
    if (*head == NULL) {
        printf("The list is already empty.\n");
        return;
    }

    struct Node *temp = *head;  // Liste başını işaret eder
    struct Node *prev = NULL;   // Sondan bir önceki düğüm için

    // Tek bir düğüm varsa
    if (temp->next == NULL) {
        free(temp);    // Tek düğümü serbest bırak
        *head = NULL;  // Listeyi boş yap
        return;
    }

    // Son düğüme kadar ilerle
    while (temp->next != NULL) {
        prev = temp;       // Sondan bir önceki düğümü işaret et
        temp = temp->next; // Son düğüme geç
    }

    prev->next = NULL; // Sondan bir önceki düğümü "son düğüm" yap
    free(temp);        // Belleği serbest bırak
}



