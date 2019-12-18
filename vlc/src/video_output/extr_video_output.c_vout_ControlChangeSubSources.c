#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* p; } ;
typedef  TYPE_2__ vout_thread_t ;
struct TYPE_4__ {int /*<<< orphan*/ * spu; int /*<<< orphan*/  dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spu_ChangeSources (int /*<<< orphan*/ *,char const*) ; 

void vout_ControlChangeSubSources(vout_thread_t *vout, const char *filters)
{
    assert(!vout->p->dummy);
    if (likely(vout->p->spu != NULL))
        spu_ChangeSources(vout->p->spu, filters);
}