#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int member_2; int /*<<< orphan*/ * longname; int /*<<< orphan*/ * name; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ vlc_sd_probe_t ;
typedef  int /*<<< orphan*/  vlc_probe_t ;
typedef  int /*<<< orphan*/  names ;

/* Variables and functions */
 int VLC_ENOMEM ; 
 int VLC_PROBE_CONTINUE ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strdup (char const*) ; 
 scalar_t__ unlikely (int) ; 
 scalar_t__ vlc_probe_add (int /*<<< orphan*/ *,TYPE_1__*,int) ; 

int vlc_sd_probe_Add (vlc_probe_t *probe, const char *name,
                      const char *longname, int category)
{
    vlc_sd_probe_t names = { strdup(name), strdup(longname), category };

    if (unlikely (names.name == NULL || names.longname == NULL
               || vlc_probe_add (probe, &names, sizeof (names))))
    {
        free (names.name);
        free (names.longname);
        return VLC_ENOMEM;
    }
    return VLC_PROBE_CONTINUE;
}