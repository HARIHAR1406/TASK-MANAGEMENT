#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a structure for the task node
typedef struct Task {
    char description[256];
    int completed;
    struct Task *next;
} Task;

// Function prototypes
Task* createTask(const char *description);
void addTask(Task **head, const char *description);
void deleteTask(Task **head, int index);
void markTaskCompleted(Task *head, int index);
void printTasks(const Task *head);
void freeTasks(Task *head);

int main() {
    Task *head = NULL;
    int choice, index;
    char description[256];

    while (1) {
        printf("\nTo-Do List:\n");
        printTasks(head);
        printf("\n1. Add Task\n");
        printf("2. Delete Task\n");
        printf("3. Mark Task as Completed\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume newline character left by scanf

        switch (choice) {
            case 1:
                printf("Enter task description: ");
                fgets(description, sizeof(description), stdin);
                description[strcspn(description, "\n")] = '\0'; // Remove trailing newline
                addTask(&head, description);
                break;
            case 2:
                printf("Enter task index to delete: ");
                scanf("%d", &index);
                deleteTask(&head, index);
                break;
            case 3:
                printf("Enter task index to mark as completed: ");
                scanf("%d", &index);
                markTaskCompleted(head, index);
                break;
            case 4:
                freeTasks(head);
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

// Function to create a new task
Task* createTask(const char *description) {
    Task *newTask = (Task*)malloc(sizeof(Task));
    if (!newTask) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    strcpy(newTask->description, description);
    newTask->completed = 0;
    newTask->next = NULL;
    return newTask;
}

// Function to add a task to the list
void addTask(Task **head, const char *description) {
    Task *newTask = createTask(description);
    newTask->next = *head;
    *head = newTask;
}

// Function to delete a task by index
void deleteTask(Task **head, int index) {
    if (index < 1 || *head == NULL) {
        printf("Invalid index\n");
        return;
    }

    Task *current = *head;
    Task *previous = NULL;

    for (int i = 1; i < index && current != NULL; i++) {
        previous = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Invalid index\n");
        return;
    }

    if (previous == NULL) {
        *head = current->next;
    } else {
        previous->next = current->next;
    }

    free(current);
}

// Function to mark a task as completed by index
void markTaskCompleted(Task *head, int index) {
    if (index < 1) {
        printf("Invalid index\n");
        return;
    }

    Task *current = head;

    for (int i = 1; i < index && current != NULL; i++) {
        current = current->next;
    }

    if (current == NULL) {
        printf("Invalid index\n");
        return;
    }

    current->completed = 1;
}

// Function to print the list of tasks
void printTasks(const Task *head) {
    int index = 1;
    while (head != NULL) {
        printf("%d. [%s] %s\n", index, head->completed ? "X" : " ", head->description);
        head = head->next;
        index++;
    }
}

// Function to free all tasks
void freeTasks(Task *head) {
    Task *tmp;
    while (head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}
