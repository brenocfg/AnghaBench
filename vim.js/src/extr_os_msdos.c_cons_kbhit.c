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
 int /*<<< orphan*/  cons_getkey () ; 
 scalar_t__ cons_key ; 

__attribute__((used)) static int
cons_kbhit(void)
{
    if (cons_key < 0)
	cons_getkey();
    return (cons_key >= 0);
}