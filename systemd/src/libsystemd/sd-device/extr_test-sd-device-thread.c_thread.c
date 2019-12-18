#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  sd_device ;

/* Variables and functions */
 int /*<<< orphan*/  assert_se (int) ; 
 int /*<<< orphan*/ * sd_device_unref (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void* thread(void *p) {
        sd_device **d = p;

        assert_se(!(*d = sd_device_unref(*d)));

        return NULL;
}