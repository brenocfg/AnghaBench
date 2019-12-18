#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ n_devices; int /*<<< orphan*/ * devices; int /*<<< orphan*/  n_allocated; } ;
typedef  TYPE_1__ sd_device_enumerator ;
typedef  TYPE_1__ sd_device ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GREEDY_REALLOC (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  assert_return (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_device_ref (TYPE_1__*) ; 

int device_enumerator_add_device(sd_device_enumerator *enumerator, sd_device *device) {
        assert_return(enumerator, -EINVAL);
        assert_return(device, -EINVAL);

        if (!GREEDY_REALLOC(enumerator->devices, enumerator->n_allocated, enumerator->n_devices + 1))
                return -ENOMEM;

        enumerator->devices[enumerator->n_devices++] = sd_device_ref(device);

        return 0;
}