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
struct histogram {scalar_t__*** data; } ;

/* Variables and functions */

__attribute__((used)) static inline unsigned int histogram_count(struct histogram *h, int r_min, int r_max,
                                           int g_min, int g_max, int b_min, int b_max)
{
    unsigned int count = 0;
    int r, g, b;
    for (r = r_min; r <= r_max; r++)
    for (g = g_min; g <= g_max; g++)
    for (b = b_min; b <= b_max; b++)
        if (h->data[r][g][b] != 0) count++;
    return count;
}