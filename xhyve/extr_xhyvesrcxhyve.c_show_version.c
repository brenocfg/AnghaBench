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
 char* VERSION ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*,char*) ; 
 char* progname ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) __attribute__ ((noreturn)) static void
show_version()
{
        fprintf(stderr, "%s: %s\n\n%s\n",progname, VERSION,
		"xhyve is a port of FreeBSD's bhyve hypervisor to OS X that\n"
		"works entirely in userspace and has no other dependencies.\n\n"
		"Homepage: http://www.xhyve.xyz\n"
		"License: BSD\n");
		exit(0);
}