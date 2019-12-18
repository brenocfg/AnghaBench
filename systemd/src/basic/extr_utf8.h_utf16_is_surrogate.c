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
typedef  int char16_t ;

/* Variables and functions */

__attribute__((used)) static inline bool utf16_is_surrogate(char16_t c) {
        return c >= 0xd800U && c <= 0xdfffU;
}