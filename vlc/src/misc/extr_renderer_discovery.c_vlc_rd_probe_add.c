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
typedef  int /*<<< orphan*/  vlc_probe_t ;
struct vlc_rd_probe {int /*<<< orphan*/ * psz_longname; int /*<<< orphan*/ * psz_name; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  names ;

/* Variables and functions */
 int VLC_ENOMEM ; 
 int VLC_PROBE_CONTINUE ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strdup (char const*) ; 
 scalar_t__ unlikely (int) ; 
 scalar_t__ vlc_probe_add (int /*<<< orphan*/ *,struct vlc_rd_probe*,int) ; 

int
vlc_rd_probe_add(vlc_probe_t *probe, const char *psz_name,
                 const char *psz_longname)
{
    struct vlc_rd_probe names = { strdup(psz_name), strdup(psz_longname) };

    if (unlikely(names.psz_name == NULL || names.psz_longname == NULL
                 || vlc_probe_add(probe, &names, sizeof(names))))
    {
        free(names.psz_name);
        free(names.psz_longname);
        return VLC_ENOMEM;
    }
    return VLC_PROBE_CONTINUE;
}