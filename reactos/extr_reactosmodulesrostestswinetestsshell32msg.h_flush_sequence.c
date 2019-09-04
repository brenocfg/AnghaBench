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
struct msg_sequence {scalar_t__ size; scalar_t__ count; int /*<<< orphan*/ * sequence; } ;

/* Variables and functions */
 int /*<<< orphan*/  heap_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void flush_sequence(struct msg_sequence **seg, int sequence_index)
{
    struct msg_sequence *msg_seq = seg[sequence_index];
    heap_free(msg_seq->sequence);
    msg_seq->sequence = NULL;
    msg_seq->count = msg_seq->size = 0;
}