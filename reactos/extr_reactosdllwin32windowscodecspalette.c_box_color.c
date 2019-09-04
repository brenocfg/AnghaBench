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
struct histogram {int dummy; } ;
struct box {int /*<<< orphan*/  b_max; int /*<<< orphan*/  b_min; int /*<<< orphan*/  g_max; int /*<<< orphan*/  g_min; int /*<<< orphan*/  r_max; int /*<<< orphan*/  r_min; } ;

/* Variables and functions */
 unsigned int histogram_color (struct histogram*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline unsigned int box_color(struct histogram *h, struct box *b)
{
    return histogram_color(h, b->r_min, b->r_max, b->g_min, b->g_max, b->b_min, b->b_max);
}