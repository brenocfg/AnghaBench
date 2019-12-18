#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* sys; } ;
typedef  TYPE_1__ vout_display_t ;
struct TYPE_7__ {int /*<<< orphan*/  sys; } ;

/* Variables and functions */
 int /*<<< orphan*/  Clean (TYPE_1__*) ; 
 int /*<<< orphan*/  CommonWindowClean (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VLC_OBJECT (TYPE_1__*) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 

__attribute__((used)) static void Close(vout_display_t *vd)
{
    Clean(vd);

    CommonWindowClean(VLC_OBJECT(vd), &vd->sys->sys);

    free(vd->sys);
}