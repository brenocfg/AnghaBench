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
struct vlc_run_args {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  stderr ; 
 int vlc_demux_process_url (struct vlc_run_args const*,char*) ; 
 char* vlc_path2uri (char const*,int /*<<< orphan*/ *) ; 

int vlc_demux_process_path(const struct vlc_run_args *args, const char *path)
{
    char *url = vlc_path2uri(path, NULL);
    if (url == NULL)
    {
        fprintf(stderr, "Error: cannot convert path to URL: %s\n", path);
        return -1;
    }

    int ret = vlc_demux_process_url(args, url);
    free(url);
    return ret;
}