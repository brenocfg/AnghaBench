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
typedef  scalar_t__ uint32_t ;
struct index {char c; scalar_t__ color; } ;

/* Variables and functions */

__attribute__((used)) static bool
find_color(struct index *index, int len, char c, uint32_t *color) {
    // there are typically very few color, so it's ok to iterate over the array
    for (int i = 0; i < len; ++i) {
        if (index[i].c == c) {
            *color = index[i].color;
            return true;
        }
    }
    *color = 0;
    return false;
}