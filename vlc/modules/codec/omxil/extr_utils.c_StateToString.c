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
typedef  int /*<<< orphan*/  psz_names ;
typedef  size_t OMX_STATETYPE ;

/* Variables and functions */

const char *StateToString(OMX_STATETYPE state)
{
    static const char *psz_names[] = {
        "OMX_StateInvalid", "OMX_StateLoaded", "OMX_StateIdle",
        "OMX_StateExecuting", "OMX_StatePause", "OMX_StateWaitForResources",
        "OMX_State unknown"
    };

    if((unsigned int)state > sizeof(psz_names)/sizeof(char*)-1)
        state = (OMX_STATETYPE)(sizeof(psz_names)/sizeof(char*)-1);
    return psz_names[state];
}