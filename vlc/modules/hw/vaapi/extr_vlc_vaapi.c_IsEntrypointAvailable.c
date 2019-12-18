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
typedef  scalar_t__ VAStatus ;
typedef  int /*<<< orphan*/  VAProfile ;
typedef  scalar_t__ VAEntrypoint ;
typedef  int /*<<< orphan*/  VADisplay ;

/* Variables and functions */
 scalar_t__ VA_STATUS_SUCCESS ; 
 int /*<<< orphan*/  free (scalar_t__*) ; 
 int vaMaxNumEntrypoints (int /*<<< orphan*/ ) ; 
 scalar_t__ vaQueryConfigEntrypoints (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int*) ; 
 scalar_t__* vlc_alloc (int,int) ; 

__attribute__((used)) static bool
IsEntrypointAvailable(VADisplay dpy, VAProfile i_profile,
                      VAEntrypoint entrypoint)
{
    VAEntrypoint *      entrypoints;
    int                 num_entrypoints = vaMaxNumEntrypoints(dpy);
    bool                ret = false;

    if (num_entrypoints <= 0)
        return false;
    entrypoints = vlc_alloc(num_entrypoints, sizeof(VAEntrypoint));

    if (!entrypoints)
        return false;

    VAStatus status =
        vaQueryConfigEntrypoints(dpy, i_profile, entrypoints, &num_entrypoints);
    if (status != VA_STATUS_SUCCESS)
        goto error;

    for (int i = 0; i < num_entrypoints; ++i)
        if (entrypoint == entrypoints[i])
        {
            ret = true;
            break;
        }

error:
    free(entrypoints);
    return ret;
}