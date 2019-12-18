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
 int /*<<< orphan*/  cover_back () ; 
 int /*<<< orphan*/  cover_fast () ; 
 int /*<<< orphan*/  cover_inflate () ; 
 int /*<<< orphan*/  cover_support () ; 
 int /*<<< orphan*/  cover_trees () ; 
 int /*<<< orphan*/  cover_wrap () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 char* zlibVersion () ; 

int main(void)
{
    fprintf(stderr, "%s\n", zlibVersion());
    cover_support();
    cover_wrap();
    cover_back();
    cover_inflate();
    cover_trees();
    cover_fast();
    return 0;
}