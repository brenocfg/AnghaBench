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
struct TYPE_5__ {struct TYPE_5__* p_next; } ;
typedef  TYPE_1__ sout_stream_t ;

/* Variables and functions */
 int /*<<< orphan*/  sout_StreamDelete (TYPE_1__*) ; 

void sout_StreamChainDelete(sout_stream_t *p_first, sout_stream_t *p_last)
{
    while(p_first != NULL)
    {
        sout_stream_t *p_next = p_first->p_next;

        sout_StreamDelete(p_first);
        if(p_first == p_last)
           break;
        p_first = p_next;
    }
}