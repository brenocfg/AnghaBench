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
 int ADV_SIZE ; 
 scalar_t__ adv_consistent (unsigned char*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  syslinux_reset_adv (unsigned char*) ; 

int syslinux_validate_adv(unsigned char *advbuf)
{
    if (adv_consistent(advbuf + 0 * ADV_SIZE)) {
	memcpy(advbuf + ADV_SIZE, advbuf, ADV_SIZE);
	return 0;
    } else if (adv_consistent(advbuf + 1 * ADV_SIZE)) {
	memcpy(advbuf, advbuf + ADV_SIZE, ADV_SIZE);
	return 0;
    } else {
	syslinux_reset_adv(advbuf);
	return -1;
    }
}