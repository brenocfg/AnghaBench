#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* buf; int /*<<< orphan*/  iovw; int /*<<< orphan*/  size; } ;
typedef  TYPE_1__ JournalImporter ;

/* Variables and functions */
 char* GREEDY_REALLOC (char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  iovw_rebase (int /*<<< orphan*/ *,char*,char*) ; 

__attribute__((used)) static char* realloc_buffer(JournalImporter *imp, size_t size) {
        char *b, *old = imp->buf;

        b = GREEDY_REALLOC(imp->buf, imp->size, size);
        if (!b)
                return NULL;

        iovw_rebase(&imp->iovw, old, imp->buf);

        return b;
}