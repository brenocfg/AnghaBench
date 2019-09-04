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
 int /*<<< orphan*/  fatal_error (char*) ; 

void
usage (void)
{
  fatal_error("\
Usage: mkdosfs [-A] [-c] [-C] [-v] [-I] [-l bad-block-file] [-b backup-boot-sector]\n\
       [-m boot-msg-file] [-n volume-name] [-i volume-id]\n\
       [-s sectors-per-cluster] [-S logical-sector-size] [-f number-of-FATs]\n\
       [-F fat-size] [-r root-dir-entries] [-R reserved-sectors]\n\
       /dev/name [blocks]\n");
}