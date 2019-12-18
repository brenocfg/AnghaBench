#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_3__* p_sys; } ;
struct TYPE_7__ {TYPE_1__ updater; } ;
typedef  TYPE_2__ subpicture_t ;
struct TYPE_8__ {struct TYPE_8__* p_subs_data; int /*<<< orphan*/  p_dec_sys; } ;
typedef  TYPE_3__ libass_spu_updater_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  DecSysRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 

__attribute__((used)) static void SubpictureDestroy( subpicture_t *p_subpic )
{
    libass_spu_updater_sys_t *p_spusys = p_subpic->updater.p_sys;

    DecSysRelease( p_spusys->p_dec_sys );
    free( p_spusys->p_subs_data );
    free( p_spusys );
}