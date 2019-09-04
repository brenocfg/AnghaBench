#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT ;
struct TYPE_7__ {TYPE_1__** ChannelMap; } ;
struct TYPE_6__ {scalar_t__ loaded; scalar_t__ hMidi; } ;
typedef  TYPE_2__ MIDIMAPDATA ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ MIDIMAP_IsBadData (TYPE_2__*) ; 
 scalar_t__ MMSYSERR_ERROR ; 
 scalar_t__ MMSYSERR_NOERROR ; 
 scalar_t__ midiOutClose (scalar_t__) ; 

__attribute__((used)) static	DWORD	modClose(MIDIMAPDATA* mom)
{
    UINT	i;
    DWORD	ret = MMSYSERR_NOERROR;

    if (MIDIMAP_IsBadData(mom)) 	return MMSYSERR_ERROR;

    for (i = 0; i < 16; i++)
    {
	DWORD	t;
	if (mom->ChannelMap[i] && mom->ChannelMap[i]->loaded > 0)
	{
	    t = midiOutClose(mom->ChannelMap[i]->hMidi);
	    if (t == MMSYSERR_NOERROR)
	    {
		mom->ChannelMap[i]->loaded = 0;
		mom->ChannelMap[i]->hMidi = 0;
	    }
	    else if (ret == MMSYSERR_NOERROR)
		ret = t;
	}
    }
    if (ret == MMSYSERR_NOERROR)
	HeapFree(GetProcessHeap(), 0, mom);
    return ret;
}