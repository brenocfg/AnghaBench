#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  match_parent; } ;
typedef  TYPE_1__ sd_device_enumerator ;

/* Variables and functions */
 int /*<<< orphan*/  set_clear_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void device_enumerator_clear_match_parent(sd_device_enumerator *enumerator) {
        if (!enumerator)
                return;

        set_clear_free(enumerator->match_parent);
}