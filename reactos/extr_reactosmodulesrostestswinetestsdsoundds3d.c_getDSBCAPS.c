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
typedef  int /*<<< orphan*/  flags ;
typedef  int DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
#define  DSBCAPS_CTRL3D 140 
#define  DSBCAPS_CTRLFREQUENCY 139 
#define  DSBCAPS_CTRLPAN 138 
#define  DSBCAPS_CTRLPOSITIONNOTIFY 137 
#define  DSBCAPS_CTRLVOLUME 136 
#define  DSBCAPS_GETCURRENTPOSITION2 135 
#define  DSBCAPS_GLOBALFOCUS 134 
#define  DSBCAPS_LOCHARDWARE 133 
#define  DSBCAPS_LOCSOFTWARE 132 
#define  DSBCAPS_MUTE3DATMAXDISTANCE 131 
#define  DSBCAPS_PRIMARYBUFFER 130 
#define  DSBCAPS_STATIC 129 
#define  DSBCAPS_STICKYFOCUS 128 
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 

const char * getDSBCAPS(DWORD xmask) {
    static struct {
        DWORD   mask;
        const char    *name;
    } flags[] = {
#define FE(x) { x, #x },
        FE(DSBCAPS_PRIMARYBUFFER)
        FE(DSBCAPS_STATIC)
        FE(DSBCAPS_LOCHARDWARE)
        FE(DSBCAPS_LOCSOFTWARE)
        FE(DSBCAPS_CTRL3D)
        FE(DSBCAPS_CTRLFREQUENCY)
        FE(DSBCAPS_CTRLPAN)
        FE(DSBCAPS_CTRLVOLUME)
        FE(DSBCAPS_CTRLPOSITIONNOTIFY)
        FE(DSBCAPS_STICKYFOCUS)
        FE(DSBCAPS_GLOBALFOCUS)
        FE(DSBCAPS_GETCURRENTPOSITION2)
        FE(DSBCAPS_MUTE3DATMAXDISTANCE)
#undef FE
    };
    static char buffer[512];
    unsigned int i;
    BOOL first = TRUE;

    buffer[0] = 0;

    for (i=0;i<sizeof(flags)/sizeof(flags[0]);i++) {
        if ((flags[i].mask & xmask) == flags[i].mask) {
            if (first)
                first = FALSE;
            else
                strcat(buffer, "|");
            strcat(buffer, flags[i].name);
        }
    }

    return buffer;
}