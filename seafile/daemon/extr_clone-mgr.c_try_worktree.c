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
 int /*<<< orphan*/  F_OK ; 
 scalar_t__ g_access (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 char* g_strdup_printf (char*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *
try_worktree (const char *worktree)
{
    char *tmp;
    unsigned int cnt;

    /* There is a repo name conflict, so we try to add a postfix */
    cnt = 1;
    while (1) {
        tmp = g_strdup_printf("%s-%d", worktree, cnt++);
        if (g_access(tmp, F_OK) < 0) {
            return tmp;
        }

        if (cnt == -1U) {
            /* we have tried too much times, so give up */
            g_free(tmp);
            return NULL;
        }

        g_free(tmp);
    }

    /* XXX: never reach here */
}