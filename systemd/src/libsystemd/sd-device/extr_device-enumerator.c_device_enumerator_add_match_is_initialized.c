#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int match_allow_uninitialized; int scan_uptodate; } ;
typedef  TYPE_1__ sd_device_enumerator ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  assert_return (TYPE_1__*,int /*<<< orphan*/ ) ; 

int device_enumerator_add_match_is_initialized(sd_device_enumerator *enumerator) {
        assert_return(enumerator, -EINVAL);

        enumerator->match_allow_uninitialized = false;

        enumerator->scan_uptodate = false;

        return 0;
}