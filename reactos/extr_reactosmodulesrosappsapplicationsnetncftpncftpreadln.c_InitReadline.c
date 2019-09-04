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
 int /*<<< orphan*/  CompletionFunction ; 
 int /*<<< orphan*/  LoadHistory () ; 
 int /*<<< orphan*/  ReCacheBookmarks () ; 
 int /*<<< orphan*/  gScreenColumns ; 
 int /*<<< orphan*/  gl_completion_proc ; 
 int /*<<< orphan*/  gl_setwidth (int /*<<< orphan*/ ) ; 

void
InitReadline(void)
{
	gl_completion_proc = CompletionFunction;
	gl_setwidth(gScreenColumns);
	LoadHistory();
	ReCacheBookmarks();
}