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
 int /*<<< orphan*/  B_TRUE ; 
 int zpool_do_attach_or_replace (int,char**,int /*<<< orphan*/ ) ; 

int
zpool_do_replace(int argc, char **argv)
{
	return (zpool_do_attach_or_replace(argc, argv, B_TRUE));
}