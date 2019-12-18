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
 int /*<<< orphan*/  XMLLINT_ERR_MEM ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int maxmem ; 
 int /*<<< orphan*/  progresult ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
OOM(void)
{
    fprintf(stderr, "Ran out of memory needs > %d bytes\n", maxmem);
    progresult = XMLLINT_ERR_MEM;
}