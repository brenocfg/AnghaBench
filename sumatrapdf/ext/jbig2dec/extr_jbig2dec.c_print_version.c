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
 int JBIG2_VERSION_MAJOR ; 
 int JBIG2_VERSION_MINOR ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static int
print_version(void)
{
    fprintf(stdout, "jbig2dec %d.%d\n", JBIG2_VERSION_MAJOR, JBIG2_VERSION_MINOR);
    return 0;
}