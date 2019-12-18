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
 scalar_t__ DT_DIR ; 
 scalar_t__ DT_LNK ; 
 scalar_t__ DT_UNKNOWN ; 
 int FALSE ; 
 int FILE_ATTRIBUTE_DIRECTORY ; 
 int GetFileAttributesA (char*) ; 
 int S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ag_asprintf (char**,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ stat (char*,struct stat*) ; 

int is_directory(const char *path, const struct dirent *d) {
#ifdef HAVE_DIRENT_DTYPE
    /* Some filesystems, e.g. ReiserFS, always return a type DT_UNKNOWN from readdir or scandir. */
    /* Call stat if we don't find DT_DIR to get the information we need. */
    /* Also works for symbolic links to directories. */
    if (d->d_type != DT_UNKNOWN && d->d_type != DT_LNK) {
        return d->d_type == DT_DIR;
    }
#endif
    char *full_path;
    struct stat s;
    ag_asprintf(&full_path, "%s/%s", path, d->d_name);
    if (stat(full_path, &s) != 0) {
        free(full_path);
        return FALSE;
    }
#ifdef _WIN32
    int is_dir = GetFileAttributesA(full_path) & FILE_ATTRIBUTE_DIRECTORY;
#else
    int is_dir = S_ISDIR(s.st_mode);
#endif
    free(full_path);
    return is_dir;
}