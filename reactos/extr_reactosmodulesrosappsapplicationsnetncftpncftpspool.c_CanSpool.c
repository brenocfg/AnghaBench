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
typedef  int /*<<< orphan*/  sdir ;

/* Variables and functions */
 scalar_t__ MkSpoolDir (char*,int) ; 
 char* gOurDirectoryPath ; 

int
CanSpool(void)
{
	char sdir[256];

	if (gOurDirectoryPath[0] == '\0') {
		return (-1);
	}
	if (MkSpoolDir(sdir, sizeof(sdir)) < 0)
		return (-1);
	return (0);
}