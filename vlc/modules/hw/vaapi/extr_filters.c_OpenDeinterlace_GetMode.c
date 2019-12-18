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
struct deint_mode {char* name; } ;
typedef  int /*<<< orphan*/  filter_t ;
typedef  int /*<<< orphan*/  VAProcFilterCapDeinterlacing ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct deint_mode*) ; 
 scalar_t__ OpenDeinterlace_IsValidType (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned int,struct deint_mode*) ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 struct deint_mode* deint_modes ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  msg_Info (int /*<<< orphan*/ *,char*,char const*,char*) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static inline int
OpenDeinterlace_GetMode(filter_t * filter, char const * deint_mode,
                        struct deint_mode * p_deint_mode,
                        VAProcFilterCapDeinterlacing const caps[],
                        unsigned int num_caps)
{
    bool fallback = false;
    if (deint_mode && strcmp(deint_mode, "auto"))
    {
        for (unsigned int i = 0; i < ARRAY_SIZE(deint_modes); ++i)
        {
            if (!strcmp(deint_mode, deint_modes[i].name))
            {
                if (OpenDeinterlace_IsValidType(filter, caps, num_caps,
                                                deint_modes + i))
                {
                    *p_deint_mode = deint_modes[i];
                    msg_Dbg(filter, "using %s deinterlace method",
                            deint_modes[i].name);
                    return VLC_SUCCESS;
                }
            }
        }
        fallback = true;
    }

    for (unsigned int i = 0; i < ARRAY_SIZE(deint_modes); ++i)
        if (OpenDeinterlace_IsValidType(filter, caps, num_caps,
                                        deint_modes + i))
        {
            *p_deint_mode = deint_modes[i];
            if (fallback)
                msg_Info(filter, "%s algorithm not available, falling back to "
                         "%s algorithm", deint_mode, deint_modes[i].name);
            else
                msg_Dbg(filter, "using %s deinterlace method",
                        deint_modes[i].name);
            return VLC_SUCCESS;
        }

    /* We shouldn't be able to reach this, 'cause if there is no deinterlacing
       algorithm available, then the driver would have told us before the
       deinterlace filtering is not supported at all. */

    msg_Err(filter, "no algorithm available");
    return VLC_EGENERIC;
}