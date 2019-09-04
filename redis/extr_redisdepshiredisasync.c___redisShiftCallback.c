#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* tail; TYPE_2__* head; } ;
typedef  TYPE_1__ redisCallbackList ;
struct TYPE_9__ {struct TYPE_9__* next; } ;
typedef  TYPE_2__ redisCallback ;

/* Variables and functions */
 int REDIS_ERR ; 
 int REDIS_OK ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,TYPE_2__*,int) ; 

__attribute__((used)) static int __redisShiftCallback(redisCallbackList *list, redisCallback *target) {
    redisCallback *cb = list->head;
    if (cb != NULL) {
        list->head = cb->next;
        if (cb == list->tail)
            list->tail = NULL;

        /* Copy callback from heap to stack */
        if (target != NULL)
            memcpy(target,cb,sizeof(*cb));
        free(cb);
        return REDIS_OK;
    }
    return REDIS_ERR;
}