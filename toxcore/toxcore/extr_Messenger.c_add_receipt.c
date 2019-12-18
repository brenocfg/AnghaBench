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
typedef  void* uint32_t ;
struct Receipts {struct Receipts* next; void* msg_id; void* packet_num; } ;
typedef  size_t int32_t ;
struct TYPE_6__ {TYPE_1__* friendlist; } ;
struct TYPE_5__ {struct Receipts* receipts_end; struct Receipts* receipts_start; } ;
typedef  TYPE_2__ Messenger ;

/* Variables and functions */
 struct Receipts* calloc (int,int) ; 
 scalar_t__ friend_not_valid (TYPE_2__*,size_t) ; 

__attribute__((used)) static int add_receipt(Messenger *m, int32_t friendnumber, uint32_t packet_num, uint32_t msg_id)
{
    if (friend_not_valid(m, friendnumber))
        return -1;

    struct Receipts *new = calloc(1, sizeof(struct Receipts));

    if (!new)
        return -1;

    new->packet_num = packet_num;
    new->msg_id = msg_id;

    if (!m->friendlist[friendnumber].receipts_start) {
        m->friendlist[friendnumber].receipts_start = new;
    } else {
        m->friendlist[friendnumber].receipts_end->next = new;
    }

    m->friendlist[friendnumber].receipts_end = new;
    new->next = NULL;
    return 0;
}