#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ dwComponentType; } ;
struct TYPE_12__ {TYPE_1__ Line; } ;
struct TYPE_10__ {struct TYPE_10__* Flink; } ;
struct TYPE_11__ {TYPE_2__ LineList; } ;
typedef  TYPE_2__* PLIST_ENTRY ;
typedef  TYPE_3__* LPMIXER_INFO ;
typedef  TYPE_4__* LPMIXERLINE_EXT ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ CONTAINING_RECORD (TYPE_2__*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  MIXERLINE_EXT ; 

LPMIXERLINE_EXT
MMixerGetSourceMixerLineByComponentType(
    LPMIXER_INFO MixerInfo,
    DWORD dwComponentType)
{
    PLIST_ENTRY Entry;
    LPMIXERLINE_EXT MixerLineSrc;

    /* get first entry */
    Entry = MixerInfo->LineList.Flink;

    while(Entry != &MixerInfo->LineList)
    {
        MixerLineSrc = (LPMIXERLINE_EXT)CONTAINING_RECORD(Entry, MIXERLINE_EXT, Entry);
        if (MixerLineSrc->Line.dwComponentType == dwComponentType)
            return MixerLineSrc;

        Entry = Entry->Flink;
    }

    return NULL;
}