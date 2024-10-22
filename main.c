#include "main.h"

// Function to create a new node
Node* createNode(const char *ruleIdentifier, const char *production) {
Node *newNode = (Node *)malloc(sizeof(Node));
newNode->ruleIdentifier = strdup(ruleIdentifier); // Store rule identifier
newNode->production = strdup(production); // Store production
newNode->next = NULL;
return newNode;
}

// Function to append a node to the linked list
void appendNode(Node **head, const char *ruleIdentifier, const char *production) {
Node *newNode = createNode(ruleIdentifier, production);
if (*head == NULL) {
*head = newNode;
} else {
Node *temp = *head;
while (temp->next != NULL) {
temp = temp->next;
}
temp->next = newNode;
}
}

// Function to free the linked list
void freeLinkedList(Node *head) {
Node *current = head;
Node *nextNode;
while (current != NULL) {
nextNode = current->next;
free(current->ruleIdentifier); // Free the rule identifier string
free(current->production); // Free the production string
free(current); // Free the node
current = nextNode;
}
}

// Function to create a linked list from the file
Node* createLinkedList(FILE *file) {
Node *head = NULL; // Head of the linked list
char line[MAX_LINE_LENGTH];
char ruleIdentifier[MAX_LINE_LENGTH];
char production[MAX_LINE_LENGTH];

// Read the file line by line and store each line in a new node
while (fgets(line, sizeof(line), file)) {
// Remove the newline character if present
line[strcspn(line, "\n")] = '\0';

// Append the split line to the linked list
// appendNode(&head, ruleIdentifier, production);
appendNode(&head, "", line);
}

return head;
}

// Function to print the linked list
void printList(Node *head) {
Node *current = head;
while (current != NULL) {
printf("Identifier: %s, Production: %s\n", current->ruleIdentifier, current->production);
current = current->next;
}
}

int main() {
FILE *file = fopen("gramatica1.txt", "r");
if (file == NULL) {
perror("Error opening file");
return 1;
}

Node *head = createLinkedList(file);

fclose(file);

// Output the contents of the linked list
printList(head);

// Free the linked list
freeLinkedList(head);

return 0;
}
