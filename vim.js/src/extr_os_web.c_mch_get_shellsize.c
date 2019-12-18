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
 int Columns ; 
 int OK ; 
 int Rows ; 
 int /*<<< orphan*/  limit_screen_size () ; 

int
mch_get_shellsize()
{
    Rows = 1;
    Columns = 1;
    limit_screen_size();
    return OK;
}