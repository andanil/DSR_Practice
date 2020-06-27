#ifndef USERLIST_H
#define USERLIST_H

#include <stdlib.h>
#include "User.h"

typedef struct node {
    User* data;
    struct node* next;
} UserListNode;

UserListNode* Add(UserListNode* node, User* data);
UserListNode* Reverse(UserListNode* head);
void FreeList(UserListNode* head);

#endif