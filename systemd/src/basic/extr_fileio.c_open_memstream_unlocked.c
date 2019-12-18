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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  FSETLOCKING_BYCALLER ; 
 int /*<<< orphan*/  __fsetlocking (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * open_memstream (char**,size_t*) ; 

FILE* open_memstream_unlocked(char **ptr, size_t *sizeloc) {
        FILE *f = open_memstream(ptr, sizeloc);
        if (!f)
                return NULL;

        (void) __fsetlocking(f, FSETLOCKING_BYCALLER);

        return f;
}