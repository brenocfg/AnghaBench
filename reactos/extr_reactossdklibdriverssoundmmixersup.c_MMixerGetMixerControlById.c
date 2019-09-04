#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ dwControlID; } ;
struct TYPE_15__ {int /*<<< orphan*/  NodeID; TYPE_1__ Control; } ;
struct TYPE_12__ {struct TYPE_12__* Flink; } ;
struct TYPE_14__ {TYPE_2__ ControlsList; } ;
struct TYPE_13__ {TYPE_2__ LineList; } ;
typedef  int /*<<< orphan*/ * PULONG ;
typedef  TYPE_2__* PLIST_ENTRY ;
typedef  int /*<<< orphan*/  MIXER_STATUS ;
typedef  TYPE_3__* LPMIXER_INFO ;
typedef  TYPE_4__* LPMIXERLINE_EXT ;
typedef  TYPE_5__* LPMIXERCONTROL_EXT ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ CONTAINING_RECORD (TYPE_2__*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  MIXERCONTROL_EXT ; 
 int /*<<< orphan*/  MIXERLINE_EXT ; 
 int /*<<< orphan*/  MM_STATUS_SUCCESS ; 
 int /*<<< orphan*/  MM_STATUS_UNSUCCESSFUL ; 

MIXER_STATUS
MMixerGetMixerControlById(
    LPMIXER_INFO MixerInfo,
    DWORD dwControlID,
    LPMIXERLINE_EXT *OutMixerLine,
    LPMIXERCONTROL_EXT *OutMixerControl,
    PULONG NodeId)
{
    PLIST_ENTRY Entry, ControlEntry;
    LPMIXERLINE_EXT MixerLineSrc;
    LPMIXERCONTROL_EXT MixerControl;

    /* get first entry */
    Entry = MixerInfo->LineList.Flink;

    while(Entry != &MixerInfo->LineList)
    {
        MixerLineSrc = (LPMIXERLINE_EXT)CONTAINING_RECORD(Entry, MIXERLINE_EXT, Entry);

        ControlEntry = MixerLineSrc->ControlsList.Flink;
        while(ControlEntry != &MixerLineSrc->ControlsList)
        {
            MixerControl = (LPMIXERCONTROL_EXT)CONTAINING_RECORD(ControlEntry, MIXERCONTROL_EXT, Entry);
            if (MixerControl->Control.dwControlID == dwControlID)
            {
                if (OutMixerLine)
                    *OutMixerLine = MixerLineSrc;
                if (OutMixerControl)
                    *OutMixerControl = MixerControl;
                if (NodeId)
                    *NodeId = MixerControl->NodeID;
                return MM_STATUS_SUCCESS;
            }
            ControlEntry = ControlEntry->Flink;
        }
        Entry = Entry->Flink;
    }

    return MM_STATUS_UNSUCCESSFUL;
}