#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ usec_t ;
struct TYPE_6__ {scalar_t__ usec_initialized; } ;
typedef  TYPE_1__ sd_device ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int device_set_usec_initialized (TYPE_1__*,scalar_t__) ; 
 scalar_t__ now (int /*<<< orphan*/ ) ; 

int device_ensure_usec_initialized(sd_device *device, sd_device *device_old) {
        usec_t when;

        assert(device);

        if (device_old && device_old->usec_initialized > 0)
                when = device_old->usec_initialized;
        else
                when = now(CLOCK_MONOTONIC);

        return device_set_usec_initialized(device, when);
}