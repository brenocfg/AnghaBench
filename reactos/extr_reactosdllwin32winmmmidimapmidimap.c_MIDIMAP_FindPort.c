#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ isdigit (char const) ; 
 TYPE_1__* midiOutPorts ; 
 unsigned int numMidiOutPorts ; 
 scalar_t__ strcmpW (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  wine_dbgstr_w (int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL	MIDIMAP_FindPort(const WCHAR* name, unsigned* dev)
{
    for (*dev = 0; *dev < numMidiOutPorts; (*dev)++)
    {
	TRACE("%s\n", wine_dbgstr_w(midiOutPorts[*dev].name));
	if (strcmpW(midiOutPorts[*dev].name, name) == 0)
	    return TRUE;
    }
    /* try the form #nnn */
    if (*name == '#' && isdigit(name[1]))
    {
        const WCHAR*  ptr = name + 1;
        *dev = 0;
        do
        {
            *dev = *dev * 10 + *ptr - '0';
        } while (isdigit(*++ptr));
	if (*dev < numMidiOutPorts)
	    return TRUE;
    }
    return FALSE;
}