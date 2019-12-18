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
 int safe_atou_full (char const*,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static inline int safe_atou(const char *s, unsigned *ret_u) {
        return safe_atou_full(s, 0, ret_u);
}