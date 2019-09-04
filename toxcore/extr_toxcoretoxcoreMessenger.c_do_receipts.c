#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct Receipts {int /*<<< orphan*/  msg_id; int /*<<< orphan*/  packet_num; struct Receipts* next; } ;
typedef  size_t int32_t ;
struct TYPE_8__ {TYPE_1__* friendlist; int /*<<< orphan*/  read_receipt_userdata; int /*<<< orphan*/  (* read_receipt ) (TYPE_2__*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_7__ {int /*<<< orphan*/ * receipts_end; struct Receipts* receipts_start; } ;
typedef  TYPE_2__ Messenger ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct Receipts*) ; 
 scalar_t__ friend_not_valid (TYPE_2__*,size_t) ; 
 int friend_received_packet (TYPE_2__*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int do_receipts(Messenger *m, int32_t friendnumber)
{
    if (friend_not_valid(m, friendnumber))
        return -1;

    struct Receipts *receipts = m->friendlist[friendnumber].receipts_start;

    while (receipts) {
        struct Receipts *temp_r = receipts->next;

        if (friend_received_packet(m, friendnumber, receipts->packet_num) == -1)
            break;

        if (m->read_receipt)
            (*m->read_receipt)(m, friendnumber, receipts->msg_id, m->read_receipt_userdata);

        free(receipts);
        m->friendlist[friendnumber].receipts_start = temp_r;
        receipts = temp_r;
    }

    if (!m->friendlist[friendnumber].receipts_start)
        m->friendlist[friendnumber].receipts_end = NULL;

    return 0;
}