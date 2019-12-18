#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int increment; } ;
typedef  TYPE_1__ strbuf_t ;

/* Variables and functions */
 int /*<<< orphan*/  die (char*) ; 

void strbuf_set_increment(strbuf_t *s, int increment)
{
    /* Increment > 0:  Linear buffer growth rate
     * Increment < -1: Exponential buffer growth rate */
    if (increment == 0 || increment == -1)
        die("BUG: Invalid string increment");

    s->increment = increment;
}