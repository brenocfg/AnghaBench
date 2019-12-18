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
 int /*<<< orphan*/  ADV_LEN ; 
 int /*<<< orphan*/  cleanup_adv (unsigned char*) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void syslinux_reset_adv(unsigned char *advbuf)
{
    /* Create an all-zero ADV */
    memset(advbuf + 2 * 4, 0, ADV_LEN);
    cleanup_adv(advbuf);
}