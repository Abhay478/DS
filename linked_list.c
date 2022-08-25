#include <stdio.h>
#include <stdlib.h>

typedef struct t_node{
    int n;
    struct t_node * next;
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

void reverse(Collection * c)
{
    node * current = c->head;
    c->head = c->head->next;
    node * ss = c->head->next;
    current->next = NULL;

    while(ss != NULL){
        c->head->next = current;
        current = c->head;
        c->head = ss;
        ss = ss->next;
    }
    c->head->next = current;
}

void addToCollection(Collection * c, int val)
{
    node * new = make(val);
    new->next = c->head;
    c->head = new; 
}

node * search(Collection * c, int val)
{
    node * current = c->head;
    while(current != NULL){
        if(current->n == val) break;
        current = current->next;
    }
    return current;
}

int deleteFromCollection(Collection * c, int val)
{
    node * current = c->head;
    if(!current) return 0;
    if(current->n == val){
        c->head = current->next;
        free(current);
        return 1;
    }

    node * out;

    while(current->next != NULL){
        if(current->next->n == val){
            out = current->next;
            current->next = out->next;
            free(out);
            return 2;
        }
        current = current->next;
    }

    return 3;
}

void list(Collection * c)
{
    node * current = c->head;
    while(current != NULL){
        printf("%d\n", current->n);
        current = current->next;
    }
}

void destroy(Collection * c)
{
    node * current = c->head;
    while(c->head != NULL){
        current = c->head;
        c->head = c->head->next;
        free(current);
    }
}

int main()
{
    Collection c;
    c.head = NULL;

    int item;

    for(int i = 1; i < 201; i++){
        addToCollection(&c, i);
    }

    deleteFromCollection(&c, 1);
    reverse(&c);

    list(&c);

    destroy(&c);

    return 0;
}