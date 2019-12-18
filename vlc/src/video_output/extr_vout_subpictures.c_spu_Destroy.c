#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_3__* p; } ;
typedef  TYPE_2__ spu_t ;
struct TYPE_7__ {int /*<<< orphan*/  thread; } ;
struct TYPE_9__ {TYPE_1__ prerender; } ;
typedef  TYPE_3__ spu_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  spu_Cleanup (TYPE_2__*) ; 
 int /*<<< orphan*/  vlc_cancel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_object_delete (TYPE_2__*) ; 

void spu_Destroy(spu_t *spu)
{
    spu_private_t *sys = spu->p;
    /* stop prerendering */
    vlc_cancel(sys->prerender.thread);
    vlc_join(sys->prerender.thread, NULL);
    /* delete filters and free resources */
    spu_Cleanup(spu);
    vlc_object_delete(spu);
}