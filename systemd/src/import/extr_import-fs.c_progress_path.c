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
struct stat {int dummy; } ;
struct TYPE_4__ {scalar_t__ size; int /*<<< orphan*/  path; } ;
typedef  TYPE_1__ ProgressInfo ;

/* Variables and functions */
 int EOWNERDEAD ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 scalar_t__ cancelled ; 
 int free_and_strdup (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  progress_show (TYPE_1__*) ; 

__attribute__((used)) static int progress_path(const char *path, const struct stat *st, void *userdata) {
        ProgressInfo *p = userdata;
        int r;

        assert(p);

        if (cancelled)
                return -EOWNERDEAD;

        r = free_and_strdup(&p->path, path);
        if (r < 0)
                return r;

        p->size = 0;

        progress_show(p);
        return 0;
}