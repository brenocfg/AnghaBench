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
 int FIRST_MODIFIER ; 
 int LAST_MODIFIER ; 
 scalar_t__* keystate ; 
 int /*<<< orphan*/  xkeymap_init () ; 

void
init_keyboard()
{
	int i;
	for (i = 0; i < LAST_MODIFIER - FIRST_MODIFIER; i++)
		keystate[i] = 0;

	xkeymap_init();
}