#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct Receipts {struct Receipts* next; } ;
typedef  size_t int32_t ;
struct TYPE_6__ {TYPE_1__* friendlist; } ;
struct TYPE_5__ {int /*<<< orphan*/ * receipts_end; struct Receipts* receipts_start; } ;
typedef  TYPE_2__ Messenger ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct Receipts*) ; 
 scalar_t__ friend_not_valid (TYPE_2__*,size_t) ; 

__attribute__((used)) static int clear_receipts(Messenger *m, int32_t friendnumber)
{
    if (friend_not_valid(m, friendnumber))
        return -1;

    struct Receipts *receipts = m->friendlist[friendnumber].receipts_start;

    while (receipts) {
        struct Receipts *temp_r = receipts->next;
        free(receipts);
        receipts = temp_r;
    }

    m->friendlist[friendnumber].receipts_start = NULL;
    m->friendlist[friendnumber].receipts_end = NULL;
    return 0;
}