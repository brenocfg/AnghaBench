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
typedef  int /*<<< orphan*/  gboolean ;
typedef  int /*<<< orphan*/  SeafDirent ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static int
threeway_diff_dirs (int n, const char *basedir, SeafDirent *dirs[], void *vdata,
                    gboolean *recurse)
{
    *recurse = TRUE;
    return 0;
}