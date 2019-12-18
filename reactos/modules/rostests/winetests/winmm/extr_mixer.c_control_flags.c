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
typedef  int DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int MIXERCONTROL_CONTROLF_DISABLED ; 
 int MIXERCONTROL_CONTROLF_MULTIPLE ; 
 int MIXERCONTROL_CONTROLF_UNIFORM ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 

__attribute__((used)) static const char * control_flags(DWORD fdwControl)
{
    static char flags[100];
    BOOL first=TRUE;
    flags[0]=0;
    if (fdwControl&MIXERCONTROL_CONTROLF_UNIFORM) {
        strcat(flags,"MIXERCONTROL_CONTROLF_UNIFORM");
        first=FALSE;
    }
    if (fdwControl&MIXERCONTROL_CONTROLF_MULTIPLE) {
        if (!first)
            strcat(flags, "|");

        strcat(flags,"MIXERCONTROL_CONTROLF_MULTIPLE");
        first=FALSE;
    }

    if (fdwControl&MIXERCONTROL_CONTROLF_DISABLED) {
        if (!first)
            strcat(flags, "|");

        strcat(flags,"MIXERCONTROL_CONTROLF_DISABLED");
    }

    return flags;
}