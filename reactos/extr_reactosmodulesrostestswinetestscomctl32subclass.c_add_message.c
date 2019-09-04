#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct message {int /*<<< orphan*/  procnum; int /*<<< orphan*/  wParam; } ;
struct TYPE_6__ {int /*<<< orphan*/  procnum; int /*<<< orphan*/  wParam; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 TYPE_1__* heap_alloc (int) ; 
 TYPE_1__* heap_realloc (TYPE_1__*,int) ; 
 TYPE_1__* sequence ; 
 int sequence_cnt ; 
 int sequence_size ; 

__attribute__((used)) static void add_message(const struct message *msg)
{
    if (!sequence)
    {
        sequence_size = 10;
        sequence = heap_alloc( sequence_size * sizeof (struct message) );
    }
    if (sequence_cnt == sequence_size)
    {
        sequence_size *= 2;
        sequence = heap_realloc( sequence, sequence_size * sizeof (struct message) );
    }
    assert(sequence);

    sequence[sequence_cnt].wParam  = msg->wParam;
    sequence[sequence_cnt].procnum = msg->procnum;

    sequence_cnt++;
}