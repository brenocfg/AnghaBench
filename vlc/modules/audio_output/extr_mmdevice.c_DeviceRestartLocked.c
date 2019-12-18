#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* sys; } ;
typedef  TYPE_1__ audio_output_t ;
struct TYPE_6__ {int /*<<< orphan*/ * acquired_device; int /*<<< orphan*/ * requested_device; } ;
typedef  TYPE_2__ aout_sys_t ;

/* Variables and functions */
 int DeviceRequestLocked (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * default_device ; 

__attribute__((used)) static int DeviceRestartLocked(audio_output_t *aout)
{
    aout_sys_t *sys = aout->sys;
    assert(sys->requested_device == NULL);
    sys->requested_device = sys->acquired_device ? sys->acquired_device
                                                 : default_device;
    return DeviceRequestLocked(aout);
}