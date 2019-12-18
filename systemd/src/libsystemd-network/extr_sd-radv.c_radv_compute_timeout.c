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
 scalar_t__ MAX (scalar_t__,int) ; 
 int /*<<< orphan*/  SD_RADV_DEFAULT_MIN_TIMEOUT_USEC ; 
 int USEC_PER_SEC ; 
 int /*<<< orphan*/  assert_return (int,int /*<<< orphan*/ ) ; 
 scalar_t__ random_u32 () ; 

__attribute__((used)) static usec_t radv_compute_timeout(usec_t min, usec_t max) {
        assert_return(min <= max, SD_RADV_DEFAULT_MIN_TIMEOUT_USEC);

        /* RFC 4861: min must be no less than 3s, max must be no less than 4s */
        min = MAX(min, 3*USEC_PER_SEC);
        max = MAX(max, 4*USEC_PER_SEC);

        return min + (random_u32() % (max - min));
}