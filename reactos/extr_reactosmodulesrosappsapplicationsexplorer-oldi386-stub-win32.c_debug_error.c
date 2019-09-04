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
 scalar_t__ remote_debug ; 
 int /*<<< orphan*/  stderr ; 

void debug_error (char* format/*, char* parm*/)
{
  if (remote_debug)
    fprintf (stderr, format/*, parm*/);
}