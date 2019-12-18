#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* sys; } ;
typedef  TYPE_2__ vout_display_t ;
struct TYPE_7__ {int /*<<< orphan*/  sys; int /*<<< orphan*/  p_sensors; } ;

/* Variables and functions */
 int /*<<< orphan*/  CommonWindowClean (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Direct3D11Close (TYPE_2__*) ; 
 int /*<<< orphan*/  Direct3D11Destroy (TYPE_2__*) ; 
 int /*<<< orphan*/  UnhookWindowsSensors (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VLC_OBJECT (TYPE_2__*) ; 

__attribute__((used)) static void Close(vout_display_t *vd)
{
    Direct3D11Close(vd);
    UnhookWindowsSensors(vd->sys->p_sensors);
#if !VLC_WINSTORE_APP
    CommonWindowClean(VLC_OBJECT(vd), &vd->sys->sys);
#endif
    Direct3D11Destroy(vd);
}