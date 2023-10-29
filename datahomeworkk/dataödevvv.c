#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struct for student information
struct Student {
    int number;
    char name[50];
    int age;
};

// Struct for the linked list node
struct Node {
    struct Student student;
    struct Node* next;
};

// Function to add odd numbers to the beginning and even numbers to the end
struct Node* addToLinkedList(struct Node* head) {
    int number;
    struct Node* newNode;
    
    while (1) {
        printf("Enter a number (-1 to stop): ");
        scanf("%d", &number);
        if (number == -1) break;
        
        newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->student.number = number;
        newNode->next = NULL;

        if (number % 2 == 1) {
            newNode->next = head;
            head = newNode;
        } else {
            if (head == NULL) {
                head = newNode;
            } else {
                struct Node* temp = head;
                while (temp->next != NULL) {
                    temp = temp->next;
                }
                temp->next = newNode;
            }
        }
    }

    return head;
}

// Function to add 100 randomly generated numbers to the list
struct Node* addRandomNumbers(struct Node* head) {
    for (int i = 0; i < 100; i++) {
        int randomNum = rand() % 1000;
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->student.number = randomNum;
        newNode->next = NULL;

        if (head == NULL) {
            head = newNode;
        } else {
            struct Node* temp = head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }
    return head;
}

// Function to sort the list from largest to smallest
struct Node* sortList(struct Node* head) {
    struct Node* current = head;
    struct Node* nextNode;
    int temp;

    if (head == NULL) {
        return head;
    }

    while (current != NULL) {
        nextNode = current->next;

        while (nextNode != NULL) {
            if (current->student.number < nextNode->student.number) {
                temp = current->student.number;
                current->student.number = nextNode->student.number;
                nextNode->student.number = temp;
            }
            nextNode = nextNode->next;
        }
        current = current->next;
    }

    return head;
}

// Function to display the student list and count
void displayStudents(struct Node* head) {
    struct Node* current = head;
    int count = 0;

    printf("Student List:\n");
    while (current != NULL) {
        printf("%d - %s %d %d\n", current->student.number, current->student.name, current->student.age, count + 1);
        current = current->next;
        count++;
    }
    printf("Total students: %d\n", count);
}

// Function to search for a student by name
struct Node* searchByName(struct Node* head, const char* name) {
    struct Node* current = head;
    while (current != NULL) {
        if (strcmp(current->student.name, name) == 0) {
            printf("Student found: %d - %s %d\n", current->student.number, current->student.name, current->student.age);
            return current;
        }
        current = current->next;
    }
    printf("Student not found.\n");
    return NULL;
}

// Function to delete the next node from the node with the searched student name
void deleteNextNode(struct Node* head, const char* name) {
    struct Node* current = head;
    while (current != NULL) {
        if (strcmp(current->student.name, name) == 0) {
            if (current->next != NULL) {
                struct Node* temp = current->next;
                current->next = current->next->next;
                free(temp);
                printf("Next student deleted.\n");
                return;
            } else {
                printf("No next student to delete.\n");
                return;
            }
        }
        current = current->next;
    }
    printf("Student not found.\n");
}

// Function to find the record with the longest name
void findLongestName(struct Node* head) {
    struct Node* current = head;
    int maxLength = 0;
    char longestName[50] = "";

    while (current != NULL) {
        int nameLength = strlen(current->student.name);
        if (nameLength > maxLength) {
            maxLength = nameLength;
            strcpy(longestName, current->student.name);
        }
        current = current->next;
    }

    if (maxLength > 0) {
        printf("The longest name in the list: %s\n", longestName);
        printf("Length: %d\n", maxLength);
    } else {
        printf("No student records found.\n");
    }
}

int main() {
    struct Node* head = NULL;
    int choice;
    char name[50];
    
    while (1) {
        printf("\nMenu:\n");
        printf("1. Add odd and even numbers to the list\n");
        printf("2. Add 100 random numbers to the list\n");
        printf("3. Sort the list from largest to smallest\n");
        printf("4. Display student list and count\n");
        printf("5. Search for a student by name\n");
        printf("6. Delete next student with searched name\n");
        printf("7. Find the longest name in the list\n");
        printf("8. Quit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                head = addToLinkedList(head);
                break;
            case 2:
                head = addRandomNumbers(head);
                break;
            case 3:
                head = sortList(head);
                break;
            case 4:
                displayStudents(head);
                break;
            case 5:
                printf("Enter the name to search: ");
                scanf("%s", name);
                searchByName(head, name);
                break;
            case 6:
                printf("Enter the name to search for deletion: ");
                scanf("%s", name);
                deleteNextNode(head, name);
                break;
            case 7:
                findLongestName(head);
                break;
            case 8:
                // Free memory and exit
                while (head != NULL) {
                    struct Node* temp = head;
                    head = head->next;
                    free(temp);
                }
                exit(0);
            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}

