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
 int /*<<< orphan*/  DSCAPS_CERTIFIED ; 
 int /*<<< orphan*/  DSCAPS_CONTINUOUSRATE ; 
 int /*<<< orphan*/  DSCAPS_EMULDRIVER ; 
 int /*<<< orphan*/  DSCAPS_PRIMARY16BIT ; 
 int /*<<< orphan*/  DSCAPS_PRIMARY8BIT ; 
 int /*<<< orphan*/  DSCAPS_PRIMARYMONO ; 
 int /*<<< orphan*/  DSCAPS_PRIMARYSTEREO ; 
 int /*<<< orphan*/  DSCAPS_SECONDARY16BIT ; 
 int /*<<< orphan*/  DSCAPS_SECONDARY8BIT ; 
 int /*<<< orphan*/  DSCAPS_SECONDARYMONO ; 
 int /*<<< orphan*/  DSCAPS_SECONDARYSTEREO ; 
 int /*<<< orphan*/  TRACE (char*,char const*) ; 

__attribute__((used)) static void _dump_DSCAPS(DWORD xmask) {
    struct {
        DWORD   mask;
        const char    *name;
    } flags[] = {
#define FE(x) { x, #x },
        FE(DSCAPS_PRIMARYMONO)
        FE(DSCAPS_PRIMARYSTEREO)
        FE(DSCAPS_PRIMARY8BIT)
        FE(DSCAPS_PRIMARY16BIT)
        FE(DSCAPS_CONTINUOUSRATE)
        FE(DSCAPS_EMULDRIVER)
        FE(DSCAPS_CERTIFIED)
        FE(DSCAPS_SECONDARYMONO)
        FE(DSCAPS_SECONDARYSTEREO)
        FE(DSCAPS_SECONDARY8BIT)
        FE(DSCAPS_SECONDARY16BIT)
#undef FE
    };
    unsigned int     i;

    for (i=0;i<sizeof(flags)/sizeof(flags[0]);i++)
        if ((flags[i].mask & xmask) == flags[i].mask)
            TRACE("%s ",flags[i].name);
}