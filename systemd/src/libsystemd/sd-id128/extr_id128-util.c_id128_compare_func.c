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
typedef  int /*<<< orphan*/  sd_id128_t ;

/* Variables and functions */
 int memcmp (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int) ; 

int id128_compare_func(const sd_id128_t *a, const sd_id128_t *b) {
        return memcmp(a, b, 16);
}