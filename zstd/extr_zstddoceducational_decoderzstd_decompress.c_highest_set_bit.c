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
typedef  int u64 ;

/* Variables and functions */

__attribute__((used)) static inline int highest_set_bit(const u64 num) {
    for (int i = 63; i >= 0; i--) {
        if (((u64)1 << i) <= num) {
            return i;
        }
    }
    return -1;
}