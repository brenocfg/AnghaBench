#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct msg_sequence {int size; size_t count; TYPE_1__* sequence; } ;
struct message {int /*<<< orphan*/  id; int /*<<< orphan*/  lParam; int /*<<< orphan*/  wParam; int /*<<< orphan*/  flags; int /*<<< orphan*/  message; } ;
struct TYPE_5__ {int /*<<< orphan*/  id; int /*<<< orphan*/  lParam; int /*<<< orphan*/  wParam; int /*<<< orphan*/  flags; int /*<<< orphan*/  message; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 TYPE_1__* heap_alloc (int) ; 
 TYPE_1__* heap_realloc (TYPE_1__*,int) ; 

__attribute__((used)) static void add_message(struct msg_sequence **seq, int sequence_index,
    const struct message *msg)
{
    struct msg_sequence *msg_seq = seq[sequence_index];

    if (!msg_seq->sequence)
    {
        msg_seq->size = 10;
        msg_seq->sequence = heap_alloc(msg_seq->size * sizeof (struct message));
    }

    if (msg_seq->count == msg_seq->size)
    {
        msg_seq->size *= 2;
        msg_seq->sequence = heap_realloc(msg_seq->sequence, msg_seq->size * sizeof (struct message));
    }

    assert(msg_seq->sequence);

    msg_seq->sequence[msg_seq->count].message = msg->message;
    msg_seq->sequence[msg_seq->count].flags = msg->flags;
    msg_seq->sequence[msg_seq->count].wParam = msg->wParam;
    msg_seq->sequence[msg_seq->count].lParam = msg->lParam;
    msg_seq->sequence[msg_seq->count].id = msg->id;

    msg_seq->count++;
}