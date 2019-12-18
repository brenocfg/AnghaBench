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
struct stat {int /*<<< orphan*/  st_mode; } ;
struct dirent {scalar_t__ d_type; int /*<<< orphan*/  d_name; } ;

/* Variables and functions */
 scalar_t__ DT_FIFO ; 
 scalar_t__ DT_LNK ; 
 scalar_t__ DT_SOCK ; 
 scalar_t__ DT_UNKNOWN ; 
 int FALSE ; 
 scalar_t__ S_ISFIFO (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISSOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ag_asprintf (char**,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ stat (char*,struct stat*) ; 

int is_named_pipe(const char *path, const struct dirent *d) {
#ifdef HAVE_DIRENT_DTYPE
    if (d->d_type != DT_UNKNOWN && d->d_type != DT_LNK) {
        return d->d_type == DT_FIFO || d->d_type == DT_SOCK;
    }
#endif
    char *full_path;
    struct stat s;
    ag_asprintf(&full_path, "%s/%s", path, d->d_name);
    if (stat(full_path, &s) != 0) {
        free(full_path);
        return FALSE;
    }
    free(full_path);
    return S_ISFIFO(s.st_mode)
#ifdef S_ISSOCK
           || S_ISSOCK(s.st_mode)
#endif
        ;
}