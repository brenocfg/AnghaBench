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
 int /*<<< orphan*/  R_FATAL ; 
 void* malloc (size_t) ; 
 int /*<<< orphan*/  report (int /*<<< orphan*/ ,char*) ; 

void *xmalloc (size_t len)
{
    void *p = malloc (len);

    if (!p) report (R_FATAL, "Out of memory.");
    return p;
}