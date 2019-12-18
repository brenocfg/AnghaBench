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
typedef  int uint32_t ;
struct TYPE_8__ {int friend_number; struct TYPE_8__* prev; struct TYPE_8__* next; TYPE_2__* av; } ;
typedef  TYPE_1__ ToxAVCall ;
struct TYPE_9__ {int calls_tail; int calls_head; TYPE_1__** calls; int /*<<< orphan*/  m; } ;
typedef  TYPE_2__ ToxAV ;
typedef  int /*<<< orphan*/  TOXAV_ERR_CALL ;

/* Variables and functions */
 int /*<<< orphan*/  TOXAV_ERR_CALL_FRIEND_ALREADY_IN_CALL ; 
 int /*<<< orphan*/  TOXAV_ERR_CALL_FRIEND_NOT_CONNECTED ; 
 int /*<<< orphan*/  TOXAV_ERR_CALL_FRIEND_NOT_FOUND ; 
 int /*<<< orphan*/  TOXAV_ERR_CALL_MALLOC ; 
 int /*<<< orphan*/  TOXAV_ERR_CALL_OK ; 
 int /*<<< orphan*/ * call_get (TYPE_2__*,int) ; 
 void* calloc (int,int) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 scalar_t__ m_friend_exists (int /*<<< orphan*/ ,int) ; 
 int m_get_friend_connectionstatus (int /*<<< orphan*/ ,int) ; 
 void* realloc (TYPE_1__**,int) ; 

ToxAVCall *call_new(ToxAV *av, uint32_t friend_number, TOXAV_ERR_CALL *error)
{
    /* Assumes mutex locked */
    TOXAV_ERR_CALL rc = TOXAV_ERR_CALL_OK;
    ToxAVCall *call = NULL;

    if (m_friend_exists(av->m, friend_number) == 0) {
        rc = TOXAV_ERR_CALL_FRIEND_NOT_FOUND;
        goto END;
    }

    if (m_get_friend_connectionstatus(av->m, friend_number) < 1) {
        rc = TOXAV_ERR_CALL_FRIEND_NOT_CONNECTED;
        goto END;
    }

    if (call_get(av, friend_number) != NULL) {
        rc = TOXAV_ERR_CALL_FRIEND_ALREADY_IN_CALL;
        goto END;
    }


    call = calloc(sizeof(ToxAVCall), 1);

    if (call == NULL) {
        rc = TOXAV_ERR_CALL_MALLOC;
        goto END;
    }

    call->av = av;
    call->friend_number = friend_number;

    if (av->calls == NULL) { /* Creating */
        av->calls = calloc (sizeof(ToxAVCall *), friend_number + 1);

        if (av->calls == NULL) {
            free(call);
            call = NULL;
            rc = TOXAV_ERR_CALL_MALLOC;
            goto END;
        }

        av->calls_tail = av->calls_head = friend_number;

    } else if (av->calls_tail < friend_number) { /* Appending */
        void *tmp = realloc(av->calls, sizeof(ToxAVCall *) * (friend_number + 1));

        if (tmp == NULL) {
            free(call);
            call = NULL;
            rc = TOXAV_ERR_CALL_MALLOC;
            goto END;
        }

        av->calls = tmp;

        /* Set fields in between to null */
        uint32_t i = av->calls_tail + 1;

        for (; i < friend_number; i ++)
            av->calls[i] = NULL;

        call->prev = av->calls[av->calls_tail];
        av->calls[av->calls_tail]->next = call;

        av->calls_tail = friend_number;

    } else if (av->calls_head > friend_number) { /* Inserting at front */
        call->next = av->calls[av->calls_head];
        av->calls[av->calls_head]->prev = call;
        av->calls_head = friend_number;
    }

    av->calls[friend_number] = call;

END:

    if (error)
        *error = rc;

    return call;
}