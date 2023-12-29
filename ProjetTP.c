#include <stdio.h>
#include <stdlib.h>

///declaration of TypeElement
typedef int TypeElm;
//typedef char TypeElm;

///declaration of a Stack
typedef struct Estack* Stack;
typedef struct Estack { TypeElm  Data; Stack Next} SNode;

///declaration of a Queue
typedef struct Element* EQueue;
typedef struct Element { TypeElm  Data; EQueue Next} QNode;
typedef struct {EQueue Head,Tail;} Queue;

///Stacks operations
///procedure InitStack
void InitStack(Stack *P)
{*P=NULL;}

///procedure Push
void Push(Stack *P, TypeElm x)
{Stack V;
 V=malloc(sizeof(SNode));
 V->Data=x;
 V->Next=*P;
 *P=V;
}

///procedure Pop
void Pop(Stack *P, TypeElm *x)
{Stack V;
 *x=(*P)->Data;
 V=*P;
 *P=(*P)->Next;
 free(V);
}

///Function isSEmpty
int isSEmpty(Stack P)
{if (P==NULL) return 1;
 else return 0;
}

///Function Top
int Top(Stack P)
{return P->Data;}


///Queues operations
///procedure InitQueue
void InitQueue(Queue *F)
{(*F).Head=NULL; (*F).Tail=NULL;}

///procedure Enqueue
void Enqueue(Queue *F, int x)
{EQueue V;
 V=malloc(sizeof(QNode));
 V->Data=x;
 V->Next=NULL;
 if ((*F).Head==NULL) (*F).Head=V; //la Queue est vide
 else (*F).Tail->Next=V;
 (*F).Tail=V;
}

///procedure Dequeue
void Dequeue(Queue *F, TypeElm *x)
{EQueue V;
 V=(*F).Head;
 *x=V->Data; //ou  *x=(*F).Head->Data;

 if ((*F).Head==(*F).Tail) {(*F).Head=NULL; (*F).Tail=NULL;}
 else (*F).Head=(*F).Head->Next; // ou  (*F).Head=V->Next;
 free(V);
}

///Function isQEmpty
TypeElm isQEmpty(Queue F)
{if (F.Head==NULL) return 1;
 else return 0;
}

///Function Head
TypeElm Head(Queue F)
{return F.Head->Data;}


 struct Task{
        int number;
        char Name[50];
        bool Complete;
        struct Task* Next;
    }Task;  



int main(int argc, char **arg){

    struct Task* Head = malloc(sizeof(struct Task));//this allocates 1 element
                                                    
    
    return 0;
}

