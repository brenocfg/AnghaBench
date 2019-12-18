#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  path; } ;
typedef  TYPE_1__ UnitFileList ;

/* Variables and functions */
 char const* basename (int /*<<< orphan*/ ) ; 
 int strcasecmp (char const*,char const*) ; 
 char* strrchr (int /*<<< orphan*/ ,char) ; 

__attribute__((used)) static int compare_unit_file_list(const UnitFileList *a, const UnitFileList *b) {
        const char *d1, *d2;

        d1 = strrchr(a->path, '.');
        d2 = strrchr(b->path, '.');

        if (d1 && d2) {
                int r;

                r = strcasecmp(d1, d2);
                if (r != 0)
                        return r;
        }

        return strcasecmp(basename(a->path), basename(b->path));
}