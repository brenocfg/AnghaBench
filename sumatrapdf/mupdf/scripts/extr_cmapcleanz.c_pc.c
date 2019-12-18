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
 int /*<<< orphan*/  printf (char*,unsigned int) ; 

void pc(unsigned int c)
{
	if (c <= 0xff) printf("<%02x>", c);
	else if (c <= 0xffff) printf("<%04x>", c);
	else if (c <= 0xffffff) printf("<%06x>", c);
	else printf("<%08x>", c);
}