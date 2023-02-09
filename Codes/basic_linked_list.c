// A simple C program to introduce
// a linked list
#include <stdio.h>
#include <stdlib.h>
 
struct Node {
    int data;
    struct Node* next;
};
typedef struct Node node;

node* create_linked_list()
{
    node *head = (node*) malloc(sizeof(node));
    head->next = NULL;
    return head;
}

void add_node(node *head, int data)
{
    node *iter = (node*) malloc(sizeof(node));
    node *new = (node*) malloc(sizeof(node));
    new->data = data;
    iter = head;
    while (iter->next != NULL)
        iter = iter->next;
    iter->next = new;
}

void show(node *head)
{
    node *iter = (node*) malloc(sizeof(node));
    iter = head;
    int count = 0;
    while (iter->next != NULL)
    {
        iter = iter->next;
        printf("%d. eleman->data = %d\n", count, iter->data);
        count ++;
    }
    printf("\n");
}

void remove_node(node *head, int data)
{
    node *iter = (node*) malloc(sizeof(node));
    iter = head;

    while (iter->next != NULL && iter->next->data != data)
        iter = iter->next;

    if (iter->next == NULL)
        printf("\nBulunamadi\n");
    else
        iter->next = iter->next->next;
}

void insert_node(node *head, int index, int data)
{
    node *iter = (node*) malloc(sizeof(node));
    node *new = (node*) malloc(sizeof(node));
    new->data = data;
    iter = head;
    for (; index != 0 && iter != NULL; index--)
        iter = iter->next;
    if (iter == NULL)
        printf("\nIstenilen index fazla\n");
    else
    {
        new->next = iter->next;
        iter->next = new;
    }
}

int main()
{
    node *head = create_linked_list();
    add_node(head, 1);
    add_node(head, 2);
    add_node(head, 3);
    add_node(head, 4);
    add_node(head, 5);
    add_node(head, 6);
    remove_node(head, 2);
    show(head);
    insert_node(head, 1, 2);
    insert_node(head, 6, 7);
    show(head);
    return 0;
}