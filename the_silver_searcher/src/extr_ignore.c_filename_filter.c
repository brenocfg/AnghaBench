#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct dirent {char* d_name; size_t d_namlen; } ;
struct TYPE_5__ {char* path_start; TYPE_2__* ig; } ;
typedef  TYPE_1__ scandir_baton_t ;
struct TYPE_6__ {struct TYPE_6__* parent; int /*<<< orphan*/ * extensions; int /*<<< orphan*/  extensions_len; } ;
typedef  TYPE_2__ ignores ;
struct TYPE_7__ {int /*<<< orphan*/  path_to_ignore; scalar_t__ search_all_files; int /*<<< orphan*/  follow_symlinks; int /*<<< orphan*/  search_hidden_files; } ;

/* Variables and functions */
 int /*<<< orphan*/  ag_asprintf (char**,char*,char const*) ; 
 int binary_search (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ ** evil_hardcoded_ignore_files ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ is_directory (char const*,struct dirent const*) ; 
 scalar_t__ is_named_pipe (char const*,struct dirent const*) ; 
 scalar_t__ is_symlink (char const*,struct dirent const*) ; 
 int /*<<< orphan*/  log_debug (char*,char const*,...) ; 
 TYPE_4__ opts ; 
 int path_ignore_search (TYPE_2__ const*,char const*,char const*) ; 
 char* strchr (char const*,char) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ *) ; 
 size_t strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 

int filename_filter(const char *path, const struct dirent *dir, void *baton) {
    const char *filename = dir->d_name;
    if (!opts.search_hidden_files && filename[0] == '.') {
        return 0;
    }

    size_t i;
    for (i = 0; evil_hardcoded_ignore_files[i] != NULL; i++) {
        if (strcmp(filename, evil_hardcoded_ignore_files[i]) == 0) {
            return 0;
        }
    }

    if (!opts.follow_symlinks && is_symlink(path, dir)) {
        log_debug("File %s ignored becaused it's a symlink", dir->d_name);
        return 0;
    }

    if (is_named_pipe(path, dir)) {
        log_debug("%s ignored because it's a named pipe or socket", path);
        return 0;
    }

    if (opts.search_all_files && !opts.path_to_ignore) {
        return 1;
    }

    scandir_baton_t *scandir_baton = (scandir_baton_t *)baton;
    const char *path_start = scandir_baton->path_start;

    const char *extension = strchr(filename, '.');
    if (extension) {
        if (extension[1]) {
            // The dot is not the last character, extension starts at the next one
            ++extension;
        } else {
            // No extension
            extension = NULL;
        }
    }

#ifdef HAVE_DIRENT_DNAMLEN
    size_t filename_len = dir->d_namlen;
#else
    size_t filename_len = 0;
#endif

    if (strncmp(filename, "./", 2) == 0) {
#ifndef HAVE_DIRENT_DNAMLEN
        filename_len = strlen(filename);
#endif
        filename++;
        filename_len--;
    }

    const ignores *ig = scandir_baton->ig;

    while (ig != NULL) {
        if (extension) {
            int match_pos = binary_search(extension, ig->extensions, 0, ig->extensions_len);
            if (match_pos >= 0) {
                log_debug("file %s ignored because name matches extension %s", filename, ig->extensions[match_pos]);
                return 0;
            }
        }

        if (path_ignore_search(ig, path_start, filename)) {
            return 0;
        }

        if (is_directory(path, dir)) {
#ifndef HAVE_DIRENT_DNAMLEN
            if (!filename_len) {
                filename_len = strlen(filename);
            }
#endif
            if (filename[filename_len - 1] != '/') {
                char *temp;
                ag_asprintf(&temp, "%s/", filename);
                int rv = path_ignore_search(ig, path_start, temp);
                free(temp);
                if (rv) {
                    return 0;
                }
            }
        }
        ig = ig->parent;
    }

    log_debug("%s not ignored", filename);
    return 1;
}