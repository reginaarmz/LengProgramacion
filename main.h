#include #include #include
#define MAX_LINE_LENGTH 100

// Node structure for the linked list
typedef struct Node {
char *ruleIdentifier;
char *production;
struct Node *next;
} Node;

Node* createNode(const char *ruleIdentifier, const char *production);
void appendNode(Node **head, const char *ruleIdentifier, const char *production);
void freeLinkedList(Node *head);
Node* createLinkedList(FILE *file);
void printList(Node *head);
