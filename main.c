#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Structure to represent the stack */
struct node;
typedef struct node *ptr;
typedef ptr stack;
struct node {
    char statement[100];
    ptr next;
};

/* Explanation of all functions under the main function */

void removeSpaces(char string[]);

stack createStack();

void push(stack ourStack, char data[]);

void pop(stack ourStack);

int isEmpty(stack ourStack);

char *top(stack ourStack);

void display(stack ourStack);

void saveToFile(FILE *output, stack ourStack);

int main() {
    char singularStatement[100];
    char command[100];
    FILE *output;
    printf("MyCommand >");
    /* Read the statement from the user */
    gets(singularStatement);
    /* Create the stacks we will use */
    stack statements = createStack();
    stack deletedStatements = createStack();
    /* Removing spaces from the entered word in case
     * the user accidentally entered spaces with it
     * (especially for commands) */
    strcpy(command, singularStatement);
    removeSpaces(command);
    /* As long as the user did not enter "quit", the program continues
     * to read the entered statements from the user */
    while (strcasecmp(command, "quit") != 0) {
        /* If the user entered "undo", delete the last statement entered */
        if (strcasecmp(command, "undo") == 0) {
            /* Save the last item in another stack in case we want to retrieval it */
            push(deletedStatements, top(statements));
            /* Delete it from the primary stack */
            pop(statements);
            if (!isEmpty(statements))
                printf("result >\n");
            else
                printf("EMPTY\n");
            /* Print the text on the screen */
            display(statements);
            /* If the user entered "redo", retrieval the last statement deleted */
        } else if (strcasecmp(command, "redo") == 0) {
            /* retrieval the statement and add it to the primary stack */
            push(statements, top(deletedStatements));
            /* Delete it from the other stack */
            pop(deletedStatements);
            if (!isEmpty(deletedStatements))
                printf("result >\n");
            /* Print the text on the screen */
            display(statements);
            /* If the user entered "print", display the stack elements in the way he entered it */
        } else if (strcasecmp(command, "print") == 0) {
            display(statements);
            /* If the user entered "save", save the stack elements in the way he entered it in the output file */
        } else if (strcasecmp(command, "save") == 0) {
            output = fopen("C:\\Users\\HP\\CLionProjects\\Project2\\output.txt", "w");
            saveToFile(output, statements);
            fclose(output);
            printf("The text was saved successfully ^-^\n");
            /* Except for the above, read the sentence and add it to the primary stack and so on*/
        } else {
            push(statements, singularStatement);
        }
        printf("MyCommand >");
        gets(singularStatement);
        strcpy(command, singularStatement);
        removeSpaces(command);
    }
    /* After exiting the program, the entered text is saved in the output file */
    output = fopen("C:\\Users\\HP\\CLionProjects\\Project2\\output.txt", "w");
    saveToFile(output, statements);
    fclose(output);
    printf("result > Good Bye! ^-^");
    return 0;
}

/* Removing blank spaces from the word */
void removeSpaces(char string[]) {
    char newString[strlen(string)];
    int i, j;
    /* Go on all the characters in the string and
     * add them to the new string, unless there
     * are spaces */
    for (i = 0, j = 0; i < strlen(string); i++) {
        if (string[i] != ' ') {
            newString[j] = string[i];
            j++;
        }
    }
    newString[j] = '\0';
    strcpy(string, newString);
}

/* Create empty stack */
stack createStack() {
    stack newStack;
    /* Allocate a block of memory for the new stack */
    newStack = (stack) malloc(sizeof(struct node));
    if (newStack == NULL) {
        printf("MEMORY IS FULL!");
        exit(0); /* The program is terminated if the memory is full */
    }
    /* New stack is pointing at NULL */
    newStack->next = NULL;
    return newStack;
}

/* Inserts a new items at the top of stack */
void push(stack ourStack, char data[]) {
    ptr temp = (ptr) malloc(sizeof(struct node));
    /* When the stack is completely full, the program will terminate (Overflow condition) */
    if (temp == NULL) {
        printf("THE STACK IS FULL!\n");
        exit(0);
    }
    /* Copy the entered data to the stack */
    strcpy(temp->statement, data);
    /* Make the node at the top of the stack */
    temp->next = ourStack->next;
    ourStack->next = temp;
}

/* Remove the last item entered to the stack */
void pop(stack ourStack) {
    ptr toDelete;
    /* When the stack is empty, the program will terminate (Underflow condition) */
    if (isEmpty(ourStack) == 1) {
        printf("THE STACK IS EMPTY!\n");
        exit(0);
    }
    toDelete = ourStack->next;
    ourStack->next = (ourStack->next)->next;
    free(toDelete); /* The item has been removed ^-^ */
}

/* Return the top element of the stack */
char *top(stack ourStack) {
    /* When the stack is empty, the program will terminate (Underflow condition) */
    if (isEmpty(ourStack) == 1) {
        printf("THE STACK IS EMPTY!\n");
        exit(0);
    } else
        return ourStack->next->statement;
}

/* Check if stack is empty or not */
int isEmpty(stack ourStack) {
    if (ourStack->next == NULL)
        return 1;
    else
        return 0;
}

/* Display the elements of the stack in the sequence they were entered */
void display(stack ourStack) {
    ptr temp = ourStack->next;
    stack reversedStatements = createStack();
    /* Reverse the stack by storing its items in another stack */
    while (temp != NULL) {
        push(reversedStatements, temp->statement);
        temp = temp->next;
    }
    ptr temp2 = reversedStatements->next;
    /* Print the elements of stack as they entered */
    while (temp2 != NULL) {
        printf("%s\n", temp2->statement);
        temp2 = temp2->next;
    }
}

/* Save the stack's element in a text file in the sequence they were entered */
void saveToFile(FILE *output, stack ourStack) {
    ptr temp = ourStack->next;
    stack reversedStatements = createStack();
    /* Reverse the stack by storing its items in another stack */
    while (temp != NULL) {
        push(reversedStatements, temp->statement);
        temp = temp->next;
    }
    ptr temp2 = reversedStatements->next;
    /* Print the elements of stack in the file as they entered */
    while (temp2 != NULL) {
        fprintf(output, "%s\n", temp2->statement);
        temp2 = temp2->next;
    }
}
