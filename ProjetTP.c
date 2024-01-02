#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

// Declaration of TypeElement
typedef int TypeElm;

// Declaration of a Stack
typedef struct SNode {
    TypeElm Data;
    struct SNode* Next;
} SNode;

typedef SNode* Stack;

// Declaration of a Queue
typedef struct QNode {
    TypeElm Data;
    struct QNode* Next;
} QNode;

typedef struct {
    QNode* Head;
    QNode* Tail;
} Queue;

// Stack operations
void InitStack(Stack* P) {
    *P = NULL;
}

void Push(Stack* P, TypeElm x) {
    SNode* V = malloc(sizeof(SNode));
    V->Data = x;
    V->Next = *P;
    *P = V;
}

void Pop(Stack* P, TypeElm* x) {
    SNode* V = *P;
    *x = V->Data;
    *P = V->Next;
    free(V);
}

int isSEmpty(Stack P) {
    return P == NULL;
}

TypeElm Top(Stack P) {
    return P->Data;
}

// Queue operations
void InitQueue(Queue* F) {
    F->Head = NULL;
    F->Tail = NULL;
}

void Enqueue(Queue* F, TypeElm x) {
    QNode* V = malloc(sizeof(QNode));
    V->Data = x;
    V->Next = NULL;
    if (F->Head == NULL) {
        F->Head = V;
    } else {
        F->Tail->Next = V;
    }
    F->Tail = V;
}

void Dequeue(Queue* F, TypeElm* x) {
    QNode* V = F->Head;
    if (x != NULL) {
        *x = V->Data;
    }
    if (F->Head == F->Tail) {
        F->Head = NULL;
        F->Tail = NULL;
    } else {
        F->Head = V->Next;
    }
    free(V);
}

int isQEmpty(Queue F) {
    return F.Head == NULL;
}

TypeElm Head(Queue F) {
    return F.Head->Data;
}

// Subtask data structure
typedef struct {
    char name[15];
    bool completed;
} Subtask;

// Task data structure
typedef struct {
    char name[15];
    bool completed;
    Subtask* subtask;
} Maintask;
//creating the projct
void createproject(char name[]) {
    printf("The %s project was created\n", name);
}
//adding a main task
void addmaintask(Queue* Q, Maintask* task) {
    Enqueue(Q, (TypeElm)task);
}
//adding a substack
void addsubtask(Stack* S, Subtask* subtask) {
    Push(S, (TypeElm)subtask);
}
//mark a task as completed
void markcompletedtask(Queue* Q, char taskName[]) {
    Queue tempQ;
    InitQueue(&tempQ);

    while (!isQEmpty(*Q)) {
        Maintask* task = (Maintask*)Head(*Q);
        if (strcmp(task->name, taskName) == 0) {
            if (task->completed) {
                printf("Task '%s' was already completed.\n", taskName);
            } else {
                task->completed = true;
                printf("Task '%s' is completed.\n", taskName);
            }
        }
        Enqueue(&tempQ, Head(*Q));
        Dequeue(Q, NULL);
    }

    while (!isQEmpty(tempQ)) {
        Enqueue(Q, Head(tempQ));
        Dequeue(&tempQ, NULL);
    }
}
//display existing tasks
void viewtasks(Queue Q) {
    if (isQEmpty(Q)) {
        printf("There are no tasks.\n");
    } else {
        Queue tempQ;
        InitQueue(&tempQ);

        while (!isQEmpty(Q)) {
            Maintask* task = (Maintask*)Head(Q);
            printf("- %s (%s)\n", task->name, task->completed ? "completed" : "not completed");
            Enqueue(&tempQ, Head(Q));
            Dequeue(&Q, NULL);
        }

        while (!isQEmpty(tempQ)) {
            Enqueue(&Q, Head(tempQ));
            Dequeue(&tempQ, NULL);
        }
    }
}

// Stack to delete a chosen task
void deletetask(Queue* Q, char taskName[]) {
    Queue tempQ;
    InitQueue(&tempQ);

    while (!isQEmpty(*Q)) {
        Maintask* task = (Maintask*)Head(*Q);
        if (strcmp(task->name, taskName) == 0) {
            printf("Task '%s' deleted successfully.\n", taskName);
        } else {
            Enqueue(&tempQ, Head(*Q));
        }
        Dequeue(Q, NULL);
    }

    while (!isQEmpty(tempQ)) {
        Enqueue(Q, Head(tempQ));
        Dequeue(&tempQ, NULL);
    }
}

int main() {
    int choice;

    Queue taskQueue;
    Stack subtaskStack;

    InitQueue(&taskQueue);
    InitStack(&subtaskStack);

    char project[15] = "";

    printf("Hello user! here's the command menu:\n");
    printf("1. Create a project\n");
    printf("2. Add a main Task\n");
    printf("3. Add Subtask\n");
    printf("4. Mark a chosen task as completed\n");
    printf("5. View the existing tasks\n");
    printf("6. Delete an existing task\n");
    printf("7. Exit\n");

    do {
        printf("Enter the chosen command: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (project[0] == '\0') {
                    printf("Enter project name: ");
                    scanf("%s", project);
                    createproject(project);
                } else {
                    printf("Project already exists.\n");
                }
                break;
            case 2:
                if (project[0] == '\0') {
                    printf("Create a project first.\n");
                } else {
                    Maintask* newTask = malloc(sizeof(Maintask));
                    printf("Enter main task name: ");
                    scanf("%s", newTask->name);
                    newTask->completed = false;
                    newTask->subtask = NULL;
                    addmaintask(&taskQueue, newTask);
                    printf("Main task added successfully.\n");
                }
                break;
            case 3:
                if (project[0] == '\0') {
                    printf("Create a project first and add its main tasks.\n");
                } else {
                    if (isQEmpty(taskQueue)) {
                        printf("you need to first create main tasks.\n");
                    } else {
                        Maintask* currentTask = (Maintask*)Head(taskQueue);
                        Subtask* newSubtask = malloc(sizeof(Subtask));
                        printf("Enter subtask name: ");
                        scanf("%s", newSubtask->name);
                        newSubtask->completed = false;
                        currentTask->subtask = newSubtask;
                        addsubtask(&subtaskStack, newSubtask);
                        printf("Subtask added successfully.\n");
                    }
                }
                break;
            case 4:
                if (project[0] == '\0') {
                    printf("Create a project first.\n");
                } else if (isQEmpty(taskQueue)) {
                    printf("No main tasks available to mark as completed.\n");
                } else {
                    char taskToMark[50];
                    printf("Enter the name of the task to mark as completed: ");
                    scanf("%s", taskToMark);
                    markcompletedtask(&taskQueue, taskToMark);
                }
                break;
            case 5:
                if (project[0] == '\0') {
                    printf("Create a project first.\n");
                } else {
                    viewtasks(taskQueue);
                }
                break;
            case 6:
                if (project[0] == '\0') {
                    printf("Create a project first.\n");
                } else if (isQEmpty(taskQueue)) {
                    printf("No tasks available to delete.\n");
                } else {
                    char taskToDelete[50];
                    printf("Enter the name of the task to delete: ");
                    scanf("%s", taskToDelete);
                    deletetask(&taskQueue, taskToDelete);
                }
                break;
            case 7:
                while (!isQEmpty(taskQueue)) {
                    Maintask* task = (Maintask*)Head(taskQueue);
                    free(task);
                    Dequeue(&taskQueue, NULL);
                }
                printf("end of the program.\n");
                break;
            default:
                printf("error.\n");
        }
    } while (choice != 7);


    sleep(10);

    return 0;
}

