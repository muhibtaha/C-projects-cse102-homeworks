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


