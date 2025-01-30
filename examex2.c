#include <stdio.h>
#include <stdlib.h>
#include "list.h"


Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode) {
        newNode->value = value;
        newNode->next = NULL;
        newNode->prev = NULL;
    }
    return newNode;
}





Node* getPrev(Node* node) {
    if (node == NULL) {
        return NULL;
    }
    return node->prev;
}

void setPrev(Node* node, Node* prevNode) {
    if (node == NULL) {
        return;
    }
    node->prev = prevNode;
}


Node* reverseDoublyLinkedL(Node* head) {
    Node* temp = NULL;
    Node* current = head;


    while (current != NULL) {
        temp = getPrev(current);
        setPrev(current, getNext(current));
        setNext(current, temp);
        current = getPrev(current);
    }


    if (temp != NULL) {
        head = getPrev(temp);
    }

    return head;
}


void printList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("%d <-> ", current->value);
        current = getNext(current);
    }
    printf("NULL\n");
}


int main() {
    Node* head = NULL;


    head = createNode(10);
    setNext(head, createNode(20));
    setPrev(getNext(head), head);
    setNext(getNext(head), createNode(30));
    setPrev(getNext(getNext(head)), getNext(head));


    printf("list :\n");
    printList(head);


    head = reverseDoublyLinkedL(head);


    printf("rversed list :\n");
    printList(head);


    return 0;
}
