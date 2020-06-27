#include "UserList.h"

UserListNode* Add(UserListNode* node, User* data)
{
	UserListNode* temp = (UserListNode*) malloc(sizeof(UserListNode));

    temp->data = data;
    temp->next = node;
    node = temp;
    return node;
}

UserListNode* Reverse(UserListNode* head)
{
	UserListNode* temp;
    UserListNode* previous = NULL;
    while (head != NULL) {
        temp = head->next;
        head->next = previous;
        previous = head;
        head = temp;
    }
    return previous;
}

void FreeList(UserListNode* head) 
{
    UserListNode* tmp = head;
    UserListNode* current;
    while (tmp != NULL) {
        current = tmp;
        tmp = tmp->next;
        free(current->data);
        free(current);
    }
}