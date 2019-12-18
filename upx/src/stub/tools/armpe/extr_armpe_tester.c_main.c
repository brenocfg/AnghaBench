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
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fopen (char*,char*) ; 
 int main2 (int,char**) ; 
 int /*<<< orphan*/  out ; 
 int /*<<< orphan*/  stdout ; 

int main(int argc, char **argv)
{
    out = stdout;
#ifndef __linux__
    out = fopen("/wtest.log", "wt");
#endif
    int ret = main2(argc, argv);
    fclose(out);
    return ret;
}