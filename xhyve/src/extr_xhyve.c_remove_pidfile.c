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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * pidfile ; 
 int /*<<< orphan*/  stderr ; 
 int unlink (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
remove_pidfile()
{
	int error;

	if (pidfile == NULL)
		return;

	error = unlink(pidfile);
	if (error < 0)
		fprintf(stderr, "Failed to remove pidfile\n");
}