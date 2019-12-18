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
typedef  int MuError ;

/* Variables and functions */
 int /*<<< orphan*/  ReleaseSemaphore (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  loaded ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void render_progress(void *cookie, MuError error)
{
	assert((int)cookie == 5678);

	fprintf(stderr, "render_progress: error=%d\n", error);
	(void)ReleaseSemaphore(loaded, 1, NULL);
}