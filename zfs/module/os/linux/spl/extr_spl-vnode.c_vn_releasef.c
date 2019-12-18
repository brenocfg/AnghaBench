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
 int /*<<< orphan*/  P_FINFO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  areleasef (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 

void
vn_releasef(int fd)
{
	areleasef(fd, P_FINFO(current));
}