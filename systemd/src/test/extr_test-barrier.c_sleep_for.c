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
typedef  scalar_t__ usec_t ;

/* Variables and functions */
 scalar_t__ USEC_PER_SEC ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int /*<<< orphan*/  usleep (scalar_t__) ; 

__attribute__((used)) static void sleep_for(usec_t usecs) {
        /* stupid usleep() might fail if >1000000 */
        assert_se(usecs < USEC_PER_SEC);
        usleep(usecs);
}