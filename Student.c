#include <stdio.h>
#include <stdlib.h>

#define BUCKET_SIZE 10

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct HashTable {
    Node* buckets[BUCKET_SIZE];
} HashTable;

unsigned int mi_Mod(int x) {
    return x % BUCKET_SIZE;
}

void insert(HashTable* hashTable, int x) {
    unsigned int hashValue = mi_Mod(x);
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = x;
    newNode->next = NULL;

    if (hashTable->buckets[hashValue] == NULL) {
        hashTable->buckets[hashValue] = newNode;
    } else {
        Node* currentNode = hashTable->buckets[hashValue];
        while (currentNode->next != NULL) {
            currentNode = currentNode->next;
        }
        currentNode->next = newNode;
    }
}

void delete(HashTable* hashTable, int x) {
    unsigned int hashValue = mi_Mod(x);
    Node* currentNode = hashTable->buckets[hashValue];
    Node* prevNode = NULL;

    while (currentNode != NULL) {
        if (currentNode->data == x) {
            if (prevNode == NULL) {
                hashTable->buckets[hashValue] = currentNode->next;
            } else {
                prevNode->next = currentNode->next;
            }
            free(currentNode);
            return;
        }
        prevNode = currentNode;
        currentNode = currentNode->next;
    }
}

Node* find(HashTable* hashTable, int x) {
    unsigned int hashValue = mi_Mod(x);
    Node* currentNode = hashTable->buckets[hashValue];

    while (currentNode != NULL) {
        if (currentNode->data == x) {
            return currentNode;
        }
        currentNode = currentNode->next;
    }

    return NULL;
}

int main() {
    HashTable hashTable;
    for (int i = 0; i < BUCKET_SIZE; i++) {
        hashTable.buckets[i] = NULL;
    }

    insert(&hashTable, 52);
    insert(&hashTable, 3235235);

    printf("%d\n", mi_Mod(52));
    printf("%d\n", mi_Mod(3235235));

    Node* foundNode = find(&hashTable, 52);
    if (foundNode != NULL) {
        printf("Element found: %d\n", foundNode->data);
    } else {
        printf("Element not found\n");
    }

    delete(&hashTable, 52);

    foundNode = find(&hashTable, 52);
    if (foundNode != NULL) {
        printf("Element found: %d\n", foundNode->data);
    } else {
        printf("Element not found\n");
    }

    return 0;
}
