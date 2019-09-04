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
 int /*<<< orphan*/  TRACE (char*) ; 
 scalar_t__ TRACE_ON (int /*<<< orphan*/ ) ; 
#define  b_r 130 
#define  b_s 129 
#define  b_x 128 
 int /*<<< orphan*/  uniscribe ; 

__attribute__((used)) static void debug_output_breaks(const short* breaks, int count)
{
    if (TRACE_ON(uniscribe))
    {
        int i;
        TRACE("[");
        for (i = 0; i < count && i < 200; i++)
        {
            switch (breaks[i])
            {
                case b_x: TRACE("x"); break;
                case b_r: TRACE("!"); break;
                case b_s: TRACE("+"); break;
                default: TRACE("*");
            }
        }
        if (i == 200)
            TRACE("...");
        TRACE("]\n");
    }
}