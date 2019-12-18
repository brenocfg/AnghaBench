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
struct TYPE_2__ {int state; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__ pp_status ; 
 void* realloc (void*,size_t) ; 

void *pp_xrealloc(void *p, size_t size)
{
    void *res;

    assert(size > 0);
    res = realloc(p, size);
    if(res == NULL)
    {
        /* Set the error flag */
        pp_status.state = 1;
    }
    return res;
}