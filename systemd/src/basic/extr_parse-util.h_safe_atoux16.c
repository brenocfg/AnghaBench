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
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 int safe_atou16_full (char const*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int safe_atoux16(const char *s, uint16_t *ret) {
        return safe_atou16_full(s, 16, ret);
}