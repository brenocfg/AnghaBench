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
typedef  int gint64 ;
struct TYPE_8__ {int /*<<< orphan*/  message; } ;
struct TYPE_7__ {scalar_t__ st_size; int /*<<< orphan*/  st_mode; } ;
typedef  TYPE_1__ STAT_STRUCT ;
typedef  TYPE_2__ GError ;
typedef  int /*<<< orphan*/  GDir ;

/* Variables and functions */
 int /*<<< orphan*/  CCNET_DOMAIN ; 
 scalar_t__ STAT_FUNC (char*,TYPE_1__*) ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 char* g_build_filename (char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_dir_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_dir_open (char const*,int /*<<< orphan*/ ,TYPE_2__**) ; 
 char* g_dir_read_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 int /*<<< orphan*/  g_set_error (TYPE_2__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static gint64
calc_recursively (const char *path, GError **calc_error)
{
    gint64 sum = 0;

    GError *error = NULL;
    GDir *folder = g_dir_open(path, 0, &error);
    if (!folder) {
        g_set_error (calc_error, CCNET_DOMAIN, 0,
                     "g_open() dir %s failed:%s\n", path, error->message);
        return -1;
    }

    const char *name = NULL;
    while ((name = g_dir_read_name(folder)) != NULL) {
        STAT_STRUCT sb;
        char *full_path= g_build_filename (path, name, NULL);
        if (STAT_FUNC(full_path, &sb) < 0) {
            g_set_error (calc_error, CCNET_DOMAIN, 0, "failed to stat on %s: %s\n",
                         full_path, strerror(errno));
            g_free(full_path);
            g_dir_close(folder);
            return -1;
        }

        if (S_ISDIR(sb.st_mode)) {
            gint64 size = calc_recursively(full_path, calc_error);
            if (size < 0) {
                g_free (full_path);
                g_dir_close (folder);
                return -1;
            }
            sum += size;
            g_free(full_path);
        } else if (S_ISREG(sb.st_mode)) {
            sum += sb.st_size;
            g_free(full_path);
        }
    }

    g_dir_close (folder);
    return sum;
}