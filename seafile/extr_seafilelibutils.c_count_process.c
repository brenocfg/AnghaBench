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
struct dirent {char* d_name; } ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ find_process_in_dirent (struct dirent*,char const*) ; 
 int /*<<< orphan*/  g_warning (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * opendir (char*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

int count_process(const char *process_name)
{
    int count = 0;
    DIR *proc_dir = opendir("/proc");
    if (!proc_dir) {
        g_warning ("failed to open /proc/ :%s\n", strerror(errno));
        return FALSE;
    }

    struct dirent *subdir = NULL;
    while ((subdir = readdir(proc_dir))) {
        char first = subdir->d_name[0];
        /* /proc/[1-9][0-9]* */
        if (first > '9' || first < '1')
            continue;
        if (find_process_in_dirent(subdir, process_name) > 0) {
            count++;
        }
    }

    closedir (proc_dir);
    return count;
}