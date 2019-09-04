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
typedef  int /*<<< orphan*/ * gl_tab_completion_proc ;

/* Variables and functions */
 int /*<<< orphan*/ * gl_completion_proc ; 
 int /*<<< orphan*/ * gl_local_filename_completion_proc ; 

void
gl_tab_completion(gl_tab_completion_proc proc)
{
	if (proc == NULL)
		proc = gl_local_filename_completion_proc;	/* default proc */
	gl_completion_proc = proc;
}