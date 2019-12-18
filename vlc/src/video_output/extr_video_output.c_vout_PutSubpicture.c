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
struct TYPE_4__ {TYPE_2__* p; } ;
typedef  TYPE_1__ vout_thread_t ;
struct TYPE_5__ {int /*<<< orphan*/ * spu; int /*<<< orphan*/  dummy; } ;
typedef  TYPE_2__ vout_thread_sys_t ;
typedef  int /*<<< orphan*/  subpicture_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  spu_PutSubpicture (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  subpicture_Delete (int /*<<< orphan*/ *) ; 

void vout_PutSubpicture( vout_thread_t *vout, subpicture_t *subpic )
{
    vout_thread_sys_t *sys = vout->p;
    assert(!sys->dummy);

    if (sys->spu != NULL)
        spu_PutSubpicture(sys->spu, subpic);
    else
        subpicture_Delete(subpic);
}