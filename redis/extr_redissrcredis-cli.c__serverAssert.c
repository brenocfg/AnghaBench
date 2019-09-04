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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 

void _serverAssert(const char *estr, const char *file, int line) {
    fprintf(stderr, "=== ASSERTION FAILED ===");
    fprintf(stderr, "==> %s:%d '%s' is not true",file,line,estr);
    *((char*)-1) = 'x';
}