#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct HelloTypeObject {int /*<<< orphan*/  len; struct HelloTypeNode* head; } ;
struct HelloTypeNode {scalar_t__ value; struct HelloTypeNode* next; } ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 struct HelloTypeNode* RedisModule_Alloc (int) ; 

void HelloTypeInsert(struct HelloTypeObject *o, int64_t ele) {
    struct HelloTypeNode *next = o->head, *newnode, *prev = NULL;

    while(next && next->value < ele) {
        prev = next;
        next = next->next;
    }
    newnode = RedisModule_Alloc(sizeof(*newnode));
    newnode->value = ele;
    newnode->next = next;
    if (prev) {
        prev->next = newnode;
    } else {
        o->head = newnode;
    }
    o->len++;
}