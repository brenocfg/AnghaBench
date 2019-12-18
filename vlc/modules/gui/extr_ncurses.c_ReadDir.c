#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct dir_entry_t {int /*<<< orphan*/ * path; int /*<<< orphan*/  file; } ;
struct TYPE_7__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ intf_thread_t ;
struct TYPE_8__ {scalar_t__ n_dir_entries; int /*<<< orphan*/  dir_entries; int /*<<< orphan*/ * current_dir; int /*<<< orphan*/  show_hidden_files; } ;
typedef  TYPE_2__ intf_sys_t ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int /*<<< orphan*/  DirsDestroy (TYPE_2__*) ; 
 int /*<<< orphan*/  IsFile (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  TAB_APPEND (scalar_t__,int /*<<< orphan*/ ,struct dir_entry_t*) ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  comdir_entries ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (struct dir_entry_t*) ; 
 struct dir_entry_t* malloc (int) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  msg_Warn (TYPE_1__*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qsort (int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/ * strdup (char const*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vlc_opendir (int /*<<< orphan*/ *) ; 
 char* vlc_readdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_strerror_c (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ReadDir(intf_thread_t *intf)
{
    intf_sys_t *sys = intf->p_sys;

    if (!sys->current_dir || !*sys->current_dir) {
        msg_Dbg(intf, "no current dir set");
        return;
    }

    DIR *current_dir = vlc_opendir(sys->current_dir);
    if (!current_dir) {
        msg_Warn(intf, "cannot open directory `%s' (%s)", sys->current_dir,
                 vlc_strerror_c(errno));
        return;
    }

    DirsDestroy(sys);

    const char *entry;
    while ((entry = vlc_readdir(current_dir))) {
        if (!sys->show_hidden_files && *entry == '.' && strcmp(entry, ".."))
            continue;

        struct dir_entry_t *dir_entry = malloc(sizeof *dir_entry);
        if (unlikely(dir_entry == NULL))
            continue;

        dir_entry->file = IsFile(sys->current_dir, entry);
        dir_entry->path = strdup(entry);
        if (unlikely(dir_entry->path == NULL))
        {
            free(dir_entry);
            continue;
        }
        TAB_APPEND(sys->n_dir_entries, sys->dir_entries, dir_entry);
        continue;
    }

    closedir(current_dir);

    if (sys->n_dir_entries > 0)
        qsort(sys->dir_entries, sys->n_dir_entries,
              sizeof(struct dir_entry_t*), &comdir_entries);
}