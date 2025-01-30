#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "stack.h"
#include "list.h"

int precedence(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 0;
    }
}


Node* infixToPostfix(char* infix) {
    Stack opStack;
    initStack(&opStack);
    Node* postfixList = NULL;
    Node* tail = NULL;

    for (int i = 0; infix[i] != '\0'; i++) {
        char ch = infix[i];


        if (isdigit(ch)) {
            Node* newNode = createNode(ch - '0');
            if (postfixList == NULL) {
                postfixList = newNode;
                tail = newNode;
            } else {
                tail->next = newNode;
                tail = newNode;
            }
        }

        else if (ch == '(') {
            push(&opStack, ch);
        }

        else if (ch == ')') {
            while (!is_empty(&opStack) && peek(&opStack) != '(') {
                Node* newNode = createNode(pop(&opStack));
                tail->next = newNode;
                tail = newNode;
            }
            pop(&opStack);
        }

        else {
            while (!is_empty(&opStack) && precedence(peek(&opStack)) >= precedence(ch)) {
                Node* newNode = createNode(pop(&opStack));
                tail->next = newNode;
                tail = newNode;
            }
            push(&opStack, ch);
        }
    }


    while (!is_empty(&opStack)) {
        Node* newNode = createNode(pop(&opStack));
        tail->next = newNode;
        tail = newNode;
    }

    return postfixList;
}


int evaluatePostfix(Node* postfixList) {
    Stack evalStack;
    initStack(&evalStack);

    Node* current = postfixList;
    while (current != NULL) {
        if (current->value >= 0 && current->value <= 9) {
            push(&evalStack, current->value + '0');
        } else {
            int val2 = pop(&evalStack) - '0';
            int val1 = pop(&evalStack) - '0';
            switch (current->value) {
                case '+':
                    push(&evalStack, (val1 + val2) + '0');
                    break;
                case '-':
                    push(&evalStack, (val1 - val2) + '0');
                    break;
                case '*':
                    push(&evalStack, (val1 * val2) + '0');
                    break;
                case '/':
                    push(&evalStack, (val1 / val2) + '0');
                    break;
            }
        }
        current = current->next;
    }

    return pop(&evalStack) - '0';
}


int main() {
    char infix[100];
    printf("Enter an infix expression: ");
    scanf("%s", infix);


    Node* postfixList = infixToPostfix(infix);


    int result = evaluatePostfix(postfixList);
    printf("Result: %d\n", result);


    Node* current = postfixList;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }

    return 0;
}
