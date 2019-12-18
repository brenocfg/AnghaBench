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
struct TYPE_6__ {int /*<<< orphan*/ * requested_device; } ;
typedef  TYPE_2__ aout_sys_t ;

/* Variables and functions */
 int DeviceRequestLocked (TYPE_1__*) ; 
 int /*<<< orphan*/ * ToWide (char const*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * default_device ; 
 int /*<<< orphan*/  default_device_b ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int DeviceSelectLocked(audio_output_t *aout, const char *id)
{
    aout_sys_t *sys = aout->sys;
    assert(sys->requested_device == NULL);

    if (id != NULL && strcmp(id, default_device_b) != 0)
    {
        sys->requested_device = ToWide(id); /* FIXME leak */
        if (unlikely(sys->requested_device == NULL))
            return -1;
    }
    else
        sys->requested_device = default_device;

    return DeviceRequestLocked(aout);
}