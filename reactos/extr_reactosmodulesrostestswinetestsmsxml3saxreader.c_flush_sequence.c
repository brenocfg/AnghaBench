#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct call_sequence {int count; int size; TYPE_1__* sequence; } ;
struct TYPE_2__ {int attr_count; int /*<<< orphan*/  arg3W; int /*<<< orphan*/  arg2W; int /*<<< orphan*/  arg1W; struct TYPE_2__* attributes; int /*<<< orphan*/  valueW; int /*<<< orphan*/  qnameW; int /*<<< orphan*/  localW; int /*<<< orphan*/  uriW; } ;

/* Variables and functions */
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_free (TYPE_1__*) ; 

__attribute__((used)) static inline void flush_sequence(struct call_sequence **seg, int sequence_index)
{
    int i;

    struct call_sequence *call_seq = seg[sequence_index];

    for (i = 0; i < call_seq->count; i++)
    {
        int j;

        for (j = 0; j < call_seq->sequence[i].attr_count; j++)
        {
            SysFreeString(call_seq->sequence[i].attributes[j].uriW);
            SysFreeString(call_seq->sequence[i].attributes[j].localW);
            SysFreeString(call_seq->sequence[i].attributes[j].qnameW);
            SysFreeString(call_seq->sequence[i].attributes[j].valueW);
        }
        heap_free(call_seq->sequence[i].attributes);
        call_seq->sequence[i].attr_count = 0;

        SysFreeString(call_seq->sequence[i].arg1W);
        SysFreeString(call_seq->sequence[i].arg2W);
        SysFreeString(call_seq->sequence[i].arg3W);
    }

    heap_free(call_seq->sequence);
    call_seq->sequence = NULL;
    call_seq->count = call_seq->size = 0;
}