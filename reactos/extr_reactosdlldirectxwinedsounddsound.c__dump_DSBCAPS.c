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

/* Variables and functions */
 int /*<<< orphan*/  DSBCAPS_CTRL3D ; 
 int /*<<< orphan*/  DSBCAPS_CTRLFREQUENCY ; 
 int /*<<< orphan*/  DSBCAPS_CTRLPAN ; 
 int /*<<< orphan*/  DSBCAPS_CTRLPOSITIONNOTIFY ; 
 int /*<<< orphan*/  DSBCAPS_CTRLVOLUME ; 
 int /*<<< orphan*/  DSBCAPS_GETCURRENTPOSITION2 ; 
 int /*<<< orphan*/  DSBCAPS_GLOBALFOCUS ; 
 int /*<<< orphan*/  DSBCAPS_LOCHARDWARE ; 
 int /*<<< orphan*/  DSBCAPS_LOCSOFTWARE ; 
 int /*<<< orphan*/  DSBCAPS_MUTE3DATMAXDISTANCE ; 
 int /*<<< orphan*/  DSBCAPS_PRIMARYBUFFER ; 
 int /*<<< orphan*/  DSBCAPS_STATIC ; 
 int /*<<< orphan*/  DSBCAPS_STICKYFOCUS ; 
 int /*<<< orphan*/  TRACE (char*,char const*) ; 

__attribute__((used)) static void _dump_DSBCAPS(DWORD xmask) {
    struct {
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
    unsigned int     i;

    for (i=0;i<sizeof(flags)/sizeof(flags[0]);i++)
        if ((flags[i].mask & xmask) == flags[i].mask)
            TRACE("%s ",flags[i].name);
}