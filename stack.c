#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct s{
    int n;
    struct s * next;
} node;

typedef struct coll{
    node * head;
} Collection;

node * make(int val)
{
    node * new = malloc(sizeof(node));
    new->n = val;
    new->next = NULL;
    return new;
}

void push(Collection * c, int val){
    node * new = make(val);
    new->next = c->head;
    c->head = new;
}

bool isEmp(Collection * c){
    return c->head == NULL;
}

int pop(Collection * c)
{
    if(isEmp(c)) return -1;
    node * first = c->head;
    int out = first->n;
    c->head = c->head->next;
    free(first);
    return out;
}

int main()
{
    Collection c;
    c.head = NULL;

    for(int i = 0; i < 2; i++){
        push(&c, i);
    }

    printf("%d\n", pop(&c));
    printf("%d\n", pop(&c));
    printf("%d\n", pop(&c));
}