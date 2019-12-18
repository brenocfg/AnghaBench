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

/* Variables and functions */
 scalar_t__ path_equal (char const*,char const*) ; 

__attribute__((used)) static inline bool path_equal_ptr(const char *a, const char *b) {
        return !!a == !!b && (!a || path_equal(a, b));
}