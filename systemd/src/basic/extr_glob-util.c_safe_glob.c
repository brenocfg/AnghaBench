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
struct TYPE_4__ {struct dirent* (* gl_readdir ) (void*) ;void* (* gl_opendir ) (char const*) ;int /*<<< orphan*/  gl_pathv; scalar_t__ gl_stat; scalar_t__ gl_lstat; scalar_t__ gl_closedir; } ;
typedef  TYPE_1__ glob_t ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int ENOENT ; 
 int ENOMEM ; 
 int GLOB_ALTDIRFUNC ; 
 int GLOB_NOMATCH ; 
 int GLOB_NOSPACE ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ closedir_wrapper ; 
 scalar_t__ errno ; 
 int errno_or_else (int /*<<< orphan*/ ) ; 
 int glob (char const*,int,int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ lstat ; 
 scalar_t__ opendir ; 
 scalar_t__ readdir_no_dot ; 
 scalar_t__ stat ; 
 scalar_t__ strv_isempty (int /*<<< orphan*/ ) ; 

int safe_glob(const char *path, int flags, glob_t *pglob) {
        int k;

        /* We want to set GLOB_ALTDIRFUNC ourselves, don't allow it to be set. */
        assert(!(flags & GLOB_ALTDIRFUNC));

        if (!pglob->gl_closedir)
                pglob->gl_closedir = closedir_wrapper;
        if (!pglob->gl_readdir)
                pglob->gl_readdir = (struct dirent *(*)(void *)) readdir_no_dot;
        if (!pglob->gl_opendir)
                pglob->gl_opendir = (void *(*)(const char *)) opendir;
        if (!pglob->gl_lstat)
                pglob->gl_lstat = lstat;
        if (!pglob->gl_stat)
                pglob->gl_stat = stat;

        errno = 0;
        k = glob(path, flags | GLOB_ALTDIRFUNC, NULL, pglob);
        if (k == GLOB_NOMATCH)
                return -ENOENT;
        if (k == GLOB_NOSPACE)
                return -ENOMEM;
        if (k != 0)
                return errno_or_else(EIO);
        if (strv_isempty(pglob->gl_pathv))
                return -ENOENT;

        return 0;
}