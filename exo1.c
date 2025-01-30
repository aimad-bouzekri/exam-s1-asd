
#include <stdio.h>
#include <stdlib.h>
#include "list.h"

Node* insertAtPosition(Node* head, int value, int k) {
    if (k < 0) {
        printf("Error: Invalid position.\n");
        return head;
    }

    Node* newNode = createNode(value);
    if (!newNode) {
        printf("Error: Memory allocation failed.\n");
        return head;
    }

    if (k == 0) { // الإدراج في بداية القائمة
        setNext(newNode, head);
        return newNode;
    }

    Node* current = head;
    for (int i = 0; i < k - 1; i++) {
        if (!current) {
            printf("Error: Position out of bounds.\n");
            free(newNode);
            return head;
        }
        current = getNext(current);
    }

    if (!current) {
        printf("Error: Position out of bounds.\n");
        free(newNode);
        return head;
    }

    setNext(newNode, getNext(current));
    setNext(current, newNode);

    return head;
}

Node* createNode(int value) ;




int main(){

Node* head = NULL;
 head = insertAtPosition(head, 10, 0);
 head = insertAtPosition(head, 15, 1);
 head = insertAtPosition(head, 20, 2);
 head = insertAtPosition(head, 25, 3);
 head = insertAtPosition(head, 30, 5);





//print list

  Node* current = head;
    while (current != NULL) {
        printf("| %d |->  ", current->value);
        current = current->next;
    }
    printf("NULL\n");

return 0;}




Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode) {
        setValue(newNode, value); 
        setNext(newNode, NULL);   
    }
    return newNode;
}
