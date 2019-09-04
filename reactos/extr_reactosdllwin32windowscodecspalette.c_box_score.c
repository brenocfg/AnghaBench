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
struct box {unsigned int r_max; unsigned int r_min; unsigned int g_max; unsigned int g_min; unsigned int b_max; unsigned int b_min; } ;

/* Variables and functions */
 unsigned int B_SCALE ; 
 unsigned int B_SHIFT ; 
 unsigned int G_SCALE ; 
 unsigned int G_SHIFT ; 
 unsigned int R_SCALE ; 
 unsigned int R_SHIFT ; 

__attribute__((used)) static inline unsigned int box_score(struct box *b)
{
    unsigned int tmp, sum = 0;
    tmp = ((b->r_max - b->r_min) << R_SHIFT) * R_SCALE; sum += tmp * tmp;
    tmp = ((b->g_max - b->g_min) << G_SHIFT) * G_SCALE; sum += tmp * tmp;
    tmp = ((b->b_max - b->b_min) << B_SHIFT) * B_SCALE; sum += tmp * tmp;
    return sum;
}